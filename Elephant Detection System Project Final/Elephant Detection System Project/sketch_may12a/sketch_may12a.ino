// Pin Definitions
const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 4;
const int echoPin2 = 5;

void setup() {
  // Initialize Serial at 9600 baud for VISA communication
  Serial.begin(9600);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}

void loop() {
  // 1. Get Distance from Sensor 1
  float dist1 = getDistance(trigPin1, echoPin1);

  // 2. Get Distance from Sensor 2
  float dist2 = getDistance(trigPin2, echoPin2);

  // 3. Send the data as a comma-separated string
  // Format: "45.20,110.50"
  Serial.print(dist1);
  Serial.print(",");
  Serial.println(dist2); // println adds the \n termination character

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

  // Return 0 if out of range
  if (distance > 400 || distance <= 0)
    return 0.00;

  return distance;
}