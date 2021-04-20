// BluetoothOrders.h

#ifndef _BLUETOOTHORDERS_h
#define _BLUETOOTHORDERS_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#define COMMANDS_COUNT_MAX        8

#define ACTION_MOVE              'A'     //Ant movement commands
#define ACTION_EMOTION           'B'     //Expression control commands
#define ACTION_RGB               'C'     //WS2812 control commands
#define ACTION_BUZZER            'D'     //Buzzer control commands
#define ACTION_ULTRASONIC        'E'     //Ultrasonic control commands
#define ACTION_CAR_MODE          'H'     //Ultrasonic Obstacle Avoidance Command
#define ACTION_GET_VOLTAGE       'I'     //Battery Power Query
#define INTERVAL_CHAR            '#'     //The directive resolves the separator character

extern String inputStringBLE;
extern bool stringComplete;

extern String inputCommandArray[COMMANDS_COUNT_MAX];
extern int paramters[COMMANDS_COUNT_MAX];

void Bluetooth_Setup(void);    //Initializes the serial port connected to Bluetooth
void Deal_Serial_Data(void);   //Parses the Bluetooth data received by the serial port


#endif












//
