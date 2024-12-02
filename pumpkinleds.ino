// Arduino Pumpkin LEDs
// Author: James Graves
// Date: 31/10/24
// Description: programs an Arduino to control an RGB LED. There are two patterns: a shifting rainbow and a flickering orangey light mimicking a candle. For Arduino club.
bool flickerMode = false; // if it is on flicker mode or rainbow mode. Kind of lazy to have it be a boolean but I don't have over 2 options so it works.
bool buttonPressed = false; 


// variables for rainbow LED code
int rgb[] = {10, 0, 0}; // array with how bright red, green, and blue should be in the LED
int increment = 1;
int colour = 1; // which colour in the rgb array to increment
int colourCounter = 0;

// variables for flickering LED code
int maxRed = 250; // maximum red brightness

void setup() {
  pinMode(12, INPUT_PULLUP); // enable internal pullup resistor for pin 12, where the button is connected
  randomSeed(analogRead(0)); 
}

void loop() {
  delay(100); // wait 100 milliseconds

  if(digitalRead(12) == HIGH && buttonPressed == false){ // buttonPressed variable is to make pressing the button have a toggle effect
    buttonPressed = true;  
    flickerMode = !flickerMode; // toggle flicker mode
    analogWrite(10, 0); // turn off LED.
    analogWrite(11, 0);
    analogWrite(9, 0);
  }
  
  if(digitalRead(12) == LOW && buttonPressed == true){
    buttonPressed = false;
  }
  
  if(!flickerMode){  // rainbow LED
    if (colourCounter != 10 ){        
          rgb[colour] += increment; 
          analogWrite(11, rgb[0]); 
          analogWrite(10, rgb[1]);
          analogWrite(9, rgb[2]);
          colourCounter++;   
        } else {
          colourCounter = 0;
          increment *= -1; // switch amount to increment by to negative/positive
          colour--; // move onto next colour
          if(colour < 0){ // to loop through the colours
            colour = 2;
          }
     }
  
  } else { // flickering LED
     int randomRed = random(maxRed);
     int randomGreen = randomRed/8 - random(8); // green level is much less than red, but also has randomness in it
     analogWrite(10, randomGreen > 0 ? randomGreen : 0); // makes sure that the green variable is not a negative number
     analogWrite(9, randomRed);
    }
}
