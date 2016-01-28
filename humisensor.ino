#include <DHT22.h>

#define DHT22_PIN 11

const long ccDHT11PollMillis=3000;
long tDeferHumi=0;

// Setup a DHT22 instance
DHT22 myDHT22(DHT22_PIN);

boolean _humiSensorIsReady=false;
int lastCHK=DHT_ERROR_DATA_TIMEOUT; 


void HumiSensorDutys(){
  if(millis()>tDeferHumi){
    tDeferHumi=millis()+ccDHT11PollMillis;
  }else{
    return;
  }
  
  DHT22_ERROR_t chk = myDHT22.readData();

  switch (chk)
  {
    case DHT_ERROR_NONE:
      _humiSensorIsReady=true;
      break;
      case DHT_BUS_HUNG:
      _humiSensorIsReady=false;
//      Serial.println("BUS Hung ");
      break;
    case DHT_ERROR_NOT_PRESENT:
//      Serial.println("Not Present ");
      _humiSensorIsReady=false;
      break;
    case DHT_ERROR_ACK_TOO_LONG:
//      Serial.println("ACK time out ");
      _humiSensorIsReady=false;
      break;
    case DHT_ERROR_SYNC_TIMEOUT:
//      Serial.println("Sync Timeout ");
      _humiSensorIsReady=false;
      break;
    case DHT_ERROR_DATA_TIMEOUT:
//      Serial.println("Data Timeout ");
      _humiSensorIsReady=false;
      break;
    case DHT_ERROR_TOOQUICK:
//      Serial.println("Polled to quick ");
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
  int res=myDHT22.getHumidityInt()/10;
  return res;
}

int GetCurrentTemperature(){
  int res=myDHT22.getTemperatureCInt()/10;
  return res;
}
