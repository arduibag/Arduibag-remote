//-----------------------------------------------------------------
//
// ArduiBAG - Michaël d'AURIA
// 27/08/2014
//
// Remote control part
//
//-----------------------------------------------------------------

#include <SoftwareSerial.h> // Serial library

//----------------------------
// Hardware configuration
//----------------------------

// Joystick PIN
#define JOY1 0 // Analog
#define JOY2 1 // Analog
#define JOY3 2 // Digital

// LED 1 PIN
#define LED1R 5 //LED 1 Red
#define LED1G 6 //LED 1 Greed
#define LED1B 7 //LED 1 Blue

// LED 2 PIN
#define LED2R 8 //LED 2 Red
#define LED2G 9 //LED 2 Ged
#define LED2B 10 //LED 2 Blue

//Oldcode
char oldcode=1;

//----------------------------------
// SETUP
//----------------------------------

void setup() {
  
  //JOSTICK SWITCH 
  pinMode(JOY3, INPUT);
  
  //LED 1 initialisation
  pinMode(LED1R, OUTPUT);
  pinMode(LED1G, OUTPUT);
  pinMode(LED1B, OUTPUT);
  
  //LED 2 initialisation
  pinMode(LED2R, OUTPUT);
  pinMode(LED2G, OUTPUT);
  pinMode(LED2B, OUTPUT);
  
 // enable internal pullup - will then read high unless button is pressed to connect to Gnd 
  digitalWrite (JOY3, HIGH); // Activate switch
 
  // Serial communication for BLUETOOTH
  Serial.begin(9600); // Or 9600, 38400 depending on your firmware version
  
  //-------------------
  // TESTING LEDS
  //-------------------
  
      //Blue
      LED (1, 1);
      LED (2, 1);
      delay (800);

      // Green
      LED (1, 10);
      LED (2, 10);
      delay (800);
      
      // Red
      LED (1, 100);
      LED (2, 100);
      delay (800);

  //---------------------------
  // waiting for the bag
  //---------------------------
   
   while(!Serial.available()) {
      LED (1, 1);
      LED (2, 1);
      delay(500);
      LED (1, 0);
      LED (2, 0);
      delay(500);
      Serial.write('a');
  }
}

//----------------------------------
// MAIN LOOP
//----------------------------------

void loop() {

  char code;
  
  code = AJoyst();
  
  if (code and code!=oldcode) {
    Serial.print(code);
    oldcode = code;
  }
   if (Serial.available()){
    allumeLED(Serial.read());
  }
}

//----------------------------------
// JOYSTICK TESTER
//----------------------------------

char AJoyst() {
  
  int val1 = 0;
  int val2 = 0;
  int val3 = 0;

  val1 = analogRead(JOY1);
  delay(100); 
  val2 = analogRead(JOY2);
  //delay(100);
  val3 = digitalRead(JOY3);
 
 
  //CLICK
  if (val1>510 and val1<530 and val2>510 and val2<530 and val3==0)return 'a';
  
  //LEFT
  if (val1>510 and val1<530 and val2>1000)return 'A';

  //RIGHT
  if (val1>510 and val1<530 and val2<20)return 'B';
   
  //DOWN
  if (val1<20 and val2>510 and val2<530)return 'C';
    
  //UP
  if (val1>1000 and val2>510 and val2<530)return 'D';
  
  //UP-LEFT
  //if (val1<20 and val2<20) return 'E';

  //haut-droit
  //if (val1>1000 and val2<10) return 'F';

  //bas-gauche
  //if (val1<20 and val2>1000) return 'G';

  //bas-droite
  //if (val1>1000 and val2>1000) return 'H';

  return 0;

}

void allumeLED(char action) {
  switch (action) {
  
    case 'B' :
      LED(1, 110);
      LED(2, 0);
      oldcode = 1; 
    break;
    
    case 'A' :
      LED(1, 0);
      LED(2, 11);
      oldcode = 1;
    break;
    
    case 'R' :
      LED(1, 110);
    break;
    
    case 'L' :
      LED (2, 110);
    break;
    
    case 'S' :
      LED (1, 100);
      LED (2, 100);
    break;
    
    case 'T' :
      LED (1, 111);
      LED (2, 100);
    break;
    
    case 'M' :
      LED (1, 101);
      LED (2, 101);
    break;
    
    default:
      LED(1,0);
      LED(2,0);
    break;
    
  }
}

//LED
void LED(char ledNumber, char colorCode) {
  
  char r,g,b;
  
  r = colorCode / 100 % 10;
  g = colorCode / 10 % 10;
  b = colorCode % 10;
  
  //LED 1
  if (ledNumber==1) { 
   digitalWrite(LED1R, r);
   digitalWrite(LED1G, g);
   digitalWrite(LED1B, b);
  } else {
  //LED 2
   digitalWrite(LED2R, r);
   digitalWrite(LED2G, g);
   digitalWrite(LED2B, b);
  }
  
}
