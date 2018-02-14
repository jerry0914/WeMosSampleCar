#include <ESP8266WiFi.h>

//============================== Variables ==============================

//********************* Running stage control ****************************
bool is_debug_mode = false;
const int STAGE_IDLE = 0;
const int STAGE_RUNNING = 1;
const int STAGE_INITIALIZING = (1<<1);
const int STAGE_FINISHED =(1<<2);
const int STAGE_FORCESHIFT =  (1<<5);
const int STAGE_ERROR =  (1<<6);
int running_stage = STAGE_IDLE;

const int STATE_PAUSED =  1;
const int STATE_INTERRUPTED=(1<<1);
const int STATE_NOT_INITIALIZED=(1<<2);
const int STATE_MIN_LIMITER=(1<<5);
const int STATE_MAX_LIMITER=(1<<6);
int control_state = STATE_NOT_INITIALIZED;

String running_result = "";
String running_description = "";
//************************** Stepping Motor and GPIO Variables **************************
const int STEP_PIN = D3;
const int DIR_PIN = D4;
const int DISABLE_PIN = D5;
const int MIN_LIMITER_PIN = D6;
const int MAX_LIMITER_PIN = D7;
//************************** WiFi and Command_stream Variables **************************
const char* WIFI_SSID = "TnVSTRESSOPEN5131ag";
const char* WIFI_PASSWORD = "";
const IPAddress WIFI_IP(192,168,10,18);
const IPAddress WIFI_MASK(255,255,255,0);
const IPAddress WIFI_GATEWAY(192,168,10,254);
const int WIFI_SERVER_PORT = 8090;
WiFiServer mWifi_server(WIFI_SERVER_PORT);
WiFiClient mWifi_client;
bool is_client_connected = false;
bool is_paused_by_wifi_reconnection = false;
//Receiving command format
const char COMMAND_SPLITTER = '|';
String rcv_command = "";
String rcv_id = "";
String rcv_parameters ="";
const char PARAMETER_SPLITTER = ',';
String rev_para1="";
String rev_para2="";
String rev_para3="";
String rev_para4="";
String rev_para5="";
//************************** Slider Variables *****************************
const float RAIL_MAX_RANGE = 3500.00;//mm
const float RAIL_MIN_RANGE = 0.00;
const float DISTANCE_PER_STEP = 0.20; //mm
float current_position = 0;
float target_position = 0;
int forceshift_steps = 0;
int forceshift_counter = 0;
int __delay_microseconds_per_step = 1333.33;
float slide_speed = 4500.00;
const float INITIALIZING_SPEED = 3300.00; 
String action_id="";
String action_command="";

//============================== Function prototypes ==============================
void set_motor_enable(bool);
bool get_motor_enable();
void set_motor_direction(int);
void set_speed(float);
float get_speed();




















