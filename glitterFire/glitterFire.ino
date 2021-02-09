#include <FastLED.h>

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    26
//#define CLK_PIN   4
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    300
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          30
#define FRAMES_PER_SECOND  120

void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set main brightness control
  FastLED.setBrightness(BRIGHTNESS);
}
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  pattern();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void pattern() 
{
  fillOrangey();
  addGlitter(80);
}

void addGlitter(fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {

//    CHSV(HUE_ORANGE - 32 + (random8() / 4), 255, 255)
    leds[ random16(NUM_LEDS) ] += CRGB::White;

//        uint16_t pixelnumber = i;
//    pixelnumber = (NUM_LEDS-1) - pixelnumber;
//    
//    nblend( leds[pixelnumber], newcolor, 64);
  }
}


void fillOrangey() {
  for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
    CRGB newcolor = CHSV(HUE_ORANGE - 40 + (random8() / 3), 255, 255);
//    leds[i] = newcolor;

    // do some smoothing
    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS-1) - pixelnumber;
    
    nblend( leds[pixelnumber], newcolor, 64);
  }
}
