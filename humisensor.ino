#include <dht.h>

#define DHT11_PIN 8

const long ccDHT11PollMillis=2000;
long tDeferHumi=0;

dht DHT;

boolean _humiSensorIsReady=false;
int lastCHK=DHTLIB_ERROR_TIMEOUT;


void HumiSensorDutys(){
  if(millis()>tDeferHumi){
    tDeferHumi=millis()+ccDHT11PollMillis;
  }else{
    return;
  }
  
  int chk = DHT.read11(DHT11_PIN);

  switch (chk)
  {
    case DHTLIB_OK:  
      _humiSensorIsReady=true;
      break;
    case DHTLIB_ERROR_CHECKSUM: 
      _humiSensorIsReady=false;
      break;
    case DHTLIB_ERROR_TIMEOUT: 
      _humiSensorIsReady=false;
      break;
    default: 	
      _humiSensorIsReady=false;
      break;
  }  
  lastCHK=chk;
}

int GetLastCHKState(){
  return lastCHK;
}

boolean IsHumiSensorReady(){
     return _humiSensorIsReady;
}

int GetCurrentHumidity(){
  int res=DHT.humidity;  
  return res;
}

int GetCurrentTemperature(){
  int res=DHT.temperature;  
  return res;
}
