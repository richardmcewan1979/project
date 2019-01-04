//this works to pass strings to java processing

//This version includes distance sensing
//This verison should be what is uplaoded to the robot module.
//it's sending distance over wifi

#include "SoftwareSerial.h"
SoftwareSerial serial_connection(10, 9); //tx/rx
#define BUFFER_SIZE 64
char inData[BUFFER_SIZE];
char inChar=-1;
int count=0;
int i=0;
float distance;
String value; 
#define trigPin 11
#define echoPin 3

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  serial_connection.begin(9600);
  serial_connection.println("Ready!!!");
  Serial.println("Started");
  
}

void loop() {

//not sure where to nest this stuff...

  
  //This will prevent bufferoverrun errors
  byte byte_count=serial_connection.available();
 if(byte_count)
 {
  Serial.println("incoming Data");
  int first_bytes=byte_count;
  int remaining_bytes=0;
  if(first_bytes=BUFFER_SIZE-1)
  {
    remaining_bytes=byte_count-(BUFFER_SIZE-1);
  }
  for(i=0;i<first_bytes;i++)
  {
    inChar=serial_connection.read();
    inData[i]=inChar;
  }
  inData[i]='\0';
  for(i=0;i<remaining_bytes;i++)
  {
    inChar=serial_connection.read();
  }
  Serial.println(inData);
  long duration, distance;
//added
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(2);
duration = pulseIn(echoPin, HIGH);
distance = float((duration /2)/29.1);
if ((distance > 99)){
distance = 10;
}
delay(25);
//end added
  value = distance;
  serial_connection.println(value);
  Serial.println(value);
  count=count+1;
 }

 delay(100);

}
