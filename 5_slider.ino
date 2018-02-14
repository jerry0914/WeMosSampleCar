

//************************** Slider Methods *****************************
void set_speed(float speed_mm_per_minute=3000.00){
  slide_speed = speed_mm_per_minute;
  long steps = slide_speed/DISTANCE_PER_STEP;
  __delay_microseconds_per_step = 60*1000000/2/steps;
  Serial.println("Set speed="+String(slide_speed)+"; Delay Time = "+String(__delay_microseconds_per_step));   
}

float get_speed(){
  return slide_speed;
}

//void __go_gack_original_point_motion_only(){
//  set_motor_enable(true);
//  set_speed(INITIALIZING_SPEED);
////  Serial.print("get_min_limiter_state=");
////  Serial.println(get_min_limiter_state());
//  if(get_min_limiter_state()){
//    //Serial.println("force_shift(100)");
//    force_shift(100);
//  }
////  Serial.print("get_min_limiter_state=");
////  Serial.println(get_min_limiter_state());
////  while(!get_min_limiter_state()){
////    Serial.println("force_shift(-10)");
////    force_shift(-10);
////  }
//  set_motor_enable(true);
//  while(!get_min_limiter_state()){
//    motor_go_one_step();
//  }
//  set_motor_enable(false);
//  set_motor_direction(LOW);
//  current_position = 0.0;
//  set_not_initialized(false);
//  set_speed(slide_speed);
//  Serial.println(String("Current position="+String(current_position)));
//}

//void go_back_original_point(){
//  __go_gack_original_point_motion_only();
//  set_idle();
//  running_result = "success";
//  running_description = "";
//  reply_to_client();
//}

void set_current_position_to_zero(){
  current_position = 0.0;
  set_not_initialized(false);
  Serial.println(String("Current position="+String(current_position)));  
}



void reply_slider_info(){ 
  String info = String("Speed="+String(get_speed())+";");
  info += String("Current position="+String(current_position)+";");
  info+=String("Debug mode="+String(is_debug_mode)+";");
  info += String("Running stage="+String(running_stage,HEX)+";");
  info += String("Control state="+String(control_state,HEX)+";");
  running_description = info;
  running_result = "success";
  reply_to_client();
}

//void force_shift(float distance){
//  if(distance>=0){
//    set_motor_direction(LOW);
//  }
//  else{
//    set_motor_direction(HIGH);
//  }
//  set_motor_enable(true);
//  int steps = abs(distance) / DISTANCE_PER_STEP;
//  int steps_counter = 0;
//  while((!get_min_limiter_state() || !get_max_limiter_state()) && steps_counter<steps){
//    motor_go_one_step();
//    steps_counter++;
//  }
//  set_motor_enable(false);
//}

