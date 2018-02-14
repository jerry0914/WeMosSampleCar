void min_limiter_state_changed(){
  if(digitalRead(MIN_LIMITER_PIN)==LOW){
    control_state |= STATE_MIN_LIMITER;
    //Serial.println("Minimum limiter is hitted!!");
  }
  else{
    control_state &= ~STATE_MIN_LIMITER;
     //Serial.println("Minimum limiter is released!!");
  }  
}

void max_limiter_state_changed(){
  if(digitalRead(MAX_LIMITER_PIN)==LOW){
    control_state |= STATE_MAX_LIMITER;
    //Serial.println("Maximum limiter is hitted!!");
  }
  else{
    control_state &= ~STATE_MAX_LIMITER;
     //Serial.println("Maximum limiter is released!!");
  }
}

void setup() {
  //put your setup code here, to run once:
  Serial.begin(9600);
  delay(5);
  attachInterrupt(MIN_LIMITER_PIN, min_limiter_state_changed, CHANGE);
  attachInterrupt(MAX_LIMITER_PIN, max_limiter_state_changed, CHANGE);
  wifi_connect();
  wifi_server_init();
  motor_init();
}

