#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Define Max and Min Pulsewidth of Datan Servo (Feet and Wrist)
#define datan_servo_min 112 //30
#define datan_servo_max 460 //150 degrees

//Define Max and Min Pulsewidth of DSS Servo (Spine and Shoulder)
#define dss_servo_min 468 //30
#define dss_servo_max 242 //150 degrees

//Define Motor Slot Number on PCA9685 (Servo Shield)
const int lff = 4; // Left front foot 
const int lfs = 0; //left front shoulder
const int rfs = 1; //right front shoulder 
const int rff = 5; //right front foot
const int fs = 2; //front spine 
const int hs = 13; //hind spine 
const int rhf = 9; //right hind foot
const int rhs = 14; //right hind shoulder 
const int lhs = 15; //left hind shoulder 
const int lhf = 8; //left hind foot
const int lfa = 6; //Left front Wrist Angle 
const int rfa = 7; //Right Front Wrist Angle 
const int lha = 10; //Left hind Wrist angle 
const int rha = 11; //Right hind Wrist Angle 

//Input Variables for motion 
int rom_spine = 15; //range of motion of spine
int rom_limb = 10; //range of motion of legs 
int rom_feet = 60; //range of motion of feet 
int dynamic = 1; //defines which dynamic to use (1 = sigmoid, 2 = sinusoid) 
int gait = 1;  // defines which gait to use 
int speed_val = 40; //Speed (changes the delay between each increment)
int step_val = 0; //defines how many steps to take (value subtracts from 11) e.g. 11-6 = 5 steps
int foot_angle = 20; //defines the orientation of the foot( + for clockwise angle from axis, - for anticlockwise angle from axis) 
int speed_val_foot = 1; // defines the speed for lifting the feet 

int resolution_dynamic_functions = 50; //increments for the dynamic functions 

//initialize functions 
void move_motor(int motor_num, int angle); //move Servo certain angle 
void home_pos(); //returns all Servos to home position 
int dynamic_movement_spine(int increment);  //dynamic function for spine 
int dynamic_movement_legs(int increment); //dynamic function for legs
int dynamic_movement_feet(int increment); 
void gait1(); //function of gait 1 (Sigmoidal gait)

//Home Positions of Servos
int h_lff = 90; //Front left foot
int h_lfs = 95; //Front left shoulder 
int h_rfs = 98; //Front right shoulder
int h_rff = 86; //Front right foot
int h_fs = 90; //Spine Front
int h_hs = 83; //Spine Hind
int h_rhf = 90; //Hind right foot
int h_rhs = 83; //Hind right shoulder
int h_lhs = 85;  //Hind left shoulder
int h_lhf = 87; //Hind left foot
int h_lfa = 99 + foot_angle; //Front Left Wrist Angle
int h_rfa = 80 + foot_angle; //Front Right Wrist Angle 
int h_lha = 94 + foot_angle; //Hind left Wrist Angle
int h_rha = 90 + foot_angle; //Hind Rigth Wrist Angle


void setup() {
  Serial.begin(115200);
  pwm.begin();
  pwm.setPWMFreq(60);
  Serial.println("Turn Power on");
  delay(1000); 
  //go to home pos 
  home_pos(); 
  Serial.println("Robot in Home Pos.");
  delay(10000); 

}


void loop() {
  if (gait == 1) {
    gait1();
  }
}

void move_motor(int motor_num, int angle){
    
  int pulsewidth; 
  if (3 < motor_num && 13 > motor_num) 
  {
    pulsewidth = map(angle, 30, 150, datan_servo_min, datan_servo_max); 
    pwm.setPWM(motor_num, 0, pulsewidth); 
    // Serial.print("Servo Num Datan: "); 
    // Serial.println(motor_num);
    // Serial.print("Angle: ");   
    // Serial.println(angle); 
  }
  else {
    pulsewidth = map(angle, 30, 150, dss_servo_min, dss_servo_max); 
    pwm.setPWM(motor_num, 0, pulsewidth); 
    // Serial.print("Servo Num DSS: "); 
    // Serial.println(motor_num);
    // Serial.print("Angle: ");   
    // Serial.println(angle); 

  }
}

void gait1(){

  // intial  and ending (half) left starting from and finishing in home position 
    
if (step_val >= 0 || step_val == 13){

  for (int i = 0; i <= resolution_dynamic_functions; i++)
  {
  move_motor(lff, h_lff + dynamic_movement_feet(i)); //lift two across feet
  move_motor(rhf, h_rhf - dynamic_movement_feet(i));
  delay(speed_val_foot); 

  }
    
  for (int i = 0 ; i <= resolution_dynamic_functions; i++) 
  {



    move_motor(fs, h_fs + (0.5 * dynamic_movement_spine(i))); //bend body via spine
    move_motor(hs, h_hs - (0.5 * dynamic_movement_spine(i)));
  
    move_motor(lfs, h_lfs + (0.5 * dynamic_movement_legs(i))); //move front shoulder
    move_motor(rfs, h_rfs + (0.5 * dynamic_movement_legs(i)));

    move_motor(rhs, h_rhs - (0.5 * dynamic_movement_legs(i))); //move back shoulder         
    move_motor(lhs, h_lhs - (0.5 * dynamic_movement_legs(i)));

    // move_motor(lfa, h_lfa + (0.5 * dynamic_movement_legs(i)));  //rotate wrists 
    // move_motor(rfa, h_rfa + (0.5 * dynamic_movement_legs(i)));
    // move_motor(lha, h_lha + (0.5 * dynamic_movement_legs(i)));
    // move_motor(rha, h_rha + (0.5 * dynamic_movement_legs(i)));

    

    
    delay(speed_val);

  } 



    for (int i = 0; i <= resolution_dynamic_functions; i++)
    {

    move_motor(lff, (h_lff + rom_feet) - dynamic_movement_feet(i)); //put feet down
    move_motor(rhf, (h_rhf - rom_feet) + dynamic_movement_feet(i));
    delay(speed_val_foot); 
 
    }
    Serial.println("Done with half step"); 

    if(step_val == 13){ // stopping from continuing half step 
      step_val++; 
    }
    
}


//------------------------------------------------------------------------------------------------------------ Real Gait Big Boy 

  for (step_val ; step_val <= 12; step_val++) //
  {
    
    if (1 <= step_val <= 11)
    { //begins step loop
      
      

      
      //left step 1-11 -------------------------------------------------------------------- LEFT
      for (int i = 0; i < resolution_dynamic_functions; i++)
      {
      move_motor(lhf, h_lhf + dynamic_movement_feet(i)); //lift two across feet
      move_motor(rff, h_rff - dynamic_movement_feet(i));
      delay(speed_val_foot); 
      }

      
      
      for (int i = 0 ; i <= resolution_dynamic_functions; i++) 
      {

       move_motor(fs, (h_fs + rom_spine) - dynamic_movement_spine(i)); //bend body
       move_motor(hs, (h_hs - rom_spine) + dynamic_movement_spine(i));

       move_motor(lfs, (h_lfs + rom_limb) - dynamic_movement_legs(i)); //move frontlegs
       move_motor(rfs, (h_rfs + rom_limb) - dynamic_movement_legs(i));

       move_motor(rhs, (h_rhs - rom_limb) + dynamic_movement_legs(i)); //move backlegs
       move_motor(lhs, (h_lhs - rom_limb) + dynamic_movement_legs(i));
       delay(speed_val); 

      }
      

      

      for (int i = 0; i < resolution_dynamic_functions; i++)
      {
      move_motor(lhf, (h_lhf + rom_feet) - dynamic_movement_feet(i)); //drop feet 
      move_motor(rff, (h_rff - rom_feet) + dynamic_movement_feet(i));
      delay(speed_val_foot); 

      }

      

      Serial.println("Done with left step"); 


      //right step 1-11 --------------------------------------------------------------------- RIGHT

      Serial.println("Starting with right step");


      for (int i = 0; i < resolution_dynamic_functions; i++) 
      { 

      move_motor(lff, h_lff + dynamic_movement_feet(i)); //lift feet 
      move_motor(rhf, h_rhf - dynamic_movement_feet(i));
      delay(speed_val_foot); 
      
      }

      
  

      for (int i = 0; i <= resolution_dynamic_functions; i++) 
      {

        move_motor(fs, (h_fs - rom_spine) + dynamic_movement_spine(i)); //bend body
        move_motor(hs, (h_hs + rom_spine) - dynamic_movement_spine(i));
        
        move_motor(lfs, (h_lfs - rom_limb) + dynamic_movement_legs(i)); //move frontlegs
        move_motor(rfs, (h_rfs - rom_limb) + dynamic_movement_legs(i));

        move_motor(rhs, (h_rhs + rom_limb) - dynamic_movement_legs(i)); //move backlegs
        move_motor(lhs, (h_lhs + rom_limb) - dynamic_movement_legs(i));

        delay(speed_val);

      }

      


      for (int i = 0; i < resolution_dynamic_functions; i++) 
      {
      move_motor(lff, (h_lff + rom_feet) - dynamic_movement_feet(i)); //drop feet
      move_motor(rhf, (h_rhf - rom_feet) + dynamic_movement_feet(i));
      delay(speed_val_foot); 

      }

    Serial.println("Done with right step"); 
    Serial.println(step_val); 

    }
  }
}

void home_pos(){
move_motor(lff, h_lff); //moves all feet to the ground
move_motor(rff, h_rff);
move_motor(lhf, h_lhf);
move_motor(rhf, h_rhf);
  delay(500);
//moves all shoulders into a right angle to the body
move_motor(lfs, h_lfs);
move_motor(rfs, h_rfs);
move_motor(lhs, h_lhs);
move_motor(rhs, h_rhs);
  delay(500);
move_motor(fs, h_fs); //moves the spine in the right angle to the body 
move_motor(hs, h_hs);
  delay(500);
move_motor(lfa, h_lfa); //moves the Wrist Angles into the right angle to the body 
move_motor(rfa, h_rfa);
move_motor(lha, h_lha);
move_motor(rha, h_rha);
  delay(500);
}

int dynamic_movement_spine(int increment){
  int motor_angle; 
  if (dynamic = 1)
  {
    motor_angle = (2 * rom_spine / (1 + exp(-0.2 * increment + 5)));
  }
  if (dynamic == 2){
    motor_angle = (rom_spine * cos((PI/resolution_dynamic_functions) * increment + PI) * rom_spine); 
  }
  return motor_angle; 

}

int dynamic_movement_legs(int increment){ 
  int motor_angle; 

  if (dynamic ==  1) {
    motor_angle = (2 * rom_limb / (1 + exp(-0.2 * increment + 5)));
  }
  if (dynamic == 2){
    motor_angle = (rom_limb * cos((PI/resolution_dynamic_functions) * increment + PI) * rom_limb); 
  }
  return motor_angle; 

}

int dynamic_movement_feet(int increment){
  int motor_angle; 
  if (dynamic == 1){
    motor_angle = (rom_feet / (1 + exp(-0.2 * increment + 5)));
  }
  if (dynamic == 2){
    motor_angle = (rom_feet * cos((PI/resolution_dynamic_functions) * increment + PI) * rom_feet); 
  }
  return motor_angle; 
}