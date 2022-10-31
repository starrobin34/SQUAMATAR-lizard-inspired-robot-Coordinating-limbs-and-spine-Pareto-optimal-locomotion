/* Main Arduino Sketch 
*/

#include <Arduino.h>
#include <gaits.h> 
#include <webinterface.h>



void setup() {
  Serial.begin(115200);

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
  server.on("/data", get_data); 
  server.on("/X5_juggernaut.csv", download_data); 
  server.begin();

  //Servos and Home Pos. 
  pwm.begin();
  pwm.setPWMFreq(60);
  Serial.println("Turn Power on");
  home_pos(); //All Servos to home position 
  Serial.println("Robot in Home Pos.");
}


void loop() {

  server.handleClient(); 

  // if (start_run == true)
  // {
    if (gait == 1)
    {
      Serial.println("Starting Gait 1"); 
      gait1();
    }

    if (gait == 2)
    {
      Serial.println("Starting Gait 2"); 
      gait2(); 
    }
  // }
  

    
}
