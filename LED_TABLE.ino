/***LED Table***
 * Created by: Nick Janita
 * 
 * How to use: Designed to be used with a button to
 * switch modes. All that needs to be changed is the defined
 * variables depending on how many rows/leds you are using. 
*/

#include <FastLED.h>


FASTLED_USING_NAMESPACE
//567 is original num
#define DATA_PIN    2
#define LED_TYPE    NEOPIXEL
#define COLOR_ORDER GRB
#define NUM_LEDS    567
#define ROW_0   0
#define ROW_1   NUM_LEDS/3 
#define ROW_2   NUM_LEDS/3 + ROW_1
#define BRIGHTNESS          50
#define FRAMES_PER_SECOND  240
#define NUM_PATTERNS 7
#define BUTTON_PIN  8

//Initializing memory for LEDS
CRGB leds[NUM_LEDS];
char btValue = "";
char input = "";
String inputString = "";
//The last int in the array is the background color
long customPat[43];

void setup() {
  delay(3000); // 3 second delay for recovery
  //
  Serial.begin(9600);
    
  //Bluetooth Value
  
  //Configuring leds to FastLED
  FastLED.addLeds<LED_TYPE,DATA_PIN>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  //Setting intial brightness
  FastLED.setBrightness(BRIGHTNESS);

  //Setting up button with a Pullup resistor (press is low)
   pinMode(BUTTON_PIN, INPUT_PULLUP); 
  

}

   //Creating array of the pattern functions
  typedef void (*ledPatterns)();
  ledPatterns patternList[] = {solidRainbow,horizontalLines,rainbow, confetti, OHIO, juggle, bpm,caramelldansen};
  
  // Index number of which pattern is currently playing
  int patternIndex = 0;
  //Base color that rotates
  int gHue = 0;
  int color =0;

  
void loop()
{ 
  //Reading in BT value if any 
  btValueReader();
   
  //If the BT value is 2 it goes to Solid color mode
  if(btValue == '2'){
    Serial.println("Going to btColor()");
    btColor();
  }
  if(btValue == '3'){
    customPattern();
  }
  
//  //plays current pattern
    patternList[patternIndex]();

  //Shows the current LED pattern
  if(patternIndex != 0){
      FastLED.show();  
      FastLED.delay(1000/FRAMES_PER_SECOND);
  }
//Delay to change speed of the LEDS
//
   //Reading if button is pressed, if it is, half second delay and pattern change
  if(patternChange()){
    nextPattern();
    delay(500);
    btValue = "";
  }

  //Changes the speed of the color change in patterns that use gHue
  EVERY_N_MILLISECONDS(1) {
    gHue+=5;
    } 
}


//Adds one to the array playing the next pattern
void nextPattern()
{
  ++patternIndex;
  if(patternIndex >= NUM_PATTERNS){
    patternIndex = 0;
  }
}

void horizontalLines()
{
  fill_rainbow(&leds[ROW_0], ROW_1, gHue, 5);
  fadeToBlackBy(leds, NUM_LEDS, 10);
  fill_rainbow(&leds[ROW_1], ROW_1, gHue, 5);
  fadeToBlackBy(leds, NUM_LEDS, 10); 
  fill_rainbow(&leds[ROW_2], ROW_1, gHue, 5);
  fadeToBlackBy(leds, NUM_LEDS, 10); 

}

void rainbow() 
{
  // using the rainbow function, the LEDS are split evenly so the effect is even in table
  fill_rainbow(&leds[ROW_0], ROW_1, gHue, 5);
  fill_rainbow(&leds[ROW_1], ROW_1, gHue, 5); 
  fill_rainbow(&leds[ROW_2], ROW_1, gHue, 5);

}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}



void OHIO()
{
  for(int i = 0; i<NUM_LEDS; i++){
    leds[i] = CRGB::Red;
  }
  FastLED.show();
  for(int dot = 0; dot < ROW_1; dot++) { 
    //
    if (Serial.available()){
      btValue = Serial.read();
      Serial.write(btValue);
    }
    
    if((digitalRead(BUTTON_PIN) == true && btValue != '1')){
      //O
      //Bottom Layer
      leds[ROW_0 + dot] = CRGB::White;
      leds[ROW_0 + dot + 1] = CRGB::Red;
      leds[ROW_0 + dot + 2] = CRGB::Red;
      leds[ROW_0 + dot + 3] = CRGB::White;
      
      //Second layer
      leds[ROW_1 + dot] = CRGB::White;
      leds[ROW_1 + dot + 1] = CRGB::Red;
      leds[ROW_1 + dot + 2] = CRGB::Red;
      leds[ROW_1 + dot + 3] = CRGB::White;
      //Third
      leds[ROW_2 + dot] = CRGB::Red;
      leds[ROW_2 + dot + 1] = CRGB::White;
      leds[ROW_2 + dot + 2] = CRGB::White;
      leds[ROW_2 + dot + 3] = CRGB::Red;
      //Space
      leds[ROW_0+4+dot] = CRGB::Red;
      leds[ROW_1+4+dot] = CRGB::Red;
      leds[ROW_2+4+dot] = CRGB::Red;
      //H
      //Bottom
      leds[ROW_0+5+dot] =CRGB::White;
      leds[ROW_0+6+dot] =CRGB::White;
      leds[ROW_0+7+dot] =CRGB::White;
      leds[ROW_0+8+dot] =CRGB::White;
      //Middle
      leds[ROW_1 + dot + 5] = CRGB::White;
      leds[ROW_1 + dot + 6] = CRGB::Red;
      leds[ROW_1 + dot + 7] = CRGB::Red;
      leds[ROW_1 + dot + 8] = CRGB::White;
      
       //Bottom
      leds[ROW_2 + dot + 5] = CRGB::White;
      leds[ROW_2 + dot + 6] = CRGB::Red;
      leds[ROW_2 + dot + 7] = CRGB::Red;
      leds[ROW_2 + dot + 8] = CRGB::White;
      //Space
      leds[ROW_0+9+dot] = CRGB::Red;
      leds[ROW_1+9+dot] = CRGB::Red;
      leds[ROW_2+9+dot] = CRGB::Red;
  
      //I
      leds[ROW_0+10+dot] = CRGB::White;
      leds[ROW_1+10+dot] = CRGB::White;
      leds[ROW_2+10+dot] = CRGB::White;
      //Space
      leds[ROW_0+11+dot] = CRGB::Red;
      leds[ROW_1+11+dot] = CRGB::Red;
      leds[ROW_2+11+dot] = CRGB::Red;
      
      //O
      //Bottom Layer
      leds[ROW_0 + dot +12] = CRGB::White;
      leds[ROW_0 + dot + 13] = CRGB::Red;
      leds[ROW_0 + dot + 14] = CRGB::Red;
      leds[ROW_0 + dot + 15] = CRGB::White;
      
      //Second layer
      leds[ROW_1 + dot + 12] = CRGB::White;
      leds[ROW_1 + dot + 13] = CRGB::Red;
      leds[ROW_1 + dot + 14] = CRGB::Red;
      leds[ROW_1 + dot + 15] = CRGB::White;
      //Third
      leds[ROW_2 + dot + 12] = CRGB::Red;
      leds[ROW_2 + dot + 13] = CRGB::White;
      leds[ROW_2 + dot + 14] = CRGB::White;
      leds[ROW_2 + dot + 15] = CRGB::Red;
      //Space
      leds[ROW_0+16+dot] = CRGB::Red;
      leds[ROW_1+16+dot] = CRGB::Red;
      leds[ROW_2+16+dot] = CRGB::Red;
      
      
      FastLED.show();
      // clear this led for the next time around the loop
      leds[dot] = CRGB::Red;
      leds[dot + ROW_1] = CRGB::Red;
      leds[dot + ROW_2] = CRGB::Red;
      delay(25);
      }
      else{
        patternIndex = 3;
      }
   }
}


//Some extra functions that were found
void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 400;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
void caramelldansen(){
  colorChange();
  char btValue = '0';
  if (Serial.available()) {
      btValue = Serial.read();
      Serial.print(btValue);
    }
  
  if(digitalRead(BUTTON_PIN) == true || btValue != 1){
    if(color == 0){
      FastLED.showColor(CRGB(255,0,0));
      delay(400);
    }
    else if(color == 1){
      FastLED.showColor(CRGB(0,255,0));
      delay(400);
     } 
    else if(color == 2){
      FastLED.showColor(CRGB(0,0,255));
      delay(400);
    }
  }
  else{
    patternIndex++;
  }
  
}

void colorChange(){
  if(color<3){
    ++color;
  }
  else{
    color = 0;
  }
}

void solidRainbow(){
  FastLED.showColor(CHSV(gHue,255,255));
  
}

void btColor(){
  Serial.println("In btColor");
  while(btValue== '2'){
    //delays the method untill serial is available
    Serial.println("btValue is still 2");
    delay(10);
    while(!Serial.available()){
      delay(1);
      Serial.print("Waiting for color choice...");
      Serial.print("\n");
    }
   inputString = "";
  //Reading in the RGB value to a string
   while(Serial.available()){
      input = Serial.read();
      //Have to delay to give ardunio time to keep up
      delay(150);
      Serial.print(input); 
      Serial.print("\n");
  
      inputString = inputString + input;
  
   }
    while(!Serial.available()&&!patternChange()){
      FastLED.showColor(inputString.toInt());
      Serial.print("Color complete");
      Serial.print("\n");
    }
    if(Serial.available()==1){
        btValue = Serial.read();
        Serial.print("Read in a new btValue in btColor");
        Serial.print("\n");
    }
  }   
}

boolean patternChange() {
  boolean changed = false;
  if(btValue == '1'){
    changed = true;
  }
  else if(digitalRead(BUTTON_PIN) == false){
    changed = true;
  }
  return changed;
}

void btValueReader(){
  if(Serial.available()){
    btValue = Serial.read();
    Serial.print(btValue);
  }
}

void customPattern(){
  //Saving the LEDS to an Array so it is saved
//  while(btValue==2){
//    //delays the method untill serial is available
//    while(!Serial.available()&&!patternChange()){
//      delay(1);
//      Serial.print("Waiting for color choice...");
//      Serial.print("\n");
//    }
//   inputString = "";
//  //Reading in the RGB value to a string
//   while(Serial.available()){
//      input = Serial.read();
//      //Have to delay to give ardunio time to keep up
//      delay(100);
//      Serial.print(input); 
//      Serial.print("\n");
//  
//      inputString = inputString + input;
//  
//   }
  while(!Serial.available()){
    delay(1);
    //Serial.println("Waiting for pattern...");
  }
      Serial.read();
  for(int i = 0;i<43;++i){
      inputString = "-" + Serial.readStringUntil('-');
      
      customPat[i] = inputString.toInt();
      Serial.println(customPat[i]);
  }
    
  Serial.println("Now setting back color");
  //Getting background color
  int backColor = customPat[42];

  FastLED.showColor(backColor);
  delay(1000);
  Serial.println("Now setting up loops");
  while(true){
    /*
     * This loop increases the movement of the pattern by one to make the LEDs "move"
     */
  
  for(int k = 0;k<NUM_LEDS/3;++k){
    int l = 0;
    int m = 0;
    int n = 0;
    int w = 0;
    int x = 0;
    int z = 0;
     for(int i = 0;i<42;++i){
        //Bottom Row
        if(i>27 && i<=41){
          if(w+k<NUM_LEDS/3){
            leds[w+k] = customPat[i]; 
//            Serial.println("LEDS on at: ");
//            Serial.println(w+k);
//            delay(10);
            ++w;
            
          }else{
            leds[l] = customPat[i];
            ++l;
            Serial.println("LEDS on at: ");
            delay(10);
          }
        }
        //Second Row
        if(i>13 && i<=27){
          if(x+k<NUM_LEDS/3){
            leds[x+k+ROW_1] = customPat[i];
//            Serial.println("LEDS on at: ");
//            Serial.println(x+k+ROW_1);
//            delay(10);
            ++x;
            
          }else{
           leds[m+ROW_1] = customPat[i];
            ++m;
//            Serial.println("LEDS on at: ");
//            delay(10);

          }
        }
        //Top Row
        if(i<=13){
          //Checking to make sure LED postion doesnt exceed total num of leds in a row
          if(z+k<NUM_LEDS/3){
            leds[z+k+ROW_2] = customPat[i];
            ++z;
//            Serial.println("LEDS on at: ");
//            Serial.println(z+k+ROW_2);
//            delay(10);

          }else{
           leds[n+ROW_2] = customPat[i];
            ++n;
//            Serial.println("LEDS on at: ");
//            delay(10);
          }
        }     
      }
      FastLED.show();
      
      leds[k] = backColor;
      leds[k + ROW_1] = backColor;
      leds[k + ROW_2] = backColor;
      delay(50);
  }
      
 }
}
