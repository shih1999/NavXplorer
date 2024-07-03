// Define pin numbers
#define ULTRA_TRIG 15
#define ULTRA_BACK 11     // Back
#define ULTRA_FRONT 42    // Front-mid
#define ULTRA_LEFT 7      // Front-left
#define ULTRA_RIGHT 40    // Front-right

#define LED 3

// Define distance thresholds
#define FRONT_DMAX 30
#define BACK_DMAX 30

// Define durations
#define LEFT_DUCK_MS 100
#define RIGHT_DUCK_MS 100
#define STOP_WAIT_MS 3000
#define ULTRA_TIMEOUT 30000

float recieve;
float duration, distance;
float front_distance, back_distance;
float left_distance, right_distance;

void setup() {
  // set ultra pin
  pinMode(ULTRA_TRIG, OUTPUT);
  pinMode(ULTRA_BACK, INPUT);
  pinMode(ULTRA_FRONT, INPUT);  
  pinMode(ULTRA_LEFT, INPUT); 
  pinMode(ULTRA_RIGHT, INPUT);
  
  Serial.begin(115200);   // baud rate
}

void loop() {
  detect();
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

float recieve_ultra(int ultra_no) { 
  duration = pulseIn(ultra_no, HIGH, ULTRA_TIMEOUT);    // 30 ms timeout
  distance = (duration * 0.0343)/2;
  return distance;
}

float ping_ultra(int ultra_no) {
  send_ultra();
  recieve = recieve_ultra(ultra_no);
  delay(100);
  return recieve;
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
  while (need_wait) {
    Serial.println("=== WAIT ===");
    delay(STOP_WAIT_MS);
    back_distance = ping_ultra(ULTRA_BACK);
    if (back_distance < BACK_DMAX) {
      need_wait = false;
    }
  }
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
    turn_left(LEFT_DUCK_MS);
  }
  else {
    turn_right(RIGHT_DUCK_MS);
  }
  start_motor();
}

void start_motor() {
  Serial.println("=== START MOTOR ===");
}

void stop_motor() {
  Serial.println("=== STOP MOTOR ===");
}

void turn_right(int duration) {
  Serial.println("=== TURN RIGHT ===");
}

void turn_left(int duration) {
  Serial.println("=== TURN LEFT ===");
}