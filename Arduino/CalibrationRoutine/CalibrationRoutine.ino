#include <ECE3.h>

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

// for normalization
int sensorNorm[8];
int16_t sensorMin[8] = {2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500}; // {768, 676, 652, 582, 582, 536, 536, 700}; 
int16_t sensorMax[8] = {0, 0, 0, 0, 0, 0, 0, 0};

// for fusion error calculation
float weights[8] = {-2.0, -1.0, -0.5, -0.25, 0.25, 0.5, 1.0, 2.0};
float fusionError;
float prevFusionError = 0;

bool motorState = true;

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

  Serial.begin(9600);
  ECE3_Init();
}

void loop() {
    if (motorState)
    {
      Serial.print("Driving . . .");
      Serial.println();
      delay(100);
    }
    delay(50);
}

void fusion()
{
  normalize();
  fusionError = 0;

  // Apply weights to compute single error value
  for (uint8_t i = 0; i < 8; i++)
    fusionError += weights[i] * sensorNorm[i];
}

// Gather 8 sensor readings and normalize them
// Use after calibrating!
void normalize()
{
  // Initialize norm array to 0
  for (uint8_t i = 0; i < 8; i++) sensorNorm[i] = 0;

  // Sum up N number of sensor readings
  uint8_t N = 1;
  for (uint8_t i = 0; i < N; i++)
  {
    ECE3_read_IR(sensorValues);
    for (uint8_t j = 0; j < 8; j++)
      sensorNorm[j] += sensorValues[j];
    // delay(10);
  }
  
  for (uint8_t i = 0; i < 8; i++)
  {
    // Divide by N for means
    sensorNorm[i] /= N;
    // Floor
    sensorNorm[i] -= sensorMin[i];
  }
  
  // Normalize 0-1000
  for (uint8_t i = 0; i < 8; i++)
  {
    sensorNorm[i] *= 1000;
    sensorNorm[i] /= sensorMax[i] - sensorMin[i];
  }
}

// Enable motors
void onMotors()
{
  motorState = true;
}

// Disable motors
void offMotors()
{
  motorState = false;
  analogWrite(left_pwm_pin, 0);
  analogWrite(right_pwm_pin, 0);
}

// Finds mins/max
void calibrate()
{
  // Motors have to be disabled
  if (motorState)
    return;
    
  digitalWrite(LED_RF, HIGH);
  
  int16_t avg[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  // Sum over 5 readings
  for (uint8_t i = 0; i < 5; i++)
  {
    ECE3_read_IR(sensorValues);
    for (uint8_t j = 0; j < 8; j++)
      avg[j] += sensorValues[j];
      
    delay(50);
  }

  // Find means
  for (uint8_t i = 0; i < 8; i++)
  {
    avg[i] /= 5;

    // Store minimum
    if (avg[i] < sensorMin[i])
      sensorMin[i] = avg[i];
    // Store maximum
    if (avg[i] > sensorMax[i])
      sensorMax[i] = avg[i];
    
  }
  printBounds();
  delay(50);
  digitalWrite(LED_RF, LOW);
}

// Print min and max bounds for normalization
void printBounds()
{
  Serial.print("Min: ");
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.print(sensorMin[i]);
    Serial.print('\t');
  }
  Serial.print("Max: ");
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
