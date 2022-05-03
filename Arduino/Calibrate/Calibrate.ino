#include <ECE3.h>

/*
Calibrates through Serial communication
 */

//#include <ECE3_LCD7.h>

uint16_t sensorValues[8]; // right -> left, 0 -> 7

const int right_push = 73;
const int left_push = 74;

const int BMP0 = 24;
const int BMP1 = 25;

const int LED_RF = 41;

///////////////////////////////////
void setup() {
  Serial.begin(9600);
  
  ECE3_Init();
}

void loop() {
  if (Serial.available())
  {
    // Clear buffer
    while(Serial.available() > 0) {
      char t = Serial.read();
    }
    printIR();
  }
  delay(100);
}

void printIR()
{
  for (uint8_t j = 0; j < 5; j++)
  {
    ECE3_read_IR(sensorValues);
    for (uint8_t i = 0; i < 8; i++)
    {
      Serial.print(sensorValues[i]);
      Serial.print(',');
    }
    Serial.println();
    delay(50);
  }
}
