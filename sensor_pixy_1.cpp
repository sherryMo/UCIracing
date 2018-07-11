//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This sketch is a good place to start if you're just getting started with 
// Pixy and Arduino.  This program simply prints the detected object blocks 
// (including color codes) through the serial console.  It uses the Arduino's 
// ICSP port.  For more information go here:
//
// http://cmucam.org/projects/cmucam5/wiki/Hooking_up_Pixy_to_a_Microcontroller_(like_an_Arduino)
//
// It prints the detected blocks once per second because printing all of the 
// blocks for all 50 frames per second would overwhelm the Arduino's serial port.
//
   
#include <SPI.h>  
#include <Pixy.h>

// This is the main Pixy object 
Pixy pixy;
const int trigPin = 10;
const int echoPin = 11;
long duration;
int distance;
int transistorG = A2; // Initialzing Analog Output to TransistorG at A2
int transistorY = A3;
int transistorR = A4;

void setup()
{
  Serial.begin(9600);
  pixy.init();
  Serial.print("Starting...\n");
  pinMode(transistorG, OUTPUT); // Sets the Analog A2 as an output
  pinMode(transistorY, OUTPUT); 
  pinMode(transistorR, OUTPUT); 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

}

void loop()
{ 
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32]; 

  int w; //the width od the wall
  int h; // height
  int s; // area
  
  // grab blocks!
  blocks = pixy.getBlocks();
  
  // If there are detect blocks, print them!
  if (blocks)
  {
    i++;
    w = pixy.blocks[i].width;
    h = pixy.blocks[i].height;
    s = w * h;
    // do this (print) every 50 frames because printing every
    // frame would bog down the Arduino
    if (i%50==0 && s > 300)
    {
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);
      for (j=0; j<blocks; j++)
      {
        sprintf(buf, "  block %d: ", j);
        Serial.print(buf); 
        pixy.blocks[j].print();
        w = pixy.blocks[j].width;
        h = pixy.blocks[j].height;
        s = w * h;
        Serial.print(s);
         if (s > 3200 && h > w){
          digitalWrite(trigPin, LOW);
          delayMicroseconds(2);
          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);
          duration = pulseIn(echoPin, HIGH);
          distance= duration*0.034/2;
          Serial.print("Distance: ");
          Serial.println(distance);
            if ( distance <  10) {  

    Serial.println("Green Transistor On\n");  // Then the transitor Green turns on
    analogWrite(transistorG, 255);   // Sends out 5V on Output A3
    analogWrite(transistorR, 0);
    analogWrite(transistorY, 0);
    delay(500); // Leaves it on for 1 seconds
  } 
  else if( 10 <= distance && distance <= 30){
    Serial.println("Yellow Transistor On\n");  // Then the transitor  turns on
    analogWrite(transistorY, 255);   // Sends out 5V on Output A2
    analogWrite(transistorG, 0);
    analogWrite(transistorR, 0);
    delay(500);
  }
  else if( 30 <= distance && distance <= 60){
    Serial.println("Red Transistor On\n");  // Then the transitor Red turns on
    analogWrite(transistorR, 255);   // Sends out 5V on Output A4
    analogWrite(transistorG, 0);
    analogWrite(transistorY, 0);
    delay(500);
  }
  else {  
    Serial.println("Transistor Off\n");  // Prints Transistor Off
    analogWrite(transistorG, 0);   // Turns off the Transistor
    analogWrite(transistorY, 0);
    analogWrite(transistorR, 0);    
    delay(500);
  }

  delay(50); // Wait 100 ms   
        }
        else{
           Serial.print("sensor do not record!\n");
           analogWrite(transistorG, 0);   // Turns off the Transistor
           analogWrite(transistorY, 0);
           analogWrite(transistorR, 0); 
        }
      }
    }
  }  
}
