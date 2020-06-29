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

void setup() {
  delay(3000); // 3 second delay for recovery
  //Serial.begin(9600);
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
  ledPatterns patternList[] = {solidRainbow,rainbow, confetti, OHIO, juggle, bpm,caramelldansen};
  
  // Index number of which pattern is currently playing
  int patternIndex = 0;
  //Base color that rotates
  int gHue = 0;
  int color =0;

  
void loop()
{ 
  //plays current pattern
  patternList[patternIndex]();

  //Shows the current LED pattern
  if(patternIndex != 0){
      FastLED.show();  
      FastLED.delay(1000/FRAMES_PER_SECOND);
  }
  
  //Delay to change speed of the LEDS
  //

   //Reading if button is pressed, if it is, half second delay and pattern change
  if((digitalRead(BUTTON_PIN) == false)){
    nextPattern();
    delay(500);
  }

  //Changes the speed of the color change in patterns that use gHue
  EVERY_N_MILLISECONDS(1) {
    ++gHue;
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

void rainbow() 
{
  // using the rainbow function, the LEDS are split evenly so the effect is even in table
  fill_rainbow(&leds[ROW_0], ROW_1, gHue, 7);
  fill_rainbow(&leds[ROW_1], ROW_1, gHue, 7); 
  fill_rainbow(&leds[ROW_2], ROW_1, gHue, 7);

}

//TODO: Get rid of this ugly pattern
void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}


//TODO: create an escape for when button is pressed and clean up code cause good god 
void OHIO()
{
  for(int i = 0; i<NUM_LEDS; i++){
    leds[i] = CRGB::Red;
  }
  FastLED.show();
  for(int dot = 0; dot < ROW_1; dot++) { 
    //

    if(digitalRead(BUTTON_PIN) == true){
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
//TODO: split evenly between the rows
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
  if(digitalRead(BUTTON_PIN) == true){
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
