#include "xil_cache.h"
#include "PmodOLEDrgb.h"
#include "xscugic.h"
#include "xscutimer.h"
#include "xil_exception.h"
#include "xtime_l.h"
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xgpiops.h"
#include "xgpio.h"
#include "queue.h"
#include <math.h>

#define INTC_DEVICE_ID XPAR_SCUGIC_SINGLE_DEVICE_ID
#define TIMER_DEVICE_ID XPAR_SCUTIMER_DEVICE_ID
#define TIMER_INTERRUPT_ID XPAR_SCUTIMER_INTR
#define TS 0.05
#define MOTOR_CHARACTERISTIC 3592

XScuGic InterruptController; // Interrupt controller instance
XScuTimer Timer; // Timer instance
//XTime tEnd, tStart;
PmodOLEDrgb oledrgb;


int tick_count, direction;
XGpio_Config *pl_tick_count_Ptr;
XGpio pl_tick_count;
XGpio_Config *pl_direction_Ptr;
XGpio pl_direction;
CircularQueue q;
int speed, acceleration;
int last_speed = 0;
int oldestTicks;
int delta;

void init_Zynq(){
	init_platform();
	init_oled();
	init_queue(&q);
	// GPIO initialization
	pl_tick_count_Ptr = XGpio_LookupConfig(XPAR_AXI_GPIO_0_DEVICE_ID);
	int status0 = XGpio_CfgInitialize(&pl_tick_count, pl_tick_count_Ptr, pl_tick_count_Ptr->BaseAddress);

	pl_direction_Ptr = XGpio_LookupConfig(XPAR_AXI_GPIO_1_DEVICE_ID);
	int status1 = XGpio_CfgInitialize(&pl_direction, pl_direction_Ptr, pl_direction_Ptr->BaseAddress);

	if (status0 != XST_SUCCESS && status1!= XST_SUCCESS) {
		xil_printf("GPIOs initialization error!\r");
		return XST_FAILURE;
	}

	// set data direction for GPIO
	XGpio_SetDataDirection(&pl_tick_count, 1, 1); // 0-> output, 1-> input.
	XGpio_SetDataDirection(&pl_direction, 1, 1); // 0-> output, 1-> input.


	// Initialize the timer
	int status2 = InitializeTimer(&Timer);
	if (status2 != XST_SUCCESS) {
		xil_printf("Timer Initialization Failed\r\n");
		return XST_FAILURE;
	}

	// Initialize the interrupt system
	status2 = SetupInterruptSystem(&InterruptController, &Timer);
	if (status2 != XST_SUCCESS) {
		xil_printf("Interrupt System Setup Failed\r\n");
		return XST_FAILURE;
	}

	// Start the timer
	xil_printf("INIT\n\r");
	XScuTimer_Start(&Timer);
}

int InitializeTimer(XScuTimer *TimerInstancePtr) { //Si inizializza il Timer
	int Status;
	XScuTimer_Config *ConfigPtr;

	// Initialize the timer driver so that it is ready to use
	ConfigPtr = XScuTimer_LookupConfig(TIMER_DEVICE_ID);
	if (ConfigPtr == NULL) {
		return XST_FAILURE;
	}

	Status = XScuTimer_CfgInitialize(TimerInstancePtr, ConfigPtr,
			ConfigPtr->BaseAddr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	// Load the timer with the value that corresponds to 5ms
	XScuTimer_LoadTimer(TimerInstancePtr, XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ / 400);

	// Enable the Auto reload mode
	XScuTimer_EnableAutoReload(TimerInstancePtr);

	// Enable the timer interrupt
	XScuTimer_EnableInterrupt(TimerInstancePtr);

	return XST_SUCCESS;
}

void init_oled() {
   EnableCaches();
   OLEDrgb_begin(&oledrgb, XPAR_PMODOLEDRGB_0_AXI_LITE_GPIO_BASEADDR,
   XPAR_PMODOLEDRGB_0_AXI_LITE_SPI_BASEADDR);


   OLEDrgb_FillBackground(&oledrgb, 0, 0, 255); //Scegli colore background
   change_fontcolor_rgb(255,255,255); //Scegli colore delle scritte
   OLEDrgb_SetCursor(&oledrgb, 1, 1);
   OLEDrgb_PutString(&oledrgb, "SPEED: " );

   OLEDrgb_SetCursor(&oledrgb, 1, 3);
   OLEDrgb_PutString(&oledrgb, "ACCELER: " );

   OLEDrgb_SetCursor(&oledrgb, 1, 5);
   OLEDrgb_PutString(&oledrgb, "DIRECT: " );
}

void TimerIntrHandler(void *CallBackRef) { //Effettiva CallBack, togliere getOldestElement
	//XTime_GetTime(&tStart);
	tick_count = XGpio_DiscreteRead(&pl_tick_count, 1);
	direction = XGpio_DiscreteRead(&pl_direction, 1);

	oldestTicks = getOldestElement(&q);
	delta = tick_count - oldestTicks;
	enqueue(&q, tick_count);
	speed = delta * 60/(MOTOR_CHARACTERISTIC*TS);
    acceleration = (speed - last_speed) * 200;
    last_speed = speed;
    xil_printf("%d, %d\n\r", (direction==1) ? speed : -speed , acceleration);
    XScuTimer_ClearInterruptStatus((XScuTimer * )CallBackRef); // Clear the interrupt status


    //printf("Elapsed: %.5lf ms\r\n", ((double)(tStart-tEnd) / (double)COUNTS_PER_SECOND)*1000);
	//xil_printf("Speed: %d RPM, Acceleration: %d RPM/s\n", (direction==1) ? speed : -speed , acceleration);
    //XTime_GetTime(&tEnd);
}

int SetupInterruptSystem(XScuGic *IntcInstancePtr, XScuTimer *TimerInstancePtr) { //Funzione per creare la callback
	int Status;

	// Initialize the interrupt controller driver
	XScuGic_Config *IntcConfig;
	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
	Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig,
			IntcConfig->CpuBaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	// Initialize the exception table and register the interrupt controller handler with the exception table
	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			(Xil_ExceptionHandler) XScuGic_InterruptHandler, IntcInstancePtr);

	// Connect the device driver handler that will be called when an interrupt for the device occurs
	Status = XScuGic_Connect(IntcInstancePtr, TIMER_INTERRUPT_ID,
			(Xil_InterruptHandler) TimerIntrHandler, (void *) TimerInstancePtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	// Enable the interrupt for the device
	XScuGic_Enable(IntcInstancePtr, TIMER_INTERRUPT_ID);

	// Enable interrupts in the ARM processor
	Xil_ExceptionEnable();
	return XST_SUCCESS;
}

//Display part


void OLEDrgb_FillBackground(PmodOLEDrgb *oledrgb, u8 R, u8 G, u8 B){ //Funzione autofatta: fa il background bianco
	OLEDrgb_SetFontBkColor(oledrgb, OLEDrgb_BuildRGB(B, R, G));
	OLEDrgb_SetFontColor(oledrgb, OLEDrgb_BuildRGB(B, R, G));
	for(int i=0; i<8; i++){
		for(int j=0; j<12; j++){
			OLEDrgb_SetCursor(oledrgb, j, i);
			OLEDrgb_PutString(oledrgb, " " );
		}
	}
}


void OledCleanup() {
   DisableCaches();
}

void print_speed(char **b){
	change_fontcolor_rgb(255,255,255);
	sprintf(*b, "%d    ", (direction==1) ? speed : -speed);
	OLEDrgb_SetCursor(&oledrgb, 1, 2);
	if(speed == 0){
		change_fontcolor_rgb(255,0,0);
		OLEDrgb_PutString(&oledrgb, "ZERO");
	}
	else
		OLEDrgb_PutString(&oledrgb, *b);
}

void print_acceleration(char **b){
	change_fontcolor_rgb(255,255,255);
	sprintf(*b, "%d     ", acceleration);
	OLEDrgb_SetCursor(&oledrgb, 1, 4);
	if(acceleration == 0){
		change_fontcolor_rgb(255,0,0);
		OLEDrgb_PutString(&oledrgb, "ZERO");
	}
	else
		OLEDrgb_PutString(&oledrgb, *b);
}


void print_direction(char **b){
	change_fontcolor_rgb(255,255,255);
	OLEDrgb_SetCursor(&oledrgb, 1, 6);
	if(direction == 1 && speed>5){
		OLEDrgb_PutString(&oledrgb, "----->      ");
	}
	else if (direction == 0 && speed>5){
		OLEDrgb_PutString(&oledrgb, "<-----      ");
	}
	else{
		change_fontcolor_rgb(255,0,0);
		OLEDrgb_PutString(&oledrgb, "STOP    ");
	}
}

void EnableCaches() {
#ifdef __MICROBLAZE__
#ifdef XPAR_MICROBLAZE_USE_ICACHE
   Xil_ICacheEnable();
#endif
#ifdef XPAR_MICROBLAZE_USE_DCACHE
   Xil_DCacheEnable();
#endif
#endif
}

void DisableCaches() {
#ifdef __MICROBLAZE__
#ifdef XPAR_MICROBLAZE_USE_DCACHE
   Xil_DCacheDisable();
#endif
#ifdef XPAR_MICROBLAZE_USE_ICACHE
   Xil_ICacheDisable();
#endif
#endif
}


void change_fontcolor_rgb(u8 R, u8 G, u8 B){
	OLEDrgb_SetFontColor(&oledrgb, OLEDrgb_BuildRGB(B, R, G));
}

//End display

int main() {
	init_Zynq();
	char b[6];
	change_fontcolor_rgb(255,255,255); //Scegli colore numeri

	while (1) {

		print_speed(&b);

		print_acceleration(&b);

		print_direction(&b);
	}

	return XST_SUCCESS;
}





