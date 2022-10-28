/* 
  this File contains all Variables and functions for the Servo movement and the gaits 
*/

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>


//Define Max and Min Pulsewidth of Datan Servo (Feet and Wrist)
#define datan_servo_min 112 //30
#define datan_servo_max 460 //150 degrees
//Define the max and min Signal for feedback of Datan Servo 
// #define datan_feedback_min 545
// #define datan_feedback_max 2496

//Define Max and Min Pulsewidth of DSS Servo (Spine and Shoulder)
#define dss_servo_min 468 //30
#define dss_servo_max 242 //150 degrees
//Define the max and min Signal for feedback of DSS Servo 
// #define dss_feedback_min 3069f_s
// #define dss_feedback_max 1280

//Define Motor Slot Number on PCA9685 (Servo Shield)
const int lff = 4; // Left front foot 
const int lfs = 0; //left front shoulder
const int rfs = 1; //right front shoulder 
const int rff = 5; //right front footconst 
const int f_s = 2; //front spine 
const int h_s = 13; //hind spine 
const int rhf = 9; //right hind foot
const int rhs = 14; //right hind shoulder 
const int lhs = 15; //left hind shoulder 
const int lhf = 8; //left hind foot
const int lfa = 6; //Left front Wrist Angle 
const int rfa = 7; //Right Front Wrist Angle 
const int lha = 10; //Left hind Wrist angle 
const int rha = 11; //Right hind Wrist Angle 

//Input Variables for motion --> adjustable in web interface  
int rom_spine = 10; //range of motion of spine
int rom_limb = 10; //range of motion of legs 
int rom_feet = 75; //range of motion of feet 
int dynamic = 1; //defines which dynamic to use (1 = sigmoid, 2 = sinusoid) 
int gait = 0;  // defines which gait to use (0, no gait, 1 = regular gait, 2 turn gait (NOT YET IMPLEMENTED)) 
int speed_val = 5000; //Speed of leg and spine (changes the delay between each increment in microseconds)
int speed_val_foot = 1000; // defines the speed for lifting the feet (changes the delay between each increment in microseconds)
int step_val = 8; //defines how many steps to take (value subtracts from 11) e.g. 11-6 = 5 steps
int foot_angle_offset = 0; //defines the offset of the angle of the feet to the vertical to the ground axis 
int front_wrist_angle = 0; //defines the orientation of the front foot( + for positive angle from axis, - for negative angle from axis) 
int hind_wrist_angle = 0; //defines the orientation of the hind foot ( + for positive angle from axis, - for negative angle from axis) 
int dynamic_wrist_angle = 1; //defines if dynamically counteracting Wrist angle is used (0 = not used, 1 = counteracting by angle,  2 = counteracting by reading analog pins (NOT YET IMPLEMENTED)) 
int rom_wrist_angle = rom_spine + rom_limb; 

//Input Variables for motion (not adjustable in web interface) 
int resolution_dynamic_functions = 400; //increments for the dynamic functions 


unsigned long ElapsedTime[11] =  {0};

//function prototypes 
void move_motor(int motor_num, int angle); //move Servo certain angle 
void home_pos(); //returns all Servos to home position  
int dynamic_movement_spine(int increment);  //dynamic function for spine 
int dynamic_movement_legs(int increment); //dynamic function for legs
int dynamic_movement_feet(int increment); 
void gait1(); //function of gait 1 (Sigmoidal gait)

//Home Positions of Servos
const int h_lff = 90; //Front left foot
const int h_lfs = 95; //Front left shoulder 
const int h_rfs = 98; //Front right shoulder
const int h_rff = 86; //Front right foot
const int h_fs = 93; //Spine Front
const int h_hs = 94; //Spine Hind
const int h_rhf = 90 + foot_angle_offset; //Hind right foot
const int h_rhs = 76 - foot_angle_offset; //Hind right shoulder
const int h_lhs = 82 + foot_angle_offset;  //Hind left shoulder
const int h_lhf = 87 - foot_angle_offset; //Hind left foot
const int h_lfa = 100 + front_wrist_angle; //Front Left Wrist Angle
const int h_rfa = 80 - front_wrist_angle; //Front Right Wrist Angle 
const int h_lha = 94 + hind_wrist_angle; //Hind left Wrist Angle
const int h_rha = 87 -  hind_wrist_angle; //Hind Rigth Wrist Angle

//Variables for measurements 


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


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

void gait1(){ //gait for lizard like forward movement 

  // intial  (half) right step starting from home position 
    
  for (int i = 0; i <= resolution_dynamic_functions; i++)
  {
  move_motor(lff, h_lff + dynamic_movement_feet(i)); //lift two across feet
  move_motor(rhf, h_rhf - dynamic_movement_feet(i));
  delayMicroseconds(speed_val_foot); 

  }
    
  for (int i = 0 ; i <= resolution_dynamic_functions; i++) 
  {



    move_motor(f_s, h_fs + (0.5 * dynamic_movement_spine(i))); //bend body via spine
    move_motor(h_s, h_hs - (0.5 * dynamic_movement_spine(i)));
  
    move_motor(lfs, h_lfs + (0.5 * dynamic_movement_legs(i))); //move front shoulder
    move_motor(rfs, h_rfs + (0.5 * dynamic_movement_legs(i)));

    move_motor(rhs, h_rhs - (0.5 * dynamic_movement_legs(i))); //move back shoulder         
    move_motor(lhs, h_lhs - (0.5 * dynamic_movement_legs(i)));

     
    if (dynamic_wrist_angle == 1)
    {
    move_motor(lfa, h_lfa + (0.5 * dynamic_movement_legs(i)) + (0.5 * dynamic_movement_spine(i)));  //rotate wrists 
    move_motor(rfa, h_rfa + (0.5 * dynamic_movement_legs(i)) + (0.5 * dynamic_movement_spine(i)));
    move_motor(lha, h_lha - ((0.5 * dynamic_movement_legs(i)) + (0.5 * dynamic_movement_spine(i))));
    move_motor(rha, h_rha - ((0.5 * dynamic_movement_legs(i)) + (0.5 * dynamic_movement_spine(i))));
    }
     
     
    delayMicroseconds(speed_val);

  } 


    for (int i = 0; i <= resolution_dynamic_functions; i++)
    {

    move_motor(lff, (h_lff + rom_feet) - dynamic_movement_feet(i)); //put feet down
    move_motor(rhf, (h_rhf - rom_feet) + dynamic_movement_feet(i));
    delayMicroseconds(speed_val_foot); 
 
    }

    Serial.println("Done with half right step"); 


//------------------------------------------------------------------------------------------------------------ Real Gait 

  unsigned long start_time = millis(); 

  for (step_val ; step_val <= 12; step_val++) //
  {
    
    if (1 <= step_val <= 11)
    { //begins step loop
      
      ElapsedTime[step_val] = millis() - start_time;  
      

      
      //left step 1-11 -------------------------------------------------------------------- LEFT
      for (int i = 0; i < resolution_dynamic_functions; i++)
      {
      move_motor(lhf, h_lhf + dynamic_movement_feet(i)); //lift two across feet
      move_motor(rff, h_rff - dynamic_movement_feet(i));
      delayMicroseconds(speed_val_foot); 
      }

      
      
      for (int i = 0 ; i <= resolution_dynamic_functions; i++) 
      {

       move_motor(f_s, (h_fs + rom_spine) - dynamic_movement_spine(i)); //bend body
       move_motor(h_s, (h_hs - rom_spine) + dynamic_movement_spine(i));

       move_motor(lfs, (h_lfs + rom_limb) - dynamic_movement_legs(i)); //move frontlegs
       move_motor(rfs, (h_rfs + rom_limb) - dynamic_movement_legs(i));

       move_motor(rhs, (h_rhs - rom_limb) + dynamic_movement_legs(i)); //move backlegs
       move_motor(lhs, (h_lhs - rom_limb) + dynamic_movement_legs(i));

        if (dynamic_wrist_angle == 1)
        {
        move_motor(lfa, h_lfa + (rom_spine - dynamic_movement_legs(i)) + (rom_limb - dynamic_movement_spine(i)));  //rotate wrists 
        move_motor(rfa, h_rfa + (rom_spine - dynamic_movement_legs(i)) + (rom_limb - dynamic_movement_spine(i)));
        move_motor(lha, h_lha + (-rom_spine + dynamic_movement_legs(i)) + (-rom_limb + dynamic_movement_spine(i)));
        move_motor(rha, h_rha + (-rom_spine + dynamic_movement_legs(i)) + (-rom_limb + dynamic_movement_spine(i)));


        // Serial.println(h_rfa + (rom_spine - dynamic_movement_legs(i)) + (rom_limb - dynamic_movement_spine(i))); 
        }

       delayMicroseconds(speed_val); 

      }
      

      

      for (int i = 0; i < resolution_dynamic_functions; i++)
      {
      move_motor(lhf, (h_lhf + rom_feet) - dynamic_movement_feet(i)); //drop feet 
      move_motor(rff, (h_rff - rom_feet) + dynamic_movement_feet(i));
      delayMicroseconds(speed_val_foot); 

      }

      

      Serial.println("Done with left step"); 


      //right step 1-11 --------------------------------------------------------------------- RIGHT

      Serial.println("Starting with right step");


      for (int i = 0; i < resolution_dynamic_functions; i++) 
      { 

      move_motor(lff, h_lff + dynamic_movement_feet(i)); //lift feet 
      move_motor(rhf, h_rhf - dynamic_movement_feet(i));
      delayMicroseconds(speed_val_foot); 
      
      }

      
  

      for (int i = 0; i <= resolution_dynamic_functions; i++) 
      {

        move_motor(f_s, (h_fs - rom_spine) + dynamic_movement_spine(i)); //bend body
        move_motor(h_s, (h_hs + rom_spine) - dynamic_movement_spine(i));
        
        move_motor(lfs, (h_lfs - rom_limb) + dynamic_movement_legs(i)); //move frontlegs
        move_motor(rfs, (h_rfs - rom_limb) + dynamic_movement_legs(i));

        move_motor(rhs, (h_rhs + rom_limb) - dynamic_movement_legs(i)); //move backlegs
        move_motor(lhs, (h_lhs + rom_limb) - dynamic_movement_legs(i));

        if (dynamic_wrist_angle == 1)
        {
        move_motor(lfa, h_lfa + (-rom_spine + dynamic_movement_legs(i)) + (-rom_limb + dynamic_movement_spine(i)));  //rotate wrists 
        move_motor(rfa, h_rfa + (-rom_spine + dynamic_movement_legs(i)) + (-rom_limb + dynamic_movement_spine(i)));
        move_motor(lha, h_lha + (rom_spine - dynamic_movement_legs(i)) + (rom_limb - dynamic_movement_spine(i)));
        move_motor(rha, h_rha + (rom_spine - dynamic_movement_legs(i)) + (rom_limb - dynamic_movement_spine(i)));
      
        // Serial.println(h_rfa + (-rom_spine + dynamic_movement_legs(i)) + (-rom_limb + dynamic_movement_spine(i))); 
        }


        delayMicroseconds(speed_val);

      }

      


      for (int i = 0; i < resolution_dynamic_functions; i++) 
      {
      move_motor(lff, (h_lff + rom_feet) - dynamic_movement_feet(i)); //drop feet
      move_motor(rhf, (h_rhf - rom_feet) + dynamic_movement_feet(i));
      delayMicroseconds(speed_val_foot); 

      }

    Serial.println("Done with right step"); 
    Serial.println(step_val); 

    }
  }

    // final (half) leftstep to get into home position
    
  for (int i = 0; i <= resolution_dynamic_functions; i++)
  {
  move_motor(lhf, h_lhf + dynamic_movement_feet(i)); //lift two across feet
  move_motor(rff, h_rff - dynamic_movement_feet(i));
  delayMicroseconds(speed_val_foot); 

  }
    
  for (int i = 0 ; i <= resolution_dynamic_functions; i++) 
  {



    move_motor(f_s, (h_fs + rom_spine) - (0.5 * dynamic_movement_spine(i))); //bend body via spine
    move_motor(h_s, (h_hs - rom_spine) + (0.5 * dynamic_movement_spine(i)));
  
    move_motor(lfs, (h_lfs + rom_limb) - (0.5 * dynamic_movement_legs(i))); //move front shoulder
    move_motor(rfs, (h_rfs + rom_limb) - (0.5 * dynamic_movement_legs(i)));

    move_motor(rhs, (h_rhs - rom_limb) + (0.5 * dynamic_movement_legs(i))); //move back shoulder         
    move_motor(lhs, (h_lhs - rom_limb) + (0.5 * dynamic_movement_legs(i)));
     
    if (dynamic_wrist_angle == 1)
    {
    move_motor(lfa, h_lfa + (rom_spine - 0.5 * dynamic_movement_legs(i)) + (rom_limb - 0.5 * dynamic_movement_spine(i)));  //rotate wrists 
    move_motor(rfa, h_rfa + (rom_spine - 0.5 * dynamic_movement_legs(i)) + (rom_limb - 0.5 * dynamic_movement_spine(i)));
    move_motor(lha, h_lha + (-rom_spine + 0.5 * dynamic_movement_legs(i)) + (-rom_limb + 0.5 * dynamic_movement_spine(i)));
    move_motor(rha, h_rha + (-rom_spine + 0.5 * dynamic_movement_legs(i)) + (-rom_limb + 0.5 * dynamic_movement_spine(i)));
    }
     
     
    delayMicroseconds(speed_val);

  } 


    for (int i = 0; i <= resolution_dynamic_functions; i++)
    {
    move_motor(lhf, (h_lhf + rom_feet) - dynamic_movement_feet(i)); //drop feet 
    move_motor(rff, (h_rff - rom_feet) + dynamic_movement_feet(i));
    delayMicroseconds(speed_val_foot); 
    }

    Serial.println("Done with final half step"); 
    Serial.println("Steps done"); 

  gait = 0; //resets gait variable 

}

void gait2(){

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
move_motor(f_s, h_fs); //moves the spine in the right angle to the body 
move_motor(h_s, h_hs);
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
    motor_angle = roundf(2 * rom_spine / (1 + exp(-0.025 * increment + 5)));
  }
  if (dynamic == 2){
    motor_angle = roundf(rom_spine * cos((PI/resolution_dynamic_functions) * increment + PI) + rom_spine); 
  }
  return motor_angle; 

}

int dynamic_movement_legs(int increment){ 
  int motor_angle; 

  if (dynamic ==  1) {
    motor_angle = roundf(2 * rom_limb / (1 + exp(-0.025 * increment + 5)));
  }
  if (dynamic == 2){
    motor_angle = roundf(rom_limb * cos((PI/resolution_dynamic_functions) * increment + PI) + rom_limb); 
  }
  return motor_angle; 

}

int dynamic_movement_feet(int increment){
  int motor_angle; 
  if (dynamic == 1){
    motor_angle = roundf(rom_feet / (1 + exp(-0.025 * increment + 5)));
  }
  if (dynamic == 2){
    motor_angle = roundf(rom_feet * cos((PI/resolution_dynamic_functions) * increment + PI) + rom_feet); 
  }
  return motor_angle; 
}