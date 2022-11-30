/* 
  this File contains the sensor functions 
*/

#include <Wire.h>
#include <Adafruit_INA219.h>
#include <MPU6050_tockn.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
Adafruit_VL53L0X dist_sensor = Adafruit_VL53L0X();
Adafruit_INA219 current_sensor(0x41); 
MPU6050 gyro(Wire);

int step_val = 0; 



int get_dist(); 
float get_current(); 
float get_gyro();  


int get_dist(){ 

  int measured_dist; 
  int sample_size = 10;
  int sum = 0;  
  int mean_dist; 

  measured_dist = dist_sensor.readRange(); 
   
  if (measured_dist <= 85)
  {
    step_val = 20; 
    Serial.println("End of track reached!"); 
  }

  if (measured_dist >= 8190) //input max reading of sensor here 
  {
    step_val = 20; 
    Serial.println("Distance sensor read max!"); 
  }

  for (size_t i = 0; i < sample_size; i++)
  {
    sum += dist_sensor.readRange();
    delay(1); 
  }

  mean_dist = sum / sample_size; 

  return mean_dist;
}

float get_current(){ 

  float current; 
  current = current_sensor.getCurrent_mA(); 
  
  return current; 
}

float get_gyro(int val){ 
  
  float measured_xaxisValue, measured_yaxisValue, measured_zaxisValue, measured_temp = 0.0;

  float x[5] = {0.0}; //arrays to store X, Y, Z - Orientation
  float y[5] = {0.0};
  float z[5] = {0.0};

  for (size_t i = 0 ; i < 5; i++) {
    gyro.update();
    x[i] = gyro.getAccAngleX();
    y[i] = gyro.getAccAngleY();
    z[i] = gyro.getGyroAngleZ();
    delay(1);
  }

  measured_xaxisValue = (x[0] + x[1] + x[2] + x[3] + x[4]) / 5; //Mean to reduce influence of noise of the sensor
  measured_yaxisValue = (y[0] + y[1] + y[2] + y[3] + y[4]) / 5;
  measured_zaxisValue = (z[0] + z[1] + z[2] + z[3] + z[4]) / 5;

  measured_temp = gyro.getTemp();

  if (val == 1)
  {
    return measured_xaxisValue; 
  }
    if (val == 2)
  {
    return measured_yaxisValue; 
  }
    if (val == 3)
  {
    return measured_zaxisValue; 
  }
    if (val == 4)
  {
    return measured_temp; 
  }
  return 0.0; 
}