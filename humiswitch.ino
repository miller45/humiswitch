

const long ccFANDEFER=10000;
const long ccLCDDEFER=100;
const long ccBUTTONDEFER=3000;
const long ccENSUREFANDEFER=12000;
const int ccRELAYSUSTAIN=2000;
const int ccMaxSensWheel=5;
boolean FanShouldBeOn=false;
boolean FanIsOn=false;
boolean FanChange=false;
long tDefer=0;
long tDeferLcdOut=0;
long tDeferEnsureFan=0;

int CurMaxOn=0;
int CurMaxOff=0;
int CurTemperature=0;
int CurHumidity=0;
int SensWheel=0;


void setup(){
  SerialInOutInit();
  StrobeRFLed(6,100,50);
  LCDOutInit(); //on bus1
  RelaysInit();
  //ServoRelaysInit();
 //  SwitchOnRelay1For(ccRELAYSUSTAIN);
}


void loop(){
  // call dutys funcs    
  //ServoRelaysDutys();
  
  RelaysDutys(); // normal relays not used any more
  ButtonSensorDutys();
  PotiSensorDutys();
  SerialInOutDutys();
  HumiSensorDutys();
  LCDOutDutys();
  // read sensors 
  // Button
  boolean button1IsOn=IsButton1On();  
  // Poti
 
  int curPot=ReadPotiValueMapped(30,75);  
  
  CurMaxOn=curPot;
  CurMaxOff=curPot;
  //Humidity Temp

  if(IsHumiSensorReady()){
     CurTemperature=GetCurrentTemperature();
     CurHumidity=GetCurrentHumidity();
     
  }
  
    
  // read inputs (button/poti)  
  // (preprocess inputs)
  // evaluate incoming (sensors and inputs)  
  
  //
  if(button1IsOn || EnsureFanNeeded()){
    DelayEnsureFan();
    FanIsOn=!FanShouldBeOn;
    FanChange=true;
  }
  
  // decide what to switch
  if(millis()>tDefer){
//    if(button1IsOn){
//      if(FanShouldBeOn){   
//         FanShouldBeOn=false;
//         FanChange=true;
//
//      }else{
//         FanShouldBeOn=true;
//         FanChange=true; 
//      }  
//      tDefer=millis()+ccBUTTONDEFER;
//    }else{
      //switch for humi
      if(CurHumidity>0 && CurHumidity<CurMaxOff){
          FanShouldBeOn=false;           
          FanChange=true;
          DelayEnsureFan();
      }
      if(CurHumidity>CurMaxOn){
          FanShouldBeOn=true;
          FanChange=true;  
          DelayEnsureFan();     
      }
//    }    
      tDefer=millis()+ccFANDEFER;
  }
  // do switch/proceed switch
  if(FanChange){
    if(FanShouldBeOn){
        if(!FanIsOn){
            SwitchOnRelay2For(ccRELAYSUSTAIN); //eg 2000
            FanIsOn=true;
        }
    }else{
        if(FanIsOn){
            SwitchOnRelay1For(ccRELAYSUSTAIN);
            FanIsOn=false;
        }
    }
    FanChange=false;
  }
  // display stuff
  if(millis()>tDeferLcdOut){

    tDeferLcdOut=millis()+ccLCDDEFER;  

    LCDPrintTemperature(CurTemperature);
    LCDPrintHumidity(CurHumidity);
    LCDPrintOnOff(CurMaxOn,CurMaxOff);
    SerialPrintAll(CurTemperature,CurHumidity,CurMaxOn,CurMaxOff);

    boolean SensFlipFlop=false;
    if(IsHumiSensorReady()){
      
       SensFlipFlop=(SensWheel % ccMaxSensWheel)==0;
       if(SensWheel<ccMaxSensWheel){
         SensWheel++;
       }else{
         SensWheel=0;
       }       
    }   
                
    LCDPrintDHTState(GetLastCHKState(),SensFlipFlop,FanShouldBeOn); 

  }

}

void DelayEnsureFan(){
   tDeferEnsureFan=millis()+ccENSUREFANDEFER;
}

boolean EnsureFanNeeded(){
   return (millis()>tDeferEnsureFan);
}



