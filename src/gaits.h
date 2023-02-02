/* 
  this File contains all Variables and functions for the Servo movement and the gaits 
*/


//Define Max and Min Pulsewidth of Datan Servo (Feet)
#define datan_servo_min 112 //30
#define datan_servo_max 460 //150 degrees
//Define the max and min Signal for feedback of Datan Servo 
#define datan_feedback_min 545 //30 degrees 
#define datan_feedback_max 2496 //150 degrees 

//Define Max and Min Pulsewidth of DSS Servo (Spine and Shoulder)
#define dss_servo_min 468 //30
#define dss_servo_max 242 //150 degrees
//Define the max and min Signal for feedback of DSS Servo 
#define dss_feedback_min 3069 //30 degrees 
#define dss_feedback_max 1280 //150 degrees 

//Define Max and Min Pulsewidth of DMS Servo (Wrist)
#define dms_servo_min 558 
#define dms_servo_max 329 
//Define the max and min Signal for feedback of DMS Servo 
#define dms_feedback_min 2810 //30 degrees 
#define dms_feedback_max 1290 //150 degrees 

//Define Motor Slot Number on PCA9685 (Servo Shield)
const int lff = 4; // Left front foot 
const int lfs = 0; //left front shoulder
const int rfs = 1; //right front shoulder 
const int rff = 5; //right front foot
const int f_s = 2; //front spine 
const int h_s = 13; //hind spine 
const int rhf = 6; //right hind foot
const int rhs = 14; //right hind shoulder 
const int lhs = 15; //left hind shoulder 
const int lhf = 7; //left hind foot
const int lfa = 9; //Left front Wrist Angle 
const int rfa = 8; //Right Front Wrist Angle 
const int lha = 10; //Left hind Wrist angle 
const int rha = 11; //Right hind Wrist Angle 

//Define Feedback pins
const int lff_feed = GPIO_NUM_2; // Left front foot 
const int lfs_feed = GPIO_NUM_0; //left front shoulder
// const int rfs_feed = GPIO_NUM_4; //right front shoulder NEEED NEW ONE
const int rff_feed = GPIO_NUM_16; //right front foot
const int f_s_feed = GPIO_NUM_17; //front spine 
const int h_s_feed = GPIO_NUM_5; //hind spine 
const int rhf_feed = GPIO_NUM_18; //right hind foot
const int rhs_feed = GPIO_NUM_19; //right hind shoulder 
const int lhs_feed = GPIO_NUM_23; //left hind shoulder 
const int lhf_feed = GPIO_NUM_34; //left hind foot
const int lfa_feed = GPIO_NUM_35; //Left front Wrist Angle 
const int rfa_feed = GPIO_NUM_32; //Right Front Wrist Angle 
const int lha_feed = GPIO_NUM_33; //Left hind Wrist angle 
const int rha_feed = GPIO_NUM_25; //Right hind Wrist Angle 

//Input Variables for motion --> adjustable in web interface  
int rom_spine = 10; //range of motion of spine
int rom_limb = 10; //range of motion of legs 
int rom_feet = 75; //range of motion of feet 
int dynamic = 1; //defines which dynamic to use (1 = sigmoid, 2 = sinusoid) 
int gait = 1;  // defines which gait to use (0, no gait, 1 = regular gait, 2 turn gait (NOT YET IMPLEMENTED)) 
int speed_val = 10; //5000 Speed of leg and spine (changes the delay between each increment in microseconds)
int speed_val_foot = 500; // defines the speed for lifting the feet (changes the delay between each increment in microseconds)
int number_of_steps = 11; //number of full steps to be taken 
int foot_center= 5; //defines the offset of the angle of the feet to the vertical to the ground axis 
int front_leg_center = 0; //defines the center where the middle of the range of motion lies (frontlegs)
int hind_leg_center = 0; //defines the center where the middle of the range of motion lies (backlegs)
int front_wrist_angle = 0; //defines the orientation of the front foot( + for positive angle from axis, - for negative angle from axis) 
int hind_wrist_angle = 0; //defines the orientation of the hind foot ( + for positive angle from axis, - for negative angle from axis) 
int dynamic_wrist_angle = 1; //defines if dynamically counteracting Wrist angle is used (0 = not used, 1 = counteracting by angle,  2 = counteracting by reading analog pins (NOT YET IMPLEMENTED)) 

//Input Variables for motion (not adjustable in web interface) 
int resolution_dynamic_functions = 400; //increments for the dynamic functions 
int rom_wrist_angle = rom_spine + rom_limb; 


//information variables  
String robot = "X5_Juggernaut"; 
int climb_incline = 90; 
String claw_angle = "10", surface = "coarse_carpet", toe_angle = "0";
float leg_length = 105;
float spine_length = 315; 


//Variables for Data Collection 
unsigned long elapsed_time[11] =  {0}; //time of step in s 
int stride[11] = {0}; 
int distance[11] = {0}; //sum covered distance in mm 
int raw_dist[11] = {0}; //dist for sum 
int first_dist = 0; 
//accelerometer/gyro 
float mean_acc_xaxis[11] =  {0};
float mean_acc_yaxis[11] = {0};
float mean_acc_zaxis[11] = {0};
float angle_xaxis[11] =  {0}; //acc at end of stride ---> for calculation of angle 
float angle_yaxis[11] = {0}; //acc at end of stride ---> for calculation of angle 
float angle_zaxis[11] = {0}; //acc at end of stride ---> for calculation of angle 
float xaxis_during_stride [80] = {0}; 
float yaxis_during_stride [80] = {0};
float zaxis_during_stride [80] = {0};
float xaxis_sum, yaxis_sum, zaxis_sum;
//current measurements
float mean_current[11] = {0}; //average current consumption per stride in A
float max_current [11] = {0};//displays maximal current spike in a stride in A 
float current_during_stride [80] = {0}; //stores current values of a stride, size displays number of measurements per stride
float curr_sum;
//Servo Success in % e.g. did Servo reach the desired position 
int lff_suc[11] = {0}; // Left front foot 
int lfs_suc[11] = {0}; //left front shoulder
int rfs_suc[11] = {0}; //right front shoulder 
int rff_suc[11] = {0}; //right front foot
int f_s_suc[11] = {0}; //front spine 
int h_s_suc[11] = {0}; //hind spine 
int rhf_suc[11] = {0}; //right hind foot
int rhs_suc[11] = {0}; //right hind shoulder 
int lhs_suc[11] = {0}; //left hind shoulder 
int lhf_suc[11] = {0}; //left hind foot
int lfa_suc[11] = {0}; //Left front Wrist Angle 
int rfa_suc[11] = {0}; //Right Front Wrist Angle 
int lha_suc[11] = {0}; //Left hind Wrist angle 
int rha_suc[11] = {0}; //Right hind Wrist Angle 




//function prototypes 
void move_motor(int motor_num, int angle); //move Servo certain angle 
void home_pos(); //returns all Servos to home position  
int dynamic_movement_spine(int increment);  //dynamic function for spine 
int dynamic_movement_legs(int increment); //dynamic function for legs
int dynamic_movement_feet(int increment); 
void gait1(); 
int sensor_to_angle(int motor_num, int feedback_pin); //convert sensor reading to angle 


//Home Positions of Servos
int h_lff = 71 + foot_center; //Front left foot
int h_lfs = 93 - front_leg_center; //Front left shoulder 
int h_rfs = 99 + front_leg_center; //Front right shoulder
int h_rff = 86 + foot_center; //Front right foot
int h_fs = 94; //Spine Front
int h_hs = 88; //Spine Hind
int h_rhf = 112 + foot_center; //Hind right foot
int h_rhs = 79 + hind_leg_center; //Hind right shoulder
int h_lhs = 83 - hind_leg_center;  //Hind left shoulder
int h_lhf = 90 - foot_center; //Hind left foot
int h_lfa = 138 + front_wrist_angle + front_leg_center ; //Front Left Wrist Angle
int h_rfa = 143 - front_wrist_angle - front_leg_center; //Front Right Wrist Angle 
int h_lha = 131 + hind_wrist_angle + hind_leg_center; //Hind left Wrist Angle
int h_rha = 141 -  hind_wrist_angle - hind_leg_center; //Hind Rigth Wrist Angle


void move_motor(int motor_num, int angle){
    
  int pulsewidth; 

  if (4 <= motor_num && 7 >= motor_num) 
  {
    pulsewidth = map(angle, 30, 150, datan_servo_min, datan_servo_max); 
    pwm.setPWM(motor_num, 0, pulsewidth); 
    // Serial.print("Servo Num Datan: "); 
    // Serial.println(motor_num);
    // Serial.print("Angle: ");   
    // Serial.println(angle); 
  }

  else if (8 <= motor_num && 11 >= motor_num){
    pulsewidth = map(angle, 30, 150, dms_servo_min, dms_servo_max); 
    pwm.setPWM(motor_num, 0, pulsewidth); 
    // Serial.print("Servo Num DMS: "); 
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

void gait1(){ //gait for regular forward movement 

   //get calibration vals for accelero here

  // intial  (half) right step starting from home position 
    
  for (int i = 0; i < resolution_dynamic_functions; i++)
  {
    move_motor(lff, h_lff + dynamic_movement_feet(i)); //lift two across feet
    move_motor(rhf, h_rhf - dynamic_movement_feet(i));
    delayMicroseconds(speed_val_foot); 

  }
    
  for (int i = 0 ; i < resolution_dynamic_functions; i++) 
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


    for (int i = 0; i < resolution_dynamic_functions; i++)
    {

    move_motor(lff, (h_lff + rom_feet) - dynamic_movement_feet(i)); //put feet down
    move_motor(rhf, (h_rhf - rom_feet) + dynamic_movement_feet(i));
    delayMicroseconds(speed_val_foot); 
 
    }

    // Serial.println("Done with half right step"); 


//------------------------------------------------------------------------------------------------------------ Real Gait 

  unsigned long start_time = millis()/1000;
  raw_dist[step_val] = get_dist();  
  // Serial.println(raw_dist[step_val]); 

  for (step_val ; step_val <= (number_of_steps - 1); step_val++) //
  {
    //left step 1-11 -------------------------------------------------------------------- LEFT

    // Serial.println("Starting with left step"); 

    for (int i = 0; i < resolution_dynamic_functions; i++)
    {
    move_motor(lhf, h_lhf + dynamic_movement_feet(i)); //lift two across feet
    move_motor(rff, h_rff - dynamic_movement_feet(i));
    delayMicroseconds(speed_val_foot); 
    }

    for (int i = 0 ; i < resolution_dynamic_functions; i++) 
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

      }

      if (i % 10 == 0) //get current/accel each 10th increment 
      {
        int curr_index = i / 10; 
        current_during_stride[curr_index] = get_current(); //index 0-39
        // Serial.println(current_during_stride[curr_index]);

        //gyro 
        xaxis_during_stride[curr_index] = get_accel(1); 
        yaxis_during_stride[curr_index] = get_accel(2); 
        zaxis_during_stride[curr_index] = get_accel(3); 
      }

      delayMicroseconds(speed_val); 
      
    }

    for (int i = 0; i < resolution_dynamic_functions; i++)
    {
    move_motor(lhf, (h_lhf + rom_feet) - dynamic_movement_feet(i)); //drop feet 
    move_motor(rff, (h_rff - rom_feet) + dynamic_movement_feet(i));
    delayMicroseconds(speed_val_foot); 

    }
    // Serial.println("Done with left step"); 

    //Success for left step                    


    //right step 1-11 --------------------------------------------------------------------- RIGHT

    // Serial.println("Starting with right step");


    for (int i = 0; i < resolution_dynamic_functions; i++) 
    { 

    move_motor(lff, h_lff + dynamic_movement_feet(i)); //lift feet 
    move_motor(rhf, h_rhf - dynamic_movement_feet(i));
    delayMicroseconds(speed_val_foot); 
    
    }

    for (int i = 0; i < resolution_dynamic_functions; i++) 
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
    
      }

      if (i % 10 == 0) //get current/accel each 10th increment 
      {
        int curr_index = 40 + (i / 10); 
        current_during_stride[curr_index] = get_current(); //index 40 - 79
        
        xaxis_during_stride[curr_index] = get_accel(1); 
        yaxis_during_stride[curr_index] = get_accel(2); 
        zaxis_during_stride[curr_index] = get_accel(3); 
      }

      delayMicroseconds(speed_val);

    }



    for (int i = 0; i < resolution_dynamic_functions; i++) 
    {
    move_motor(lff, (h_lff + rom_feet) - dynamic_movement_feet(i)); //drop feet
    move_motor(rhf, (h_rhf - rom_feet) + dynamic_movement_feet(i));
    delayMicroseconds(speed_val_foot); 

    }

  // Serial.println("Done with right step"); 
  

    //read Sensors/get data
    //------------------------------------------------------------------

    elapsed_time[step_val] = (millis()/1000) - start_time; 
    stride[step_val] = step_val + 1; 

    if (step_val == 0)
    {
      distance[step_val] = raw_dist[step_val] - get_dist(); 
    }

    if (step_val > 0)
    { 
      int temp_dist = get_dist(); 
      distance[step_val] = raw_dist[(step_val - 1)] - temp_dist;
      raw_dist[step_val] = temp_dist;
    }

    // //find max and calc mean current 
    max_current[step_val] = current_during_stride[0];  

    for (size_t i = 0; i < (sizeof(current_during_stride) / sizeof(current_during_stride[0])); i++)
    {
      if (max_current[step_val] < current_during_stride[i])
      {
        max_current[step_val] = current_during_stride[i]; 
      }
    }

    curr_sum = 0.0; 
    for (size_t i = 0; i < (sizeof(current_during_stride) / sizeof(current_during_stride[0])); i++)
    {
      curr_sum += current_during_stride[i]; 
    }

    mean_current[step_val] = curr_sum / (sizeof(current_during_stride) / sizeof(current_during_stride[0])); 

    //accelerometer and gyro 
    //calc mean acceleration during step for each axis 
    for (size_t i = 0; i < (sizeof(xaxis_during_stride) / sizeof(xaxis_during_stride[0])); i++)
    {
      xaxis_sum += xaxis_during_stride[i]; 
      yaxis_sum += yaxis_during_stride[i]; 
      zaxis_sum += zaxis_during_stride[i]; 
    }
    mean_acc_xaxis[step_val] = xaxis_sum / (sizeof(xaxis_during_stride) / sizeof(xaxis_during_stride[0])); 
    mean_acc_yaxis[step_val] = yaxis_sum / (sizeof(xaxis_during_stride) / sizeof(xaxis_during_stride[0]));
    mean_acc_zaxis[step_val] = zaxis_sum / (sizeof(xaxis_during_stride) / sizeof(xaxis_during_stride[0]));

    //calc pitch, yaw, roll 
    angle_xaxis[step_val] = get_angles(1); 




    // //debugging vals 
    // Serial.println(step_val);  //print step val for all steps 
    // Serial.println(distance[step_val]);                                                                     
    // Serial.println(max_current[step_val]); 
    // Serial.println(mean_current[step_val]); 
    // Serial.println(xaxis_val[step_val]);
    // Serial.println(temp[step_val]); 
    // Serial.println("======================================================="); 
    
  // server.handleClient(); //needed if live table used ?!
  }

  // final (half) leftstep to get into home position
  // Serial.println("Starting with final half left step"); 
    
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

    // Serial.println("Done with final half step"); 
    Serial.println("All Steps done"); 

  gait = 0; //resets gait variable  

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

Serial.println("Robot in home pos");
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

int sensor_to_angle(int motor_num, int feedback_pin){
  int feedback_val = analogRead(feedback_pin); 
  int angle; 

  if (4 <= motor_num && 7 >= motor_num){
    angle = map(feedback_val, datan_feedback_min, datan_feedback_max, 30, 150); 
    Serial.print("Servo Num Datan: "); 
    Serial.println(motor_num);
    Serial.print("Angle: ");   
    Serial.println(angle); 
  }

  else if (8 <= motor_num && 11 >= motor_num){
    angle = map(feedback_val, dms_feedback_min, dms_feedback_max, 30, 150);
    Serial.print("Servo Num DMS: "); 
    Serial.println(motor_num);
    Serial.print("Angle: ");   
    Serial.println(angle);
  }

  else {
    angle = map(feedback_val, dss_feedback_min, dss_feedback_max, 0, 270); 
    Serial.print("Servo Num DSS: "); 
    Serial.println(motor_num);
    Serial.print("Angle: ");   
    Serial.println(angle); 
  }

  return angle; 
}