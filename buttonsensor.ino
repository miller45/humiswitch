int button1Pin=6;

boolean IsButton1On(){
  boolean result=false;
  int buttonState=digitalRead(button1Pin);
  if(buttonState==HIGH){
    result=true;
  }
  return result;
}

void ButtonSensorDutys(){
  // nothing so far
}
