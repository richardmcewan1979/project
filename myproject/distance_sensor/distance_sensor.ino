//this is good and working

#define trigPin 11
#define echoPin 3

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
long duration, distance;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(2);
duration = pulseIn(echoPin, HIGH);
distance = (duration /2)/29.1;

Serial.println(distance);
delay(10);

}
