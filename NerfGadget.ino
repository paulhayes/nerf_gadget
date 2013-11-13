#include <LedControl.h>
#include<stdlib.h>

const int MODE_MAGAZINE = 0;
const int MODE_SPEEDOMETER = 1;

const int irled = 12;
const int ird = 2;
const int led = 13;

const int modeButton = 2;
const int actionButton = 3;
const int resetButton = 4;

const int maxDuration = (0ul)-1;
const int THRESHOLD = 900;
double nerfDartLength = 0.071;
 

unsigned long startTime;
unsigned long endTime;
unsigned long lastIrChange;
boolean irOn;

boolean modeButtonLastState;
boolean actionButtonLastState;
boolean resetButtonLastState;

int mode = 0;

const int numMagazines = 4;
int magazine = 0;
int magazines[4] = {6,18,25,35};

LedControl lc1=LedControl(10,11,12,2);
 
void setup(){
  pinMode(irled,OUTPUT);
  pinMode(led,OUTPUT);
 
  pinMode( modeButton, INPUT );
  pinMode( actionButton, INPUT );
 
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
 
  if( analogRead(ird ) > THRESHOLD ){
     
    startTime = micros();  
    digitalWrite(led,HIGH);
    while( analogRead(ird ) > THRESHOLD ){
        //delayMicroseconds(8);          
    }
    digitalWrite(led,LOW);
    endTime = micros();
    
    /* ir sensor tripped */
    switch(mode){
      case MODE_MAGAZINE:
        magazine--;
        MagazineMode();
        break;
      case MODE_SPEEDOMETER:
        SpeedometerMode();
        break;
    }
  }
  
  CheckButtons();
}

inline void CheckButtons(){
  boolean modeButtonState = digitalRead( modeButton ) == HIGH;
  boolean actionButtonState = digitalRead( actionButton ) == HIGH;  
  boolean resetButtonState = digitalRead( resetButton ) == HIGH;
  
  if( modeButtonState != modeButtonLastState && !modeButtonState ){
    mode = ( mode + 1 ) % 2;
    displayInt( 0 );
    Serial.print("mode pressed ");
    Serial.println( mode );
  }

  if( actionButtonState != actionButtonLastState && !actionButtonState ){
    ActionPressed();
    Serial.println("action pressed");
  }

  if( resetButtonState != resetButtonLastState && !resetButtonState ){
    ResetPressed();
    Serial.println("reset pressed");

  }
  
  modeButtonLastState = modeButtonState;
  actionButtonLastState = actionButtonState;
  resetButtonLastState = resetButtonState;
}

inline void ActionPressed(){
  if( mode == MODE_MAGAZINE ){
    magazine--;
    MagazineMode();
  }
  else {
  }
}

inline void ResetPressed(){
  if( mode == MODE_MAGAZINE ){
    int i=0;
    while( magazines[i] <= magazine && i<numMagazines ) i++;
    if( i==numMagazines ) i=0;
    Serial.println( i );
    magazine = magazines[i];
    MagazineMode();
  }
  else {
    
  }
}

void SpeedometerMode(){
  unsigned long duration = 0;
  if( endTime < startTime ) {
    duration = ( maxDuration - startTime ) + endTime;
  }
  else duration = endTime - startTime;
   
  double speed = nerfDartLength * 1000000.0 / duration;
  
  if( Serial ){
    Serial.println( duration );
    Serial.print( "speed: " );
    Serial.println( speed );      
  }
  
  displayDouble( speed );
}

inline void MagazineMode(){
  if( magazine < 0 ) magazine = 0;
  displayInt( magazine );
}

void displayInt(int value){
  byte tens = ( value / 10 ) % 10;
  byte ones = value % 10;
  
  lc1.setDigit(0,0,tens,false);
  lc1.setDigit(0,1,ones,false);

}

void displayDouble(double value){
  char buffer[4];
  unsigned char minStringWidthIncDecimalPoint = 4;
  char numVarsAfterDecimal = 2;
  dtostrf( value, minStringWidthIncDecimalPoint, numVarsAfterDecimal, buffer );

  int j=0;
  for(int i=0;i<4;i++){
    if( buffer[i] == '.' || buffer[i] == '0' ) continue;
    byte number = buffer[i] - 48;
    boolean isDotNext = i<2 && buffer[i+1] == '.';
    lc1.setDigit(0,j,number,isDotNext);
    j++;
  }  
}


