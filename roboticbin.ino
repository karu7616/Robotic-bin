 /*
                            *
                            * Project Name:  ROBOTIC BIN
                            * Author List:   Krishna kumar
                            * Filename:      roboticbin
                            * Functions:     stepper motor drivig,servo(open,close),sensor detection for metal,plastic and bio degradable
                            * Global Variables: 
                            *const int stepsPerRevolution=200;
                            */

/* This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.*/
#include <Stepper.h>
#include <Servo.h>

Servo myservo;
Servo myservo1;// create servo object to control a servo
const int stepsPerRevolution=200;
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  // set the speed at 10 rpm:
  myStepper.setSpeed(10);
  
  
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(6,INPUT);//inductive sensor pin : for metal detection
  pinMode(5,INPUT);//inductive sensor pin : for metal detection
  pinMode(4,INPUT);//capacitive sensor pin : for plastic detection
  pinMode(3,INPUT);//ir sensor2 pin : for waste detection
  pinMode(2,INPUT);//ir sensor1 pin : for hand detection
 // initiaize the servo pin
  myservo.attach(1); //bottom servo motor : for dropping the waste in bins from the hopper
  myservo1.attach(0); //top servo : for opening and closing the hopper of bin
  
}

void loop()
{
  /*
   * Function Name: ir sensor1 for hand detection
   * Input: ir sensor1
   * Output: top servo 
  */
  if(digitalRead(2)==LOW)       //sensor detection for hand
  {
    myservo1.write(180);        // tell servo to go to position 180(open).
    delay(3000);
    myservo1.write(0);          // tell servo to go to position 0(close).
  }
  /*
   * Function Name: ir sensor2 for waste detection
   * Input: ir sensor2
   * Output: bottom servo 
  */
 if(digitalRead(3)==LOW)
 {    if(digitalRead(5)||digitalRead(6))  //if metal is detected
        {
           myStepper.step(60);              // tell stepper to go to position of bin of metal.
           myservo.write(120);              // tell servo to go to position 120(open).
           delay(3000);
           myservo.write(50);               // tell servo to go to position 50(close).
           myStepper.step(-60);             // tell stepper to go to position of bin of metal.
        }
      else if(digitalRead(0)==HIGH) //if biodegradable waste is detected 
        {
           myStepper.step(-60);             // tell stepper to go to position of bin of plastic.
           myservo.write(120);              // tell servo to go to position 120(open).
           delay(3000);
           myservo.write(50);               // tell servo to go to position 50(close).
           myStepper.step(60);              // tell stepper to go to position of bin of plastic.
        }
      else //it is plastic
        {
           myservo.write(120);               // tell servo to go to position 120(open). 
           delay(3000);
           myservo.write(50);                 // tell servo to go to position 50(close).
        }
 }
}
