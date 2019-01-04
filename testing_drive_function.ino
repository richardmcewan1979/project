
//Introducing *Jeff* an obstacle avoiding robot
//Richard McEwan 2018

///////////////////////////////////////////////
//////Initialise pins///////////////////////////
///////////////////////////////////////////////
//////Global variables//////////////////////////
///////////////////////////////////////////////


// connect motor controller pins to Arduino digital pins
// motor one
int enA = 6;
int in1 = 12;
int in2 = 8;

// motor two
int enB = 5;
int in3 = 7;
int in4 = 4;

//sensor
const int trigPin = 11;
const int echoPin = 9;
long duration;
int distance;

//set the threshold for obstacle avoidance (cm)
int threshold = 20;

//set a counter. 
//Modulo division will produce a crude randomiser for responding function
int count = 0;


///////////////////////////////////////////////
///////////The set up function/////////////////
///////////////////////////////////////////////


void setup() {
// put your setup code here, to run once:

//radar pins
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
Serial.begin(9600);

// set all the motor control pins to outputs
pinMode(enA, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
  
//initial delay creates a pause before Jeff acts
delay(2000);
}


///////////////////////////////////////////////
//////////////Radar function///////////////////
///////////////////////////////////////////////

void radar()
{
//updates the global variable distance
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

distance = duration*0.034/2;
Serial.print("distance: ");
Serial.println(distance);
delay(10);
}


/////////////////////////////////////////////////
////////Individual Motor functions///////////////
/////////////////////////////////////////////////
////////Stop, Forward and Back///////////////
/////////////////////////////////////////////////

//motor A stop
void right_stop()
{
  // turn off motor A (Right)
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
}

//motor B stop
void left_stop()
{
  // turn off motor B (left)
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
}

//motor A forward
void right_forward()
{
      // turn on motor A (Right)
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
}

//motor B forward
void left_forward()
{
  // turn on motor B (left)
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
}

//motor A backward
void right_backward()
{
      // turn on motor A (Right)
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
}

//motor B backward
void left_backward()
{
  // turn on motor B (left)
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
}

////////////////////////////////////////////
/////Driving functions//////////////////////
////////////////////////////////////////////
/////Forward, reverse, right, left, still///
////////////////////////////////////////////

void forward()
{
right_forward();
left_forward();
}

void reverse()
{
right_backward();
left_backward();
}

void right()
{
//A back, B forward
right_backward();
left_forward();
}

void left()
{
//B back, A forward
right_forward();
left_backward();
}

void still()
{
right_stop();
left_stop();  
}


///////////////////////////////////////////////
////////////Responding to obstacle function////
///////////////////////////////////////////////
//////Stop, reverse, and a random turn/////////
///////////////////////////////////////////////
///modulo division on count determines direction
////////////////////////////////////////////////

void respond()
{
  if (count % 2 == false)
  {
     still();
    delay(750);
    reverse();
    delay(500); 
    right();
    delay(300);
  } else {
     still();
    delay(750);
    reverse();
    delay(500);
    left(); 
    delay(300);
  }
}


//////////////////////////////////////////////
//////////////////////////////////////////////
////////Main drive function///////////////////
//////////////////////////////////////////////

void drive()
{

//get the distance
radar();

  // if the distance above threshold go forward
  if (distance > threshold) {
    forward();
    Serial.print("going forward ");
  } 
  
  //If distance less than threshold respond
  else {
   respond();
  Serial.print("responding ");
  }

//added serial readouts for testing and debugging.
}



///////////////////////////////////////////////
///////////Main loop function//////////////////
///////////////////////////////////////////////

void loop() {
// put your main code here, to run repeatedly:

count +=1;
drive();
//delay to steady the signal
delay(10);

}



/*

References and notes (for myself).
1. Google: 'TopTechBoy.com', Paul McWorter, to introduce Arduino and circuits.
Approx 4-10 hours/lessons could be based on his stuff or just follow his videos. Excellent tuition.  
He is an engineer/teacher who does cool Python/Arduino stuff and high attitude balloons. 
Takes students on path to use potentiometer to increase brightness of LED, and beyond.
2. instructables.com, search Arduino for ideas and links to products.
3. Sensor: HC-SRO4 Ultrasonic Sensor
4. Motor relay: L298N Dual Motor Controller. Google to see how to run them obvious from the code. Note need to remove two EN pins (enablers for PWM to be able to accelerate motors). I used 200 as a constant. Range 0-255 like LEDS on PWM.
5. Cheap Chinese Arduino copy required I download new driver software patch for the USB driver chip.
(See on the chip CH340G or something, hard to read without binoculars, google to find a driver to download). 
6. £15 from Banggood.com for for chassis, sensor, switch, motors, motor relay, cheap Arduino  wheels and few wires. Bargain.
7. Chassis is fiddly and very small annoying nuts and bolts, so next I'd buy the kit but use a different body e.g. Mechano or Lego maybe. 
8. Powering off a 9v battery. 
9. Motor relay feeds off 5v to power Arduino.
10. Be a good summary project to a crash electronics course for kids. Labour time approx 5 -7 hours for me.
11.Additional costs: Bought a glue gun, solder iron, multimeter, few female/male wires and breadboard.
12. Code is mine apart from standard sensor stuff. 

*/

