

int relay1Pin=17;
int relay2Pin=16;

long tRELAY1=0; // millis when to switch off relay1
long tRELAY2=0;

void SwitchOnRelay1For(long msecs){
  tRELAY1=millis()+msecs;
}

void SwitchOnRelay2For(long msecs){
  tRELAY2=millis()+msecs;
}

void RelaysDutys(){
 
  long curMillis=millis();
  if( curMillis< tRELAY1){
    digitalWrite(relay1Pin,HIGH);
    //LedOutSetRFLed((curMillis  % 30 < 10));

  }else{
    digitalWrite(relay1Pin,LOW);
   // LedOutSetRFLed(LOW);
  }
  if(curMillis< tRELAY2){
    digitalWrite(relay2Pin,HIGH);
    //LedOutSetRFLed((curMillis  % 30 < 20) );
  }else{
    digitalWrite(relay2Pin,LOW);
    //LedOutSetRFLed(LOW);
  }
 
}

void RelaysInit(){
   pinMode(relay1Pin,OUTPUT);
   pinMode(relay2Pin,OUTPUT);
}


