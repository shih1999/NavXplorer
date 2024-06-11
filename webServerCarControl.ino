#include <WiFi.h>
#include <WebServer.h>

// Own wifi credentials
const char* ssid = "Yvonne";
const char* password = "Yvonne0813";

// Define pin numbers
#define ULTRA_TRIG 15
#define ULTRA_BACK 11     // Back
#define ULTRA_FRONT 42    // Front-mid
#define ULTRA_LEFT 7      // Front-left
#define ULTRA_RIGHT 40    // Front-right

#define LEFT_MOTOR1 35
#define LEFT_MOTOR2 36    
#define RIGHT_MOTOR1 38   
#define RIGHT_MOTOR2 37
#define LEFT_MOTORen 21
#define RIGHT_MOTORen 20

#define LED 3

// Define distance thresholds
#define FRONT_DMAX 30
#define BACK_DMAX 45

// Define durations
#define LEFT_DUCK_MS 10
#define RIGHT_DUCK_MS 10
#define LEFT_TURN_MS 30
#define RIGHT_TURN_MS 30
#define STOP_WAIT_MS 1000

#define ULTRA_TIMEOUT 30000

// Global variables
float recieve;
float duration, distance;
float front_distance, back_distance;
float left_distance, right_distance;

// status variables
String current_status = "Idle";
float machine_on = 0;   // 0: off, 1: on

// create web server on port 8000
WebServer server(8000);

// Function prototypes
void initializePins();
void connectToWiFi();
void startServer();
void waitForMachineStart();
void start_machine();
void stop_machine();
void detect();
void check_back();
void check_front();
void wait();
void check_dir();
void send_ultra();
float receive_ultra(int ultra_no);
float ping_ultra(int ultra_no);
void start_motor();
void stop_motor();
void turn_right(int duration);
void turn_left(int duration);
void handleCommand();
void handleStatus();
void handleRoot();

void setup() {
  // Initialize pins
  initializePins();

  // Initialize Serial Monitor
  Serial.begin(9600);

  // Connect to Wi-Fi
  connectToWiFi();

  // Start the server
  startServer();

  // Wait for machine start signal
  waitForMachineStart();
  
  // Start motor after machine_on = 1
  start_machine();
}

void loop() {
  if (!machine_on) {    // if machine_on = 0
    stop_machine();
    return;
  }

  detect();
  // Handles incoming client requests on the server
  server.handleClient();
}

void initializePins() {
  // Ultrasonic sensor pins
  pinMode(ULTRA_TRIG, OUTPUT);
  pinMode(ULTRA_BACK, INPUT);
  pinMode(ULTRA_FRONT, INPUT);  
  pinMode(ULTRA_LEFT, INPUT); 
  pinMode(ULTRA_RIGHT, INPUT);

  // Motor pins
  pinMode(LEFT_MOTOR1, OUTPUT);
  pinMode(LEFT_MOTOR2, OUTPUT);
  pinMode(RIGHT_MOTOR1, OUTPUT);
  pinMode(RIGHT_MOTOR2, OUTPUT);
  pinMode(LEFT_MOTORen, OUTPUT);
  pinMode(RIGHT_MOTORen, OUTPUT);

  // Motor speed
  analogWrite(LEFT_MOTORen, 120);
  analogWrite(RIGHT_MOTORen, 120);
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void startServer() {
  server.on("/", handleRoot);
  server.on("/status", handleStatus);
  server.on("/command", handleCommand);
  server.begin();
  Serial.println("HTTP server started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void waitForMachineStart() {
  while (!machine_on) {
    Serial.println("Waiting for machine start signal ...");
    delay(1000);
  }
}

void start_machine() {
  current_status = "Started"
  start_motor();
}

void stop_machine() {
  stop_motor();
  current_status = "Terminated"
}

void detect() {
  check_back();
  check_front();
}

void check_back() {
  back_distance = ping_ultra(ULTRA_BACK);
  Serial.print("Back distance: ");
  Serial.print(back_distance);
  Serial.println("");
  if (back_distance > BACK_DMAX) {
    wait();
  }
}

void check_front() {
  front_distance = ping_ultra(ULTRA_FRONT);
  Serial.print("Front distance: ");
  Serial.print(front_distance);
  Serial.println("");
  if (front_distance < FRONT_DMAX) {
    check_dir();
  }
}

void wait() {
  current_status = "Wait";
  stop_motor();

  bool need_wait = true;
  while (need_wait) {
    Serial.println("=== WAIT ===");
    delay(STOP_WAIT_MS);
    back_distance = ping_ultra(ULTRA_BACK);
    if (back_distance < BACK_DMAX) {
      need_wait = false;
    }
  }
  delayMicroseconds(10);
  start_motor();
}

void check_dir() {
  stop_motor();
  left_distance = ping_ultra(ULTRA_LEFT);
  right_distance = ping_ultra(ULTRA_RIGHT);
  
  Serial.print("Left distance: ");
  Serial.println(left_distance);
  Serial.print("Right distance: ");
  Serial.println(right_distance);
  
  if (left_distance > right_distance){
    current_status = "Duck Left";
    turn_left(LEFT_DUCK_MS);
  }
  else {
    current_status = "Duck Right";
    turn_right(RIGHT_DUCK_MS);
  }
  delay(1000);
  start_motor();
}

void send_ultra() {
  digitalWrite(ULTRA_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRA_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRA_TRIG, LOW);
}

float recieve_ultra(int ultra_no) { 
  duration = pulseIn(ultra_no, HIGH, ULTRA_TIMEOUT);    // 30 ms timeout
  distance = (duration*.0343)/2;
  return distance;
}

float ping_ultra(int ultra_no) {
  send_ultra();
  recieve = recieve_ultra(ultra_no);
  delay(100);
  return recieve;
}

void start_motor() {
  Serial.println("=== START MOTOR ===");

  digitalWrite(LEFT_MOTOR1, HIGH);
  digitalWrite(LEFT_MOTOR2, LOW);

  digitalWrite(RIGHT_MOTOR1, HIGH);
  digitalWrite(RIGHT_MOTOR2, LOW);

  current_status = "Moving";
}

void stop_motor() {
  Serial.println("=== STOP MOTOR ===");

  digitalWrite(LEFT_MOTOR1, LOW);
  digitalWrite(LEFT_MOTOR2, LOW);

  digitalWrite(RIGHT_MOTOR1, LOW);
  digitalWrite(RIGHT_MOTOR2, LOW);
  
  current_status = "Stopped";
}

void turn_right(int duration) {
  Serial.println("=== TURN RIGHT ===");

  digitalWrite(LEFT_MOTOR1, HIGH);
  digitalWrite(LEFT_MOTOR2, LOW);

  digitalWrite(RIGHT_MOTOR1, LOW);
  digitalWrite(RIGHT_MOTOR2, HIGH);

  delay(duration);
}

void turn_left(int duration) {
  Serial.println("=== TURN LEFT ===");

  digitalWrite(LEFT_MOTOR1, LOW);
  digitalWrite(LEFT_MOTOR2, HIGH);

  digitalWrite(RIGHT_MOTOR1, HIGH);
  digitalWrite(RIGHT_MOTOR2, LOW);

  delay(duration);
}

// Handles commands received from the client (eg. python code)
void handleCommand() {
  if (server.hasArg("turn")) {
    int turnSignal = server.arg("turn").toInt();
    Serial.print("Received turn signal: ");
    Serial.println(turnSignal);

    switch (turnSignal) {
      case 0:
        current_status = "FORWARD";
        break;

      case 1:
        current_status = "TURN LEFT";
        turn_left(LEFT_TURN_MS);
        break;

      case 2:
        current_status = "TURN RIGHT";
        turn_right(RIGHT_TURN_MS);
        break;

      case 3:
        current_status = "BACKWARD";
        break;
      
      default:
        Serial.println("Unknown command");
        break;
    }
    server.send(200, "text/plain", "OK");
  } 
  else if (server.hasArg("action")) {
    int actionSignal = server.arg("action").toInt();
    Serial.print("Received action signal: ");
    Serial.println(actionSignal);

    switch (actionSignal) {
      case 0:
        machine_on = 0;   // stop car
        break;
      case 1:
        machine_on = 1;   // start car
        break;
      default:
        Serial.println("Unknown command");
        break;
   }
   server.send(200, "text/plain", "OK");
  }
  else {
    server.send(400, "text/plain", "Invalid Request");
  }
}

/*
The JavaScript code in handleRoot() fetches the status data from the "/status" route,
it triggers the client-side request for status data,
which in turn triggers the handleStatus() function to send the status data back to the client.
*/

// Handles requests for the status of the ESP32 car
void handleStatus() {
  String message = current_status + ";";
  message += String(front_distance) + ";";
  message += String(back_distance) + ";";
  message += String(left_distance) + ";";
  message += String(right_distance);
  server.send(200, "text/plain", message);
}

// Handles the root ("/") route of the web server.
void handleRoot() {
  String message = "<html><body>";
  message += "<h1>ESP32 Car Status</h1>";
  message += "<p>Status: <span id='current_status'>" + current_status + "</span></p>";
  message += "<p>Front distance: <span id='front_distance'>" + String(front_distance) + " cm</span></p>";
  message += "<p>Back distance: <span id='back_distance'>" + String(back_distance) + " cm</span></p>";
  message += "<p>Left distance: <span id='left_distance'>" + String(left_distance) + " cm</span></p>";
  message += "<p>Right distance: <span id='right_distance'>" + String(right_distance) + " cm</span></p>";
  message += "<script>";
  message += "function fetchData() {";
  message += "  fetch('/status').then(response => response.text()).then(data => {";
  message += "    const parts = data.split(';');";
  message += "    document.getElementById('current_status').innerText = parts[0];";
  message += "    document.getElementById('front_distance').innerText = parts[1] + ' cm';";
  message += "    document.getElementById('back_distance').innerText = parts[2] + ' cm';";
  message += "    document.getElementById('left_distance').innerText = parts[3] + ' cm';";
  message += "    document.getElementById('right_distance').innerText = parts[4] + ' cm';";
  message += "  });";
  message += "}";
  message += "setInterval(fetchData, 1000);"; // Fetch data every second
  message += "</script>";
  message += "</body></html>";
  server.send(200, "text/html", message);
}