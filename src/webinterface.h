/* 
    webinterface 
*/

#include <WiFi.h>
#include <WebServer.h>

//Wifi Credentials 
const char* ssid = "X5 Robot Juggernaut"; 
const char* password = ""; 
String argument_name; 

//fuction prototypes 
void handle_root(); 
void download_data(); 

WebServer server(80); 

void handle_root(){

  //Webpage Styling 
  String html = "<!DOCTYPE html> <html style=\"background-color:Teal;\"> <head><meta name=\"viewport\" content=\"width=device-width, minimumscale=1.0, maximum-scale=1.0, initial-scale=1\" /><style> body {text-align: left; max-width: 800px; margin: 10px auto;} ";
  html += "#updateView { max-width: 100px; display: none; margin-top: 30px; } #dataVals { max-width: 100px; display: block; margin-top: 30px; } .convertButton ";
  html += "{ clear: both; position:relative; margin-top: 30px; -moz-box-shadow: 0px 1px 0px 0px #fff6af; -webkit-box-shadow: 0px 1px 0px 0px #fff6af; box-shadow: 0px 1px 0px 0px #fff6af; background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #ffec64), color-stop(1, #ffab23)); ";
  html += "background:-moz-linear-gradient(top, #ffec64 5%, #ffab23 100%); background:-webkit-linear-gradient(top, #ffec64 5%, #ffab23 100%); background:-o-linear-gradient(top, #ffec64 5%, #ffab23 100%); background:-ms-linear-gradient(top, #ffec64 5%, #ffab23 100%); background:linear-gradient(to bottom, #ffec64 5%, #ffab23 100%); ";
  html += "filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#ffec64', endColorstr='#ffab23',GradientType=0); background-color:#ffec64; -moz-border-radius:6px; -webkit-border-radius:6px; border-radius:6px; border:1px solid #ffaa22; display:inline-block; cursor:pointer; color:#333333; font-family:Arial; font-size:21px; ";
  html += "padding:14px 69px; text-decoration:none; text-shadow:0px 1px 0px #ffee66; } .convertButton:hover { background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #ffab23), color-stop(1, #ffec64)); background:-moz-linear-gradient(top, #ffab23 5%, #ffec64 100%); background:-webkit-linear-gradient(top, #ffab23 5%, #ffec64 100%); ";
  html += "background:-o-linear-gradient(top, #ffab23 5%, #ffec64 100%); background:-ms-linear-gradient(top, #ffab23 5%, #ffec64 100%); background:linear-gradient(to bottom, #ffab23 5%, #ffec64 100%); filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#ffab23', endColorstr='#ffec64',GradientType=0); background-color:#ffab23; } ";
  html += ".convertButton:active { position:relative; top:1px; }</style></head>";

  //html body 
  html += "<body> <h1 style=\"text-align: left;\">Climbing Robot X5 Juggernaut</h1> <p>&nbsp;</p>"; 

  //generating the DOWNLOAD button
  //CHANGE NAME OF csv output file HERE!!!
  html += "<body><a href=\"/X5_juggernaut.csv\"><button style=\"display: block; width: 100%;\">DOWNLOAD</button></a><br/></body>";

  String myIP = WiFi.softAPIP().toString();
  html += "<body><h2 style=\"text-align: left;\"><span style=\"text-decoration: underline;\">Climbing Parameters:</span></h2>";
  html += "<form action='http://" + myIP + "' method='POST'>";
  html += "Steps:<input type='text' name='step_input' value='"; 
  html += number_of_steps;
  html += "'><BR>";
  html += "Speed of Gait:<input type='text' name='speed_input' value='";
  html += speed_val;
  html += "'><BR>";
  html += "Speed of foot lift:<input type='text' name='speed_input1' value='";
  html += speed_val_foot;
  html += "'><BR>";
  html += "Limb range of motion:<input type='text' name='range_input' value='";
  html += rom_limb;
  html += "'><BR>";
  html += "Spine range of motion:<input type='text' name='range_input1' value='";
  html += rom_spine;
  html += "'><BR>";
  html += "Feet range of motion:<input type='text' name='range_input2' value='";
  html += rom_feet;
  html += "'><BR>";
  html += "Foot center:<input type='text' name='foot_offset' value='";
  html += foot_center;
  html += "'><BR>";
  html += "Front wrist angle:<input type='text' name='front_wrist' value='";
  html += front_wrist_angle;
  html += "'><BR>";
  html += "Hind wrist angle:<input type='text' name='hind_wrist' value='";
  html += hind_wrist_angle;
  html += "'><BR>";
  html += "Dynamic of wrist angle:<input type='text' name='dynamic_wrist' value='";
  html += dynamic_wrist_angle;
  html += "'><BR>";
  html += "Front leg center:<input type='text' name='front center' value='";
  html += front_leg_center;
  html += "'><BR>";
  html += "Hind leg center:<input type='text' name='hind center' value='";
  html += hind_leg_center;
  html += "'><BR>";
  html += "Dynamics:<input type='text' name='function_input' value='";
  html += dynamic;
  html += "'><BR>";
  html += "Gait:<input type='text' name='gait_input' value='";
  html += gait;
  html += "'><BR>";
  html += "<input type='submit' value='Enter'>"; // omit <input type='submit' value='Enter'> for just 'enter'
  html += "</form>";
  html += "</body></html>";
  
  server.send(200, "text/html", html); 

  if (server.args() > 0 ) { // Arguments were received
    for ( uint8_t i = 0; i < server.args(); i++ ) {

      argument_name = server.argName(i);

      if (server.argName(i) == "step_input") {

        number_of_steps = server.arg(i).toInt();
      }
      if (server.argName(i) == "gait_input") {

        gait = server.arg(i).toInt();
      }
      if (server.argName(i) == "speed_input") {

        speed_val = server.arg(i).toInt();
      }
      if (server.argName(i) == "range_input") {

        rom_limb = server.arg(i).toInt();
      }
      if (server.argName(i) == "range_input1") {

        rom_spine = server.arg(i).toInt();
      }
      if (server.argName(i) == "function_input") {

        dynamic = server.arg(i).toInt();
      }
      if (server.argName(i) == "speed_input1") {

        speed_val_foot = server.arg(i).toInt();
      }
      if (server.argName(i) == "range_input2") {

        rom_feet = server.arg(i).toInt();
      }
      if (server.argName(i) == "foot_offset") {

        foot_center = server.arg(i).toInt();
      }
      if (server.argName(i) == "front_wrist") {

        front_wrist_angle = server.arg(i).toInt();
      }
      if (server.argName(i) == "hind_wrist") {

        hind_wrist_angle = server.arg(i).toInt();
      }
      if (server.argName(i) == "dynamic_wrist") {

        dynamic_wrist_angle = server.arg(i).toInt();
      }
      if (server.argName(i) == "front center") {

        front_leg_center = server.arg(i).toInt();
      }
      if (server.argName(i) == "hind center") {

        hind_leg_center = server.arg(i).toInt();
      }
    }

    //redefine variables to update 
    h_lff = hh_lff + foot_center; 
    h_lfs = hh_lfs - front_leg_center;
    h_rfs = hh_rfs + front_leg_center;
    h_rff = hh_rff + foot_center;
    h_rhf = hh_rhf + foot_center;
    h_rhs = hh_rhs + hind_leg_center;
    h_lhs = hh_lhs - hind_leg_center;
    h_lhf = hh_lhf - foot_center;
    h_lfa = hh_lfa + front_wrist_angle - front_leg_center; 
    h_rfa = hh_rfa - front_wrist_angle + front_leg_center; 
    h_lha = hh_lha + hind_wrist_angle - hind_leg_center; 
    h_rha = hh_rha -  hind_wrist_angle + hind_leg_center; 
    rom_wrist_angle = rom_spine + rom_limb; 
    home_pos();

    if (gait == 1) //maybe in function handle root ? 
    {
      Serial.println("Starting Gait 1"); 
      gait1();
    }
  }
}

void download_data(){
//builds a dataframe in .csv format
  String txt = "";

  //First Row
  //fixed input values
  txt += "Robot";
  txt += ", ";
  txt += "Dynamics";
  txt += ", ";
  txt += "Gait_speed";
  txt += ", ";
  txt += "Foot_lift_speed";
  txt += ", ";
  txt += "Limb_rom";
  txt += ", ";
  txt += "Spine_rom";
  txt += ", ";
  txt += "Feet_rom";
  txt += ", ";
  txt += "Feet_angle_center";
  txt += ", ";
  txt += "Front_leg_center";
  txt += ", ";
  txt += "Hind_leg_center";
  txt += ", ";
  txt += "Dynamic_wrist_angle";
  txt += ", ";
  txt += "Front_wrist_angle";
  txt += ", ";
  txt += "Hind_wrist_angle";
  txt += ", ";
  txt += "Toe_Angle";
  txt += ", ";
  txt += "Claw_Angle";
  txt += ", ";
  txt += "Surface";
  txt += ", ";
  txt += "Incline_degree";
  txt += ", ";
  txt += "leg_length_in_mm";
  txt += ", ";
  txt += "spine_length_in_mm";
  txt += ", ";
  

  //data collection
  txt += "Stride";
  txt += ", ";
  txt += "Distance_per_stride_mm";
  txt += ", ";
  txt += "Time_in_s";
  txt += ", ";
  txt += "X_mean_acc_in_g";
  txt += ", ";
  txt += "Y_mean_acc_in_g";
  txt += ", ";
  txt += "Z_mean_acc_in_g";
  txt += ", ";
  txt += "Angle_yaxis";
  txt += ", ";
  txt += "Angle_zaxis";
  txt += ", ";
  txt += "Mean_Current_Consumption_in_mA";
  txt += ", ";
  txt += "Current_Spike_in_mA";
  txt += ", ";
  txt += "FL_Feet_Success_in_percent";
  txt += ", ";
  txt += "FR_Feet_Success_in_percent";
  txt += ", ";
  txt += "HR_Feet_Success_in_percent";
  txt += ", ";
  txt += "HL_Feet_Success_in_percent";
  txt += ", ";
  txt += "FL_Leg_Success_in_percent";
  txt += ", ";
  txt += "FR_Leg_Success_in_percent";
  txt += ", ";
  txt += "HR_Leg_Success_in_percent";
  txt += ", ";
  txt += "HL_Leg_Success_in_percent";
  txt += ", ";
  txt += "LF_Wrist_Success_in_percent";
  txt += ", ";
  txt += "RF_Wrist_Success_in_percent";
  txt += ", ";
  txt += "LH_Wrist_Success_in_percent";
  txt += ", ";
  txt += "RH_Wrist_Success_in_percent";
  txt += " \n"; //linebreak 

//Second row 
//fixed vals 
  txt += robot;
  txt += ", ";
  txt += dynamic;
  txt += ", ";
  txt += speed_val;
  txt += ", ";
  txt += speed_val_foot;
  txt += ", ";
  txt += rom_limb;
  txt += ", ";
  txt += rom_spine;
  txt += ", ";
  txt += rom_feet;
  txt += ", ";
  txt += foot_center;
  txt += ", ";
  txt += front_leg_center;
  txt += ", ";
  txt += hind_leg_center;
  txt += ", ";
  txt += dynamic_wrist_angle;
  txt += ", ";
  txt += front_wrist_angle;
  txt += ", ";
  txt += hind_wrist_angle;
  txt += ", ";
  txt += toe_angle;
  txt += ", ";
  txt += claw_angle;
  txt += ", ";
  txt += surface;
  txt += ", ";
  txt += climb_incline;
  txt += ", ";
  txt += leg_length;
  txt += ", ";
  txt += spine_length;
  txt += ", ";



  //data collection 
  txt += stride[0]; //stride
  txt += ", ";
  txt += distance[0]; // dist
  txt += ", ";
  txt += elapsed_time[0]; //time
  txt += ", ";
  txt += mean_acc_xaxis[0];//xgyro
  txt += ", ";
  txt += mean_acc_yaxis[0];//ygyro
  txt += ", ";
  txt += mean_acc_zaxis[0];//zgyro
  txt += ", ";
  txt += angle_yaxis[0];//zgyro
  txt += ", ";
  txt += angle_zaxis[0];//zgyro
  txt += ", ";
  txt += mean_current[0];// mean current during stride
  txt += ", ";
  txt += max_current[0];// current spike of stride
  txt += ", ";
  //feet success 
  txt += lff_suc[0];
  txt += ", ";
  txt += rff_suc[0];
  txt += ", ";
  txt += rhf_suc[0];
  txt += ", ";
  txt += lhf_suc[0];
  txt += ", ";
  //shoulder success 
  txt += lfs_suc[0];
  txt += ", ";
  txt += rfs_suc[0];
  txt += ", ";
  txt += rhs_suc[0];
  txt += ", ";
  txt += lhs_suc[0];
  txt += ", ";
  //wrist success 
  txt += lfa_suc[0];
  txt += ", ";
  txt += rfa_suc[0];
  txt += ", ";
  txt += lha_suc[0];
  txt += ", ";
  txt += rha_suc[0];
  txt += " \n";  //linebreak


//Row 3
//fixed vals 
  txt += robot;
  txt += ", ";
  txt += dynamic;
  txt += ", ";
  txt += speed_val;
  txt += ", ";
  txt += speed_val_foot;
  txt += ", ";
  txt += rom_limb;
  txt += ", ";
  txt += rom_spine;
  txt += ", ";
  txt += rom_feet;
  txt += ", ";
  txt += foot_center;
  txt += ", ";
  txt += front_leg_center;
  txt += ", ";
  txt += hind_leg_center;
  txt += ", ";
  txt += dynamic_wrist_angle;
  txt += ", ";
  txt += front_wrist_angle;
  txt += ", ";
  txt += hind_wrist_angle;
  txt += ", ";
  txt += toe_angle;
  txt += ", ";
  txt += claw_angle;
  txt += ", ";
  txt += surface;
  txt += ", ";
  txt += climb_incline;
  txt += ", ";
  txt += leg_length;
  txt += ", ";
  txt += spine_length;
  txt += ", ";

  txt += stride[1]; //stride
  txt += ", ";
  txt += distance[1]; // dist
  txt += ", ";
  txt += elapsed_time[1]; //time
  txt += ", ";
  txt += mean_acc_xaxis[1];//xgyro
  txt += ", ";
  txt += mean_acc_yaxis[1];//ygyro
  txt += ", ";
  txt += mean_acc_zaxis[1];//zgyro
  txt += ", ";
  txt += angle_yaxis[1];//zgyro
  txt += ", ";
  txt += angle_zaxis[1];//zgyro  
  txt += ", ";
  txt += mean_current[1];// mean current during stride
  txt += ", ";
  txt += max_current[1];// current spike of stride
  txt += ", ";
  //feet success 
  txt += lff_suc[1];
  txt += ", ";
  txt += rff_suc[1];
  txt += ", ";
  txt += rhf_suc[1];
  txt += ", ";
  txt += lhf_suc[1];
  txt += ", ";
  //shoulder success 
  txt += lfs_suc[1];
  txt += ", ";
  txt += rfs_suc[1];
  txt += ", ";
  txt += rhs_suc[1];
  txt += ", ";
  txt += lhs_suc[1];
  txt += ", ";
  //wrist success 
  txt += lfa_suc[1];
  txt += ", ";
  txt += rfa_suc[1];
  txt += ", ";
  txt += lha_suc[1];
  txt += ", ";
  txt += rha_suc[1];
  txt += " \n";  //linebreak

  //Row 4
//fixed vals 
  txt += robot;
  txt += ", ";
  txt += dynamic;
  txt += ", ";
  txt += speed_val;
  txt += ", ";
  txt += speed_val_foot;
  txt += ", ";
  txt += rom_limb;
  txt += ", ";
  txt += rom_spine;
  txt += ", ";
  txt += rom_feet;
  txt += ", ";
  txt += foot_center;
  txt += ", ";
  txt += front_leg_center;
  txt += ", ";
  txt += hind_leg_center;
  txt += ", ";
  txt += dynamic_wrist_angle;
  txt += ", ";
  txt += front_wrist_angle;
  txt += ", ";
  txt += hind_wrist_angle;
  txt += ", ";
  txt += toe_angle;
  txt += ", ";
  txt += claw_angle;
  txt += ", ";
  txt += surface;
  txt += ", ";
  txt += climb_incline;
  txt += ", ";
  txt += leg_length;
  txt += ", ";
  txt += spine_length;
  txt += ", ";

  txt += stride[2]; //stride
  txt += ", ";
  txt += distance[2]; // dist
  txt += ", ";
  txt += elapsed_time[2]; //time
  txt += ", ";
  txt += mean_acc_xaxis[2];//xgyro
  txt += ", ";
  txt += mean_acc_yaxis[2];//ygyro
  txt += ", ";
  txt += mean_acc_zaxis[2];//zgyro
  txt += ", ";
  txt += angle_yaxis[2];//zgyro
  txt += ", ";
  txt += angle_zaxis[2];//zgyro  
  txt += ", ";
  txt += mean_current[2];// mean current during stride
  txt += ", ";
  txt += max_current[2];// current spike of stride
  txt += ", ";
  //feet success 
  txt += lff_suc[2];
  txt += ", ";
  txt += rff_suc[2];
  txt += ", ";
  txt += rhf_suc[2];
  txt += ", ";
  txt += lhf_suc[2];
  txt += ", ";
  //shoulder success 
  txt += lfs_suc[2];
  txt += ", ";
  txt += rfs_suc[2];
  txt += ", ";
  txt += rhs_suc[2];
  txt += ", ";
  txt += lhs_suc[2];
  txt += ", ";
  //wrist success 
  txt += lfa_suc[2];
  txt += ", ";
  txt += rfa_suc[2];
  txt += ", ";
  txt += lha_suc[2];
  txt += ", ";
  txt += rha_suc[2];
  txt += " \n";  //linebreak

  //Row 5 
//fixed vals 
  txt += robot;
  txt += ", ";
  txt += dynamic;
  txt += ", ";
  txt += speed_val;
  txt += ", ";
  txt += speed_val_foot;
  txt += ", ";
  txt += rom_limb;
  txt += ", ";
  txt += rom_spine;
  txt += ", ";
  txt += rom_feet;
  txt += ", ";
  txt += foot_center;
  txt += ", ";
  txt += front_leg_center;
  txt += ", ";
  txt += hind_leg_center;
  txt += ", ";
  txt += dynamic_wrist_angle;
  txt += ", ";
  txt += front_wrist_angle;
  txt += ", ";
  txt += hind_wrist_angle;
  txt += ", ";
  txt += toe_angle;
  txt += ", ";
  txt += claw_angle;
  txt += ", ";
  txt += surface;
  txt += ", ";
  txt += climb_incline;
  txt += ", ";
  txt += leg_length;
  txt += ", ";
  txt += spine_length;
  txt += ", ";

  txt += stride[3]; //stride
  txt += ", ";
  txt += distance[3]; // dist
  txt += ", ";
  txt += elapsed_time[3]; //time
  txt += ", ";
  txt += mean_acc_xaxis[3];//xgyro
  txt += ", ";
  txt += mean_acc_yaxis[3];//ygyro
  txt += ", ";
  txt += mean_acc_zaxis[3];//zgyro
  txt += ", ";
  txt += angle_yaxis[3];//zgyro
  txt += ", ";
  txt += angle_zaxis[3];//zgyro  
  txt += ", ";
  txt += mean_current[3];// mean current during stride
  txt += ", ";
  txt += max_current[3];// current spike of stride
  txt += ", ";
  //feet success 
  txt += lff_suc[3];
  txt += ", ";
  txt += rff_suc[3];
  txt += ", ";
  txt += rhf_suc[3];
  txt += ", ";
  txt += lhf_suc[3];
  txt += ", ";
  //shoulder success 
  txt += lfs_suc[3];
  txt += ", ";
  txt += rfs_suc[3];
  txt += ", ";
  txt += rhs_suc[3];
  txt += ", ";
  txt += lhs_suc[3];
  txt += ", ";
  //wrist success 
  txt += lfa_suc[3];
  txt += ", ";
  txt += rfa_suc[3];
  txt += ", ";
  txt += lha_suc[3];
  txt += ", ";
  txt += rha_suc[3];
  txt += " \n";  //linebreak

  //Row 6 
//fixed vals 
  txt += robot;
  txt += ", ";
  txt += dynamic;
  txt += ", ";
  txt += speed_val;
  txt += ", ";
  txt += speed_val_foot;
  txt += ", ";
  txt += rom_limb;
  txt += ", ";
  txt += rom_spine;
  txt += ", ";
  txt += rom_feet;
  txt += ", ";
  txt += foot_center;
  txt += ", ";
  txt += front_leg_center;
  txt += ", ";
  txt += hind_leg_center;
  txt += ", ";
  txt += dynamic_wrist_angle;
  txt += ", ";
  txt += front_wrist_angle;
  txt += ", ";
  txt += hind_wrist_angle;
  txt += ", ";
  txt += toe_angle;
  txt += ", ";
  txt += claw_angle;
  txt += ", ";
  txt += surface;
  txt += ", ";
  txt += climb_incline;
  txt += ", ";
  txt += leg_length;
  txt += ", ";
  txt += spine_length;
  txt += ", ";

  txt += stride[4]; //stride
  txt += ", ";
  txt += distance[4]; // dist
  txt += ", ";
  txt += elapsed_time[4]; //time
  txt += ", ";
  txt += mean_acc_xaxis[4];//xgyro
  txt += ", ";
  txt += mean_acc_yaxis[4];//ygyro
  txt += ", ";
  txt += mean_acc_zaxis[4];//zgyro
  txt += ", ";
  txt += angle_yaxis[4];//zgyro
  txt += ", ";
  txt += angle_zaxis[4];//zgyro  
  txt += ", ";
  txt += mean_current[4];// mean current during stride
  txt += ", ";
  txt += max_current[4];// current spike of stride
  txt += ", ";
  //feet success 
  txt += lff_suc[4];
  txt += ", ";
  txt += rff_suc[4];
  txt += ", ";
  txt += rhf_suc[4];
  txt += ", ";
  txt += lhf_suc[4];
  txt += ", ";
  //shoulder success 
  txt += lfs_suc[4];
  txt += ", ";
  txt += rfs_suc[4];
  txt += ", ";
  txt += rhs_suc[4];
  txt += ", ";
  txt += lhs_suc[4];
  txt += ", ";
  //wrist success 
  txt += lfa_suc[4];
  txt += ", ";
  txt += rfa_suc[4];
  txt += ", ";
  txt += lha_suc[4];
  txt += ", ";
  txt += rha_suc[4];
  txt += " \n";  //linebreak

  //Row 7 
//fixed vals 
  txt += robot;
  txt += ", ";
  txt += dynamic;
  txt += ", ";
  txt += speed_val;
  txt += ", ";
  txt += speed_val_foot;
  txt += ", ";
  txt += rom_limb;
  txt += ", ";
  txt += rom_spine;
  txt += ", ";
  txt += rom_feet;
  txt += ", ";
  txt += foot_center;
  txt += ", ";
  txt += front_leg_center;
  txt += ", ";
  txt += hind_leg_center;
  txt += ", ";
  txt += dynamic_wrist_angle;
  txt += ", ";
  txt += front_wrist_angle;
  txt += ", ";
  txt += hind_wrist_angle;
  txt += ", ";
  txt += toe_angle;
  txt += ", ";
  txt += claw_angle;
  txt += ", ";
  txt += surface;
  txt += ", ";
  txt += climb_incline;
  txt += ", ";
  txt += leg_length;
  txt += ", ";
  txt += spine_length;
  txt += ", ";

  txt += stride[5]; //stride
  txt += ", ";
  txt += distance[5]; // dist
  txt += ", ";
  txt += elapsed_time[5]; //time
  txt += ", ";
  txt += mean_acc_xaxis[5];//xgyro
  txt += ", ";
  txt += mean_acc_yaxis[5];//ygyro
  txt += ", ";
  txt += mean_acc_zaxis[5];//zgyro
  txt += ", ";
  txt += angle_yaxis[5];//zgyro
  txt += ", ";
  txt += angle_zaxis[5];//zgyro  
  txt += ", ";
  txt += mean_current[5];// mean current during stride
  txt += ", ";
  txt += max_current[5];// current spike of stride
  txt += ", ";
  //feet success 
  txt += lff_suc[5];
  txt += ", ";
  txt += rff_suc[5];
  txt += ", ";
  txt += rhf_suc[5];
  txt += ", ";
  txt += lhf_suc[5];
  txt += ", ";
  //shoulder success 
  txt += lfs_suc[5];
  txt += ", ";
  txt += rfs_suc[5];
  txt += ", ";
  txt += rhs_suc[5];
  txt += ", ";
  txt += lhs_suc[5];
  txt += ", ";
  //wrist success 
  txt += lfa_suc[5];
  txt += ", ";
  txt += rfa_suc[5];
  txt += ", ";
  txt += lha_suc[5];
  txt += ", ";
  txt += rha_suc[5];
  txt += " \n";  //linebreak

  //Row 8 
//fixed vals 
  txt += robot;
  txt += ", ";
  txt += dynamic;
  txt += ", ";
  txt += speed_val;
  txt += ", ";
  txt += speed_val_foot;
  txt += ", ";
  txt += rom_limb;
  txt += ", ";
  txt += rom_spine;
  txt += ", ";
  txt += rom_feet;
  txt += ", ";
  txt += foot_center;
  txt += ", ";
  txt += front_leg_center;
  txt += ", ";
  txt += hind_leg_center;
  txt += ", ";
  txt += dynamic_wrist_angle;
  txt += ", ";
  txt += front_wrist_angle;
  txt += ", ";
  txt += hind_wrist_angle;
  txt += ", ";
  txt += toe_angle;
  txt += ", ";
  txt += claw_angle;
  txt += ", ";
  txt += surface;
  txt += ", ";
  txt += climb_incline;
  txt += ", ";
  txt += leg_length;
  txt += ", ";
  txt += spine_length;
  txt += ", ";

  txt += stride[6]; //stride
  txt += ", ";
  txt += distance[6]; // dist
  txt += ", ";
  txt += elapsed_time[6]; //time
  txt += ", ";
  txt += mean_acc_xaxis[6];//xgyro
  txt += ", ";
  txt += mean_acc_yaxis[6];//ygyro
  txt += ", ";
  txt += mean_acc_zaxis[6];//zgyro
  txt += ", ";
  txt += angle_yaxis[6];//zgyro
  txt += ", ";
  txt += angle_zaxis[6];//zgyro  
  txt += ", ";
  txt += mean_current[6];// mean current during stride
  txt += ", ";
  txt += max_current[6];// current spike of stride
  txt += ", ";
  //feet success 
  txt += lff_suc[6];
  txt += ", ";
  txt += rff_suc[6];
  txt += ", ";
  txt += rhf_suc[6];
  txt += ", ";
  txt += lhf_suc[6];
  txt += ", ";
  //shoulder success 
  txt += lfs_suc[6];
  txt += ", ";
  txt += rfs_suc[6];
  txt += ", ";
  txt += rhs_suc[6];
  txt += ", ";
  txt += lhs_suc[6];
  txt += ", ";
  //wrist success 
  txt += lfa_suc[6];
  txt += ", ";
  txt += rfa_suc[6];
  txt += ", ";
  txt += lha_suc[6];
  txt += ", ";
  txt += rha_suc[6];
  txt += " \n";  //linebreak

  //Row 9 
//fixed vals 
  txt += robot;
  txt += ", ";
  txt += dynamic;
  txt += ", ";
  txt += speed_val;
  txt += ", ";
  txt += speed_val_foot;
  txt += ", ";
  txt += rom_limb;
  txt += ", ";
  txt += rom_spine;
  txt += ", ";
  txt += rom_feet;
  txt += ", ";
  txt += foot_center;
  txt += ", ";
  txt += front_leg_center;
  txt += ", ";
  txt += hind_leg_center;
  txt += ", ";
  txt += dynamic_wrist_angle;
  txt += ", ";
  txt += front_wrist_angle;
  txt += ", ";
  txt += hind_wrist_angle;
  txt += ", ";
  txt += toe_angle;
  txt += ", ";
  txt += claw_angle;
  txt += ", ";
  txt += surface;
  txt += ", ";
  txt += climb_incline;
  txt += ", ";
  txt += leg_length;
  txt += ", ";
  txt += spine_length;
  txt += ", ";

  txt += stride[7]; //stride
  txt += ", ";
  txt += distance[7]; // dist
  txt += ", ";
  txt += elapsed_time[7]; //time
  txt += ", ";
  txt += mean_acc_xaxis[7];//xgyro
  txt += ", ";
  txt += mean_acc_yaxis[7];//ygyro
  txt += ", ";
  txt += mean_acc_zaxis[7];//zgyro
  txt += ", ";
  txt += angle_yaxis[7];//zgyro
  txt += ", ";
  txt += angle_zaxis[7];//zgyro  
  txt += ", ";
  txt += mean_current[7];// mean current during stride
  txt += ", ";
  txt += max_current[7];// current spike of stride
  txt += ", ";
  //feet success 
  txt += lff_suc[7];
  txt += ", ";
  txt += rff_suc[7];
  txt += ", ";
  txt += rhf_suc[7];
  txt += ", ";
  txt += lhf_suc[7];
  txt += ", ";
  //shoulder success 
  txt += lfs_suc[7];
  txt += ", ";
  txt += rfs_suc[7];
  txt += ", ";
  txt += rhs_suc[7];
  txt += ", ";
  txt += lhs_suc[7];
  txt += ", ";
  //wrist success 
  txt += lfa_suc[7];
  txt += ", ";
  txt += rfa_suc[7];
  txt += ", ";
  txt += lha_suc[7];
  txt += ", ";
  txt += rha_suc[7];
  txt += " \n";  //linebreak

  //Row 10
//fixed vals 
  txt += robot;
  txt += ", ";
  txt += dynamic;
  txt += ", ";
  txt += speed_val;
  txt += ", ";
  txt += speed_val_foot;
  txt += ", ";
  txt += rom_limb;
  txt += ", ";
  txt += rom_spine;
  txt += ", ";
  txt += rom_feet;
  txt += ", ";
  txt += foot_center;
  txt += ", ";
  txt += front_leg_center;
  txt += ", ";
  txt += hind_leg_center;
  txt += ", ";
  txt += dynamic_wrist_angle;
  txt += ", ";
  txt += front_wrist_angle;
  txt += ", ";
  txt += hind_wrist_angle;
  txt += ", ";
  txt += toe_angle;
  txt += ", ";
  txt += claw_angle;
  txt += ", ";
  txt += surface;
  txt += ", ";
  txt += climb_incline;
  txt += ", ";
  txt += leg_length;
  txt += ", ";
  txt += spine_length;
  txt += ", ";

  txt += stride[8]; //stride
  txt += ", ";
  txt += distance[8]; // dist
  txt += ", ";
  txt += elapsed_time[8]; //time
  txt += ", ";
  txt += mean_acc_xaxis[8];//xgyro
  txt += ", ";
  txt += mean_acc_yaxis[8];//ygyro
  txt += ", ";
  txt += mean_acc_zaxis[8];//zgyro
  txt += ", ";
  txt += angle_yaxis[8];//zgyro
  txt += ", ";
  txt += angle_zaxis[8];//zgyro  
  txt += ", ";
  txt += mean_current[8];// mean current during stride
  txt += ", ";
  txt += max_current[8];// current spike of stride
  txt += ", ";
  //feet success 
  txt += lff_suc[8];
  txt += ", ";
  txt += rff_suc[8];
  txt += ", ";
  txt += rhf_suc[8];
  txt += ", ";
  txt += lhf_suc[8];
  txt += ", ";
  //shoulder success 
  txt += lfs_suc[8];
  txt += ", ";
  txt += rfs_suc[8];
  txt += ", ";
  txt += rhs_suc[8];
  txt += ", ";
  txt += lhs_suc[8];
  txt += ", ";
  //wrist success 
  txt += lfa_suc[8];
  txt += ", ";
  txt += rfa_suc[8];
  txt += ", ";
  txt += lha_suc[8];
  txt += ", ";
  txt += rha_suc[8];
  txt += " \n";  //linebreak

  //Row 11 
//fixed vals 
  txt += robot;
  txt += ", ";
  txt += dynamic;
  txt += ", ";
  txt += speed_val;
  txt += ", ";
  txt += speed_val_foot;
  txt += ", ";
  txt += rom_limb;
  txt += ", ";
  txt += rom_spine;
  txt += ", ";
  txt += rom_feet;
  txt += ", ";
  txt += foot_center;
  txt += ", ";
  txt += front_leg_center;
  txt += ", ";
  txt += hind_leg_center;
  txt += ", ";
  txt += dynamic_wrist_angle;
  txt += ", ";
  txt += front_wrist_angle;
  txt += ", ";
  txt += hind_wrist_angle;
  txt += ", ";
  txt += toe_angle;
  txt += ", ";
  txt += claw_angle;
  txt += ", ";
  txt += surface;
  txt += ", ";
  txt += climb_incline;
  txt += ", ";
  txt += leg_length;
  txt += ", ";
  txt += spine_length;
  txt += ", ";

  txt += stride[9]; //stride
  txt += ", ";
  txt += distance[9]; // dist
  txt += ", ";
  txt += elapsed_time[9]; //time
  txt += ", ";
  txt += mean_acc_xaxis[9];//xgyro
  txt += ", ";
  txt += mean_acc_yaxis[9];//ygyro
  txt += ", ";
  txt += mean_acc_zaxis[9];//zgyro
  txt += ", ";
  txt += angle_yaxis[9];//zgyro
  txt += ", ";
  txt += angle_zaxis[9];//zgyro  
  txt += ", ";
  txt += mean_current[9];// mean current during stride
  txt += ", ";
  txt += max_current[9];// current spike of stride
  txt += ", ";
  //feet success 
  txt += lff_suc[9];
  txt += ", ";
  txt += rff_suc[9];
  txt += ", ";
  txt += rhf_suc[9];
  txt += ", ";
  txt += lhf_suc[9];
  txt += ", ";
  //shoulder success 
  txt += lfs_suc[9];
  txt += ", ";
  txt += rfs_suc[9];
  txt += ", ";
  txt += rhs_suc[9];
  txt += ", ";
  txt += lhs_suc[9];
  txt += ", ";
  //wrist success 
  txt += lfa_suc[9];
  txt += ", ";
  txt += rfa_suc[9];
  txt += ", ";
  txt += lha_suc[9];
  txt += ", ";
  txt += rha_suc[9];
  txt += " \n";  //linebreak

  //Row 12 
//fixed vals 
  txt += robot;
  txt += ", ";
  txt += dynamic;
  txt += ", ";
  txt += speed_val;
  txt += ", ";
  txt += speed_val_foot;
  txt += ", ";
  txt += rom_limb;
  txt += ", ";
  txt += rom_spine;
  txt += ", ";
  txt += rom_feet;
  txt += ", ";
  txt += foot_center;
  txt += ", ";
  txt += front_leg_center;
  txt += ", ";
  txt += hind_leg_center;
  txt += ", ";
  txt += dynamic_wrist_angle;
  txt += ", ";
  txt += front_wrist_angle;
  txt += ", ";
  txt += hind_wrist_angle;
  txt += ", ";
  txt += toe_angle;
  txt += ", ";
  txt += claw_angle;
  txt += ", ";
  txt += surface;
  txt += ", ";
  txt += climb_incline;
  txt += ", ";
  txt += leg_length;
  txt += ", ";
  txt += spine_length;
  txt += ", ";

  txt += stride[10]; //stride
  txt += ", ";
  txt += distance[10]; // dist
  txt += ", ";
  txt += elapsed_time[10]; //time
  txt += ", ";
  txt += mean_acc_xaxis[10];//xgyro
  txt += ", ";
  txt += mean_acc_yaxis[10];//ygyro
  txt += ", ";
  txt += mean_acc_zaxis[10];//zgyro
  txt += ", ";
  txt += angle_yaxis[10];//zgyro
  txt += ", ";
  txt += angle_zaxis[10];//zgyro  
  txt += ", ";
  txt += mean_current[10];// mean current during stride
  txt += ", ";
  txt += max_current[10];// current spike of stride
  txt += ", ";
  //feet success 
  txt += lff_suc[10];
  txt += ", ";
  txt += rff_suc[10];
  txt += ", ";
  txt += rhf_suc[10];
  txt += ", ";
  txt += lhf_suc[10];
  txt += ", ";
  //shoulder success 
  txt += lfs_suc[10];
  txt += ", ";
  txt += rfs_suc[10];
  txt += ", ";
  txt += rhs_suc[10];
  txt += ", ";
  txt += lhs_suc[10];
  txt += ", ";
  //wrist success 
  txt += lfa_suc[10];
  txt += ", ";
  txt += rfa_suc[10];
  txt += ", ";
  txt += lha_suc[10];
  txt += ", ";
  txt += rha_suc[10];


  server.send(200, "html/text", txt); 
}
