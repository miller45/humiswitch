

#include <Servo.h> 
#include <LiquidCrystal.h>

#include <dht.h>

#define DHT11_PIN 8
#define SERVO_PIN 9
#define ROT_APIN 10

dht DHT;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);


Servo myservo;  // create servo object to control a servo 
               //a maximum of eight servo objects can be created 

 

const int relaxpos=175;
const int activepos=0;
int midpos=89;
//const int relaxpos=140;
//const int activepos=0;
// include the library code:


static float floatvar = 12345.67;

static char humBuffer[15];
static char tmpBuffer[15];


int maxVal=13100;
int minVal=0;
 
void setup() 
{ 
  Serial.begin(9600);
  
  // init serve
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object 
  

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("init done");
  delay(1000);  
} 
 
 
void loop() 
{ 
	delay(1);
	int dial=analogRead(A4);
	delay(1);
	Serial.println(dial);
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(dial);
	int xdial=(midpos/2)+dial/10;
	int tmplvl=map(xdial,minVal,maxVal,30,60);
	lcd.setCursor(0, 1);
	lcd.print(xdial);
	myservo.write(xdial);
	delay(10);

	//89 mid
	//doSwitchOff();
#if off
  
  boolean dhtok=false;
 int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
      dhtok=true;
      break;
    case DHTLIB_ERROR_CHECKSUM: 
	break;
    case DHTLIB_ERROR_TIMEOUT: 
	break;
    default: 
        break;
  }
  lcd.clear();
  dtostrf(DHT.humidity,3, 1, humBuffer);
  dtostrf(DHT.temperature,3, 1, tmpBuffer);
  lcd.print( tmpBuffer );  
  lcd.print("C ");
  lcd.print( humBuffer );
  lcd.print ("rH");
  lcd.setCursor(0, 1);

  int tmplvl=map(dial,0,1024,30,60);
  lcd.print( "X ");
  lcd.print( dial );
  lcd.print( "   ");
// map(value, fromLow, fromHigh, toLow, toHigh)

  delay(500);
#endif
} 


void doSwitchOff(){
    myservo.write(activepos);
    delay(2000);
	int betpos=relaxpos/2;
	myservo.write(betpos);
	delay(2000);
    myservo.write(relaxpos);
	delay(2000);
}

//String formatTimeDigits (int num)
//{
//  String fmt="";
//  fmt+="";  
//  if(num<10){
//    fmt+="000";
//  }else
//  if(num<100){
//    fmt+="00";
//  }else
//  if(num<1000){
//    fmt+="0";
//  }
//  fmt+=num;
//  return fmt;  
//}

