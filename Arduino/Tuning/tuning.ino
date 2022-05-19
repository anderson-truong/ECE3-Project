#include <ECE3.h>

// 360 pulses per wheel rev
// Wheel diameter: 7 cm

// Odometer - slow car down for difficult sections
// Speed up for easy sections
// 180 donut independent of speed
// Closed-loop control of speed (increase pwm to match certain speed)

// ==========================================================
//                           SETUP
// ==========================================================

// PINS
const int left_nslp_pin=31;
const int left_dir_pin=29;
const int left_pwm_pin=40;
const int right_nslp_pin=11;
const int right_dir_pin=30;
const int right_pwm_pin=39;

// PID Values
const float kP = 0.6;
const float kD = 0.02;
const int baseSpd = 100;

// Sensor Fusion
float fusionError;
float prevFusionError = 0;
float weights[8] = {-0.8, -0.4, -0.2, -0.1, 0.1, 0.2, 0.4, 0.8};

// Donut
uint8_t flips = 0;
uint8_t turnSpeed = 80;
uint8_t encoderCountsBeforeFlip = 360;
bool prevCrosspiece = false;

// Normalization
uint16_t sensorValues[8]; // right -> left, 0 -> 7
int sensorNorm[8];
//const int16_t sensorMin[8] { 421, 467, 421, 513, 444, 536, 513, 559 };
//const int16_t sensorMax[8] { 2005, 1982, 1896, 1645, 1707, 2332, 1830, 2078};
int16_t sensorMin[8] { 721, 632, 558, 536, 581, 536, 558, 744 };
int16_t sensorMax[8] { 2500, 2500, 1934, 1806, 1887, 2408, 2313, 2500};
// int16_t sensorMin[8] { 300, 300, 300, 300, 300, 300, 300, 300 };
// int16_t sensorMax[8] { 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500};

// PWM for each motor
int16_t leftPwm = 0;
int16_t rightPwm = 0;

// ==========================================================
//                         END SETUP
// ==========================================================

// Returns average encoder count
// from left and right encoders
int averageEncoderCount()
{
  return ((getEncoderCount_left() + getEncoderCount_right())/2);
}

///////////////////////////////////
void setup() {
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
    checkForFlip();
    leftPwm = baseSpd - kP*fusionError - kD*(fusionError - prevFusionError);
    rightPwm = baseSpd + kP*fusionError + kD*(fusionError - prevFusionError);
    /*
    Serial.print(leftPwm);
    Serial.print('\t');
    Serial.print(rightPwm);
    Serial.println();
    /*
    // Normalize pwm
    int maxPwm = leftPwm > rightPwm ? leftPwm : rightPwm;
    if (maxPwm > 250)
    {
      leftPwm *= 250;
      leftPwm /= maxPwm;
      rightPwm *= 250;
      rightPwm /= maxPwm;
    }
    */ 
    analogWrite(left_pwm_pin,leftPwm);
    analogWrite(right_pwm_pin,rightPwm);
    prevFusionError = fusionError;
}

void checkForFlip()
{
    uint16_t avg = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
      //Serial.print(sensorNorm[i]);
      //Serial.print('\t');
      avg += sensorNorm[i];
    }
    //Serial.println();
    avg /= 8;
    
    // Crosspiece is encountered when average of
    // normalized values exceeds a threshold
    bool crosspiece = (avg > 800);

    // Condition not met
    if (!crosspiece)
    {
      prevCrosspiece = false;
      return;
    }

    // Crosspiece was previously encountered
    if (prevCrosspiece)
    {
        // First flip at end
      if (flips == 0)
      {
        resetEncoderCount_left();
        resetEncoderCount_right();
        
        // Check if completed flip
        digitalWrite(right_dir_pin, HIGH);
        while (averageEncoderCount() < 360)
        {
          analogWrite(left_pwm_pin, turnSpeed);
          analogWrite(right_pwm_pin, turnSpeed);
        }
        digitalWrite(right_dir_pin, LOW);
        prevFusionError = 0;
      }
      
      // Stop after returning to start
      else if (flips == 1)
      {
        analogWrite(left_nslp_pin, LOW);
        analogWrite(right_nslp_pin, LOW);
      }
      flips++;
    }
    prevCrosspiece = crosspiece;
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

void normalize()
{
  ECE3_read_IR(sensorValues);
  for (uint8_t i = 0; i < 8; i++) {
    sensorNorm[i] = sensorValues[i];
    if (sensorNorm[i] - sensorMin[i] < 0)
      sensorNorm[i] = 0;
    else
      sensorNorm[i] -= sensorMin[i];
    sensorNorm[i] *= 1000;
    sensorNorm[i] /= sensorMax[i] - sensorMin[i];
  }
}
