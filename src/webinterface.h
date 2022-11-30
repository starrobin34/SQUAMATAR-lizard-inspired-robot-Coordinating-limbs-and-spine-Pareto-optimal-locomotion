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
void get_data(); 


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

  // html += "<body><h2 style=\"text-align: left;\"><span style=\"text-decoration: underline;\">Live Data:</span></h2>";

  //   //Live Data Table 
  // html += "<table style=\"height: 83px; margin-left: auto; margin-right: auto;\" width=\"727\">";                     
  // html += "<tbody>";
  // html += "<tr style=\"height: 33.875px;\">";                                                                         //row header
  // html += "<td style=\"width: 174px; text-align: center; height: 33.875px;\"><strong>Stride</strong></td>";
  // html += "<td style=\"width: 174px; text-align: center; height: 33.875px;\"><strong>Climbed Distance</strong></td> ";
  // html += "<td style=\"width: 174px; text-align: center; height: 33.875px;\"><strong>Time</strong></td>";
  // html += "<td style=\"width: 175px; text-align: center; height: 33.875px;\"><strong>FL-Feet</strong></td>";
  // html += "<td style=\"width: 176px; text-align: center; height: 33.875px;\"><strong>FR-Feet</strong></td>";
  // html += "<td style=\"width: 176px; text-align: center; height: 33.875px;\"><strong>HR-Feet</strong></td>";
  // html += "<td style=\"width: 176px; text-align: center; height: 33.875px;\"><strong>HL-Feet</strong></td>";
  // html += "<td style=\"width: 174px; text-align: center; height: 33.875px;\"><strong>Y-Gyro</strong></td>";
  // html += "<td style=\"width: 174px; text-align: center; height: 33.875px;\"><strong>Mean Current</strong></td>";
  // html += "<td style=\"width: 176px; text-align: center; height: 33.875px;\"></tr>";

  // //table which displays live sensor data during each run
  // html += "<tr style=\"height: 45px;\"> <td style=\"width: 174px; text-align: center; height: 45px;\">1</td>";                                     //row stride 1
  // html += "<td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r1_0\">";
  // html += distance[0];                                                                                                        //climbed distance entry 1
  // html += "</div></td> <td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r1_1\">";
  // html += ElapsedTime[0];                                                                                                        //Time distance entry 1
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r1_2\">";
  // html += fl_rad[0];                                                                                                        //FL-Feet distance entry 1
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r1_3\">";
  // html += fr_rad[0];                                                                                                        //FR-Feet distance entry 1
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r1_4\">";
  // html += hr_rad[0];                                                                                                        //HR-Feet distance entry 1
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r1_5\">";
  // html += hl_rad[0];                                                                                                        //HL-Feet distance entry 1
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r1_6\">";
  // html += yaxisValue[0];                                                                                                        //Y-Gyro distance entry 1
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r1_7\">";
  // html += mean_current[0];                                                                                                        //c_mean distance entry 1
  // html += "</div></td> </tr>";

  // html += "<tr style=\"height: 45px;\"> <td style=\"width: 174px; text-align: center; height: 45px;\">2</td>";           //row stride 2
  // html += "<td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r2_0\">";
  // html += distance[1];
  // html += "</div></td> <td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r2_1\">";
  // html += ElapsedTime[1];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r2_2\">";
  // html += fl_rad[1];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r2_3\">";
  // html += fr_rad[1];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r2_4\">";
  // html += hr_rad[1];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r2_5\">";
  // html += hl_rad[1];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r2_6\">";
  // html += yaxisValue[1];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r2_7\">";
  // html += mean_current[1];
  // html += "</div></td> </tr>";

  // html += "<tr style=\"height: 45px;\"> <td style=\"width: 174px; text-align: center; height: 45px;\">3</td>";           //row stride 3
  // html += "<td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r3_0\">";
  // html += distance[2];
  // html += "</div></td> <td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r3_1\">";
  // html += ElapsedTime[2];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r3_2\">";
  // html += fl_rad[2];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r3_3\">";
  // html += fr_rad[2];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r3_4\">";
  // html += hr_rad[2];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r3_5\">";
  // html += hl_rad[2];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r3_6\">";
  // html += yaxisValue[2];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r3_7\">";
  // html += mean_current[2];
  // html += "</div></td> </tr>";


  // html += "<tr style=\"height: 45px;\"> <td style=\"width: 174px; text-align: center; height: 45px;\">4</td>";           //row stride 4
  // html += "<td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r4_0\">";
  // html += distance[3];
  // html += "</div></td> <td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r4_1\">";
  // html += ElapsedTime[3];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r4_2\">";
  // html += fl_rad[3];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r4_3\">";
  // html += fr_rad[3];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r4_4\">";
  // html += hr_rad[3];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r4_5\">";
  // html += hl_rad[3];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r4_6\">";
  // html += yaxisValue[3];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r4_7\">";
  // html += mean_current[3];
  // html += "</div></td> </tr>";


  // html += "<tr style=\"height: 45px;\"> <td style=\"width: 174px; text-align: center; height: 45px;\">5</td>";           //row stride 5
  // html += "<td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r5_0\">";
  // html += distance[4];
  // html += "</div></td> <td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r5_1\">";
  // html += ElapsedTime[4];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r5_2\">";
  // html += fl_rad[4];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r5_3\">";
  // html += fr_rad[4];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r5_4\">";
  // html += hr_rad[4];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r5_5\">";
  // html += hl_rad[4];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r5_6\">";
  // html += yaxisValue[4];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r5_7\">";
  // html += mean_current[4];
  // html += "</div></td> </tr>";

  // html += "<tr style=\"height: 45px;\"> <td style=\"width: 174px; text-align: center; height: 45px;\">6</td>";           //row stride 6
  // html += "<td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r6_0\">";
  // html += distance[5];
  // html += "</div></td> <td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r6_1\">";
  // html += ElapsedTime[5];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r6_2\">";
  // html += fl_rad[5];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r6_3\">";
  // html += fr_rad[5];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r6_4\">";
  // html += hr_rad[5];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r6_5\">";
  // html += hl_rad[5];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r6_6\">";
  // html += yaxisValue[5];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r6_7\">";
  // html += mean_current[5];
  // html += "</div></td> </tr>";


  // html += "<tr style=\"height: 45px;\"> <td style=\"width: 174px; text-align: center; height: 45px;\">7</td>";           //row stride 7
  // html += "<td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r7_0\">";
  // html += distance[6];
  // html += "</div></td> <td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r7_1\">";
  // html += ElapsedTime[6];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r7_2\">";
  // html += fl_rad[6];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r7_3\">";
  // html += fr_rad[6];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r7_4\">";
  // html += hr_rad[6];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r7_5\">";
  // html += hl_rad[6];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r7_6\">";
  // html += yaxisValue[6];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r7_7\">";
  // html += mean_current[6];
  // html += "</div></td> </tr>";


  // html += "<tr style=\"height: 45px;\"> <td style=\"width: 174px; text-align: center; height: 45px;\">8</td>";           //row stride 8
  // html += "<td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r8_0\">";
  // html += distance[7];
  // html += "</div></td> <td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r8_1\">";
  // html += ElapsedTime[7];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r8_2\">";
  // html += fl_rad[7];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r8_3\">";
  // html += fr_rad[7];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r8_4\">";
  // html += hr_rad[7];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r8_5\">";
  // html += hl_rad[7];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r8_6\">";
  // html += yaxisValue[7];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r8_7\">";
  // html += mean_current[7];
  // html += "</div></td> </tr>";


  // html += "<tr style=\"height: 45px;\"> <td style=\"width: 174px; text-align: center; height: 45px;\">9</td>";           //row stride 9
  // html += "<td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r9_0\">";
  // html += distance[8];
  // html += "</div></td> <td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r9_1\">";
  // html += ElapsedTime[8];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r9_2\">";
  // html += fl_rad[8];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r9_3\">";
  // html += fr_rad[8];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r9_4\">";
  // html += hr_rad[8];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r9_5\">";
  // html += hl_rad[8];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r9_6\">";
  // html += yaxisValue[8];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r9_7\">";
  // html += mean_current[8];
  // html += "</div></td> </tr>";

  // html += "<tr style=\"height: 45px;\"> <td style=\"width: 174px; text-align: center; height: 45px;\">10</td>";           //row stride 10
  // html += "<td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r10_0\">";
  // html += distance[9];
  // html += "</div></td> <td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r10_1\">";
  // html += ElapsedTime[9];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r10_2\">";
  // html += fl_rad[9];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r10_3\">";
  // html += fr_rad[9];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r10_4\">";
  // html += hr_rad[9];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r10_5\">";
  // html += hl_rad[9];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r10_6\">";
  // html += yaxisValue[9];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r10_7\">";
  // html += mean_current[9];
  // html += "</div></td> </tr>";

  // html += "<tr style=\"height: 45px;\"> <td style=\"width: 174px; text-align: center; height: 45px;\">11</td>";           //row stride 11
  // html += "<td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r11_0\">";
  // html += distance[10];
  // html += "</div></td> <td style=\"width: 174px; text-align: center; height: 45px;\"><div id=\"r11_1\">";
  // html += ElapsedTime[10];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r11_2\">";
  // html += fl_rad[10];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r11_3\">";
  // html += fr_rad[10];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r11_4\">";
  // html += hr_rad[10];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r11_5\">";
  // html += hl_rad[10];
  // html += "</div></td> <td style=\"width: 176px; text-align: center; height: 45px;\"<div id=\"r11_6\">";
  // html += yaxisValue[10];
  // html += "</div></td> <td style=\"width: 175px; text-align: center; height: 45px;\"<div id=\"r11_7\">";
  // html += mean_current[10];
  // html += "</div></td> </tr>";
  // html += "</tbody> </table></div><BR>";     

  
  // //UPDATE RATE button:
  // html += " <a onClick=\"changeView()\" class=\"convertButton\" id=\"viewButton\">Update Rate</a> <div id=\"dataVals\"> </div> </div> <div id=\"updateView\"> <label for=\"fader\">Update rate in Milliseconds</label><br /> ";
  // html += "<input type=\"range\" style=\"width: 300px\" min=\"200\" max=\"5000\" value=\"2000\" id=\"fader\" step=\"1\" oninput=\"outputUpdate(value)\"> <output for=\"fader\" id=\"volume\">2000</output></div> <script> var changed = false; function changeView(){ if(changed == false){ document.getElementById('updateView').style.display = 'block'; ";
  // html += "document.getElementById('dataVals').style.display = 'none'; document.getElementById('viewButton').innerHTML = \"Show Data\"; changed = true; } else{ document.getElementById('updateView').style.display = 'none'; document.getElementById('dataVals').style.display = 'block'; document.getElementById('viewButton').innerHTML = \"Update Rate\"; changed = false; } } function loadDoc() { ";
  // html += "var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = function() { if (this.readyState == 4 && this.status == 200) { var obj = JSON.parse(this.responseText);";

  // //Parsing JSON-Array with positions in table
  // html += "document.getElementById(\"r1_0\").innerHTML = obj.data[0].dataValue;";
  // html += "document.getElementById(\"r1_1\").innerHTML = obj.data[1].dataValue;";
  // html += "document.getElementById(\"r1_2\").innerHTML = obj.data[2].dataValue;";
  // html += "document.getElementById(\"r1_3\").innerHTML = obj.data[3].dataValue;";
  // html += "document.getElementById(\"r1_4\").innerHTML = obj.data[4].dataValue;";
  // html += "document.getElementById(\"r1_5\").innerHTML = obj.data[5].dataValue;";
  // html += "document.getElementById(\"r1_6\").innerHTML = obj.data[6].dataValue;";
  // html += "document.getElementById(\"r1_7\").innerHTML = obj.data[7].dataValue;";

  // html += "document.getElementById(\"r2_0\").innerHTML = obj.data[8].dataValue;";
  // html += "document.getElementById(\"r2_1\").innerHTML = obj.data[9].dataValue;";
  // html += "document.getElementById(\"r2_2\").innerHTML = obj.data[10].dataValue;";
  // html += "document.getElementById(\"r2_3\").innerHTML = obj.data[11].dataValue;";
  // html += "document.getElementById(\"r2_4\").innerHTML = obj.data[12].dataValue;";
  // html += "document.getElementById(\"r2_5\").innerHTML = obj.data[13].dataValue;";
  // html += "document.getElementById(\"r2_6\").innerHTML = obj.data[14].dataValue;";
  // html += "document.getElementById(\"r2_7\").innerHTML = obj.data[15].dataValue;";

  // html += "document.getElementById(\"r3_0\").innerHTML = obj.data[16].dataValue;";
  // html += "document.getElementById(\"r3_1\").innerHTML = obj.data[17].dataValue;";
  // html += "document.getElementById(\"r3_2\").innerHTML = obj.data[18].dataValue;";
  // html += "document.getElementById(\"r3_3\").innerHTML = obj.data[19].dataValue;";
  // html += "document.getElementById(\"r3_4\").innerHTML = obj.data[20].dataValue;";
  // html += "document.getElementById(\"r3_5\").innerHTML = obj.data[21].dataValue;";
  // html += "document.getElementById(\"r3_6\").innerHTML = obj.data[22].dataValue;";
  // html += "document.getElementById(\"r3_7\").innerHTML = obj.data[23].dataValue;";


  // html += "document.getElementById(\"r4_0\").innerHTML = obj.data[24].dataValue;";
  // html += "document.getElementById(\"r4_1\").innerHTML = obj.data[25].dataValue;";
  // html += "document.getElementById(\"r4_2\").innerHTML = obj.data[26].dataValue;";
  // html += "document.getElementById(\"r4_3\").innerHTML = obj.data[27].dataValue;";
  // html += "document.getElementById(\"r4_4\").innerHTML = obj.data[28].dataValue;";
  // html += "document.getElementById(\"r4_5\").innerHTML = obj.data[29].dataValue;";
  // html += "document.getElementById(\"r4_6\").innerHTML = obj.data[30].dataValue;";
  // html += "document.getElementById(\"r4_7\").innerHTML = obj.data[31].dataValue;";


  // html += "document.getElementById(\"r5_0\").innerHTML = obj.data[32].dataValue;";
  // html += "document.getElementById(\"r5_1\").innerHTML = obj.data[33].dataValue;";
  // html += "document.getElementById(\"r5_2\").innerHTML = obj.data[34].dataValue;";
  // html += "document.getElementById(\"r5_3\").innerHTML = obj.data[35].dataValue;";
  // html += "document.getElementById(\"r5_4\").innerHTML = obj.data[36].dataValue;";
  // html += "document.getElementById(\"r5_5\").innerHTML = obj.data[37].dataValue;";
  // html += "document.getElementById(\"r5_6\").innerHTML = obj.data[38].dataValue;";
  // html += "document.getElementById(\"r5_7\").innerHTML = obj.data[39].dataValue;";


  // html += "document.getElementById(\"r6_0\").innerHTML = obj.data[40].dataValue;";
  // html += "document.getElementById(\"r6_1\").innerHTML = obj.data[41].dataValue;";
  // html += "document.getElementById(\"r6_2\").innerHTML = obj.data[42].dataValue;";
  // html += "document.getElementById(\"r6_3\").innerHTML = obj.data[43].dataValue;";
  // html += "document.getElementById(\"r6_4\").innerHTML = obj.data[44].dataValue;";
  // html += "document.getElementById(\"r6_5\").innerHTML = obj.data[45].dataValue;";
  // html += "document.getElementById(\"r6_6\").innerHTML = obj.data[46].dataValue;";
  // html += "document.getElementById(\"r6_7\").innerHTML = obj.data[47].dataValue;";


  // html += "document.getElementById(\"r7_0\").innerHTML = obj.data[48].dataValue;";
  // html += "document.getElementById(\"r7_1\").innerHTML = obj.data[49].dataValue;";
  // html += "document.getElementById(\"r7_2\").innerHTML = obj.data[50].dataValue;";
  // html += "document.getElementById(\"r7_3\").innerHTML = obj.data[51].dataValue;";
  // html += "document.getElementById(\"r7_4\").innerHTML = obj.data[52].dataValue;";
  // html += "document.getElementById(\"r7_5\").innerHTML = obj.data[53].dataValue;";
  // html += "document.getElementById(\"r7_6\").innerHTML = obj.data[54].dataValue;";
  // html += "document.getElementById(\"r7_7\").innerHTML = obj.data[55].dataValue;";


  // html += "document.getElementById(\"r8_0\").innerHTML = obj.data[56].dataValue;";
  // html += "document.getElementById(\"r8_1\").innerHTML = obj.data[57].dataValue;";
  // html += "document.getElementById(\"r8_2\").innerHTML = obj.data[58].dataValue;";
  // html += "document.getElementById(\"r8_3\").innerHTML = obj.data[59].dataValue;";
  // html += "document.getElementById(\"r8_4\").innerHTML = obj.data[60].dataValue;";
  // html += "document.getElementById(\"r8_5\").innerHTML = obj.data[61].dataValue;";
  // html += "document.getElementById(\"r8_6\").innerHTML = obj.data[62].dataValue;";
  // html += "document.getElementById(\"r8_7\").innerHTML = obj.data[63].dataValue;";


  // html += "document.getElementById(\"r9_0\").innerHTML = obj.data[64].dataValue;";
  // html += "document.getElementById(\"r9_1\").innerHTML = obj.data[65].dataValue;";
  // html += "document.getElementById(\"r9_2\").innerHTML = obj.data[66].dataValue;";
  // html += "document.getElementById(\"r9_3\").innerHTML = obj.data[67].dataValue;";
  // html += "document.getElementById(\"r9_4\").innerHTML = obj.data[68].dataValue;";
  // html += "document.getElementById(\"r9_5\").innerHTML = obj.data[69].dataValue;";
  // html += "document.getElementById(\"r9_6\").innerHTML = obj.data[70].dataValue;";
  // html += "document.getElementById(\"r9_7\").innerHTML = obj.data[71].dataValue;";


  // html += "document.getElementById(\"r10_0\").innerHTML = obj.data[72].dataValue;";
  // html += "document.getElementById(\"r10_1\").innerHTML = obj.data[73].dataValue;";
  // html += "document.getElementById(\"r10_2\").innerHTML = obj.data[74].dataValue;";
  // html += "document.getElementById(\"r10_3\").innerHTML = obj.data[75].dataValue;";
  // html += "document.getElementById(\"r10_4\").innerHTML = obj.data[76].dataValue;";
  // html += "document.getElementById(\"r10_5\").innerHTML = obj.data[77].dataValue;";
  // html += "document.getElementById(\"r10_6\").innerHTML = obj.data[78].dataValue;";
  // html += "document.getElementById(\"r10_7\").innerHTML = obj.data[79].dataValue;";



  // html += "document.getElementById(\"r11_0\").innerHTML = obj.data[80].dataValue;";
  // html += "document.getElementById(\"r11_1\").innerHTML = obj.data[81].dataValue;";
  // html += "document.getElementById(\"r11_2\").innerHTML = obj.data[82].dataValue;";
  // html += "document.getElementById(\"r11_3\").innerHTML = obj.data[83].dataValue;";
  // html += "document.getElementById(\"r11_4\").innerHTML = obj.data[84].dataValue;";
  // html += "document.getElementById(\"r11_5\").innerHTML = obj.data[85].dataValue;";
  // html += "document.getElementById(\"r11_6\").innerHTML = obj.data[86].dataValue;";
  // html += "document.getElementById(\"r11_7\").innerHTML = obj.data[87].dataValue;";

  // html += "} }; xhttp.open(\"POST\", \"/data\", true); xhttp.send(); ";
  // html += "} var timedEvent = setInterval(function(){ loadDoc(); }, 2000); function outputUpdate(vol) { clearInterval(timedEvent); timedEvent = setInterval(function(){ loadDoc(); }, vol); document.querySelector('#volume').value = vol; delayVal = vol; } </script> </body>";






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


         

      

  //  test test test 
       

  //if live data probably better here 
      if (gait == 1) //maybe in function handle root ? 
    {
      Serial.println("Starting Gait 1"); 
      gait1();
    }

    }
    }
}

void get_data(){

// String data = "{\"data\":[";   //JSON Array which is called to refresh handleRobot()-html in the background
//   data += "{\"dataValue\":\"";
//   data += distance[0]; // table content line 1
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += ElapsedTime[0];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fl_rad[0];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fr_rad[0];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hr_rad[0];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hl_rad[0];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += yaxisValue[0];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += mean_current[0];
//   data += "\"},";

//   data += "{\"dataValue\":\"";
//   data += distance[1]; // table content line 2
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += ElapsedTime[1];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fl_rad[1];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fr_rad[1];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hr_rad[1];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hl_rad[1];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += yaxisValue[1];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += mean_current[1];
//   data += "\"},";

//   data += "{\"dataValue\":\"";
//   data += distance[2]; // table content line 3
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += ElapsedTime[2];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fl_rad[2];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fr_rad[2];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hr_rad[2];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hl_rad[2];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += yaxisValue[2];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += mean_current[2];
//   data += "\"},";

//   data += "{\"dataValue\":\"";
//   data += distance[3]; // table content line 4
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += ElapsedTime[3];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fl_rad[3];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fr_rad[3];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hr_rad[3];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hl_rad[3];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += yaxisValue[3];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += mean_current[3];
//   data += "\"},";

//   data += "{\"dataValue\":\"";
//   data += distance[4]; // table content line 5
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += ElapsedTime[4];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fl_rad[4];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fr_rad[4];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hr_rad[4];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hl_rad[4];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += yaxisValue[4];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += mean_current[4];
//   data += "\"},";

//   data += "{\"dataValue\":\"";
//   data += distance[5]; // table content line 6
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += ElapsedTime[5];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fl_rad[5];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fr_rad[5];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hr_rad[5];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hl_rad[5];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += yaxisValue[5];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += mean_current[5];
//   data += "\"},";

//   data += "{\"dataValue\":\"";
//   data += distance[6]; // table content line 7
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += ElapsedTime[6];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fl_rad[6];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fr_rad[6];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hr_rad[6];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hl_rad[6];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += yaxisValue[6];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += mean_current[6];
//   data += "\"},";

//   data += "{\"dataValue\":\"";
//   data += distance[7]; // table content line 8
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += ElapsedTime[7];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fl_rad[7];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fr_rad[7];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hr_rad[7];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hl_rad[7];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += yaxisValue[7];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += mean_current[7];
//   data += "\"},";

//   data += "{\"dataValue\":\"";
//   data += distance[8]; // table content line 9
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += ElapsedTime[8];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fl_rad[8];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fr_rad[8];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hr_rad[8];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hl_rad[8];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += yaxisValue[8];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += mean_current[8];
//   data += "\"},";

//   data += "{\"dataValue\":\"";
//   data += distance[9]; // table content line 10
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += ElapsedTime[9];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fl_rad[9];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fr_rad[9];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hr_rad[9];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hl_rad[9];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += yaxisValue[9];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += mean_current[9];
//   data += "\"},";

//   data += "{\"dataValue\":\"";
//   data += distance[10]; // table content line 11
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += ElapsedTime[10];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fl_rad[10];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += fr_rad[10];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hr_rad[10];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += hl_rad[10];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += yaxisValue[10];
//   data += "\"},";
//   data += "{\"dataValue\":\"";
//   data += mean_current[10];

  
//   data += "\"}";
//   data += "]}";
//   server.send(200, "text/html", data);
//   Serial.println("data: ");
//   Serial.println(data);
    
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
  txt += "Distance in m";
  txt += ", ";
  txt += "Time in s";
  txt += ", ";
  txt += "X_Gyro_degrees/s";
  txt += ", ";
  txt += "Y_Gyro_degrees/s";
  txt += ", ";
  txt += "Z_Gyro_degrees/s";
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
  txt += xaxis_val[0];//xgyro
  txt += ", ";
  txt += yaxis_val[0];//ygyro
  txt += ", ";
  txt += zaxis_val[0];//zgyro
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
  txt += xaxis_val[1];//xgyro
  txt += ", ";
  txt += yaxis_val[1];//ygyro
  txt += ", ";
  txt += zaxis_val[1];//zgyro
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
  txt += xaxis_val[2];//xgyro
  txt += ", ";
  txt += yaxis_val[2];//ygyro
  txt += ", ";
  txt += zaxis_val[2];//zgyro
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
  txt += xaxis_val[3];//xgyro
  txt += ", ";
  txt += yaxis_val[3];//ygyro
  txt += ", ";
  txt += zaxis_val[3];//zgyro
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
  txt += xaxis_val[4];//xgyro
  txt += ", ";
  txt += yaxis_val[4];//ygyro
  txt += ", ";
  txt += zaxis_val[4];//zgyro
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
  txt += xaxis_val[5];//xgyro
  txt += ", ";
  txt += yaxis_val[5];//ygyro
  txt += ", ";
  txt += zaxis_val[5];//zgyro
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
  txt += xaxis_val[6];//xgyro
  txt += ", ";
  txt += yaxis_val[6];//ygyro
  txt += ", ";
  txt += zaxis_val[6];//zgyro
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
  txt += xaxis_val[7];//xgyro
  txt += ", ";
  txt += yaxis_val[7];//ygyro
  txt += ", ";
  txt += zaxis_val[7];//zgyro
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
  txt += xaxis_val[8];//xgyro
  txt += ", ";
  txt += yaxis_val[8];//ygyro
  txt += ", ";
  txt += zaxis_val[8];//zgyro
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
  txt += xaxis_val[9];//xgyro
  txt += ", ";
  txt += yaxis_val[9];//ygyro
  txt += ", ";
  txt += zaxis_val[9];//zgyro
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
  txt += xaxis_val[10];//xgyro
  txt += ", ";
  txt += yaxis_val[10];//ygyro
  txt += ", ";
  txt += zaxis_val[10];//zgyro
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
  // txt += " \n";  //linebreak

  server.send(200, "html/text", txt);
}

// void start_robot(){
//     Serial.println("Start Button pressed"); 
//     start_run = true; 
// }