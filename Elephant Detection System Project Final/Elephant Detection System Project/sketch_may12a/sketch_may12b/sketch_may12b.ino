// // Pin Definitions
// const int enA = 9;  // PWM pin for speed control
// const int in1 = 8;  // Direction pin 1
// const int in2 = 7;  // Direction pin 2

// void setup() {
//   // Set all motor control pins to outputs
//   pinMode(enA, OUTPUT);
//   pinMode(in1, OUTPUT);
//   pinMode(in2, OUTPUT);

//   // Set initial direction to FORWARD
//   digitalWrite(in1, HIGH);
//   digitalWrite(in2, LOW);
// }

// void loop() {
//   // Accelerate from 0 to maximum speed (255)
//   for (int i = 0; i <= 255; i++) {
//     analogWrite(enA, i);
//     delay(20); // Adjust delay to change acceleration speed
//   }

//   delay(500); // Hold max speed for 1 second

//   // Decelerate from maximum speed to 0
//   for (int i = 255; i >= 0; i--) {
//     analogWrite(enA, i);
//     delay(20);
//   }

//   delay(500); // Stay off for 1 second
// }







// //////////////////////with motor controllers and ultrasonic sensors

// Pin Definitions
const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 4;
const int echoPin2 = 5;

// ================= L298N MOTOR PINS (ADDED) =================
const int ENA = 6;   // PWM Motor A speed
const int IN1 = 7;
const int IN2 = 8;

const int ENB = 9;   // PWM Motor B speed
const int IN3 = 10;
const int IN4 = 11;

// ============================================================

void setup() {
  // Initialize Serial at 9600 baud for VISA communication
  Serial.begin(9600);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // ================= MOTOR SETUP (ADDED) =================
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // =======================================================
}

void loop() {

  // 1. Get Distance from Sensor 1
  float dist1 = getDistance(trigPin1, echoPin1);

  // 2. Get Distance from Sensor 2
  float dist2 = getDistance(trigPin2, echoPin2);

  // 3. Send the data as a comma-separated string
  Serial.print(dist1);
  Serial.print(",");
  Serial.println(dist2);

  // ================= MOTOR CONTROL FROM LABVIEW (ADDED) =================
  if (Serial.available() > 0) {

    String input = Serial.readStringUntil('\n'); // read full line

    int commaIndex = input.indexOf(',');

    if (commaIndex > 0) {

      int pwm1 = input.substring(0, commaIndex).toInt();
      int pwm2 = input.substring(commaIndex + 1).toInt();

      // Motor A direction forward
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
         
        //  Apply PWM speed
      analogWrite(ENA, pwm1);

      // Motor B direction forward
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

      // Apply PWM speed
      analogWrite(ENB, pwm2);
    }
  }
  // =====================================================================

  delay(100);
}

// Function to calculate distance in cm
float getDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);

  float distance = duration * 0.034 / 2.0;

  if (distance > 400 || distance <= 0)
    return 0.00;

  return distance;
}