

//************************** Stepping Motor and GPIO Control *****************************
void set_motor_enable(bool flag=true){
  int state = flag?LOW:HIGH;
  digitalWrite(DISABLE_PIN,state);
}

bool get_motor_enable(){
  return digitalRead(DISABLE_PIN)==LOW;
}

//bool fresh_limiter_state(){
//  if(digitalRead(MAX_LIMITER_PIN)==LOW){
//    control_state |= STATE_MAX_LIMITER;
//  }
//  else{
//    control_state &= ~STATE_MAX_LIMITER;
//  }
//  if(digitalRead(MIN_LIMITER_PIN)==LOW){
//    control_state |= STATE_MIN_LIMITER;
//  }
//  else{
//    control_state &= ~STATE_MIN_LIMITER;
//  }
//}

//bool get_min_limiter_state(){
//  return digitalRead(MIN_LIMITER_PIN)==LOW;
//}

//Direction of motor;1=backward,otherwise=forward
void set_motor_direction(int dir=0){
  if(dir==1){
    digitalWrite(DIR_PIN,HIGH);  
  }
  else{
    digitalWrite(DIR_PIN,LOW);  
  }
}

void motor_go_one_step(){
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(__delay_microseconds_per_step);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(__delay_microseconds_per_step);
}

void motor_init(){
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(DISABLE_PIN, OUTPUT);
  pinMode(MAX_LIMITER_PIN, INPUT);
  pinMode(MIN_LIMITER_PIN, INPUT);
  digitalWrite(STEP_PIN,LOW); 
  digitalWrite(DIR_PIN,LOW); 
  digitalWrite(DISABLE_PIN,LOW); 
  set_motor_enable(false);
}

