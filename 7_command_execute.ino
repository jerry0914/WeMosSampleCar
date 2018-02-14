void execute(){
  //******************************* Refresh limiter state *********************************
  //fresh_limiter_state();
  //******************************* State=INTERRUPTED *********************************
  if (get_interrupted()){
    //Serial.println("Interrupted");
    set_motor_enable(false);
    set_motor_direction(LOW);
    running_result = "failed";
    running_description+="User interrupted; ";
    reply_to_client();
    set_idle();
    set_interrupt(false);
    set_not_initialized(true);
    set_pause(false);
    action_id = "";
    action_command = "";
  }
  //******************************* State=PAUSED *********************************
  else if(get_pause()){
//    set_motor_enable(false);
//    set_motor_direction(LOW);
  }
  else{
    //******************************* Stage=FORCESHIFT *********************************
    if(get_forceshift()){
      if(forceshift_counter<forceshift_steps){
        if(get_max_limiter_state()){
          set_forceshift(false);
          set_error(true);
          running_description = "Maximum limiter is hitted!!!";
          set_finished();
        }
        else if(get_min_limiter_state()){
          set_forceshift(false);
          set_error(true);
          running_description = "Minimum limiter is hitted!!!";
          set_finished();
        }
        else{
          motor_go_one_step();
          forceshift_counter++;
        }
      }
      else{
        set_forceshift(false);
        set_finished();     
      }
    }    
    //******************************* Stage=INITIALIZING *********************************
    else if(get_initializing()){
      //Serial.println("Initializing");
      if(get_min_limiter_state()){
        delay(1200);
        set_motor_direction(0);
        int count = 0;               
        while(count <30){
          count++;
          motor_go_one_step();
        }         
        set_initializing(false);
        current_position = 0.0;    
      }
      else{
        motor_go_one_step();
      }
    }
    //******************************* Stage=RUNNING *********************************
    else if(get_running()){
      if(get_not_initialized())
      {
        if(is_debug_mode){
          set_current_position_to_zero();
        }
        else{
          set_initializing(true); 
        }
      }
      else{
        // ------------------------- Moving forward --------------------------
        if((target_position - current_position)>0.1){
          if(get_max_limiter_state()){
            set_error(true);
            running_description += "Maximum limiter is hitted!!!; ";
            set_finished();        
          }
          else if(get_min_limiter_state() && current_position >(DISTANCE_PER_STEP*5)){
            set_error(true);
            running_description += "Minimum limiter is hitted!!!; ";
            set_finished();
          }
          else{
            set_motor_direction(LOW);
            set_motor_enable(true);
            motor_go_one_step();
            current_position+=DISTANCE_PER_STEP;
          }      
        }
        // ------------------------- Moving backward --------------------------
        else if((current_position-target_position)>0.1){
          if(get_min_limiter_state() & current_position>(DISTANCE_PER_STEP*2)){
            set_error(true);
            running_description += "Minimum limiter is hitted!!!; ";
            set_finished();
          }
          else if(get_max_limiter_state()){
            set_error(true);
            running_description += "Maximum limiter is hitted!!!; ";
            set_finished();        
          }
          else{
            set_motor_direction(HIGH);
            set_motor_enable(true);
            motor_go_one_step();
            current_position-=DISTANCE_PER_STEP;
          }
        }
        else{
          set_finished();
        }
      }      
    }
    //******************************* Stage=FINISHED *********************************
    else if(get_finished()){
      //Serial.println("Finished");
      if(get_error()){
        running_result = "failed";
      }
      else{
        running_result = "success";
      }
      if((action_command=="shift" || action_command=="moveto" && !get_initializing()) || action_command=="initialize" ){
        rcv_id = action_id;
        rcv_command = action_command;
        String msg = String("Current position="+String(current_position)+";");
        //Serial.println(msg);
        running_description+=msg;
      }
      reply_to_client();
      action_id="";
      action_command = "";
      set_idle();
    }
    //******************************* Stage=IDLE *********************************
    else{
      //Serial.println("Is idle");
      set_motor_direction(LOW);
      set_motor_enable(false);
    }
  }
}

