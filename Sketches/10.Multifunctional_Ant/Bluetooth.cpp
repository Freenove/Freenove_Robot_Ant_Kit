#include "BluetoothOrders.h"
#include "External_Devices.h"

String inputStringBLE = "";
bool stringComplete = false;

String inputCommandArray[COMMANDS_COUNT_MAX];
int paramters[COMMANDS_COUNT_MAX];

//Initializes the serial port connected to Bluetooth
void Bluetooth_Setup(void)
{
  Serial.begin(9600);
}

//Parses the Bluetooth data received by the serial port
void Deal_Serial_Data(void)
{
  String inputStringTemp = inputStringBLE;
  int string_length = inputStringTemp.length();
  for (u8 i = 0; i < COMMANDS_COUNT_MAX; i++) {
    int index = inputStringTemp.indexOf(INTERVAL_CHAR);
    if (index < 0) {
      if (string_length > 0) {
        inputCommandArray[i] = inputStringTemp;         //Get command
        paramters[i] = inputStringTemp.toInt();//Get parameters
      }
      break;
    }
    inputCommandArray[i] = inputStringTemp.substring(0, index);
    inputStringTemp = inputStringTemp.substring(index + 1);
    paramters[i] = inputCommandArray[i].toInt();
  }
  stringComplete = false;
  inputStringBLE = "";
}

//Serial interrupt event
void serialEvent() {
  while (Serial.available()) {
    inputStringBLE=Serial.readStringUntil('\n');
    stringComplete = true;
  }
}
