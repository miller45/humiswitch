int potiPin=A2;


int ReadPotiValueRaw(){
  return analogRead(potiPin);
}

int ReadPotiValueMapped(int from, int to){
   int raw=ReadPotiValueRaw();
   int mapped=map(raw,0,1022,from,to);
   return constrain(mapped,from,to);
}

void PotiSensorDutys(){
}
