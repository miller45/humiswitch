void SerialInOutInit(){
   Serial.begin(38400);
}

void SerialInOutDutys(){
}

void SerialPrintAll(int curTemperature,int curHumidity,int curMaxOn,int curMaxOff){
  Serial.print("T=");
  Serial.print(curTemperature);
  
  Serial.print(" H=");
  Serial.print(curHumidity);
  Serial.print(" ON>");
  Serial.println(curMaxOn);
}
