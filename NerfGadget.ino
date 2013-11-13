#include <LedControl.h>
#include<stdlib.h>

const int irled = 12;
const int ird = 2;
const int led = 13;
const int maxDuration = (0ul)-1;
const int THRESHOLD = 900;
double nerfDartLength = 0.071;
 
 
unsigned long startTime;
unsigned long endTime;
unsigned long lastIrChange;
boolean irOn;
 
LedControl lc1=LedControl(10,11,12,2);
 
void setup(){
  pinMode(irled,OUTPUT);
  pinMode(led,OUTPUT);
 
  irOn = false;
 
   digitalWrite( irled, HIGH );
 
  Serial.begin(9600);
 
  /*while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }*/
 
  Serial.println("Analyze IR Remote");
 
  lc1.shutdown(0,false);
  lc1.setIntensity(0,8);
  lc1.setDigit(0,0,4,false);
  lc1.setDigit(0,1,2,false);
}
 
void loop(){
  while( true ){
 
  if( analogRead(ird ) > THRESHOLD ){
     
      startTime = micros();
     
      digitalWrite(led,HIGH);
     
      while( analogRead(ird ) > THRESHOLD ){
          //delayMicroseconds(8);
          
          
      }
     
      digitalWrite(led,LOW);
 
      endTime = micros();
     
      unsigned long duration = 0;
      if( endTime < startTime ) {
        duration = ( maxDuration - startTime ) + endTime;
      }
      else duration = endTime - startTime;
     
      double speed = nerfDartLength * 1000000.0 / duration;
      int speedRound = speed + 0.5;
      Serial.println( duration );
      Serial.print( "speed: " );
      Serial.println( speed );
      Serial.print( "speed rounded: " );
      Serial.println( speedRound );
      
      char buffer[4];
      unsigned char minStringWidthIncDecimalPoint = 4;
      char numVarsAfterDecimal = 2;
      dtostrf( speed, minStringWidthIncDecimalPoint, numVarsAfterDecimal, buffer );
      
      Serial.print( "speed: " );
      Serial.println( buffer );
      int j=0;
      for(int i=0;i<4;i++){
        if( buffer[i] == '.' || buffer[i] == '0' ) continue;
        byte number = buffer[i] - 48;
        boolean isDotNext = i<2 && buffer[i+1] == '.';
        lc1.setDigit(0,j,number,isDotNext);
        j++;
      }
  }
 
  }
}


