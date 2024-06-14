#include <WiFi.h>
#include <WebServer.h>

// Own wifi credentials
const char* ssid = "Yvonne";
const char* password = "Yvonne0813";

// create web server on port 80
WebServer server(80);

// Define pin numbers
#define ULTRA_TRIG 15
#define ULTRA_BACK 11     // Back
#define ULTRA_FRONT 42    // Front-mid
#define ULTRA_LEFT 7      // Front-left
#define ULTRA_RIGHT 40    // Front-right

#define LEFT_MOTOR1 38
#define LEFT_MOTOR2 37    
#define RIGHT_MOTOR1 35   
#define RIGHT_MOTOR2 36
#define LEFT_MOTORen 21
#define RIGHT_MOTORen 20

#define LED 3

// Define distance thresholds
#define FRONT_DMAX 80
#define BACK_DMAX 60

// Define durations
#define LEFT_TURN_MS 200
#define RIGHT_TURN_MS 300
#define LEFT_DUCK_MS 3
#define RIGHT_DUCK_MS 3
#define STOP_WAIT_MS 500

#define ULTRA_TIMEOUT 300000

float receive;
float duration, distance;
float front_distance, back_distance;
float left_distance, right_distance;
String current_status = "Idle";
int machine_on = 0;   // 0: off, 1: on

void setup() {
  // NOTE: Please ensure the baud rate matches with the serial monitor
  Serial.begin(115200);

  // Connect to Wi-Fi
  connectToWiFi();

  // Start the server
  server.on("/", handleRoot);
  server.on("/status", handleStatus);
  server.on("/action", handleAction);
  server.on("/turn", handleTurn);
  server.begin();
  Serial.println("HTTP server started");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

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
  analogWrite(LEFT_MOTORen, 100);
  analogWrite(RIGHT_MOTORen, 100);
  
  stop_motor();   // Ensure motors are stopped initially
}

void loop() {
  server.handleClient();
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }
  if (machine_on) {
    detect();
  }
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

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

// Handles requests for the status of the ESP32 car
void handleStatus() {
  String message = current_status + ";";
  message += String(front_distance) + ";";
  message += String(back_distance) + ";";
  message += String(left_distance) + ";";
  message += String(right_distance);
  server.send(200, "text/plain", message);
}

void handleAction() {
  if (server.hasArg("action")) {
    String action = server.arg("action");
    Serial.print("Action command received: ");
    Serial.println(action);
    if (action == "1") {
      start_motor();
    } else if (action == "0") {
      stop_motor();
    }
    server.send(200, "text/plain", "Action command received");
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}

void handleTurn() {
  if (server.hasArg("turn")) {
    String turn = server.arg("turn");
    Serial.print("Turn command received: ");
    Serial.println(turn);
    if (turn == "1") {
      turn_left(LEFT_TURN_MS);
    } else if (turn == "2") {
      turn_right(RIGHT_TURN_MS);
    }
    server.send(200, "text/plain", "Turn command received");
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}

void detect() {
  check_back();
  check_front();
}

void send_ultra() {
  digitalWrite(ULTRA_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRA_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRA_TRIG, LOW);
}

float receive_ultra(int ultra_no) { 
  duration = pulseIn(ultra_no, HIGH, ULTRA_TIMEOUT);    // 30 ms timeout
  distance = (duration * 0.0343) / 2;
  return distance;
}

float ping_ultra(int ultra_no) {
  send_ultra();
  receive = receive_ultra(ultra_no);
  delay(100);
  return receive;
}

void check_front() {
  front_distance = ping_ultra(ULTRA_FRONT);
  Serial.print("Front distance: ");
  Serial.println(front_distance);
  if (front_distance < FRONT_DMAX) {
    check_dir();
  }
}

void check_back() {
  back_distance = ping_ultra(ULTRA_BACK);
  Serial.print("Back distance: ");
  Serial.println(back_distance);
  if (back_distance > BACK_DMAX) {
    wait();
  }
}

void wait() {
  bool need_wait = true;
  stop_motor();
  current_status = "Wait";
  while (need_wait) {
    Serial.println("=== WAIT ===");
    delay(STOP_WAIT_MS);
    back_distance = ping_ultra(ULTRA_BACK);
    if (back_distance < BACK_DMAX) {
      need_wait = false;
    }
  }
  delay(50);
  start_motor();
  current_status = "Moving";
}

void check_dir() {
  stop_motor();
  left_distance = ping_ultra(ULTRA_LEFT);
  right_distance = ping_ultra(ULTRA_RIGHT);
  
  Serial.print("Left distance: ");
  Serial.println(left_distance);
  Serial.print("Right distance: ");
  Serial.println(right_distance);
  
  if (left_distance > right_distance) {
    current_status = "Turn Left";
    turn_left(LEFT_DUCK_MS);
  } else {
    current_status = "Turn Right";
    turn_right(RIGHT_DUCK_MS);
  }
  delay(50);
  start_motor();
  current_status = "Moving";
}

void start_motor() {
  Serial.println("=== START MOTOR ===");
  digitalWrite(LEFT_MOTOR1, HIGH);
  digitalWrite(LEFT_MOTOR2, LOW);

  digitalWrite(RIGHT_MOTOR1, HIGH);
  digitalWrite(RIGHT_MOTOR2, LOW);
  current_status = "Moving";
  machine_on = 1;
  delay(100);
}

void stop_motor() {
  Serial.println("=== STOP MOTOR ===");

  digitalWrite(LEFT_MOTOR1, LOW);
  digitalWrite(LEFT_MOTOR2, LOW);

  digitalWrite(RIGHT_MOTOR1, LOW);
  digitalWrite(RIGHT_MOTOR2, LOW);
  current_status = "Stopped";
  machine_on = 0;
  delay(100);
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
