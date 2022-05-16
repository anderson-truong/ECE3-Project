#include <ECE3.h>

// 360 pulses per wheel rev
// Wheel diameter: 7 cm

// Odometer - slow car down for difficult sections
// Speed up for easy sections
// 180 donut indepedent of speed
// Closed-loop control of speed (increase pwm to match certain speed)

uint16_t sensorValues[8]; // right -> left, 0 -> 7

const int left_nslp_pin=31; // nslp ==> awake & ready for PWM
const int left_dir_pin=29;
const int left_pwm_pin=40;
const int right_nslp_pin=11;
const int right_dir_pin=30;
const int right_pwm_pin=39;

// PID Values
const float kP = 2;
const float kD = 0.0;
const int baseSpd = 100;

bool crosspiece = false;
bool flipped = false;

// Normalization
int sensorNorm[8];
int16_t sensorMin[8] { 490, 444, 421, 375, 421, 398, 444, 537 };
int16_t sensorMax[8] { 2450, 2500, 1674, 1626, 1697, 2142, 2019, 2500};

// Sensor Fusion
float fusionError;
float prevFusionError = 0;
float weights[8] = {-0.4, -0.3, -0.2, -0.1, 0.1, 0.2, 0.3, 0.4};

// PWM for each motor
int16_t leftPwm = 0;
int16_t rightPwm = 0;

int average()
{
  return ((getEncoderCount_left() + getEncoderCount_right())/2);
}

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

  //Serial.begin(9600);
  ECE3_Init();
  delay(2000);
}

void loop() {
    fusion();
    leftPwm = baseSpd - kP*fusionError - kD*(fusionError - prevFusionError);
    rightPwm = baseSpd + kP*fusionError + kD*(fusionError - prevFusionError);
    // Normalize pwm
    int maxPwm = leftPwm > rightPwm ? leftPwm : rightPwm;
    if (maxPwm > 250)
    {
      leftPwm *= 250;
      leftPwm /= maxPwm;
      rightPwm *= 250;
      rightPwm /= maxPwm;
    }
    //Serial.print(leftPwm);
    //Serial.print('\t');
    //Serial.println(rightPwm);
    analogWrite(left_pwm_pin,leftPwm);
    analogWrite(right_pwm_pin,rightPwm);
    prevFusionError = fusionError;
}

void flip()
{
  bool current = true;
  for (uint8_t i = 0; i < 8; i++)
    if (sensorNorm[i] < 1500)
      current = false;

  if (current && crosspiece && !flipped)
  {
    flipped = true;
    resetEncoderCount_left();
    resetEncoderCount_right();

    // Check if completed 180 turn
    while (average() < 360)
    {
      analogWrite(left_pwm_pin, 50);
      analogWrite(right_pwm_pin, -50);
    }
  }
  crosspiece = current;
}

void normalize()
{
  // Initialize norm array to 0
  for (uint8_t i = 0; i < 8; i++) sensorNorm[i] = 0;

  ECE3_read_IR(sensorValues);
  for (uint8_t j = 0; j < 8; j++)
    sensorNorm[j] += sensorValues[j];
    
  for (uint8_t i = 0; i < 8; i++)
  {
    // Floor
    sensorNorm[i] -= sensorMin[i];
  }
  
  // Normalize
  for (uint8_t i = 0; i < 8; i++)
  {
    sensorNorm[i] *= 1000;
    sensorNorm[i] /= sensorMax[i] - sensorMin[i];
  }
}

void fusion()
{
  normalize();
  fusionError = 0;
  for (uint8_t i = 0; i < 8; i++)
  {
    fusionError += weights[i] * sensorNorm[i];
  }
  fusionError /= 8;
}
