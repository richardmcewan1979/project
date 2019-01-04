//This version includes distance sensing

//this not working yet

//point is to integrat automation and bluetooth/python

#include "SoftwareSerial.h"
SoftwareSerial serial_connection(10, 9); //tx/rx
#define BUFFER_SIZE 64
char inData[BUFFER_SIZE];
char inChar=-1;
int count=0;
int i=0;
#define trigPin 11
#define echoPin 3

//wheel A
int ENA=6;
int IN1=12;
int IN2=8;

//wheel B
int ENB=5;
int IN3=7;
int IN4=4;

void setup() {
  //distance sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //wheels
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);  
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  
  //blue_tooth module
  Serial.begin(9600);
  serial_connection.begin(9600);
  serial_connection.println("Ready!!!");
  Serial.println("Started");

  
}



////function declarations outside of other loops



void loop() {
  
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
  
//Distance sensor output
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(2);
duration = pulseIn(echoPin, HIGH);
distance = int((duration /2)/29.1);
delay(10);

  serial_connection.println("Hello from Blue Distance:" +String(distance));
  count++;
 }
 delay(100);

}
