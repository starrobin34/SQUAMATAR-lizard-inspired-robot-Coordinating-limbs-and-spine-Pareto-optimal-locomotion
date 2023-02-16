/* 
  this File contains all Variables and functions for the Servo movement and the gaits 
*/

//Define Max and Min Pulsewidth of Batan Servo (Feet)
#define datan_servo_min 112 //30
#define datan_servo_max 460 //150 degrees
//Define the max and min Signal for feedback of Datan Servo 
#define datan_feedback_min 540 //30 degrees 
#define datan_feedback_max 2329 //150 degrees 

//Define Max and Min Pulsewidth of DSS Servo (Spine and Shoulder)
#define dss_servo_min 468 //30
#define dss_servo_max 242 //150 degrees
//Define the max and min Signal for feedback of DSS Servo 
#define dss_feedback_min 2420 //30 degrees 
#define dss_feedback_max 881 //150 degrees 

//Define Max and Min Pulsewidth of DMS Servo (Wrist)
#define dms_servo_min 615
#define dms_servo_max 100
//Define the max and min Signal for feedback of DMS Servo 
#define dms_feedback_min 3076 //30 degrees 
#define dms_feedback_max 1612 //150 degrees 

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

//Define Feedback pins for Servos 
const int f_s_feed = GPIO_NUM_34; //front spine 
const int h_s_feed = GPIO_NUM_35; //hind spine 
const int lfs_feed = GPIO_NUM_34; //left front shoulder !!!!!!!!!!!!!CHANGE
const int rfs_feed = GPIO_NUM_32; //right front shoulder
const int rfa_feed = GPIO_NUM_33; //Right Front Wrist Angle  
// const int lfa_feed = GPIO_NUM_33; //Left front Wrist Angle
const int rff_feed = GPIO_NUM_39; 
const int lhf_feed = GPIO_NUM_36;

//Input Variables for motion --> adjustable in web interface  
int rom_spine = 10; //range of motion of spine
int rom_limb = 10; //range of motion of legs 
int rom_feet = 75; //range of motion of feet 
int dynamic = 1; //defines which dynamic to use (1 = sigmoid, 2 = sinusoid) 
int gait = 1;  // defines which gait to use (0, no gait, 1 = regular gait, 2 turn gait (NOT YET IMPLEMENTED)) 
int speed_val = 500; //(500 Standard) Speed of leg and spine (changes the delay between each increment in microseconds)
int speed_val_foot = 500; // defines the speed for lifting the feet (changes the delay between each increment in microseconds)
int number_of_steps = 3; //number of full steps to be taken 
int foot_center= 0; //defines the offset of the angle of the feet to the vertical to the ground axis 
int front_leg_center = 0; //defines the center where the middle of the range of motion lies (frontlegs)
int hind_leg_center = 0; //defines the center where the middle of the range of motion lies (backlegs)
int front_wrist_angle = 0; //defines the orientation of the front foot( + for positive angle from axis, - for negative angle from axis) 
int hind_wrist_angle = 0; //defines the orientation of the hind foot ( + for positive angle from axis, - for negative angle from axis) 
int dynamic_wrist_angle = 1; //defines if dynamically counteracting Wrist angle is used (0 = not used, 1 = counteracting by angle,  2 = counteracting by reading analog pins (NOT YET IMPLEMENTED)) 

//Input Variables for motion (not adjustable in web interface) 
int resolution_dynamic_functions = 400; //increments for the dynamic functions 
int rom_wrist_angle = rom_spine + rom_limb; 

//information variables  
int climb_incline = 90; 
String claw_angle = "10", surface = "coarse_carpet", toe_angle = "0", robot = "X5_Juggernaut";
float leg_length = 105, spine_length = 315, spine_middle = 181, should_offset = 45; 
float spine_front = (spine_length - spine_middle) / 2;  

//Variables for Data Collection 
unsigned long elapsed_time[11] =  {0}; //time of step in s 
int stride[11] = {0}; 
int distance[11] = {0}; //sum covered distance in mm 
//accelerometer/gyro 
float mean_acc_xaxis[11] =  {0};
float mean_acc_yaxis[11] = {0};
float mean_acc_zaxis[11] = {0};
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

  //Wrist
  else if (8 <= motor_num && 11 >= motor_num){
    pulsewidth = map(angle, 0, 270, dms_servo_min, dms_servo_max); 
    pwm.setPWM(motor_num, 0, pulsewidth); 
    // Serial.print("Servo Num DMS: "); 
    // Serial.println(motor_num);
    // Serial.print("Angle: ");   
    // Serial.println(angle); 

  }
    //Spine Shoulder 
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

  //calibration vals for accelerometer angle calc 
  y_ang_offset = get_accel(4);
  z_ang_offset = get_accel(5);
  // Serial.println(y_ang_offset); 
  // Serial.println(z_ang_offset);


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
  int first_dist = get_dist();  
  // Serial.println(raw_dist[step_val]); 

  //Correcting the Wrist angle (tilt angle in between steps (psi))
  double alpha = (PI/180) * 0.5 * rom_spine; 
  double beta = (PI/180) * 0.5 * rom_limb; 
  double delta = atan((2*cos(alpha + beta)* leg_length + 2*cos(alpha)*should_offset)/(2*cos(alpha)*spine_front + spine_middle)); 
  double psi_delta = atan((leg_length + should_offset)/(spine_front + 0.5* spine_middle)); 
  double psi_max = psi_delta - delta; 
  psi_max = psi_max *(180 / PI) + 20; 

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
      move_motor(lfa, h_lfa + (rom_spine - dynamic_movement_spine(i)) + (rom_limb - dynamic_movement_legs(i)) + (psi_max - abs(psi_max - i*(psi_max/200))));  //rotate wrists 
      move_motor(rfa, h_rfa + (rom_spine - dynamic_movement_spine(i)) + (rom_limb - dynamic_movement_legs(i)) + (psi_max - abs(psi_max - i*(psi_max/200))));
      move_motor(lha, h_lha + (-rom_spine + dynamic_movement_spine(i)) + (-rom_limb + dynamic_movement_legs(i)) + (psi_max - abs(psi_max - i*(psi_max/200))));
      move_motor(rha, h_rha + (-rom_spine + dynamic_movement_spine(i)) + (-rom_limb + dynamic_movement_legs(i)) + (psi_max - abs(psi_max - i*(psi_max/200))));

      }

      if (i % 10 == 0) //get current/accel each 10th increment 
      {
        int curr_index = i / 10; 
        current_during_stride[curr_index] = get_current(); //index 0-39
        // Serial.println(current_during_stride[curr_index]);

        //gyro PROBLEM: SLOW !!!!!!!!!
        // xaxis_during_stride[curr_index] = get_accel(1); 
        // yaxis_during_stride[curr_index] = get_accel(2); 
        // zaxis_during_stride[curr_index] = get_accel(3); 
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

    //Success (currently only measured for the left step and not for the feet (not enough pins)) 
    float fs_diff_angle =  ((h_fs + rom_spine) - rom_spine) - abs(((h_fs + rom_spine) - rom_spine) - sensor_to_angle(f_s, f_s_feed)); 
    f_s_suc[step_val] = roundf(100 * fs_diff_angle / ((h_fs + rom_spine) - rom_spine)); 

    float hs_diff_angle = ((h_hs - rom_spine) + rom_spine) - abs(((h_hs - rom_spine) + rom_spine) - sensor_to_angle(h_s, h_s_feed)); 
    h_s_suc[step_val] = roundf(100 * hs_diff_angle / ((h_hs - rom_spine) + rom_spine)); 

    float lfs_diff_angle = ((h_lfs + rom_limb) - rom_limb) - abs(((h_lfs + rom_limb) - rom_limb) - sensor_to_angle(lfs, lfs_feed)); 
    lfs_suc[step_val] = roundf(100 * lfs_diff_angle / ((h_lfs + rom_limb) - rom_limb)); 

    float rfs_diff_angle = ((h_rfs + rom_limb) - rom_limb) - abs(((h_rfs + rom_limb) - rom_limb) - sensor_to_angle(rfs, rfs_feed)); 
    rfs_suc[step_val] = roundf(100 * rfs_diff_angle / ((h_rfs + rom_limb) - rom_limb)); 

    float rff_diff_angle = ((h_lhf + rom_feet) - rom_feet) - abs(((h_lhf + rom_feet) - rom_feet) - sensor_to_angle(rff, rff_feed)); 
    rff_suc[step_val] = roundf(100 * rff_diff_angle / ((h_lhf + rom_feet) - rom_feet)); 

    float lhf_diff_angle = ((h_lhf + rom_feet) - rom_feet) - abs(((h_lhf + rom_feet) - rom_feet) - sensor_to_angle(lhf, lhf_feed)); 
    lhf_suc[step_val] = roundf(100 * lhf_diff_angle / ((h_lhf + rom_feet) - rom_feet)); 

    //wrists --> include psi angle !!! 
    float rfa_diff_angle = h_rfa - abs(h_rfa - sensor_to_angle(rfa, rfa_feed)); 
    rfa_suc[step_val] = roundf(100 * rfa_diff_angle / h_rfa); 

    // float lfa_diff_angle = h_lfa - abs(h_lfa - sensor_to_angle(lfa, lfa_feed)); 
    // lfa_suc[step_val] = roundf(100 * lfa_diff_angle / h_lfa); 



                     


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
      move_motor(lfa, h_lfa + (-rom_spine + dynamic_movement_spine(i)) + (-rom_limb + dynamic_movement_legs(i)) + (psi_max - abs(psi_max - i*(psi_max/200))));  //rotate wrists 
      move_motor(rfa, h_rfa + (-rom_spine + dynamic_movement_spine(i)) + (-rom_limb + dynamic_movement_legs(i)) + (psi_max - abs(psi_max - i*(psi_max/200))));
      move_motor(lha, h_lha + (rom_spine - dynamic_movement_spine(i)) + (rom_limb - dynamic_movement_legs(i)) + (psi_max - abs(psi_max - i*(psi_max/200))));
      move_motor(rha, h_rha + (rom_spine - dynamic_movement_spine(i)) + (rom_limb - dynamic_movement_legs(i)) + (psi_max - abs(psi_max - i*(psi_max/200))));
    
      }

      if (i % 10 == 0) //get current/accel each 10th increment 
      {
        int curr_index = 40 + (i / 10); 
        current_during_stride[curr_index] = get_current(); //index 40 - 79
        
        // xaxis_during_stride[curr_index] = get_accel(1); 
        // yaxis_during_stride[curr_index] = get_accel(2); 
        // zaxis_during_stride[curr_index] = get_accel(3); 
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

    int raw_dist; 
    if (step_val == 0)
    {
      raw_dist =  get_dist(); 
      distance[step_val] = first_dist - raw_dist; //327 - 188 = 139
    }

    if (step_val > 0)
    { 
      int temp_dist = get_dist(); 
      distance[step_val] =  raw_dist - temp_dist; // 188 - 90 = 98
      raw_dist = temp_dist; 
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

    //accelerometer
    //calc mean acceleration during step for each axis ---> Too slow !!!!!!!!
    // for (size_t i = 0; i < (sizeof(xaxis_during_stride) / sizeof(xaxis_during_stride[0])); i++)
    // {
    //   xaxis_sum += xaxis_during_stride[i]; 
    //   yaxis_sum += yaxis_during_stride[i]; 
    //   zaxis_sum += zaxis_during_stride[i]; 
    // }
    // mean_acc_xaxis[step_val] = xaxis_sum / (sizeof(xaxis_during_stride) / sizeof(xaxis_during_stride[0])); 
    // mean_acc_yaxis[step_val] = yaxis_sum / (sizeof(xaxis_during_stride) / sizeof(xaxis_during_stride[0]));
    // mean_acc_zaxis[step_val] = zaxis_sum / (sizeof(xaxis_during_stride) / sizeof(xaxis_during_stride[0]));
    // Serial.println( mean_acc_xaxis[step_val]);
    // Serial.println( mean_acc_yaxis[step_val]);
    // Serial.println( mean_acc_zaxis[step_val]);

    //calc pitch, roll 
    angle_yaxis[step_val] = get_accel(4); 
    angle_zaxis[step_val] = get_accel(5); 
    // Serial.println(angle_yaxis[step_val]); 
    // Serial.println(angle_zaxis[step_val]); 

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

  step_val = 0; 
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
  // Serial.println(feedback_val); 
  int angle; 

  if (4 <= motor_num && 7 >= motor_num){
    angle = map(feedback_val, datan_feedback_min, datan_feedback_max, 30, 150); 
    // Serial.print("Servo Num Datan: "); 
    // Serial.println(motor_num);
    // Serial.print("Angle: ");   
    // Serial.println(angle); 
  }

  //Wrist 
  else if (8 <= motor_num && 11 >= motor_num){
    angle = map(feedback_val, dms_feedback_min, dms_feedback_max, 0, 270);
    // Serial.print("Servo Num DMS: "); 
    // Serial.println(motor_num);
    // Serial.print("Angle: ");   
    // Serial.println(angle);
  }

  else {
    angle = map(feedback_val, dss_feedback_min, dss_feedback_max, 30, 150); 
    // Serial.print("Servo Num DSS: "); 
    // Serial.println(motor_num);
    // Serial.print("Angle: ");   
    // Serial.println(angle); 
  }

  return angle; 
}