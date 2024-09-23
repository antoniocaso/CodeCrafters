################################################################################
# GEMINI PROJECT
################################################################################


from bsp import board
from networking import wifi
from networking import socket
from protocols import HTTP
from zerynth.zdm import zdm

import threading
import adc
import serial
import gpio
from math import math

import json

from drivers import SSD1306
import graphics

#-> PIN DECLARATIONS AND INITIALIZATION BELOW
TEMPSENSOR = D39
trillo = D35
readOther = D34
readMine = D33
apticFeedback = D27
redLed = D14
greenLed = D12

serial.serial()
gpio.mode(TEMPSENSOR, INPUT_ANALOG)
gpio.mode(trillo, INPUT_PULLDOWN)
gpio.mode(readOther, INPUT_PULLDOWN)
gpio.mode(readMine, INPUT_PULLDOWN)
gpio.mode(apticFeedback,OUTPUT)
gpio.mode(redLed,OUTPUT)
gpio.mode(greenLed,OUTPUT)



#-> WIFI SSID AND PASSWORD BELOW
ssid = "Mi"
passwd = "password"


#-> SERVER URL BELOW
ip="192.168.242.254"
url = "http://"+ip+"/?id=2&ip=127.0.0.104"


#-> LOCK DECLARATION BELOW
lock = threading.Lock()


#-> GLOBAL VARIABLES AND FLAGS BELOW
globalTemp = 0.0
ora = 0
minuto = 0
state = 0
sendNotification = False
readGeminiData = False
readMyData = False



#-> TEMPERATURE CONSTANTS BELOW
R1 = 10000.0 
Beta = 3950.0  
To = 301.15   
Ro = 10000.0 


#->INTERRUPT FUNCTIONS BELOW
def onTrilloFall(): 
    global sendNotification
    global readGeminiData
    global readMyData
    #display._display_Print_Bitmap(display._display_Merge_Bitmap(graphic_oled.MENU[state] , display._display_String_to_Bitmap(str(ora)+":"+str(minuto), 7,1)))

    sendNotification = True
    readGeminiData = False
    readMyData = False
 
def onReadOtherFall(): 
    global sendNotification
    global readGeminiData
    global readMyData

    sendNotification = False
    readGeminiData = True
    readMyData = False

def onReadMineFall(): 
    global sendNotification
    global readGeminiData
    global readMyData

    sendNotification = False
    readGeminiData = False
    readMyData = True
 


#-> HTTP REQUEST THREAD DECLARATION BELOW
def httpPolling():
    while True:
        global globalTemp
        global sendNotification
        global readGeminiData
        global readMyData
        global ora
        global minuto
        global state
        # if it's unlocked, lock it and continue printing. Else wait.
        lock.acquire()
        
        #In case of button pression sendNotification becomes true, I change a flag into the request that lets the server know that he has to send the trill
        if(sendNotification):
            state = 2
            print("Trillo inviato")
            connection = HTTP.HTTP()
            print(globalTemp)
            test = connection.post(url, body='{"notification":1,"myData":'+str(globalTemp)+',"hour":ora,"minute":minuto}')
            data = test.data #check if you received notification

            gpio.set(redLed,HIGH)
            gpio.set(greenLed,HIGH)
            sleep(200)
            gpio.set(redLed,LOW)
            gpio.set(greenLed,LOW)

            #zdm
            agent1.publish({"Temperatura":globalTemp},"Device 1")

            
            if (data != None):
                y = json.loads(data)
                ora = y["hour"]
                minuto = y["minute"]
                if(y["notification"] == 1):
                    print("Trillo")
                    gpio.set(apticFeedback,HIGH)
                    sleep(100)
                    gpio.set(apticFeedback,LOW)
                    sleep(100)
                    gpio.set(apticFeedback,HIGH)
                    sleep(100)
                    gpio.set(apticFeedback,LOW)

            print("Request sent")
            connection.destroy()

            #print that notify went good


        elif(readGeminiData):
            state = 3
            print("Lettura altri dati inviato")
            connection = HTTP.HTTP()
            print(globalTemp)
            test = connection.post(url, body='{"notification":0,"myData":'+str(globalTemp)+',"hour":ora,"minute":minuto}')
            data = test.data #check if you received notification
            
            #zdm
            agent1.publish({"Temperatura":globalTemp},"Device 1")


            if (data != None):
                y = json.loads(data)
                ora = y["hour"]
                minuto = y["minute"]
                print("I dati dell'altro bracciale sono: ")
                print(y["myData"])
                if(y["notification"] == 1):
                    print("Trillo")
                    gpio.set(apticFeedback,HIGH)
                    sleep(100)
                    gpio.set(apticFeedback,LOW)
                    sleep(100)
                    gpio.set(apticFeedback,HIGH)
                    sleep(100)
                    gpio.set(apticFeedback,LOW)
                if(y["myData"] > 37):
                    gpio.set(redLed,HIGH)
                    sleep(200)
                    gpio.set(redLed,LOW)
                    sleep(100)
                    gpio.set(redLed,HIGH)
                    sleep(200)
                    gpio.set(redLed,LOW)
                    sleep(100)
                    gpio.set(redLed,HIGH)
                    sleep(200)
                    gpio.set(redLed,LOW)
                if(y["myData"] <= 37):
                    gpio.set(greenLed,HIGH)
                    sleep(200)
                    gpio.set(greenLed,LOW)
                    sleep(100)
                    gpio.set(greenLed,HIGH)
                    sleep(200)
                    gpio.set(greenLed,LOW)
                    sleep(100)
                    gpio.set(greenLed,HIGH)
                    sleep(200)
                    gpio.set(greenLed,LOW)

            print("Request sent")
            connection.destroy()

            #print the received data to the oled screen here

        
        else:
            state = 0
            connection = HTTP.HTTP()
            print(globalTemp)
            test = connection.post(url, body='{"notification":0,"myData":'+str(globalTemp)+',"hour":ora,"minute":minuto}')
            data = test.data
            
            #zdm
            agent1.publish({"Temperatura":globalTemp},"Device 1")

            if (data != None):
                y = json.loads(data)
                print(y["myData"])
                ora = y["hour"]
                minuto = y["minute"]
                print(ora)
                print(minuto)
                if(y["notification"] == 1):
                    print("Trillo")
                    gpio.set(apticFeedback,HIGH)
                    sleep(200)
                    gpio.set(apticFeedback,LOW)
                    sleep(100)
                    gpio.set(apticFeedback,HIGH)
                    sleep(200)
                    gpio.set(apticFeedback,LOW)

                    
                    display._display_Print_Bitmap(graphics.trillo(1))
                    display._display_Print_Bitmap(graphics.trillo(2))
                    
                else: 
                    print("culo")

            print("Request sent")
            connection.destroy()

        #aggiornare orario


        readMyData = False
        sendNotification = False
        readGeminiData = False
        # unlock and allow another thread to call the print
        lock.release()
        #display._display_Print_Bitmap(display._display_Merge_Bitmap(graphic_oled.MENU[state] , display._display_String_to_Bitmap(str(ora)+":"+str(minuto), 7,1)))

        menu1=display._display_Merge_6x2_Row_Bitmap(graphics.menu(1), display._display_String_to_Bitmap("à", 1,0,1))
        display._display_Print_Bitmap(menu1)
        menu1.clear()
        """
        menuUpdate=display._display_Merge_6x2_Row_Bitmap(graphics.menu(state), display._display_String_to_Bitmap("à", 1,0,1))
        display._display_Print_Bitmap(menuUpdate)
        menuUpdate.clear()
        """
        sleep(10000)



#-> SENSOR READING THREAD DECLARATION BELOW
def sensorReading():
    while True:
        global globalTemp
        global state 
        #display._display_Print_string(str(globalTemp))

        #->READING SERIAL DATA BELOW

        #->READING ANALOG DATA BELOW
        Vs=adc.read(TEMPSENSOR)*0.0008

        Rt = 10000 * Vs/ (3.3 - Vs)
        T = 1/(1/To + math.log(Rt/Ro)/Beta)-5
        Tc = T - 273.15

        # if it's unlocked, lock it and continue printing. Else wait.
        lock.acquire()
        
        globalTemp = Tc
        print(globalTemp)


        #-> DISPLAYING SELF DATA ON OLED BELOW
        if(readMyData):
            state = 3
            print(globalTemp)
            print("Oled prints your data here for you to see")

            for i in range(1,3):
                bitmappo=graphics.bpm(i)
                display._display_Print_Bitmap(bitmappo)
                bitmappo.clear()
            for i in range(1,3):
                bitmappo=graphics.bpm(i)
                display._display_Print_Bitmap(bitmappo)
                bitmappo.clear()


            bitmappo=graphics.bpm(3)
            display._display_Print_Bitmap(bitmappo)
            bitmappo.clear()
            """
            temp = display._display_String_to_Bitmap(str(globalTemp), 4,1)
            dataToDisplay = display._display_Merge_Bitmap(bitmappo, temp)
            bitmappo.clear()
            temp.clear()
            display._display_Print_Bitmap(dataToDisplay)
            dataToDisplay.clear()
            """
            menu1=display._display_Merge_6x2_Row_Bitmap(graphics.menu(1), display._display_String_to_Bitmap("à", 1,0,1))
            display._display_Print_Bitmap(menu1)
            menu1.clear()


            readMyData = False
            sendNotification = False
            readGeminiData = False
        
        # unlock and allow another thread to call the print
        lock.release()
        sleep(1000)

#-> DISPLAY INITIALIZATION BELOW
display = SSD1306.SSD1306(60)
#Bitmap avvio
for i in range(1,6):
    bitmappo=graphics.gemini(i)
    display._display_Print_Bitmap(bitmappo)

"""
for i in range(1,5):
    bitmappo=graphics.braccialetto2(i)
    display._display_Print_Bitmap(bitmappo)
"""

#-> BITMAP MENU WITHOUT WIFI
menu=display._display_Merge_6x2_Row_Bitmap(graphics.menu(1), display._display_String_to_Bitmap("ò", 1,0,1))
display._display_Print_Bitmap(menu)
menu.clear()

#-> WIFI CONNECTION BELOW
print("configuring...")
wifi.configure(
        ssid=ssid,
        password=passwd)
print("connecting...")
wifi.start()
print("connected...")
print("info ", wifi.info())


#-> BITMAP MENU WITH WIFI
menu1=display._display_Merge_6x2_Row_Bitmap(graphics.menu(1), display._display_String_to_Bitmap("à", 1,0,1))
display._display_Print_Bitmap(menu1)
menu1.clear()

#-> ZDM AGENT START BELOW
agent1 = zdm.Agent()
agent1.start()


#->ATTACHING INTERRUPTS BELOW
gpio.on_rise(trillo, onTrilloFall, pull=INPUT_PULLUP) 
gpio.on_rise(readOther, onReadOtherFall, pull=INPUT_PULLUP) 
gpio.on_rise(readMine, onReadMineFall, pull=INPUT_PULLUP) 


#-> STARTING THE THREADS BELOW
thread(httpPolling)
thread(sensorReading)