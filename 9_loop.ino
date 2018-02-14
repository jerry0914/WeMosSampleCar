void loop() {
  if(WiFi.status() != WL_CONNECTED){
    //Serial.println("WiFi disconnected, try to reconnect...");
    if(get_running()){
      is_paused_by_wifi_reconnection = true;
      set_pause(true);
    }
    wifi_connect();
  }
  check_wifi_clinet_connection();
  if(mWifi_client.available()){
    String raw_data = read_from_client();
    //Serial.print("Data received:");
    //Serial.println(raw_data);
    raw_data_parser(raw_data,rcv_id,rcv_command,rcv_parameters);
    command_parser();
  }
  execute();
}

