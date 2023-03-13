/* Main Arduino Sketch 
*/

#include <Arduino.h>
#include <Wire.h>
#include <sensor_functions.h>
#include <gaits.h> 
#include <webinterface.h>

void setup() {
  Serial.begin(115200);
  while (!Serial)
  delay(1000);
  Serial.println("Serial is up.");
  Wire.begin(); 
  pinMode(GPIO_NUM_4, OUTPUT);

//Wifi 
/* Go to http://192.168.4.1 in a web browser
   connected to the ESP AP to see the webinterface 
*/
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
+  Serial.println(IP);

  //callback functions for http requests  
  server.on("/", handle_root); 
  server.on("/X5_juggernaut.csv", download_data); 
  server.begin();

  //Initialize/Settings I2C Devices
  pwm.begin();
  pwm.setPWMFreq(60);

  //Current sensor 
  Serial.begin(115200);
  while(!Serial);
  Serial.println();
  while(ina219.begin() != true) {
    Serial.println("INA219 begin failed");
    delay(2000);
  }
  ina219.linearCalibrate(ina219Reading_mA, extMeterReading_mA);
  Serial.println();

  //distance Sensor 
  if (! vl53.begin(0x29, &Wire)) {
    Serial.print(F("Error on init of VL sensor: "));
    Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }
  if (! vl53.startRanging()) {
    Serial.print(F("Couldn't start ranging: "));
    Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }

  vl53.setTimingBudget(100); // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
  vl53.VL53L1X_SetDistanceMode(2); //2 = long, 1=short

  //Gyro 
  if (bmi160.softReset() != BMI160_OK){
    Serial.println("reset false");
    while(1);
  }
  //set and init the bmi160 i2c address
  if (bmi160.I2cInit(i2c_addr) != BMI160_OK){
    Serial.println("init false");
    while(1);
  }

  home_pos(); //All Servos to home position 

  for (size_t i = 0; i < 5; i++) //blink led 
  {
    digitalWrite(GPIO_NUM_4, HIGH);
    delay(100);
    digitalWrite(GPIO_NUM_4, LOW);
    delay(100); 
  }
  delay(1000); 
}

void loop() {
  server.handleClient(); 
}
