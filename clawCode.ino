#include <Servo.h>

//Defining pins

#define VCC_PIN 13

#define TRIGGER_PIN 12 // sonar trigger pin will be attached to Arduino pin 12

#define ECHO_PIN 11 // sonar echo pint will be attached to Arduino pin 11

#define GROUND_PIN 10 //

#define MAX_DISTANCE 200 // maximum distance set to 200 cm

#define openAngle 120

#define closeAngle 50


// defines variables

long duration;

int distance;

//int closed = 0; //State of claw: 0 = Open, 1 = closed

Servo myservo;  // create servo object to control a servo

int val;   


void setup() {
  
  myservo.attach(9);  
  Serial.begin(9600);  // set data transmission rate to communicate with computer

  pinMode(ECHO_PIN, INPUT) ;  

  pinMode(TRIGGER_PIN, OUTPUT) ;

  pinMode(GROUND_PIN, OUTPUT);  

  pinMode(VCC_PIN, OUTPUT);  

  digitalWrite(GROUND_PIN,LOW); 

  digitalWrite(VCC_PIN, HIGH) ; 



  myservo.write(openAngle); //start opened
  
}

void loop() {
 
  digitalWrite(TRIGGER_PIN, LOW); 

  delayMicroseconds(2);

  digitalWrite(TRIGGER_PIN, HIGH);  

  delayMicroseconds(20);

  digitalWrite(TRIGGER_PIN, LOW);


  duration = pulseIn(ECHO_PIN, HIGH);

  distance= duration*0.034/2;  // Calculating the distance

  if(distance < 15){ // Signal to pickup object

      delay(1000); // All delays for getting the claw into position above pickup/drop sites
      val = closeAngle;
     
  }  
  else if(distance > 30){ // Signal to drop object
      delay(1500);
      val = openAngle;
      
  }

  if(distance > 40){ //Reset to open position
      delay(1500);
      val = openAngle;
      
  }

   myservo.write(val);
    
      
 // if the distance measurement becomes extremely high, it is likely an error. Default to a maximum value of MAX_DISTANCE to identify this condition.

  if (distance > MAX_DISTANCE)  

    {distance = MAX_DISTANCE ;}


   

  Serial.print("Distance: ") ;  // Prints the distance on the Serial Monitor

  Serial.println(distance);
  

}
