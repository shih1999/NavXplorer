// Define pin numbers
#define LEFT_MOTOR1 38
#define LEFT_MOTOR2 37    
#define RIGHT_MOTOR1 35   
#define RIGHT_MOTOR2 36

#define LEFT_MOTORen 21
#define RIGHT_MOTORen 20
   
void setup() {
  pinMode(LEFT_MOTORpin1, OUTPUT);
  pinMode(LEFT_MOTORpin2, OUTPUT);
  pinMode(RIGHT_MOTORpin1, OUTPUT);
  pinMode(RIGHT_MOTORpin2, OUTPUT);
  pinMode(LEFT_MOTORen, OUTPUT);
  pinMode(RIGHT_MOTORen, OUTPUT);
}

void loop() {
  analogWrite(LEFT_MOTORen, 70);
  analogWrite(RIGHT_MOTORen, 70);
  
  digitalWrite(LEFT_MOTORpin1, HIGH);
  digitalWrite(LEFT_MOTORpin2, LOW);

  digitalWrite(RIGHT_MOTORpin1, HIGH);
  digitalWrite(RIGHT_MOTORpin2, LOW);
  delay(3000);

  digitalWrite(LEFT_MOTORpin1, LOW);
  digitalWrite(LEFT_MOTORpin2, HIGH);

  digitalWrite(RIGHT_MOTORpin1, LOW);
  digitalWrite(RIGHT_MOTORpin2, HIGH);
  delay(3000);
}
