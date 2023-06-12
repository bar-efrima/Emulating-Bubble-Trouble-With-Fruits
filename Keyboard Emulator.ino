/*
 * playing the game Bubble Trouble by emulating a PC keyboard

Banana gun:
When pressed, the character shoots and outputs a laser beam sound.
Orange Controller: 
The character moves according to the orange movement.
Cheat mode: 
by touching the sweet potato, an additional player emerges and helps the character shot.

The circuit- 
-The banana is connected to pin A1.
-When touched, the program responds according to the capacity change. 
It outputs a laser beam sound and emulates the "up arrow key,“ which leads to a gunshot.
-The sweet potato is connected to pin A2.
When touched, the cheat mode is activated, the program responds to the capacity change and as a result
emulates commands on the keyboard, which adds an additional shooter.
-Movement: motion sensor: The accelerometer measures the x and y movements according to the orange movment , 
it emulate the keyboard's arrows corresponding to the movement measured. 

Video link:
https://www.youtube.com/watch?v=XRUjBdCev2o&ab_channel=BarEfrima

Created By:
Bar Efrima 
*/
#include <Adafruit_CircuitPlayground.h>
#include "Keyboard.h" // keyboard keys
#include "pitches.h" //musical notes libary

char ctrlKey = KEY_LEFT_GUI;
int sensorValue1, sensorValue2 ;
int lightValue;

void setup() {
  CircuitPlayground.begin();
  Keyboard.begin();
}

void loop() {
    float movementX, movementY, movement;
     movementX = abs(CircuitPlayground.motionX());  // read the X motion (absolute value)
     movementY = abs(CircuitPlayground.motionY());  // read the Y motion (absolute value)
     movement = (movementX  , movementY ); // aggregate the movement sensed
     lightValue = CircuitPlayground.lightSensor();
     sensorValue1 = CircuitPlayground.readCap(A1); // read the capacity from pi A1
     sensorValue2 = CircuitPlayground.readCap(A2);// read the capacity from pi A2
     
  //cheat code -  helper friend - add one more player who will shot together
  if( sensorValue2>1015){
    Keyboard.press(KEY_ESC);
    Keyboard.press(KEY_DOWN_ARROW);
     Keyboard.press(0xE0);
    Keyboard.releaseAll();
    delay(1001);
    Keyboard.press(KEY_DOWN_ARROW) ;
    delay(100);
    Keyboard.press(0xE0);
    
  }
  
  // firing gun with sound
    if(sensorValue1 > 1015){   
      Keyboard.press(KEY_UP_ARROW);
      Serial.print(sensorValue1);
      CircuitPlayground.playTone(NOTE_A7 , 200); 
      delay(100);
    }
   // moving player to the left 
    if(movement>5){
      //Serial.print("left");
      //Serial.println(movement);
      Keyboard.press(KEY_LEFT_ARROW); 
      delay(300);
     }
    // moving player the right
       if(movement<5 && movement>3){
        Keyboard.press(KEY_RIGHT_ARROW); 
         delay(200);
       }
 
  Keyboard.releaseAll();
}
