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

long enc_bin_cnt;
const unsigned long enc_bin_len = 50; // 50 ms bins

const float kP = 0.1; // 0.08
const float kD = 0.0; // 0.8
const int baseSpd = 100; // 180

int turns = 0;

int sensorNorm[8];
int16_t sensorMin[8] { 490, 444, 421, 375, 421, 398, 444, 537 };
int16_t sensorMax[8] { 2450, 2500, 1674, 1626, 1697, 2142, 2019, 2500};
float fusionError;
float prevFusionError = 0;
float weights[8] = {-0.4, -0.3, -0.2, -0.1, 0.1, 0.2, 0.3, 0.4};

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

  // pinMode(LED_RF, OUTPUT);

  //Serial.begin(9600);
  ECE3_Init();
  delay(2000);
}

void loop() {
    fusion();
    //turn();
    //Serial.print(fusionError);
    //Serial.println();
    if (turns < 2)
    {
      analogWrite(left_pwm_pin,baseSpd - kP*fusionError - kD*(fusionError - prevFusionError));
      analogWrite(right_pwm_pin,baseSpd + kP*fusionError + kD*(fusionError - prevFusionError));
    }
    prevFusionError = fusionError;
    //delay(50);
}

void turn()
{
  bool condition = true;
  bool loopCondition[2] = {true, true};
  for (uint8_t j = 0; j < 2; j++)
  {
    for (uint8_t i = 0; i < 8; i++)
      if (sensorNorm[i] < 1000)
        loopCondition[j] = false;
    condition *= loopCondition[j];
    delay(50);
  }
  if (condition)
  {
    turns++;
    if (turns == 0)
    {
      resetEncoderCount_left();
    delay(50);
    enc_bin_cnt = getEncoderCount_left();
    while (enc_bin_cnt < 380)
    {
      delay(50);
      enc_bin_cnt = getEncoderCount_left();
    }
    }
  }
}

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
    //delay(10);
  }
  
  for (uint8_t i = 0; i < 8; i++)
  {
    // Divide by N for averages
    sensorNorm[i] /= N;
    // Floor
    sensorNorm[i] -= sensorMin[i];
  }
  
  // Normalize
  for (uint8_t i = 0; i < 8; i++)
  {
    sensorNorm[i] *= 1000;
    sensorNorm[i] /= sensorMax[i] - sensorMin[i];
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
}
