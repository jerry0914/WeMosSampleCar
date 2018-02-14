
//********************* Running stage control Functions****************************

//=================================== Control state ===================================
bool get_pause(){
  return (control_state & STATE_PAUSED)>0;
}

void set_pause(bool flag=true){
  if(flag){
    control_state |= STATE_PAUSED;
  }
  else{
    control_state &= ~STATE_PAUSED;
  }
}

bool get_interrupted(){
  return (control_state & STATE_INTERRUPTED)>0;
}

void set_interrupt(bool flag=true){
  if(flag){
    control_state |= STATE_INTERRUPTED;
  }
  else{
    control_state &= ~STATE_INTERRUPTED;
  }
}

bool get_min_limiter_state(){
  return (control_state & STATE_MIN_LIMITER)>0;
}

bool get_max_limiter_state(){
  return (control_state & STATE_MAX_LIMITER)>0;
}

bool get_not_initialized(){
  return (control_state & STATE_NOT_INITIALIZED)>0;
}

void set_not_initialized(bool flag = false){
  if(flag){
    control_state |= STATE_NOT_INITIALIZED;
  }
  else{
    control_state &= ~STATE_NOT_INITIALIZED;
  }
}

//=================================== Running stage ===================================

bool get_idle(){
  return running_stage == STAGE_IDLE;
}

void set_idle(){
  //Serial.println("Set to Idle");
  running_stage = STAGE_IDLE;
  //Serial.println("Running stage="+String(running_stage,HEX));
}

bool get_running(){
  return (running_stage & STAGE_RUNNING)>0;
}

void set_running(bool flag=true){
  if(flag){
    running_stage |= STAGE_RUNNING;
    running_stage &= ~STAGE_FINISHED;
  }
  else{
    running_stage &= ~STAGE_RUNNING;
  }
}

bool get_initializing(){
  return (running_stage & STAGE_INITIALIZING)>0;
}

void set_initializing(bool flag=false){
  if(flag){
    long steps = INITIALIZING_SPEED/DISTANCE_PER_STEP;
    __delay_microseconds_per_step = 60*1000000/2/steps;
    running_stage |= STAGE_INITIALIZING;
    set_motor_direction(HIGH);
    set_motor_enable(true);
  }
  else{
    if(get_initializing()){
      set_speed(slide_speed);
      running_stage |= STAGE_FINISHED;
      set_not_initialized(false);
    }
    running_stage &= ~STAGE_INITIALIZING;
  }
}

void set_finished(){
  set_running(false);
  //set_initializing(false);
  running_stage |= STAGE_FINISHED;
  set_motor_direction(LOW);
  set_motor_enable(false);
}

bool get_finished(){
  return (running_stage & STAGE_FINISHED)>0;
}

void set_forceshift(bool flag=true){
  if(flag){
      set_not_initialized(true);
      running_stage |= STAGE_FORCESHIFT;      
  }
  else{
    running_stage &= ~STAGE_FORCESHIFT;
    forceshift_steps = 0;
    forceshift_counter = 0;
  }
}

bool get_forceshift(){
  return (running_stage & STAGE_FORCESHIFT)>0;
}

void set_error(bool flag=true){
  if(flag){
      running_stage |= STAGE_ERROR;
  }
  else{
    running_stage &= ~STAGE_ERROR;
  }
}

bool get_error(){
  return (running_stage & STAGE_ERROR)>0;
}






