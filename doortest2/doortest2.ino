#include <FastLED.h>

#define LED_PIN_A 3

#define COLOR_ORDER GRB
#define CHIPSET     WS2812B

#define NUM_LEDS 10                                       //Total LEDs Count

#define BRIGHTNESS  100
#define FRAMES_PER_SECOND 60

const int BTN_YES = 10;
const int BTN_NO = 9;


bool BTN_STATE = false;
int LST_YBTN_STATE = HIGH;
int CRN_YBTN_STATE;
int COUNTY = 0;
int LST_NBTN_STATE = HIGH;
int CRN_NBTN_STATE;
int COUNTN = 0;
int initialstate = 0;
int oldstate = 0;

bool gReverseDirection = false;

unsigned long lastDebounceTime = 0;  // the last time the btn was toggled
unsigned long debounceDelay = 50;    // the debounce time

CRGB leds[NUM_LEDS];




void setup() {
  Serial.begin(9600);
  delay(3000) ;            //Power-up safety delay

  FastLED.addLeds<CHIPSET, LED_PIN_A, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );

  FastLED.setBrightness( BRIGHTNESS );

  pinMode(BTN_YES, INPUT_PULLUP);
  pinMode(BTN_NO, INPUT);
}
void loop() {

  CRN_YBTN_STATE = digitalRead(BTN_YES);
  CRN_NBTN_STATE = digitalRead(BTN_NO);

  if ((CRN_YBTN_STATE == HIGH ) && (CRN_NBTN_STATE == HIGH) && (LST_YBTN_STATE == LOW) && (LST_NBTN_STATE == LOW)) {
    //DiscSparkers();
    COUNTY = 0;
    COUNTN = 0;
    for (int y = 0; y < 10; y++) {
      int b = y;
      leds[b] = CRGB::Black;
      FastLED.show();
    }
  }

    // LST_YBTN_STATE = CRN_YBTN_STATE;
    //LST_NBTN_STATE = CRN_NBTN_STATE;

    if (COUNTN + COUNTY < 10) {

      if ((CRN_YBTN_STATE == HIGH ) && (CRN_NBTN_STATE == LOW) && (LST_YBTN_STATE == LOW)) {

        for (int y = 0; y <= COUNTY ; y++) {
          int a = y;
          leds[a] = CRGB::Green;
          FastLED.show();


          Serial.println(COUNTY);
          // delay(200);
          //leds[a] = CRGB::Black;

        } COUNTY++;

      }
      LST_YBTN_STATE = CRN_YBTN_STATE;





      if ((CRN_NBTN_STATE == HIGH) && (CRN_YBTN_STATE == LOW) && (LST_NBTN_STATE == LOW)) {
        int i = 0;
        for (int y = 0; y <= COUNTN ; y++) {

          // int b = 17 - i;
          int b = 9 - i;
          leds[b] = CRGB::Red;
          FastLED.show();
          i++;
        }
        COUNTN++;
      }

      LST_NBTN_STATE = CRN_NBTN_STATE;
    }

  }








// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100
/*#define COOLING  50

  // SPARKING: What chance (out of 255) is there that a new spark will be lit?
  // Higher chance = more roaring fire.  Lower chance = more flickery fire.
  // Default 120, suggested range 50-200.
  #define SPARKING 140

  void DiscSparkers()
  {
  // Array of temperature readings at each simulation cell
  static uint8_t heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if ( random8() < SPARKING ) {
    int y = random8(7);
    heat[y] = qadd8( heat[y], random8(160, 255) );
  }

  // Step 4.  Map from heat cells to LED colors
  //  for (int x = 0; x < NUM_STRIPS; x++) {
  for ( int j = 0; j < NUM_LEDS; j++) {
    CRGB color = HeatColor( heat[j]);
    int pixelnumber;
    if ( gReverseDirection ) {
      pixelnumber = (NUM_LEDS - 1) - j;
    } else {
      pixelnumber = j;
    }
    //leds[x][pixelnumber] = color;
    leds[pixelnumber] = color;
  }
  }*/
