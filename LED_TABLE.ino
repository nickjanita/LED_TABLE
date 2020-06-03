/***LED Table***
 * Created by: Nick Janita
 * 
 * How to use: Designed to be used with a button to
 * switch modes. All that needs to be changed is the defined
 * variables depending on how many rows/leds you are using. 
*/

#include <FastLED.h>

FASTLED_USING_NAMESPACE

#define DATA_PIN    2
#define LED_TYPE    NEOPIXEL
#define COLOR_ORDER GRB
#define NUM_LEDS    300
#define ROW_0   0
#define ROW_1   NUM_LEDS/3 - 1
#define ROW_2   NUM_LEDS/3 + ROW_1
#define BRIGHTNESS          50
#define FRAMES_PER_SECOND  120
#define NUM_PATTERNS 5
#define BUTTON_PIN  8;

//Initializing memory for LEDS
CRGB leds[NUM_LEDS];

void setup() {
  delay(3000); // 3 second delay for recovery
  
  //Configuring leds to FastLED
  FastLED.addLeds<LED_TYPE,DATA_PIN>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  //Setting intial brightness
  FastLED.setBrightness(BRIGHTNESS);

  //Setting up button with a Pullup resistor (press is low)
  pinMode(BUTTON_PIN, INPUT_PULLUP); 

}

   //Creating array of the pattern functions
  typedef void (*ledPatterns)();
  ledPatterns patternList[] = {rainbow, confetti, OHIO, juggle, bpm};
  
  // Index number of which pattern is currently playing
  int patternIndex = 0;
  //Base color that rotates
  int gHue = 0;

  
void loop()
{ 
  //plays current pattern
  patternList[patternIndex]();

  //Shows the current LED pattern
  FastLED.show();  
  
  //Delay to change speed of the LEDS
  FastLED.delay(1000/FRAMES_PER_SECOND);

   //Reading if button is pressed, if it is, half second delay and pattern change
  if(digitalRead(BUTTON_PIN) == false){
    nextPattern();
    delay(500);
  }

  //Changes the speed of the color change in patterns that use gHue
  EVERY_N_MILLISECONDS(10) {
    ++gHue;
    } 
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

//
void nextPattern()
{
  ++patternIndex;
  if(patternIndex >= 5){
    patternIndex = 0;
  }
}

void rainbow() 
{
  // using the rainbow function, the LEDS are split evenly so the effect is even in table
  fill_rainbow(&leds[ROW_0], ROW_1, gHue, 7);
  fill_rainbow(&leds[ROW_1], ROW_2, gHue, 7); 
  fill_rainbow(&leds[ROW_2], NUM_LEDS, gHue, 7);
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
  for(int dot = 0; dot < 100; dot++) { 
    //O
    for(int i = 0;i<3;++i){
      leds[dot+i] = CRGB::Red;
    }
    //Second layer
    leds[ROW_1+dot] = CRGB::Red;
    leds[ROW_1+dot+1] = CRGB::White;
    leds[ROW_1+dot+2] = CRGB::Red;
    //Third
    for(int i = 0;i<3;++i){
      leds[200+dot+i] = CRGB::Red;
    }
    //H
    //Top
    leds[4+dot] =CRGB::Red;
    leds[5+dot] = CRGB::White;
    leds[6+dot] =CRGB::Red;
    //Middle
    for(int i = 4;i<7;++i){
      leds[ROW_1+dot+i] = CRGB::Red;
    }
     //Bottom
    leds[ROW_2+4+dot] =CRGB::Red;
    leds[ROW_2+5+dot] = CRGB::White;
    leds[ROW_2+6+dot] =CRGB::Red;

    //I
    leds[8+dot] = CRGB::Red;
    leds[100+8+dot] = CRGB::Red;
    leds[ROW_2+8+dot] = CRGB::Red;
    leds[9+dot] = CRGB::White;
    leds[100+9+dot] = CRGB::White;
    leds[ROW_2+9+dot] = CRGB::White;

    //O
    for(int i = 0;i<3;++i){
      leds[10+dot+i] = CRGB::Red;
    }
    //Second layer
    leds[10+ROW_1+dot] = CRGB::Red;
    leds[10+ROW_1+dot+1] = CRGB::White;
    leds[10+ROW_1+dot+2] = CRGB::Red;
    //Third
    for(int i = 0;i<3;++i){
      leds[10+ROW_2+dot+i] = CRGB::Red;
    }

    
    
    FastLED.show();
            // clear this led for the next time around the loop
            leds[dot] = CRGB::White;
            leds[dot+ROW_1]=CRGB::White;
            leds[dot+ROW_2]=CRGB::White;
            leds[dot+4] = CRGB::White;
            leds[dot+ROW_1+4]=CRGB::White;
            leds[dot+ROW_2+4]=CRGB::White;
            leds[dot+8] = CRGB::White;
            leds[dot+ROW_1+8]=CRGB::White;
            leds[dot+ROW_2+8]=CRGB::White;
            leds[dot+10] = CRGB::White;
            leds[dot+ROW_1+10]=CRGB::White;
            leds[dot+ROW_2+10]=CRGB::White;
            delay(100);
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
  
