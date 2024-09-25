clear;
clc;


% Create a Simulink bus object
global_var = Simulink.Bus;
 
 
DistanceMiddleField = Simulink.BusElement;
DistanceMiddleField.Name = 'Distance_Middle';
DistanceMiddleField.DataType = 'double';
global_var.Elements(1) = DistanceMiddleField;

DistanceLeftField = Simulink.BusElement;
DistanceLeftField.Name = 'Distance_Left';
DistanceLeftField.DataType = 'double';
global_var.Elements(2) = DistanceLeftField;

DistanceRightField = Simulink.BusElement;
DistanceRightField.Name = 'Distance_Right';
DistanceRightField.DataType = 'double';
global_var.Elements(3) = DistanceRightField;
 
EncoderField = Simulink.BusElement; 
EncoderField.Name = 'Encoder';
EncoderField.DataType = 'double';
global_var.Elements(4) = EncoderField;


Square = Simulink.BusElement;
Square.Name = 'Square';
Square.DataType = 'string';
global_var.Elements(5) = Square;


Cross = Simulink.BusElement;
Cross.Name = 'Cross';
Cross.DataType = 'string';
global_var.Elements(6) = Cross;


Dpad_right = Simulink.BusElement;
Dpad_right.Name = 'Dpad_Right';
Dpad_right.DataType = 'string';
global_var.Elements(7) = Dpad_right;


Dpad_left = Simulink.BusElement;
Dpad_left.Name = 'Dpad_Left';
Dpad_left.DataType = 'string';
global_var.Elements(8) = Dpad_left;

Analog_Left_X = Simulink.BusElement;
Analog_Left_X.Name = 'Analog_Left_X';
Analog_Left_X.DataType = 'double';
global_var.Elements(9) = Analog_Left_X;

Analog_Left_Y = Simulink.BusElement;
Analog_Left_Y.Name = 'Analog_Left_Y';
Analog_Left_Y.DataType = 'double';
global_var.Elements(10) = Analog_Left_Y;


Battery_Level = Simulink.BusElement;
Battery_Level.Name = 'Battery_Level';
Battery_Level.DataType = 'double';
global_var.Elements(11) = Battery_Level;

Communication = Simulink.BusElement;
Communication.Name = 'Communication';
Communication.DataType = 'string';
global_var.Elements(12) = Communication;



Led_Front = Simulink.BusElement;
Led_Front.Name = 'Led_Front';
Led_Front.DataType = 'uint';
global_var.Elements(13) = Led_Front;

Led_Back_1 = Simulink.BusElement;
Led_Back_1.Name = 'Led_Back_1';
Led_Back_1.DataType = 'uint';
global_var.Elements(14) = Led_Back_1;

Led_Back_2 = Simulink.BusElement;
Led_Back_2.Name = 'Led_Back_2';
Led_Back_2.DataType = 'uint';
global_var.Elements(15) = Led_Back_2;

Battery_Temperature = Simulink.BusElement;
Battery_Temperature.Name = 'Battery_Temperature';
Battery_Temperature.DataType = 'uint';
global_var.Elements(16) = Battery_Temperature;

Accelerometer = Simulink.BusElement;
Accelerometer.Name = 'Accelerometer';
Accelerometer.DataType = 'double';
global_var.Elements(16) = Accelerometer;

State = Simulink.BusElement;
State.Name = 'State';
State.DataType = 'string';
global_var.Elements(16) = State;

clearvars -except global_var
% Save the bus object to the base workspace
assignin('base', 'global_var', global_var);



