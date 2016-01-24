/*
  LiquidCrystal Library 
 
 using a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
  
  The circuit (default):
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

#define startupdelay 1000

// include the library code:
#include <LiquidCrystal.h>

int ccDegree=0;
int ccDegreeCelsius=1;
int ccRHumidity=2;


// initialize the library with the numbers of the interface pins
//sparkfun model  LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8); //bus 1
LiquidCrystal lcd(3, 4, 9, 10,11,12);
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
   lcd.begin(8, 2);
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
  }else{
     lcd.write(ccArrowDownChar);
  }
  if(flipFlop){
      lcd.cursor();
      //lcd.write(ccFlipONChar);
  }else{
      lcd.noCursor();
      //lcd.write(ccFlipOFFChar);
  }

}
