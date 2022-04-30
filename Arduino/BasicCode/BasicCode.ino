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

const int BMP0 = 24;
const int BMP1 = 25;
const int BMP2 = 6;

const int LED_RF = 41;

const float kP = 0.005;
const float kD = 0.002;
const int baseSpd = 150;

int sensorNorm[8];
int16_t sensorMin[8] = {768, 676, 652, 582, 582, 536, 536, 700}; //{2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500};
float fusionError;
float prevFusionError = 0;
float weights[8] = {-2., -1., -0.5, -0.25, 0.25, 0.5, 1., 2.};

uint8_t calib = 0;

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

  // Bumper 0 disables motors
  pinMode(BMP0, INPUT_PULLUP);
  attachInterrupt(BMP0, offMotors, FALLING);

  // Bumper 1 enables motors
  pinMode(BMP1, INPUT_PULLUP);
  attachInterrupt(BMP1, onMotors, FALLING);

  // Bumper 2 calibrates
  pinMode(BMP2, INPUT_PULLUP);
  attachInterrupt(BMP2, calibrate, FALLING);

  pinMode(left_push, INPUT_PULLUP);
  //attachInterrupt(left_push, incrementCalibrate, FALLING);

  pinMode(LED_RF, OUTPUT);

  //Serial.begin(9600);
  ECE3_Init();
}

void loop() {
    if (calib == 0)
    {
      fusion();
      analogWrite(left_pwm_pin,baseSpd - kP*fusionError - kD*(fusionError - prevFusionError));
      analogWrite(right_pwm_pin,baseSpd + kP*fusionError + kD*(fusionError - prevFusionError));
      prevFusionError = fusionError;
    }
    delay(50);
}

void normalize()
{
  int16_t sensorMax = 0;
  // Sum up N number of sensor readings
  for (uint8_t i = 0; i < 1; i++)
  {
    ECE3_read_IR(sensorValues);
    for (uint8_t j = 0; j < 8; j++)
      sensorNorm[j] += sensorValues[j];
    //delay(10);
  }
  
  for (uint8_t i = 0; i < 8; i++)
  {
    // Divide by N for averages
    sensorNorm[i] /= 1;
    // Floor
    sensorNorm[i] -= sensorMin[i];
    // Find max
    if (sensorNorm[i] > sensorMax)
      sensorMax = sensorNorm[i];
  }
  
  // Normalize
  for (uint8_t i = 0; i < 8; i++)
  {
    sensorNorm[i] *= 1000;
    sensorNorm[i] /= sensorMax;
    //Serial.print(sensorNorm[i]);
    //Serial.print('\t');
  }
  //Serial.println();
}

void fusion()
{
  normalize();
  fusionError = 0;
  for (uint8_t i = 0; i < 8; i++)
  {
    fusionError += weights[i] * sensorNorm[i];
  }
  //Serial.print(fusionError);
  //Serial.println();
}

void offMotors()
{
  calib = 1;
  digitalWrite(LED_RF, HIGH);
  analogWrite(left_pwm_pin, 0);
  analogWrite(right_pwm_pin, 0);
}

void onMotors()
{
  calib = 0;
  digitalWrite(LED_RF, LOW);
}

// Finds mins
void calibrate()
{
  offMotors();
  int minVals[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  for (uint8_t i = 0; i < 5; i++)
  {
    ECE3_read_IR(sensorValues);
    for (uint8_t j = 0; j < 8; j++)
    {
      minVals[j] += sensorValues[j];
    }
  }
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.print(minVals[i]);
    Serial.print('\t');
    minVals[i] /= 5;
    
    if (minVals[i] < sensorMin[i])
      sensorMin[i] = minVals[i];
  }
  Serial.println();
  //printMins();
  delay(50);
}

void printMins()
{
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.print(sensorMin[i]);
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
