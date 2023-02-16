/* 
  this File contains the sensor functions 
*/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Adafruit_VL53L1X.h"
#include "DFRobot_INA219.h"
#include <DFRobot_BMI160.h>


Adafruit_VL53L1X vl53 = Adafruit_VL53L1X();
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
DFRobot_INA219_IIC ina219(&Wire, INA219_I2C_ADDRESS4);
DFRobot_BMI160 bmi160;
const int8_t i2c_addr = 0x69;

// Revise the following two paramters according to actual reading of the INA219 and the multimeter
// for linearly calibration
float ina219Reading_mA = 1000;
float extMeterReading_mA = 1000;

float y_ang_offset = 0.0; 
float z_ang_offset = 0.0; 

int step_val = 0; 

int get_dist(); 
float get_current(); 
float get_accel(int val); 


int get_dist(){ 

  int measured_dist; 
  int sample_size = 10;
  int sum = 0;  
  int mean_dist; 

  measured_dist = vl53.distance();

   
  // if (measured_dist <= 20)
  // {
  //   step_val = 20; 
  //   Serial.print(measured_dist); 
  //   Serial.println("End of track reached!"); 
  // }

  // if (measured_dist == -1) //input max reading of sensor here 
  // {
  //   step_val = 20; 
  //   Serial.print(measured_dist); 
  //   Serial.println("Distance sensor read max!"); 
  // }

  for (size_t i = 0; i < sample_size; i++)
  {
    sum += vl53.distance();
    delay(1); 
  }

  mean_dist = sum / sample_size; 

    // Serial.print("Dist. Sensor read: "); 
    // Serial.println(mean_dist); 
  
  return mean_dist;
}

float get_current(){ 

  float current; 
  current = ina219.getCurrent_mA(); 
  
  return current; 
}

float get_accel(int val){ 
  
  float measured_xaxisValue, measured_yaxisValue, measured_zaxisValue;
  float z_angle, y_angle; 
  int rslt;
  int16_t accelGyro[6]={0}; 
  float rad_to_deg = 180 / PI;

  //Mean for more precision 
  float x[5] = {0.0}; //arrays to store acceleration in X, Y, Z 
  float y[5] = {0.0};
  float z[5] = {0.0};

  for (size_t i = 0 ; i < 5; i++) {
    rslt = bmi160.getAccelGyroData(accelGyro); //SLOW !!!
        x[i] = accelGyro[3]/16384.0; //get linear acceleration in g-force 
        y[i] = accelGyro[4]/16384.0; 
        z[i] = accelGyro[5]/16384.0;   
  }

  measured_xaxisValue = (x[0] + x[1] + x[2] + x[3] + x[4]) / 5; //Mean to reduce influence of noise of the sensor
  measured_yaxisValue = (y[0] + y[1] + y[2] + y[3] + y[4]) / 5;
  measured_zaxisValue = (z[0] + z[1] + z[2] + z[3] + z[4]) / 5;

  //No mean 
  // rslt = bmi160.getAccelGyroData(accelGyro);
  // if (rslt == 0)
  // {
  // measured_xaxisValue = accelGyro[3]/16384.0;
  // measured_yaxisValue = accelGyro[4]/16384.0;
  // measured_zaxisValue = accelGyro[5]/16384.0;
  // }
  
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
    y_angle = (rad_to_deg * (atan2(measured_yaxisValue, measured_xaxisValue))) - y_ang_offset;
    return y_angle; 
  }
  if (val == 5)
  {
    z_angle = (rad_to_deg * (atan2(-measured_zaxisValue, measured_xaxisValue))) - z_ang_offset; 
    return z_angle; 
  }
  
  return 0.0; 
}

