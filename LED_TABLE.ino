#include <FastLED.h>

FASTLED_USING_NAMESPACE

#define DATA_PIN    2
#define LED_TYPE    NEOPIXEL
#define COLOR_ORDER GRB
#define NUM_LEDS    300
#define ROW_1   NUM_LEDS/3
#define ROW_2   NUM_LEDS/3 + ROW_1
#define ROW_3   NUM_LEDS/3 + ROW_2
CRGB leds[NUM_LEDS];

#define AUDIO_INPUT A0
#define BRIGHTNESS          50
#define FRAMES_PER_SECOND  120
int button = 8;
void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(button, INPUT_PULLUP); // set the internal pull up resistor, unpressed button is HIGH
  
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {rainbow, confetti, snakeboi, juggle, bpm};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 
  if(digitalRead(button) == false){
    delay(500);
    nextPattern();
  }
  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow(&leds[0], ROW_1, gHue, 7);
  fill_rainbow(&leds[99], ROW_2, gHue, 7); 
  fill_rainbow(&leds[199], ROW_3, gHue, 7);
}


void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void snakeboi()
{
  for(int dot = 0; dot < 100; dot++) { 
    //O
    for(int i = 0;i<3;++i){
      leds[dot+i] = CRGB::Red;
    }
    //Second layer
    leds[100+dot] = CRGB::Red;
    leds[100+dot+1] = CRGB::White;
    leds[100+dot+2] = CRGB::Red;
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
      leds[100+dot+i] = CRGB::Red;
    }
     //Bottom
    leds[200+4+dot] =CRGB::Red;
    leds[200+5+dot] = CRGB::White;
    leds[200+6+dot] =CRGB::Red;

    //I
    leds[8+dot] = CRGB::Red;
    leds[100+8+dot] = CRGB::Red;
    leds[200+8+dot] = CRGB::Red;
    leds[9+dot] = CRGB::White;
    leds[100+9+dot] = CRGB::White;
    leds[200+9+dot] = CRGB::White;

    //O
    for(int i = 0;i<3;++i){
      leds[10+dot+i] = CRGB::Red;
    }
    //Second layer
    leds[10+100+dot] = CRGB::Red;
    leds[10+100+dot+1] = CRGB::White;
    leds[10+100+dot+2] = CRGB::Red;
    //Third
    for(int i = 0;i<3;++i){
      leds[10+200+dot+i] = CRGB::Red;
    }

    
    
    FastLED.show();
            // clear this led for the next time around the loop
            leds[dot] = CRGB::White;
            leds[dot+100]=CRGB::White;
            leds[dot+200]=CRGB::White;
            leds[dot+4] = CRGB::White;
            leds[dot+100+4]=CRGB::White;
            leds[dot+200+4]=CRGB::White;
            leds[dot+8] = CRGB::White;
            leds[dot+100+8]=CRGB::White;
            leds[dot+200+8]=CRGB::White;
            leds[dot+10] = CRGB::White;
            leds[dot+100+10]=CRGB::White;
            leds[dot+200+10]=CRGB::White;
            delay(100);
        }
}

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
  
