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
float kP = 1.3;
float kD = 4.5;
int baseSpd = 70;

int flips = 0;
bool crosspiece = false;

// Normalization
int sensorNorm[8];
int16_t sensorMin[8] { 536, 536, 468, 375, 421, 375, 421, 505 };
int16_t sensorMax[8] { 2500, 2500, 2500, 2242, 1982, 2147, 1559, 2500};

// Sensor Fusion
float fusionError;
float prevFusionError = 0;
float weights[8] = {-0.5, -0.35, -0.2, -0.05, 0.05, 0.2, 0.35, 0.5};
// float weights[8] = {-0.6, -0.3, -0.15, -0.05, 0.05, 0.15, 0.3, 0.6};

// PWM for each motor
int16_t leftPwm = 0;
int16_t rightPwm = 0;

int encoderCount = 0;

int averageEncoderCount()
{
  return ((getEncoderCount_left() + getEncoderCount_right())/2);
}

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

  //Serial.begin(9600);
  ECE3_Init();
  delay(2000);
}

void loop() {
    fusion();
    checkForFlip();

    kP = 1.3;
    kD = 4.5;
    if (averageEncoderCount() <= 750 && flips == 0)
    {
      // high Kp and Kd to quickly straighten out from starting position
      // My guess is that we need to raise kD
      kP = 1.7;
      kD = 5.5;
      baseSpd = 100;
    }
    else if (averageEncoderCount() > 750 && averageEncoderCount() < 1500 && flips == 0)
    {
      // slowww
      // @Anderson, we want to tune these distances to be as close as possible to the start/end of the hard section
      // so that we spend as little time as possible in the slow state
      baseSpd = 50;
    }
    else if (averageEncoderCount() > 3750 && flips == 0)
    {
      //@Anderson, for this long curve section, we might want to tune it slightly so that we can go
      // through the smooth part of the long curve at a higher speed, then slow down for the sharper curve
      // at the end. Just a thought, definitely lower priority
      kP = 1.4;
      kD = 5.5;
      baseSpd = 80;
    }
    else if (averageEncoderCount() < 3000 && flips == 1)
    {
      kP = 1.4;
      kD = 5.5;
      baseSpd = 80;
    }
    else if (averageEncoderCount() > 5200 && averageEncoderCount() < 6250 && flips == 1)
    {
      // slowww
      baseSpd = 50;
    }
    else if (averageEncoderCount() > 6250 && flips == 1)
    {
      // This one is also for the last little segment, so we want high Kp & Kd to straighten out for the finish
      kP = 1.7;
      kD = 5.5;
      baseSpd = 100;
    }
    else
    {
      // @Anderson, we want to work on tuning this straight section so that we raise the base speed to go faster
      // My guess is again that we need to raise kD
      kP = 0.9;
      kD = 5.5;
      baseSpd = 150;
    }
    leftPwm = baseSpd - kP*fusionError - kD*(fusionError - prevFusionError);
    rightPwm = baseSpd + kP*fusionError + kD*(fusionError - prevFusionError);
    analogWrite(left_pwm_pin,leftPwm);
    analogWrite(right_pwm_pin,rightPwm);

    prevFusionError = fusionError;
}

void checkForFlip()
{
    int avg = 0;
    for (uint8_t i = 0; i < 8; i++)
      // Value is not high, condition not met
      avg += sensorNorm[i];
    avg /= 8;
    bool condition = (avg > 800);

  if (condition && crosspiece)
  {
    //Serial.println("Flip condition met");
    if (flips == 0)
    {
      flips++;

     resetEncoderCount_left();
     resetEncoderCount_right();
      // Check if completed 180 turn
      digitalWrite(right_dir_pin, HIGH);
      while (averageEncoderCount() < 345)
      {
        // Serial.println("Turning...");
        analogWrite(left_pwm_pin, 140);
        analogWrite(right_pwm_pin, 140);
      }
      digitalWrite(right_dir_pin, LOW);
    }
    else if (flips == 1) {
        flips++;
        analogWrite(left_pwm_pin, 0);
        analogWrite(right_pwm_pin, 0);
        delay(30000);
    }
  }
  crosspiece = condition;
}

void normalize()
{
  // Initialize norm array to 0
  for (uint8_t i = 0; i < 8; i++) sensorNorm[i] = 0;

  ECE3_read_IR(sensorValues);
  for (uint8_t j = 0; j < 8; j++) {
    sensorNorm[j] += sensorValues[j];
  }

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
    // Serial.print(sensorNorm[i]);
    // Serial.print("\t");
  }
    // Serial.println("");
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
