void command_parser(){
  //********************** Command: shift **********************
  if(rcv_command=="shift"){
    action_id = rcv_id;
    action_command = rcv_command;
    if(rev_para1.length()>0){
      float _shift = rev_para1.toFloat();
      target_position = current_position+_shift;
      if(target_position > RAIL_MAX_RANGE){
        target_position = RAIL_MAX_RANGE;
        running_description += "Target position is above the maximum range; ";
        set_error(true);
      }
      else if(target_position < RAIL_MIN_RANGE){
        target_position = RAIL_MIN_RANGE;
        running_description += "Target position is below the minimum range; ";
        set_error(true);
      }
      set_running(true);
    }
    //--------------- Incorrect parameters ---------------
    else{
      String desc = String ("Command \""+rcv_command+"\" has invaliable parameter(s); ");
      running_description +=  desc;
      set_error(true);
      set_finished();
    }
  }
  //********************** Command: moveto **********************
  else if(rcv_command=="moveto"){
    action_id = rcv_id;
    action_command = rcv_command;
    if(rev_para1.length()>0){
      target_position = rev_para1.toFloat();
      if(target_position > RAIL_MAX_RANGE){
        target_position = RAIL_MAX_RANGE;
        running_description += "Target position is above the maximum range; ";
        set_error(true);
      }
      else if(target_position < RAIL_MIN_RANGE){
        target_position = RAIL_MIN_RANGE;
        running_description +=  "Target position is below the minimum range; ";
        set_error(true);
      }
      set_running(true);
    }
    //--------------- Incorrect parameters ---------------
    else{
      String desc = String ("Command \""+rcv_command+"\" has invaliable parameter(s); ");
      running_description +=  desc;
      set_error(true);
      set_finished();
    }      
  }
  //********************** Command: initialize **********************
  else if(rcv_command=="initialize"){
    action_id = rcv_id;
    action_command = rcv_command;
    if(is_debug_mode){
      set_current_position_to_zero();
      set_finished();
    }
    else{
      //Serial.println("Start initializing...");
      set_initializing(true);
      //Serial.println("Speed="+String(slide_speed)+"; Delay time="+String(__delay_microseconds_per_step)); 
    }   
  }
  //********************** Command: pause **********************
  else if(rcv_command=="pause"){
    set_pause(true);
  }
  //********************** Command: resume **********************
  else if(rcv_command=="resume"){
    set_pause(false);
  }
  //********************** Command: setspeed **********************
  else if(rcv_command=="setspeed"){
    if(rev_para1.length()>0){
      float speed_mm_minute = rev_para1.toFloat();
      set_speed(speed_mm_minute);
      running_result = "success";
      String msg = String ("Speed="+String(speed_mm_minute)+";");
      running_description += msg;
      reply_to_client();
    }
    //--------------- Incorrect parameters ---------------
    else{
      String desc = String ("Command \""+rcv_command+"\" has invaliable parameter(s); ");
      running_description +=  desc;
      set_error(true);
      set_finished();
    }
  }
  //********************** Command: getspeed **********************
  else if(rcv_command=="getspeed"){
    running_description = String("Speed="+String(get_speed()));
    set_finished(); 
  }  
  //********************** Command: stop **********************
  else if(rcv_command=="stop"){
    set_interrupt();
  }
  //********************** Command: forceshift **********************
  else if(rcv_command=="forceshift"){
    if(rev_para1.length()>0){     
      float _shift = rev_para1.toFloat();
      if(_shift>=0){
        set_motor_direction(LOW);
      }
      else{
        set_motor_direction(HIGH);          
      }
      forceshift_steps = abs(_shift) / DISTANCE_PER_STEP;
      if(forceshift_steps>0){
        set_forceshift(true);
        set_motor_enable(true);
      }
    }
    else{
      String desc = String ("Command \""+rcv_command+"\" has invaliable parameter(s); ");
      running_description +=  desc;
      set_error(true);
      set_finished();
    }
  }
      //--------------- Incorrect parameters ---------------
    
  //********************** Command: resetzero **********************
  else if(rcv_command=="resetzero"){
    set_current_position_to_zero();
    set_finished();
  }
  //********************** Command: getposition **********************
  else if(rcv_command=="getposition"){
    running_description = String("Current position="+String(current_position));
    running_result = "success";
    reply_to_client();
  }  
  //********************** Command: getinfo **********************
  else if(rcv_command=="getinfo"){
    reply_slider_info();
  }
  //********************** Command: setdebug **********************  
  else if(rcv_command == "setdebug"){
    rev_para1.toLowerCase();
    is_debug_mode = (rev_para1.compareTo("true") == 0) || (rev_para1.compareTo("1") == 0);
    running_description = String("Debug mode="+String(is_debug_mode));
    running_result = "success";
    reply_to_client();
  }
  //********************** Command: getmaxrange **********************  
  else if(rcv_command == "getmaxrange"){
    running_description = String("Maximum range="+String(RAIL_MAX_RANGE));
    running_result = "success";
    reply_to_client();
  }
  //********************** Command: getminlength **********************  
  else if(rcv_command == "getminrange"){
    running_description = String("Minimum range="+String(RAIL_MIN_RANGE));
    running_result = "success";
    reply_to_client();
  }
    
  //********************** Invalid command **********************
  else{
    String desc = String ("Invalid  command: \""+rcv_command+"\" has received; ");
    running_description +=  desc;
    set_error(true);
    set_finished();
  }
}
