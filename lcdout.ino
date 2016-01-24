
#define startupdelay 1000

// include the library code:
#include <LiquidCrystal.h>
#include <LCDKeypad.h>

int ccDegree=0;
int ccDegreeCelsius=1;
int ccRHumidity=2;


LCDKeypad lcd;



// make custom character degree
byte degreebits[8] = {
  0b01100,
  0b10010,
  0b01100,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

// make custom character degree
byte degreecelsiusbits[8] = {
  0b11000,
  0b11000,
  0b00000,
  0b00110,
  0b01000,
  0b01000,
  0b00110,
  0b00000
};



// make custom character degree
byte rhumiditybits[8] = {
  0b11000,
  0b11000,
  0b00000,
  0b00000,
  0b00101,
  0b00111,
  0b00101,
  0b00000
};

int ccPercentWithr=3; 
// make custom character degree
byte ccPercentWithrBits[8] = {
  0b10100,
  0b01000,
  0b10100,
  0b00000,
  0b00111,
  0b00100,
  0b00100,
  0b00000
};

//int ccFlipONChar=4; 
//// make custom character degree
//byte ccFlipONCharBits[8] = {
//  0b10000,
//  0b01000,
//  0b00100,
//  0b00010,
//  0b00001,
//  0b00000,
//  0b00000,
//  0b00000
//};
//
//int ccFlipOFFChar=5; 
//// make custom character degree
//byte ccFlipOFFCharBits[8] = {
//  0b00001,
//  0b00010,
//  0b00100,
//  0b01000,
//  0b10000,
//  0b00000,
//  0b00000,
//  0b00000
//};


#define ccArrowUpChar 4
// make custom character degree
byte ccArrowUpCharBits[8] = {
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00000
};

#define ccArrowDownChar 5
// make custom character degree
byte ccArrowDownCharBits[8] = {
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00000
};




static char humBuffer[15];
static char tmpBuffer[15];
static char genBuffer[15];

void LCDOutInit(){
  //   lcd.begin(16, 2);
  delay(startupdelay);
  lcd.begin(16, 2);
  lcd.createChar(ccDegree, degreebits);
  lcd.createChar(ccDegreeCelsius, degreecelsiusbits);
  lcd.createChar(ccRHumidity,rhumiditybits);
  lcd.createChar(ccPercentWithr,ccPercentWithrBits),
  lcd.createChar(ccArrowUpChar,ccArrowUpCharBits),
  lcd.createChar(ccArrowDownChar,ccArrowDownCharBits),
  lcd.clear();
  lcd.print("LCDinit");   
  lcd.write(ccDegreeCelsius);
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("        ");
  // delay(5000);
}

void LCDOutDutys(){
}


// valuemapping

//  0123456789ABCDEFGH
//0!45° 40% 
//1!ON>50% OFF<45%


void LCDPrintTemperature(int temp){
  lcd.setCursor(0,0);
  dtostrf(temp,2, 0, tmpBuffer);
  lcd.print(tmpBuffer);
  lcd.write(ccDegreeCelsius);

}

void LCDPrintHumidity(int humi){
  lcd.setCursor(3,0);
  dtostrf(humi,2, 0, humBuffer);
  lcd.print(humBuffer);
  lcd.write(ccPercentWithr); //percent with small r
  lcd.print("H");
}  

void LCDPrintOnOff(int onHumi,int offHumi){
  lcd.setCursor(0,1);
  lcd.print(">");
  lcd.print(onHumi); 
}

void LCDPrintDHTState(int state,boolean flipFlop, boolean fanShouldBeOn){

  lcd.setCursor(4,1);
  dtostrf(state,2, 0, genBuffer);
  lcd.print(genBuffer);
  lcd.setCursor(4,1);
  //  lcd.print(" ");
  lcd.setCursor(7,1);
  if(fanShouldBeOn){
    lcd.write(ccArrowUpChar);
  }
  else{
    lcd.write(ccArrowDownChar);
  }
  if(flipFlop){
    lcd.cursor();
    //lcd.write(ccFlipONChar);
 }
  else{
    lcd.noCursor();
    //lcd.write(ccFlipOFFChar);
  }

}

void LCDPrintBtnState(int state,long lastOffTime){

  lcd.setCursor(11,1);
//  dtostrf(state,2, 0, genBuffer);
//  lcd.print(genBuffer);
  dtostrf(lastOffTime,6, 0, genBuffer);
  lcd.print(genBuffer);
  
}




int curfakePoti=0;


long tLastBtnOffTime=0;



boolean IsButton1On(){
  boolean result=false;
  int keyP=ReadKeyPad();
  if(keyP==KEYPAD_SELECT){
    result=true;
  }
  return result;
}

void ButtonSensorDutys(){
  long mnow=millis();
  boolean go=true;
  // nothing so far
  int keyP=ReadKeyPad();
  if(keyP==KEYPAD_NONE){
     tLastBtnOffTime=mnow;
  }
  int nd=CalcOnTime(mnow, tLastBtnOffTime);
  LCDPrintBtnState(keyP,nd);   
    if(keyP==KEYPAD_UP){    
        if(curfakePoti+nd<1024){
           curfakePoti+=nd;
        }
    }
    else
      if(keyP==KEYPAD_DOWN){
        if(curfakePoti-nd>0){
           curfakePoti-=nd;
        }

      }
 
}

float CalcOnTime(long nowTime,long lastTime){
  float m=nowTime;
  float l=lastTime;
  float cdiff=(m-l);
  
  return cdiff/500;
}


int ReadKeyPad()
{
  int buttonPressed=lcd.button();  
  return buttonPressed;
}


int ReadPotiValueMapped(int from, int to){
  int raw=curfakePoti;
  //  raw=512;
  int mapped=map(raw,0,1023,from,to);
  return constrain(mapped,from,to);
}

void PotiSensorDutys(){
}


