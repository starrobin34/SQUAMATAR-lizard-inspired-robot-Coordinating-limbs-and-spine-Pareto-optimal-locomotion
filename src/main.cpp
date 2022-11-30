/* Main Arduino Sketch 
*/

#include <Arduino.h>
#include <sensor_functions.h>
#include <gaits.h> 
#include <webinterface.h>



void setup() {
  Serial.begin(115200);
  while (!Serial)
  delay(1000);
  Serial.println("Serial is up.");

  Wire.begin();
  Wire.setClock(100000);

  pinMode(led_gpio, OUTPUT);

//Wifi 
/* Go to http://192.168.4.1 in a web browser
   connected to the ESP AP to see the webinterface 
*/
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  //callback functions for http requests  
  server.on("/", handle_root); 
  // server.on("/data", get_data); 
  server.on("/X5_juggernaut.csv", download_data); 
  server.begin();

  //Initialize/Settings I2C Devices
  pwm.begin();
  pwm.setPWMFreq(60);
  delay(200); 
  current_sensor.begin();
  delay(200); 
  gyro.begin(); 
  delay(200); 
  dist_sensor.begin(0x29);
  dist_sensor.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_LONG_RANGE); 
  delay(200); 
  Serial.println("All I2C Devices successfull"); 
  Serial.println("Turn Power on"); 
  home_pos(); //All Servos to home position 
  for (size_t i = 0; i < 5; i++)
  {
    digitalWrite(led_gpio, HIGH);
    delay(100);
    digitalWrite(led_gpio, LOW);
    delay(100); 
  }
}


void loop() {

  server.handleClient(); 

  // if (start_run == true)
  // {
    // if (gait == 1) //maybe in function handle root ? 
    // {
    //   Serial.println("Starting Gait 1"); 
    //   gait1();
    // }

    // if (gait == 2)
    // {
    //   Serial.println("Starting Gait 2"); 
    //   gait2(); 
    // }
  // }
  

    
}
