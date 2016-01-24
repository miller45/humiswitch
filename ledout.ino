
void LedOutDutys(){
}

void LedOutInit(){

}

void LedOutSetRFLed(int val){
   digitalWrite(13, val);
}

void PulseRFLed(int ontime){
   digitalWrite(13, HIGH);
   delay(ontime);
   digitalWrite(13, LOW);
}

void StrobeRFLed(int count, int ontime,int offtime){  
   for(int i=0;i<count;i++){
     digitalWrite(13, HIGH);
     delay(ontime);
     digitalWrite(13, LOW);
     delay(offtime);
   }
}


