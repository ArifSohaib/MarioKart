//#include <Wire.h> 
//#include <Servo.h>
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7);  // Set the LCD I2C address
// Analog Pin A4 SDA - Data 
// Analog Pin A5 SCL - Clock (Edge Pin)
/*
 * Filename: Bluetooth.ino
 * Source: https://www.youtube.com/watch?v=fJvtMszk2G4
 * Date: March 2, 2017
*/

char c;
char recievedChar;
boolean newData = false;
//SoftwareSerial mySerial(10,11);
// Reading 4x4 Keypad with ONE Arduino Pin
// by Hari Wiguna, 2016
// Source: https://www.youtube.com/watch?v=G14tREsVqz0&t=325s
// Check schematics and resistors placement.


int ENA = 6;
int ENB = 5;
int in1 = 7;
int in2 = 8;
int in3 = 9;
int in4 = 11;

int spd = 255;
int spdT = 150;
int dly =15;
int dlyP = 30;
int dlyT = 30;

// Information on L298N and PWM control
// PWM ranges from 0 to 255. Pins D6 & D9 are used here.  Use analogWrite(6,255) for PWM.
//http://tronixstuff.com/2014/11/25/tutorial-l298n-dual-motor-controller-modules-and-arduino/
void setup()
{ 
  
  //pinMode(RIGHT_FRONT,OUTPUT); 
  //pinMode(RIGHT_REAR,OUTPUT); 
//  pinMode(LEFT_FORWARD,OUTPUT); 
//  pinMode(LEFT_REVERSE,OUTPUT); 
//  pinMode(RIGHT_FORWARD,OUTPUT);
//  pinMode(RIGHT_REVERSE,OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in3, OUTPUT);

  Serial.begin(9600);
  
//  mySerial.begin(9600);
  //Serial.println("Testing Bluetooth.  Sync with Android Bluetooth now.");
}
void loop()
{ 
  recvInfo();
  moveUsingInput();
  //Test1();
}

void moveUsingInput(){
  int control = (recievedChar - '0');

  if(newData){
    Serial.print(control);
  }

  while(newData == true){
    
    if(control == 1){
      FORWARD(spd, dly);
      Serial.println("moving forward");
      //delay(dly*3);
      //PAUSE(spd, dlyP);
    }
    else if (control == 2){
      REVERSE(spd, dly);
      Serial.println("moving reverse");
      //delay(dly*3);
      //PAUSE(spd, dlyP);
    }
    else if (control == 3){
      
      LEFT(spdT, dlyT);
      Serial.println("moving left");
      //delay(dly*3);
      //PAUSE(spd, dlyP);
    }
    else if (control == 4){
      RIGHT(spdT, dlyT);
      Serial.println("moving right");
      //delay(dly*);
      //PAUSE(spd, dlyP);
    }
    else if(control == 5){
      PAUSE(spd, dlyP);
      Serial.println("paused");
    }
    else if(control == 6){
      spd = spd + 20;
      spdT = spdT + 20;
      Serial.println("increasing speed");
      Serial.println(spd);
    }
    else if(control == 7){
      spd = spd - 20;
      spdT = spdT - 20;
      Serial.println("decreasing speed");
      Serial.println(spd);
    }
    else{
      Serial.println("unknown input");
      PAUSE(spd,dlyP);
    }
    newData = false;
    //PAUSE(spd,dlyP);
  }

    

}

void FORWARD(int spd, int dly)
{ 
//  for(int i=0; i<=spd;i+=10){
//    
//    analogWrite(LEFT_FORWARD,i);
//    analogWrite(RIGHT_FORWARD, i);
//    analogWrite(LEFT_REVERSE,0);
//    analogWrite(RIGHT_REVERSE,0);
//    delay(dly);
//  }
  analogWrite(ENA, spd);
  analogWrite(ENB, spd);
  digitalWrite(in1, HIGH);
  digitalWrite(in4, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
}
void REVERSE(int spd, int dly)
{           
//  for(int i=0; i<=spd; i+=10){  
//    analogWrite(LEFT_FORWARD,0);
//    analogWrite(RIGHT_FORWARD, 0);
//    analogWrite(LEFT_REVERSE,i);
//    analogWrite(RIGHT_REVERSE,i);
//    delay(dly);
//  }
  analogWrite(ENA, spd);
  analogWrite(ENB, spd);
  digitalWrite(in1, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
}
void LEFT(int spd, int dly)
{           
//  int spdR = spd/2;
//  for(int i=0;i<=spd;i+=10){
//    
//    analogWrite(LEFT_FORWARD,i);
//    analogWrite(RIGHT_FORWARD, 0);
//    analogWrite(LEFT_REVERSE,0);
//    analogWrite(RIGHT_REVERSE,i/2);
//    delay(dly);
//  }
  analogWrite(ENA, spd);
  analogWrite(ENB, spd/2);
  digitalWrite(in1, HIGH);
  digitalWrite(in4, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
}
void RIGHT(int spd, int dly)
{ 
//  int spdR = spd/2;
//  for(int i=0;i<=spd;i+=10){
//    analogWrite(LEFT_FORWARD,0);
//    analogWrite(RIGHT_FORWARD, i);
//    analogWrite(LEFT_REVERSE,i/2);
//    analogWrite(RIGHT_REVERSE,0);
//    delay(dly);
//  }
  analogWrite(ENA, spd/2);
  analogWrite(ENB, spd);
  digitalWrite(in1, HIGH);
  digitalWrite(in4, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
}

void PAUSE(int spd, int dly)
{ 
//  for(int i=spd; i>=0;i-=10){
//    analogWrite(LEFT_FORWARD,i);
//    analogWrite(RIGHT_FORWARD, i);
//    analogWrite(LEFT_REVERSE,i);
//    analogWrite(RIGHT_REVERSE,i);
//    delay(dly);
//  }
  analogWrite(ENA, 0);
  analogWrite(ENA, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}  
void SQUARE()
{ 
//  delay(5000); lcd.setCursor ( 0, 0 ); lcd.print ("STOPPED.           ");      
//  lcd.setCursor ( 0, 1 ); lcd.print ("                 ");      
  digitalWrite(4,LOW);    digitalWrite(5,LOW);   analogWrite(6,0);
  digitalWrite(7,LOW);  digitalWrite(8,LOW);  analogWrite(9,0);
  while (1) {};
}

void recvInfo(){
  if(Serial.available() > 0){
    recievedChar = Serial.read();
    newData = true;
  }
}
 
  

