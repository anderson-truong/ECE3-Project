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

const int right_push = 73;
const int left_push = 74;

const int bmp0 = 24;

const int LED_RF = 41;

const int kP = 5;
const float kD = 0;//= 40;
const int baseSpd = 40;

uint16_t sensorAvg[8];
uint16_t sensorMin[11];
uint16_t sensorMax[11];
uint8_t calibratePos = 0;
uint16_t weights[8] = {-0.8, -0.4, -0.2, -0.1, 0.1, 0.2, 0.4, 0.8};

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

  pinMode(bmp0, INPUT_PULLUP);
  attachInterrupt(bmp0, printIR, FALLING);

  pinMode(left_push, INPUT_PULLUP);
  attachInterrupt(left_push, incrementCalibrate, FALLING);

  pinMode(LED_RF, OUTPUT);
  
  ECE3_Init();

// set the data rate in bits/second for serial data transmission
  Serial.begin(9600); 
  delay(2000); //Wait 2 seconds before starting 
  
}

void loop() {
  // put your main code here, to run repeatedly: 
  static int previousError = 0;

  //ECE3_read_IR(sensorValues);

  //analogWrite(left_pwm_pin,baseSpd);
//  analogWrite(right_pwm_pin,baseSpd);
    delay(50);
//  digitalWrite(LED_RF, HIGH);
//  delay(250);
//  digitalWrite(LED_RF, LOW);
//  delay(250);
}

void printCalibrate()
{
  Serial.print("Calibrate Pos: ");
  Serial.print(calibratePos);
  Serial.println();
  Serial.print("Min");
  Serial.println();
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.print(sensorMin[i]);
    Serial.print('\t');
  }
  Serial.println();
  Serial.print("Max");
  Serial.println();
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.print(sensorMax[i]);
    Serial.print('\t');
  }
  Serial.println();
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
  }
  Serial.println();
}

void incrementCalibrate()
{
  if (calibratePos < 7)
    calibratePos++;
  else
    calibratePos = 0;
}

void zeroInitialize()
{
  for (uint8_t i = 0; i < 8; i++)
    sensorAvg[i] = 0;
  sensorMin[calibratePos] = 2500;
  sensorMax[calibratePos] = 0;
}

// sensorValues[0] is the right-most
void calibrate()
{
  zeroInitialize();
  for (uint8_t i = 0; i < 5; i++)
  {
    ECE3_read_IR(sensorValues);
    for (uint8_t j = 0; j < 8; j++)
    {
      sensorAvg[j] += sensorValues[j];
    }
    delay(50);
  }
  for (uint8_t i = 0; i < 8; i++)
  {
    sensorAvg[i] /= 5;
//    Serial.print(sensorAvg[i]);
//    Serial.print('\t');
  }
  // Find mins/maxs
  //int m = 0;
  for (uint8_t i = 0; i < 8; i++)
  {
    if (sensorAvg[i] < sensorMin[calibratePos]) 
      sensorMin[calibratePos] = sensorAvg[i];
    if (sensorAvg[i] > sensorMax[calibratePos])
      sensorMax[calibratePos] = sensorAvg[i];
//    if (sensorValues[i] > sensorValues[m]) m = i;
  }
  //Serial.print(m);
  sensorMax[calibratePos] -= sensorMin[calibratePos];
  printCalibrate();
}

void sensorFusion()
{
  uint16_t weightedAvg;
  for (uint8_t i = 0; i < 8; i++)
  {
    sensorValues[i] -= sensorMin[i];
    sensorValues[i] = (1000 * sensorValues[i])/sensorMax[i];
    weightedAvg += sensorValues[i] * weights[i];
  }
}
