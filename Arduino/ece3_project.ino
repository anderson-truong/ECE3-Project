#include <ECE3.h>

const int left_nslp_pin=31; // nslp ==> awake & ready for PWM
const int left_dir_pin=29;
const int left_pwm_pin=40;
const int right_nslp_pin=11; // nslp ==> awake & ready for PWM
const int right_dir_pin=30;
const int right_pwm_pin=39;
const int LED_RF = 41;


uint16_t sensorValues[8];
float Kp = 2;
float Kd = 2;
uint16_t baseSpeed = 100;

// Calibration:
// 8 mins, 8 maxs, 8 weights
uint16_t sensorMins[8] = {250, 250, 250, 250, 250, 250, 250, 250};
uint16_t sensorMaxs[8] = {1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800};
int16_t sensorWeights[8] = {-8, -4, -2, 1, 1, 2, 4, 8};
int16_t errorTerm;
int16_t lastErrorTerm = 0;
int16_t deltaErrorTerm;
int16_t goal = 0;
int leftSpd = 100;
int rightSpd = 100;

void setup()
{
  ECE3_Init();
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  delay(2000);
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
}

void calibrate() {
  
}

void sensorFusion() {
  int16_t weightedAvg = 0;
  for (int i = 0; i < 8; i++) {
    sensorValues[i] -= sensorMins[i]; // subtract minimum
    sensorValues[i] = (1000 * sensorValues[i]) / (sensorMaxs[i] - sensorMins[i]); // normalize values
    weightedAvg += sensorValues[i] * sensorWeights[i]; // apply weight
    // Serial.println(i);
    Serial.println(sensorValues[i]);
    // Serial.println();
  }
  weightedAvg /= 8;
  // Serial.println("Weighted Average: ");
  // Serial.println(weightedAvg);
  errorTerm = goal - weightedAvg; // check sign of answer
  Serial.println("ERROR: ");
  Serial.println(errorTerm);
  errorTerm /= 20;
  deltaErrorTerm = (errorTerm - lastErrorTerm);
  Serial.println("DELTA ERROR: ");
  Serial.println(deltaErrorTerm);
  lastErrorTerm = errorTerm;
}

void loop()
{
  // read raw sensor values
  ECE3_read_IR(sensorValues);
  /*
  for (int i = 0; i < 8; i++) {
    Serial.println(sensorValues[i]);
    Serial.println("!");
  }
  */

  sensorFusion();
  float l = (leftSpd + Kp * errorTerm + Kd * deltaErrorTerm);
  float r = (rightSpd - Kp * errorTerm - Kd * deltaErrorTerm);
  l /= 3;
  r /= 3;
  analogWrite(left_pwm_pin, l);
  analogWrite(right_pwm_pin, r);
  Serial.println("L, R:");
  Serial.println(l);
  Serial.println(r);
}
