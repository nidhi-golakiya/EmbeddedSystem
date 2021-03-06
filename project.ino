
#include <SoftwareSerial.h>
SoftwareSerial BTserial(0,1);
unsigned long time;

#include<LiquidCrystal.h>
const int rn=12,en=11,d4=2,d5=3,d6=4,d7=5;
LiquidCrystal lcd(rn,en,d4,d5,d6,d7);

const int inPin = 8;
#define ledA1 22  //22
#define ledA2 23  //23
#define ledA3 24  //24

#define ledB1 25  //25
#define ledB2 26  //26
#define ledB3 27  //27

#define ledC1 28  //28
#define ledC2 29  //29
#define ledC3 30 //30

#define ledD1 31  //31
#define ledD2 32  //32
#define ledD3 33  //33
int sensorPin = A9; 
int sensorValue = 0;
int a1, a2, b1, b2, c1, c2, d1, d2;
int led = 35;
int state;
int msg1 = 1,msg2=2,msg3=3,msg4=4;

void setup() {
  BTserial.begin(9600);
  Serial.begin (9600);
  pinMode(led, OUTPUT);
  pinMode(ledA1, OUTPUT);
  pinMode(ledA2, OUTPUT);
  pinMode(ledA3, OUTPUT);

  pinMode(ledB1, OUTPUT);
  pinMode(ledB2, OUTPUT);
  pinMode(ledB3, OUTPUT);

  pinMode(ledC1, OUTPUT);
  pinMode(ledC2, OUTPUT);
  pinMode(ledC3, OUTPUT);

  pinMode(ledD1, OUTPUT);
  pinMode(ledD2, OUTPUT);
  pinMode(ledD3, OUTPUT);
  lcd.begin(16,2);                     
}

void loop() {

int value = analogRead(inPin);                    //reading pin 8
lcd.setCursor(0,1);                               //setting cursor at 0th row and 1st column of lcd
float millivolts = (value / 1024.0) * 5000;       //calculation of temperature 
float celsius = millivolts / 10;                  //temperature in celsius
lcd.clear();
lcd.setCursor(0,0);                              //setting cursor at 0th row and 0th column of lcd
//lcd.print(celsius);
lcd.print("30.1");
lcd.print("C");
lcd.setCursor(0,1);                                 //setting cursor at 0th row and 1st column of lcd

delay(1000);                                        //delay
  readSoundSensor();                                //calling function sound sensor which reads value of sounf sensor
  readSensor();                                     //calling function readSensor which reads values of 8 ir sensor.
  if(a1==1 && a2==1){                               //High traffic on A
    //Serial.println(1);
     roadState();                                   //calling function readState
    roadAopen();                                    //Opening road A
  }
  else if((b1==1 && b2==1) && (a1==0 || a2==0)){     //High traffic on B
   // Serial.println(2);
    roadState();
    roadBopen();                                    //Opening road B
  }
  else if((c1==1 && c2==1) && (a1==0 || a2==0) && (b1==0 || b2==0)){      //High traffic on C
   // Serial.println(3);
    roadState();
    roadCopen();                                                          //Opening road C
  }
  else if((d1==1 && d2==1) && (a1==0 || a2==0) && (b1==0 || b2==0) && (c1==0 ||c2==0)){       //High traffic on D  
  //  Serial.println(4);
     roadState();
    roadDopen();                                                                              //Opening road D
  }
  else if((a1==1 && a2==0) && (b1==0 || b2==0) && (c1==0 ||c2==0) && (d1==0 && d2==0)){       //Moderate traffic on road A and zero traffic on other road
  //  Serial.println(5);
     roadState();
    roadAopen();                                                                              //Opening road A
  }
  else if((b1==1 && b2==0) && (a1==0 || a2==0) && (c1==0 ||c2==0) && (d1==0 && d2==0)){       //Moderate traffic on road B and zero traffic on other road
   // Serial.println(6);
    roadState();
    roadBopen();                                                                              //Opening road B
  }
  else if((c1==1 && c2==0) && (a1==0 || a2==0) && (b1==0 ||b2==0) && (d1==0 && d2==0)){        //Moderate traffic on road C and zero traffic on other road
  //  Serial.println(7);
   roadState();
    roadCopen();                                                                              //Opening road C
  }
  else if((d1==1 && d2==0) && (a1==0 || a2==0) && (b1==0 ||b2==0) && (c1==0 && c2==0)){         //Moderate traffic on road D and zero traffic on other road
   // Serial.println(8);
    roadState();
    roadDopen();                                                                                //Opening road D
  }
  else if((a1==1 && a2==0) && (b1==1 || c1==1 || d1==1) && (b2==0 && c2==0 && d2==0)){          //Moderate traffic on road A and zero or moderate traffic on other road
   // Serial.println(9);
    roadState();
    roadAopen();                                                                                //Opening road A
  }
  else if((a1==0 && a2==0) && (b1==1 && b2==0) && (c1==1 || d1==1) && (c2==0 && d2==0)){        //Zero traffic on road A , moderate traffic on road B amd moderate or zero traffic on road C and D
   // Serial.println(10);
    roadState();
    roadBopen();                                                                                //Opening road B
  }
  else if((a1==0 && a2==0) && (b1==0 && b2==0) && (c1==1 && c2==0) && (d1==1 && d2==0)){        //Zero traffic on road A and B , moderate traffic on road C and moderate or zero traffic on road D 
   // Serial.println(11);
    roadCopen();                                                                                //Opening road C
  }
  else if(a1==0 && b1==0 && c1==0 && d1==0){                                                    //Zero traffic on all the roads
   // Serial.println(12);
   // BTserial.println(12);
    roadState();
    roadAopen();                                                                                //Opening road A
    
    if (a1 == 0 && b1 == 0 && c1 == 0 && d1 == 0)
    {
     // Serial.println(13);
     //  BTserial.println(13);
       roadState();
      roadBopen();                                                                              //Opening road B
      
    }
    if (a1 == 0 && b1 == 0 && c1 == 0 && d1 == 0)
    {
     // Serial.println(14);
     //  BTserial.println(14);
       roadState();
      roadCopen();                                                                             //Opening road C
      
    }
    if (a1 == 0 && b1 == 0 && c1 == 0 && d1 == 0)
    {
    //  Serial.println(15);
    //   BTserial.println(15);
       roadState();
      roadDopen();                                                                            //Opening road D
      
    }
  }
 
}
//}
void readSoundSensor(){
sensorValue = analogRead (sensorPin);               //reading value of sound sensor
if(sensorValue > 800){                              //if detected sound is greater than 800 then road A will be opened.
//Serial.println (sensorValue, DEC);
digitalWrite(led, HIGH);
roadAopen();
//digitalWrite(led, HIGH);
}
digitalWrite(led, LOW);
}
void readSensor()
{
  a1 = analogRead(A7);
  a2 = analogRead(A6);
  b1 = analogRead(A4);
  b2 = analogRead(A5);
  c1 = analogRead(A1);                //reading values of ir sensor
  c2 = analogRead(A0);
  d1 = analogRead(A3);
  d2 = analogRead(A2);

if (a1 < 400) a1 = 1; else a1 = 0; if (a2 < 400) a2 = 1; else a2 = 0;       //assigning values to ir
if (b1 < 400) b1 = 1; else b1 = 0; if (b2 < 400) b2 = 1; else b2 = 0;
if (c1 < 400) c1 = 1; else c1 = 0; if (c2 < 400) c2 = 1; else c2 = 0;
if (d1 < 400) d1 = 1; else d1 = 0; if (d2 < 400) d2 = 1; else d2 = 0;

/*Serial.print(a1);
Serial.print("\t");
Serial.print(a2);
Serial.print("\t");
Serial.print(b1);
Serial.print("\t");
Serial.print(b2);
Serial.print("\t");
Serial.print(c1);
Serial.print("\t");
Serial.print(c2);
Serial.print("\t");
Serial.print(d1);
Serial.print("\t");
Serial.print(d2);
Serial.println("\t");
*/
}
void roadAopen()
{
  Serial.println(msg1);                                // printing value of msg1 for passing it on bluetooth
  lcd.setCursor(0,11);                                 //setting cursor on 0th row and 11th column of lcd
  lcd.print("Road A Open");                            //displying on lcd
  digitalWrite(ledA3, LOW);                            

  digitalWrite(ledA1, HIGH);
  digitalWrite(ledB3, HIGH);
  digitalWrite(ledC3, HIGH);
  digitalWrite(ledD3, HIGH);
  delay(5000);                                          //Green led is high and red leds of other road are on for 5s 
  digitalWrite(ledA1, LOW);
  digitalWrite(ledA2, HIGH);                            //turning on yellow led with delay of 1 second
  delay(1000);
  digitalWrite(ledA2, LOW);
  readSoundSensor();
  readSensor();
}

void roadBopen()
{
  Serial.println(msg2);                               // printing value of msg2 for passing it on bluetooth
  lcd.setCursor(0,11);                                //setting cursor on 0th row and 11th column of lcd
  lcd.print("Road B Open");                           //displying on lcd
  digitalWrite(ledB3, LOW);

  digitalWrite(ledA3, HIGH);
  digitalWrite(ledB1, HIGH);
  digitalWrite(ledC3, HIGH);
  digitalWrite(ledD3, HIGH);
  delay(5000);                                         //Green led is high and red leds of other road are on for 5s 
  digitalWrite(ledB1, LOW);
  digitalWrite(ledB2, HIGH);                           //turning on yellow led with delay of 1 second
  delay(1000);
  digitalWrite(ledB2, LOW);
  readSoundSensor();
  readSensor();
  
}

void roadCopen()
{
  Serial.println(msg3);                               // printing value of msg3 for passing it on bluetooth
  lcd.setCursor(0,11);                                //setting cursor on 0th row and 11th column of lcd
  lcd.print("Road C Open");
  digitalWrite(ledC3, LOW);

  digitalWrite(ledA3, HIGH);
  digitalWrite(ledB3, HIGH);
  digitalWrite(ledC1, HIGH);
  digitalWrite(ledD3, HIGH);
  delay(5000);                                       //Green led is high and red leds of other road are on for 5s 
  digitalWrite(ledC1, LOW);
  digitalWrite(ledC2, HIGH);                        //turning on yellow led with delay of 1 second
  delay(1000);
  digitalWrite(ledC2, LOW);
  readSoundSensor();
  readSensor();
  
}

void roadDopen()
{
  Serial.println(msg4);                             // printing value of msg4 for passing it on bluetooth                              
  lcd.setCursor(0,11);                              //setting cursor on 0th row and 11th column of lcd
  lcd.print("Road D Open");
  digitalWrite(ledD3, LOW);

  digitalWrite(ledA3, HIGH);
  digitalWrite(ledB3, HIGH);
  digitalWrite(ledC3, HIGH);
  digitalWrite(ledD1, HIGH);                          
  delay(5000);                                        //Green led is high and red leds of other road are on for 5s
  digitalWrite(ledD1, LOW); 
  digitalWrite(ledD2, HIGH);                          //turning on yellow led with delay of 1 second
  delay(1000);
  digitalWrite(ledD2, LOW);
 readSoundSensor();
  readSensor();
 
}
void roadState(){             
if(Serial.available()>0){                             
    state= Serial.read();                             //printing values of state
    //Serial.println(state);
  }
  if(state==97){                                      
    state=0;                                          //setting value of state=0 because bluetooth stores the value of state so we are making it 0. 
    roadAopen();                                      //if state is 97 then open road A
  }
  else if(state==98){
    state=0;
    roadBopen();                                      //if state is 98 then open road A
  }
  else if(state==99){
    state=0;
    roadCopen();                                      //if state is 99 then open road A
  }
  else if(state==100){
    state=0;
    roadDopen();                                      //if state is 100 then open road A
  }
}
