#include "BluetoothOrders.h"

String inputStringBLE = "";
bool stringComplete = false;
long baudRate[] = {2400, 9600, 19200, 115200};  
int baudRateCount = sizeof(baudRate) / sizeof(baudRate[0]);  

String inputCommandArray[COMMANDS_COUNT_MAX];
int paramters[COMMANDS_COUNT_MAX];

//Initializes the serial port connected to Bluetooth
void Bluetooth_Setup(void)
{
  for (int i = 0; i < baudRateCount; i++) {  
    Serial.begin(baudRate[i]);  
    delay(100);  
    Serial.flush();
  #if (BLUETOOTH_CONFIG==1)
    Serial.println("AT+NAMEBT05");  // Or use Serial.print("AT+NAMEBT05-BLE\r\n");  
    delay(200);  
    Serial.println("AT+UART8");  
    delay(200);  
  #endif
  #if (BLUETOOTH_CONFIG==2)
    Serial.println("AT+NAME=BT05");  // Or use Serial.print("AT+NAMEBT05-BLE\r\n");  
    delay(200);  
    Serial.println("AT+ROLE=0");  
    delay(200);  
    Serial.println("AT+UART=4");  
    delay(200);  
  #endif
    Serial.end();
  } 
  Serial.begin(115200);  
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
        inputCommandArray[i] = inputStringTemp;    //Get command
        paramters[i] = inputStringTemp.toInt();    //Get parameters
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
