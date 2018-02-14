

//************************** Command process *****************************
String get_spilted_substring(String data, char separator, int index){
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++){
    if (data.charAt(i) == separator || i == maxIndex){
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void raw_data_parser(String data,String &id, String &cmd, String &parameters){  
  id = get_spilted_substring(data,COMMAND_SPLITTER,0);
  cmd = get_spilted_substring(data,COMMAND_SPLITTER,1);
  cmd.toLowerCase();
  parameters = get_spilted_substring(data,COMMAND_SPLITTER,2);
  param_parser(parameters,rev_para1,rev_para2,rev_para3,rev_para4,rev_para5);
//  Serial.print("ID=");
//  Serial.println(rcv_id);
//  Serial.print("Command=");
//  Serial.println(rcv_command);
//  if(rev_para1.length()>0){
//    Serial.print("Param1=");
//    Serial.println(rev_para1);
//  }
//  if(rev_para2.length()>0){
//    Serial.print("Param2=");
//    Serial.println(rev_para2);
//  }
//  if(rev_para3.length()>0){
//    Serial.print("Param3=");
//    Serial.println(rev_para3);
//  }
//  if(rev_para4.length()>0){
//    Serial.print("Param4=");
//    Serial.println(rev_para4);
//  }
//  if(rev_para5.length()>0){
//    Serial.print("Param5=");
//    Serial.println(rev_para5);
//  }
}

void param_parser(String params,String &para1,String &para2,String &para3,String &para4,String &para5){
  para1 = get_spilted_substring(params,PARAMETER_SPLITTER,0);
  para2 = get_spilted_substring(params,PARAMETER_SPLITTER,1);
  para3 = get_spilted_substring(params,PARAMETER_SPLITTER,2);
  para4 = get_spilted_substring(params,PARAMETER_SPLITTER,3);
  para5 = get_spilted_substring(params,PARAMETER_SPLITTER,4);
}


//************************** WiFi-Connection *****************************
void wifi_connect(){
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);  
    /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
       would try to act as both a client and an access-point and could cause
       network-issues with your other WiFi-devices on your WiFi-network. */
    WiFi.mode(WIFI_STA);
    WiFi.config(WIFI_IP,WIFI_GATEWAY,WIFI_MASK);
    WiFi.begin(WIFI_SSID);    
    while (WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }
    if(is_paused_by_wifi_reconnection){
      is_paused_by_wifi_reconnection = false;
      set_pause(false);
    }  
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Mask: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("Gateway: ");
    Serial.println(WiFi.gatewayIP());
  }
}

void wifi_server_init(){  
  mWifi_server.close();
  mWifi_server.begin();
  Serial.print("Server is started, port=[");
  Serial.print(WIFI_SERVER_PORT);
  Serial.println("]");
}

void check_wifi_clinet_connection(){ 
  if(!mWifi_client){
    is_client_connected = false;
    mWifi_client = mWifi_server.available();
  }    
  if(mWifi_client){
    if(mWifi_client.connected()){
      if(!is_client_connected){
        Serial.println("Client connected");
        Serial.print("Client IP: ");
        Serial.println(mWifi_client.remoteIP());
        is_client_connected = true;
      }
    }
    else{
      if(is_client_connected){
        Serial.println("Client is disconnected");
      }
      is_client_connected = false;
      mWifi_client.stop();
    }    
  }
}

String read_from_client(){
    String receiving_msg = "";
    receiving_msg = mWifi_client.readStringUntil('\r');
    receiving_msg.trim();
    mWifi_client.flush();
    return receiving_msg;
}

void reply_to_client(){
  if(mWifi_client){
    String reply_msg = String(rcv_id+"|"+rcv_command+"|"+running_result);
    if(running_description.length()>0){
      reply_msg = String(reply_msg+"|"+running_description);
    }
    running_result="";
    running_description = ""; 
    mWifi_client.println(reply_msg);
  }
}




