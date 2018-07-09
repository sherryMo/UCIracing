// defines pins numbers
const int trigPin = 10;
const int echoPin = 11;
long duration;
int distance;
int transistorG = A2; // Initialzing Analog Output to TransistorG at A2
int transistorY = A3;
int transistorR = A4;

void setup()
{
  pinMode(transistorG, OUTPUT); // Sets the Analog A2 as an output
  pinMode(transistorY, OUTPUT); 
  pinMode(transistorR, OUTPUT); 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the Serial Monitor

}

void loop()
{

// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

  if ( distance <  10) {  

    Serial.println("Green Transistor On");  // Then the transitor Green turns on
    analogWrite(transistorG, 255);   // Sends out 5V on Output A3
    analogWrite(transistorR, 0);
    analogWrite(transistorY, 0);
    delay(1000); // Leaves it on for 1 seconds
  } 
  else if( 10 <= distance && distance <= 30){
    Serial.println("Yellow Transistor On");  // Then the transitor  turns on
    analogWrite(transistorY, 255);   // Sends out 5V on Output A2
    analogWrite(transistorG, 0);
    analogWrite(transistorR, 0);
    delay(1000);
  }
  else if( 30 <= distance && distance <= 60){
    Serial.println("Red Transistor On");  // Then the transitor Red turns on
    analogWrite(transistorR, 255);   // Sends out 5V on Output A4
    analogWrite(transistorG, 0);
    analogWrite(transistorY, 0);
    delay(1000);
  }
  else {  
    Serial.println("Transistor Off");  // Prints Transistor Off
    analogWrite(transistorG, 0);   // Turns off the Transistor
    analogWrite(transistorY, 0);
    analogWrite(transistorR, 0);    
    delay(1000);
  }

  delay(100); // Wait 100 ms 
} // loop

