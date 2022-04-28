#include <ECE3.h>

// Base code.
// 
// *  NOTE: this code will do only three things:
// *    --rotate one wheel, and 
// *    --blink the right front mainboard LED.
// *    
// *  You will need to add more code to
// *  make the car do anything useful. 
// 

//#include <ECE3_LCD7.h>

uint16_t sensorValues[8]; // right -> left, 0 -> 7

const int left_nslp_pin=31; // nslp ==> awake & ready for PWM
const int left_dir_pin=29;
const int left_pwm_pin=40;
const int right_nslp_pin=11;
const int right_dir_pin=30;
const int right_pwm_pin=39;

const int LED_RF = 41;

const int kP = 10;
const float kD = 40;
const int baseSpd = 200;

///////////////////////////////////
void setup() {
// put your setup code here, to run once:
  pinMode(left_nslp_pin,OUTPUT);
  pinMode(left_dir_pin,OUTPUT);
  pinMode(left_pwm_pin,OUTPUT);
  pinMode(right_nslp_pin,OUTPUT);
  pinMode(right_dir_pin,OUTPUT);
  pinMode(right_pwm_pin,OUTPUT);

  digitalWrite(left_dir_pin,LOW);
  digitalWrite(left_nslp_pin,HIGH);
  digitalWrite(right_dir_pin,LOW);
  digitalWrite(right_nslp_pin,HIGH);

  pinMode(LED_RF, OUTPUT);
  
  ECE3_Init();

// set the data rate in bits/second for serial data transmission
  Serial.begin(9600); 
  delay(2000); //Wait 2 seconds before starting 
  
}

void loop() {
  // put your main code here, to run repeatedly: 
  static int previousError = 0;

  ECE3_read_IR(sensorValues);

  //analogWrite(left_pwm_pin,baseSpd);
  //analogWrite(right_pwm_pin,baseSpd);

// 
  
//  ECE3_read_IR(sensorValues);
/*
  for (unsigned char i = 0; i < 8; i++)
    {
      Serial.print(sensorValues[i]);
      Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
    }
    */
    uint8_t maxIr = 0;
    uint8_t minIr = 2500;
    for (uint8_t i = 0; i < 8; i++)
    {
      if (sensorValues[i] > sensorValues[maxIr]) maxIr = i;
      if (sensorValues[i] < sensorValues[minIr]) minIr = i;
    }
    /*
    for (uint8_t i = 0; i < 8; i++)
    {
      if (i == maxIr)
        Serial.print('@');
      else
        Serial.print('_');
      Serial.print('\t');
    }*/
    int correction = 0;
    int error, deltaError;
    // Need to turn right
    if (maxIr <= 3)
    {
      error = 3 - maxIr;
      deltaError = error - previousError;
//      Serial.print(baseSpd + kP*error);
//      Serial.print(" , ");
//      Serial.print(baseSpd - kD*deltaError);
      //analogWrite(left_pwm_pin,baseSpd + kP*error);
      //analogWrite(right_pwm_pin,baseSpd - kD*deltaError);
    }
    // Need to turn left
    else
    {
      error = maxIr - 4;
      deltaError = error - previousError;
//      Serial.print(baseSpd - kD*deltaError);
//      Serial.print(" , ");
//      Serial.print(baseSpd + kP*error);
      //analogWrite(left_pwm_pin,baseSpd - kD*deltaError);
      //analogWrite(right_pwm_pin,baseSpd + kP*error);
    }
    previousError = error;
    Serial.print("D: ");
    Serial.print(abs(maxIr - minIr));
    Serial.println();
    delay(50);
//  digitalWrite(LED_RF, HIGH);
//  delay(250);
//  digitalWrite(LED_RF, LOW);
//  delay(250);
    
  }
