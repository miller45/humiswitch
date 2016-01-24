// Not needed anymore

/*

#include <Servo.h> 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
				
//simulate 2 relays with servo switching two microswitchtes
int servoPin=10;

long tSRELAY1=0; // millis when to switch off relay1
long tSRELAY2=0;
int lastServoPos=-1;
int midServoPos=100;
int leftServoPos=122;
int rightServoPos=88;

void SwitchOnSRelay1For(long msecs){
  tSRELAY1=millis()+msecs;
}

void SwitchOnSRelay2For(long msecs){
  tSRELAY2=millis()+msecs;
}

void ServoRelaysDutys(){
  int newServoPos=lastServoPos;
  long curMillis=millis();
  
  boolean bothOff=true;
  if( curMillis< tSRELAY1){
    newServoPos=leftServoPos;
    bothOff=false;
  }
  if( curMillis< tSRELAY2){
    newServoPos=rightServoPos;
    bothOff=false;
  }
  if(bothOff){
    newServoPos=midServoPos;
  }
  
  if(lastServoPos!=newServoPos){
      myservo.write(newServoPos);
      lastServoPos=newServoPos;
  }
}

void ServoRelaysInit(){
   myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object 
   lastServoPos=midServoPos;
   myservo.write(lastServoPos);
}

*/
