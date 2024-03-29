#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define LED_COUNT 200

#define MAX 255
#define BRIGHTNESS 80

#define LONG_WAIT 180000
#define SHORT_WAIT 30000
#define EXTRA_LONG_TRANS 60000
#define LONG_TRANS 20000
#define SHORT_TRANS 5000
#define RAPID_TRANS 1000
//
/* #define LONG_WAIT 18000 */
/* #define SHORT_WAIT 3000 */
/* #define EXTRA_LONG_TRANS 15000 */
/* #define LONG_TRANS 5000 */
/* #define SHORT_TRANS 2000 */
/* #define RAPID_TRANS 100 */

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_RGB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

//MAX_X and MAX_Y represent the largest X and Y value from the table of Positions
//This is used to derive where the middle of the tree is in the X and Y direction.
//For example if MAX_X = 20, then LEDs at a position of 10 would be the middle of
//the tree.
#define MAX_X 36
#define MAX_Y 64

uint32_t red = strip.Color(MAX,0,0);
uint32_t green = strip.Color(0,MAX,0);
uint32_t darkgreen = strip.Color(0,2*MAX/3,0);
uint32_t blue = strip.Color(0,0,MAX);
uint32_t cyan = strip.Color(0,MAX,MAX);
uint32_t yellow = strip.Color(MAX,5*MAX/8,0);
uint32_t magenta = strip.Color(MAX,0,MAX);
uint32_t white = strip.Color(MAX,MAX,MAX);
uint32_t black = strip.Color(0,0,0);
uint32_t silver = strip.Color(MAX-10,MAX-10,MAX);
uint32_t pink = strip.Color(MAX,MAX/2,MAX/2);
uint32_t purple = strip.Color(MAX/2,0,MAX/2);
uint32_t orange = strip.Color(MAX,MAX/3,0);


//Define the X,Y positions of each pixel.  The first array element is the X
//coordinate of the first LED in the string, the second array element is the
//Y coordinate of the first LED.   The third array element is the X position of
//the second LED, etc...
//byte Positions[LED_COUNT*2] =
//{
//15,1,   15,2,   14,3,   14,4,   14,4,   15,4,   16,5,   20,9,   17,11,  19,14,  // 0 - 9
//16,18,  16,18,  24,17,  25,16,  25,16,  27,13,  30,11,  31,12,  31,12,  31,12,  //10 - 19
//28,11,  30,8,   28,9,   28,14,  28,14,  27,14,  30,10,  28,8,   20,8,   22,6,   //20 - 29
//18,7,   18,6,   26,8,   24,9,   19,14,  24,14,  24,14,  27,14,  27,14,  29,15,  //30 - 39
//29,16,  30,16,  31,17,  26,17,  26,18,  26,20,  24,21,  24,22,  22,22,  24,22,  //40 - 49
//26,29,  26,24,  24,24,  28,26,  26,26,  25,26,  24,24,  24,21,  24,21,  23,18,  //50 - 59
//26,21,  21,18,  18,18,  20,24,  16,27,  18,26,  16,29,  21,28,  27,29,  27,26,  //60 - 69
//25,25,  26,24,  26,30,  25,28,  27,31,  25,31,  27,31,  19,30,  27,34,  30,34,  //70 - 79
//28,25,  25,36,  20,35,  22,34,  22,40,  23,40,  23,37,  25,35,  22,38,  23,37,  //80 - 89
//22,37,  19,35,  17,35,  14,35,  11,37,  13,40,  15,39,  18,37,  18,39,  21,38,  //90 - 99
//22,44,  18,48,  20,48,  19,50,  19,51,  18,49,  15,51,  15,51,  15,51,  13,42,  //100-109
//13,43,  15,46,  15,48,  16,48,  17,48,  19,49,  18,47,  21,49,  18,47,  16,45,  //110-119
//15,47,  13,40,  12,39,  13,39,  13,38,  13,38,  13,38,  13,38,  13,38,  22,34,  //120-129
//14,38,  14,38,  14,38,  14,38,  9,35,   13,34,  8,34,   9,33,   8,30,   13,31,  //130-139
//13,32,  13,29,  9,27,   9,26,   6,26,   6,25,   9,27,   4,24,   4,24,   6,24,   //140-149
//15,27,  16,29,  15,27,  15,29,  16,25,  15,21,  14,23,  8,16,   12,13,  9,18,   //150-159
// 8,18,  11,20,  12,20,  6,15,   6,15,   6,16,   6,16,   7,20,   8,20,   10,18,  //160-169
//14,20,  14,17,  16,19,  20,18,  17,16,  16,16,  15,12,  13,14,  8,13,   6,9,    //170-179
// 6,8,    5,9,   6,13,   4,14,   2,12,   5,15,   6,15,   5,14,   7,13,   7,12,   //180-189
// 9,9,    8,8,   8,8,    8,8,    10,8,   15,4,   15,4,   14,3,   14,2,   14,1    //190-199
//};
byte Positions[LED_COUNT*2] = {
14, 62,    13, 63,    13, 60,    13, 59,    13, 57,    10, 54,    11, 52,    15, 52,    11, 55,    10, 54,
10, 53,    8, 53,    5, 54,    3, 53,    3, 56,    4, 56,    3, 56,    3, 56,    3, 56,    13, 48,
1, 48,    8, 51,    1, 48,    10, 55,    12, 63,    17, 46,    10, 46,    8, 46,    1, 48,    1, 48,
5, 45,    5, 47,    4, 47,    3, 47,    4, 49,    7, 52,    4, 52,    9, 48,    7, 49,    9, 49,
9, 49,    8, 52,    10, 53,    14, 54,    16, 54,    17, 51,    19, 49,    22, 51,    22, 50,    24, 48,
26, 50,    29, 49,    29, 48,    27, 48,    27, 48,    21, 45,    26, 51,    2, 57,    23, 55,    22, 55,
22, 55,    17, 46,    20, 46,    21, 46,    24, 47,    23, 46,    21, 45,    21, 41,    26, 44,    26, 44,
26, 44,    26, 42,    26, 40,    25, 41,    22, 42,    21, 41,    21, 41,    19, 44,    15, 45,    14, 46,
13, 44,    11, 42,    11, 43,    7, 43,    6, 42,    5, 44,    5, 44,    7, 42,    6, 42,    7, 40,
11, 42,    5, 38,    10, 34,    5, 38,    1, 48,    1, 48,    9, 41,    1, 48,    16, 47,    14, 42,
7, 40,    13, 34,    13, 33,    17, 30,    13, 33,    5, 40,    8, 27,    7, 33,    8, 35,    6, 34,
13, 33,    7, 36,    7, 37,    9, 37,    11, 36,    11, 36,    15, 37,    18, 37,    20, 34,    22, 33,
7, 37,    23, 36,    25, 38,    24, 35,    24, 37,    24, 34,    23, 35,    23, 34,    21, 35,    23, 34,
21, 34,    20, 28,    21, 28,    20, 29,    21, 30,    22, 31,    20, 28,    20, 26,    17, 23,    18, 26,
20, 26,    13, 28,    11, 27,    8, 25,    8, 26,    11, 22,    8, 25,    10, 25,    11, 24,    11, 24,
13, 28,    13, 18,    11, 18,    11, 21,    13, 18,    11, 19,    12, 17,    15, 18,    13, 23,    15, 24,
12, 17,    20, 21,    20, 23,    20, 23,    21, 21,    21, 19,    21, 20,    20, 16,    20, 11,    19, 11,
19, 12,    16, 15,    16, 15,    14, 16,    12, 16,    14, 10,    14, 10,    15, 10,    15, 13,    15, 13,
12, 34,    14, 10,    12, 34,    12, 34,    12, 26,    17, 24,    14, 28,    17, 29,    17, 30,    17, 35,
19, 41,    17, 29,    17, 41,    16, 41,    17, 40,    16, 46,    14, 47,    14, 51,    16, 51,    12, 63
};

byte num_list[LED_COUNT] = {
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200
};


void setup() {
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  /* defaultLoop(); */
  //testLoop();
  /* rainbowLoop(); */
  //initLoop();
  loop2020();
}

void loop2020(){
  /* solid(silver); */
  vertWipe(false,red, black,1000);
  vertLine(true,silver, red,1000);
  vertWipe(false,silver, red,1000);

  {
  uint32_t colors[] = {red,silver,red,silver,red,silver};
  uint16_t num_colors = sizeof(colors)/(sizeof(colors[0]));
  rainbowLines(100, LONG_WAIT, num_colors, colors);
  }
  /* vertWipe(false,red, silver,1000); */
  /* vertLine(true,black, red,1000); */
  {
  uint32_t colors[] = {red,silver,green};
  uint16_t num_colors = sizeof(colors)/(sizeof(colors[0]));
  rainbowDissolve(100, LONG_TRANS, num_colors, colors);
  }

  /* two_solid(red,cyan); */
  /* delay(SHORT_WAIT); */
  /* rainbowTransition(num_colors, colors); */
  /* rainbowWave(100, LONG_WAIT, num_colors, colors); */
  /* fadeFromExisting(cyan, LONG_TRANS); */
  /* transitionFade(red, green, blue, 100, 1000); */
  /* transitionFade(cyan, red, darkgreen, 100, SHORT_TRANS); */
}

void testLoop() {
  uint32_t colors[] = {red, green};
  uint16_t num_colors = sizeof(colors)/(sizeof(colors[0]));
  // rainbowTransition(num_colors, colors);
  //delay(RAPID_TRANS);
  rainbowWave(1, LONG_WAIT, num_colors, colors);
}

void initLoop(){
    // uncomment to gather led positions (manual process):
    initialize(strip.Color(255,255,255));
    initialize(strip.Color(255,255,255));
    initialize(strip.Color(255,255,255));
    getLocations(strip.Color(255, 255, 255));
}
void rainbowLoop() {
  /* Serial.println("verticalTransitionWave"); */
  /* rainbowTransition(green, red, blue); */
  /* delay(SHORT_TRANS); */
  /* transition(yellow, blue); */
  /* delay(SHORT_TRANS); */
  uint32_t colors[] = {red, yellow, green,blue, purple, red, yellow, green, blue, purple};
  uint16_t num_colors = sizeof(colors)/(sizeof(colors[0]));
  rainbowTransition(num_colors, colors);
  delay(LONG_TRANS);
  rainbowWave(100, LONG_WAIT, num_colors, colors);
  delay(SHORT_TRANS);
  /* verticalTransitionWave(red, silver, 100, 200000); */
  rainbow();
  delay(LONG_TRANS);
  rainbowTwinkle(500, LONG_TRANS);
  delay(LONG_TRANS);
  //rainbowShimmer(LONG_TRANS, 60, num_colors, colors);
  //delay(SHORT_TRANS);
  /* solid(red); */
  /* delay(SHORT_TRANS); */
  /* solid(orange); */
  /* delay(SHORT_TRANS); */
  /* solid(yellow); */
  /* delay(SHORT_TRANS); */
  /* solid(green); */
  /* delay(SHORT_TRANS); */
  /* solid(blue); */
  /* delay(SHORT_TRANS); */
  /* solid(purple); */
  /* delay(SHORT_TRANS); */
  /* transitionFade(red, green, blue, 100, 1000); */
  /* transitionFade(blue, red, green, 100, 1000); */
  /* transitionFade(green, blue, red, 100, 1000); */
  /* rainbow(); */
  /* delay(SHORT_TRANS); */
  // delay(LONG_WAIT);
  /* verticalTransitionWave(red, silver, 100, 200000); */
  // verticalTransitionWave(blue, green, 100, 20000);
  //verticalTransitionWave(red, blue, 1000, 20000);
}

void defaultLoop() {


     Serial.println("Solid");
     solid(red);
     delay(SHORT_WAIT);
     Serial.println("Dissolving First Half");
     firstHalfDissolve(silver,SHORT_TRANS);
     delay(SHORT_WAIT);
     Serial.println("Dissolving Second Half");
     secondHalfDissolve(green,SHORT_TRANS);
     Serial.println("Dissolving First Half");
     firstHalfDissolve(red,SHORT_TRANS);
     Serial.println("waiting for next");
     delay(SHORT_WAIT);
     secondHalfDissolve(green,SHORT_TRANS);
     delay(SHORT_WAIT);
     firstHalfDissolve(silver,SHORT_TRANS);
     delay(SHORT_WAIT);
     secondHalfDissolve(red,SHORT_TRANS);
     delay(SHORT_WAIT);
     firstHalfDissolve(silver,SHORT_TRANS);
     secondHalfDissolve(green,SHORT_TRANS);
     firstHalfDissolve(blue,SHORT_TRANS);
     delay(SHORT_WAIT);
     secondHalfDissolve(green,SHORT_TRANS);
     firstHalfDissolve(silver,SHORT_TRANS);
     secondHalfDissolve(red,SHORT_TRANS);
     firstHalfDissolve(green,SHORT_TRANS);
     secondHalfDissolve(green,SHORT_TRANS);
     delay(SHORT_WAIT);

////     Serial.println("Solid2");
////     two_solid(red,green);
////     delay(10000);
////
////     Serial.println("Dissolve");
////     dissolve(red, green,10000);
////     delay(3000);

     Serial.println("Fade");
     fade(green, blue,LONG_TRANS);
     delay(SHORT_WAIT);

////     Serial.println("HorizWipe");
////     horizWipe(false,strip.Color(0,255,255),strip.Color(0,0,255),5000);
////     delay(3000);
////
////     Serial.println("centerHorizWipe");
////     centerHorizWipe(strip.Color(0,255,0),strip.Color(255,0,0),5000);
////     delay(3000);
////
////     Serial.println("vertWipe");
////     vertWipe(false,strip.Color(255,0,0),strip.Color(0,0,255),5000);
////     delay(3000);
////
////     Serial.println("vertLine");
////     vertLine(false,strip.Color(0,255,0),strip.Color(255,0,0),5000);
////     delay(3000);

     Serial.println("transition");
     transition(blue, green);
     delay(SHORT_WAIT);

     Serial.println("verticalTransitionWave");
     verticalTransitionWave(blue,green,100,EXTRA_LONG_TRANS);

     Serial.println("verticalTransitionWave");
     verticalTransitionWave(red,green,100,EXTRA_LONG_TRANS);

////     Serial.println("vertCenterWave");
////     vertCenterWave(strip.Color(255,255,0),strip.Color(0,255,255),150,5000);
////     delay(3000);

     Serial.println("fade");
     fadeFromExisting(red, LONG_TRANS);
     delay(SHORT_WAIT);

////     Serial.println("setBlock");
////     setBlock(3,strip.Color(255,255,255));
////     delay(3000);

    Serial.println("Shimmer");
    shimmer(red, green,EXTRA_LONG_TRANS,25);
    fadeFromExisting(green, LONG_TRANS);
    shimmer(green, red,EXTRA_LONG_TRANS,25);
    fadeFromExisting(red, LONG_TRANS);

}

/* strobes the given rhythm with a solid color*/
void strobe(uint32_t rhythm[], uint32_t rhythm_size, int repeats){
  /* uint32_t colors[LED_COUNT]; */
  /* for(uint16_t j=0; j<strip.numPixels(); j++){ */
  /*   colors[j] = strip.getPixelColor(j); */
  /* } */
  for(int c = 0; c < repeats; c++){
    for(uint16_t i = 0; i < rhythm_size; i++){
      for(uint16_t j=0; j<strip.numPixels(); j++){
        strip.setPixelColor(j,black);
      }
      strip.show();
      delay(50);
      for(uint16_t j=0; j<strip.numPixels(); j++){
        strip.setPixelColor(j,red);
      }
      strip.show();
      delay(rhythm[i]);
    }
  }
}

void rainbowDissolve(uint32_t tick, uint32_t duration, uint16_t num_colors, uint32_t colors[]) {

  uint32_t elapsed_time = 0;
  /* uint32_t tick = duration/(strip.numPixels()+50); */
  bool temp[strip.numPixels()];
  uint8_t rand;

  for(uint16_t j=0; j<strip.numPixels(); j++){
    strip.setPixelColor(j,colors[j % num_colors]);
  }

  while (elapsed_time < duration){
    rand = random(strip.numPixels());
    if (temp[rand]){
      rand = random(strip.numPixels());
      if (temp[rand]){
        for(uint16_t i=0; i<strip.numPixels(); i++){
          if (!temp[i]) {
            rand=i; i = 999;
          }
        }
      }
    }
    temp[rand] = true;
    strip.setPixelColor(rand,colors[elapsed_time % num_colors]);
    strip.show();
    elapsed_time += 1 ;
  }

  /* for(uint16_t j=0; j<strip.numPixels(); j++){ */
  /*   strip.setPixelColor(j,colors[elapsed_time % num_colors]); */
  /* } */
  /* strip.show(); */
}

void rainbowTransition(uint16_t num_colors, uint32_t colors[])
{
  uint32_t elapsed_time = 0;
  uint32_t temp_color;
  float offset = 0;

  float multiplier = float(num_colors);
  float max = float(MAX_Y);
  float denominator = max / multiplier;
  float y_coord;
  float percent;
  uint32_t current;
  uint32_t next;
  int intpart;

  for(uint16_t i=0; i<strip.numPixels(); i++){
    if(offset > MAX_Y) offset = 0;
    // we want y_coord to wrap around to the top, so when y_coord is less than zero,
    // we need to add MAX_Y to it, that way we don't deal with silly abs()ing stuff
    // and percent will never be greater than 1

    y_coord = float(Positions[i*2+1]) - offset;
    if(y_coord < 0) y_coord = y_coord + MAX_Y;
    percent = y_coord/denominator;

    // we can generailze the percent by dropping the int part of it
    intpart = (int)percent;
    percent = percent - intpart;

    // now, in order to add colors, we can do that, except that there will be a hard-stop
    // at the beginning and end. this means we need to add a third transition back to the first color
    // we should be able to generalize this for the number of colors given
    for(uint16_t j = 1; j <= num_colors; j++){
      current = colors[j-1];
      next = j < num_colors ? colors[j] : colors[0];
      if(y_coord < denominator * j){
        temp_color = colorSlope(current, next, percent);
        break;
      }
    }

    strip.setPixelColor(i,temp_color);
  }
  strip.show();


}

void rainbowWave(uint32_t tick, uint32_t duration, uint16_t num_colors, uint32_t colors[])
{
  uint32_t elapsed_time = 0;
  uint32_t temp_color;
  float offset = 0;

  float multiplier = float(num_colors);
  float max = float(MAX_Y);
  float denominator = max / multiplier;
  float y_coord;
  float percent;
  uint32_t current;
  uint32_t next;
  int intpart;
  while (elapsed_time < duration)
    {
      for(uint16_t i=0; i<strip.numPixels(); i++){
        if(offset > MAX_Y) offset = 0;
        // we want y_coord to wrap around to the top, so when y_coord is less than zero,
        // we need to add MAX_Y to it, that way we don't deal with silly abs()ing stuff
        // and percent will never be greater than 1

        y_coord = float(Positions[i*2+1]) - offset;
        if(y_coord < 0) y_coord = y_coord + MAX_Y;
        percent = y_coord/denominator;

        // we can generailze the percent by dropping the int part of it
        intpart = (int)percent;
        percent = percent - intpart;

        // now, in order to add colors, we can do that, except that there will be a hard-stop
        // at the beginning and end. this means we need to add a third transition back to the first color
        // we should be able to generalize this for the number of colors given
        for(uint16_t j = 1; j <= num_colors; j++){
          current = colors[j-1];
          next = j < num_colors ? colors[j] : colors[0];
          if(y_coord < denominator * j){
            temp_color = colorSlope(current, next, percent);
            break;
          }
        }

        strip.setPixelColor(i,temp_color);
      }
      offset += 1 ;
      strip.show();
      delay(tick);
      elapsed_time += tick + 5;
    }
}

uint32_t rainbow()
{
  for(uint16_t i=0; i<strip.numPixels(); i++){
    if (i % 6 == 0){
      strip.setPixelColor(i,red);
    } else if (i % 6 == 1){
      strip.setPixelColor(i,orange);
    } else if (i % 6 == 2){
      strip.setPixelColor(i,yellow);
    } else if (i % 6 == 3){
      strip.setPixelColor(i,green);
    } else if (i % 6 == 4){
      strip.setPixelColor(i,blue);
    } else if (i % 6 == 5){
      strip.setPixelColor(i,purple);
    }
  }
  strip.show();
}

/********************************************************/
void rainbowShimmer(uint32_t duration, uint32_t amount, uint16_t num_colors, uint32_t colors[] )
{
  //amount needs to be below 75, otherwise the arduino will run out of memory!
  uint16_t shimmer_pixel_num[amount];
  uint32_t shimmer_pixel_old_color[amount];
  uint32_t shimmer_pixel_new_color[amount];
  uint16_t shimmer_pixel_percent[amount];
  uint32_t elapsed_time = 0;
  uint32_t shimmer_color;

  for(uint16_t i=0; i < amount; i++){
    shimmer_pixel_num[i] = 0;
  }

  //randomize the colors
  int previous = 0;
  int c = random(num_colors);
  int current;
  for(uint16_t i=0; i < strip.numPixels(); i++){
    current = i / num_colors;
    if(current > previous) {
      previous = current;
      c = random(num_colors);
    }
    //chunk the random color
    strip.setPixelColor(i,colors[c]);
  }

  while (elapsed_time < duration){
    shimmer_color = colors[random(num_colors)];
    for(uint16_t i=0; i < amount; i++){
      if (shimmer_pixel_num[i] == 0 && random(10) > 6) {
        shimmer_pixel_num[i] = random(LED_COUNT);
        shimmer_pixel_percent[i] = 0;
        shimmer_pixel_old_color[i] = strip.getPixelColor(shimmer_pixel_num[i]);
        shimmer_pixel_new_color[i] = colors[random(num_colors)];
      }
      if (shimmer_pixel_num[i] > 0) {
        if (i% 2 == 0) {
          shimmer_pixel_percent[i] += 2;
        } else {
          shimmer_pixel_percent[i] += 4;
        }
        if (shimmer_pixel_percent[i] >= 200) {
          int c = random(num_colors);
          //when done shimmering, set to the new color
          strip.setPixelColor(shimmer_pixel_num[i],shimmer_pixel_new_color[i]);
          shimmer_pixel_num[i] = 0;
        } else {
          strip.setPixelColor(
                              shimmer_pixel_num[i],
                              colorSlope(
                                         shimmer_pixel_old_color[i],
                                         shimmer_pixel_new_color[i],
                                         abs(1.0 - float(shimmer_pixel_percent[i])/100)
                                         )
                              );
        }
      }
    }

    strip.show();
    delay(50);
    elapsed_time += 50 + 5 ;
  }

  /* for(uint16_t i=0; i < strip.numPixels(); i++){ */
  /*   strip.setPixelColor(i,c_base); */
  /* } */
  /* strip.show(); */

}

uint32_t rainbowTwinkle(uint32_t tick, uint32_t duration)
{
  uint32_t offset = 0;
  uint32_t elapsed_time = 0;
  while(duration > elapsed_time){
    for(uint32_t i=0; i<strip.numPixels(); i++){
      uint32_t decision = (offset + i) % 6;
      if (decision == 0){
        strip.setPixelColor(i,red);
      } else if (decision == 1){
        strip.setPixelColor(i,orange);
      } else if (decision == 2){
        strip.setPixelColor(i,yellow);
      } else if (decision == 3){
        strip.setPixelColor(i,green);
      } else if (decision == 4){
        strip.setPixelColor(i,blue);
      } else if (decision == 5){
        strip.setPixelColor(i,purple);
      }
    }
    offset++;
    delay(tick);
    strip.show();
    elapsed_time += tick + 5;
  }
}

/*******************************************************/
uint32_t colorSlope(uint32_t c1, uint32_t c2, float percent)
{
  uint32_t temp_color, temp_c1_component, temp_c2_component;

     temp_color = 0;
     temp_c1_component = (c1 & 0x00ff0000) >> 16;
     temp_c2_component = (c2 & 0x00ff0000) >> 16;
     temp_color = uint32_t(temp_c1_component + (float(temp_c2_component) - float(temp_c1_component)) * percent);
     temp_color = temp_color << 8;

     temp_c1_component = (c1 & 0x0000ff00) >> 8;
     temp_c2_component = (c2 & 0x0000ff00) >> 8;
     temp_color += uint32_t(temp_c1_component + (float(temp_c2_component) - float(temp_c1_component)) * percent);
     temp_color = temp_color << 8;

     temp_c1_component = (c1 & 0x000000ff);
     temp_c2_component = (c2 & 0x000000ff);
     temp_color += uint32_t(temp_c1_component + (float(temp_c2_component) - float(temp_c1_component)) * percent);

  return temp_color;
}
/*******************************************************/
void solid(uint32_t color)
{
  for(uint16_t i=0; i<strip.numPixels(); i++)
  { strip.setPixelColor(i,color); }

  strip.show();
}
/*******************************************************/
void two_solid(uint32_t color_1, uint32_t color_2)
{
  for(uint16_t i=0; i<strip.numPixels(); i++)
  { if (i % 2 == 0)
      {strip.setPixelColor(i,color_1);}
    else
      {strip.setPixelColor(i,color_2);}
  }

  strip.show();
}
/*******************************************************/
void dissolve(uint32_t c_from, uint32_t c_to, uint32_t duration)
{
   uint32_t elapsed_time = 0;
   uint32_t tick = duration/(strip.numPixels()+50);
   bool temp[strip.numPixels()];
   int  rand;

   for(uint16_t j=0; j<strip.numPixels(); j++)
   { temp[j] = false;
     strip.setPixelColor(j,c_from);
   }

   while (elapsed_time < duration)
   {
     rand = random(strip.numPixels());
     if (temp[rand])
     { rand = random(strip.numPixels());
       if (temp[rand])
       {
         for(uint16_t i=0; i<strip.numPixels(); i++)
         { if (!temp[i]) {rand=i; i = 999;} }
       }
     }
     temp[rand] = true;
     strip.setPixelColor(rand,c_to);
     strip.show();
     delay(tick);

     elapsed_time += tick+5;
   }

   for(uint16_t j=0; j<strip.numPixels(); j++)
   { strip.setPixelColor(j,c_to);}
   strip.show();

} //dissolve



/*******************************************************/
void firstHalfDissolve(uint32_t c_to, uint32_t duration)
{
   uint32_t elapsed_time = 0;
   uint32_t tick = duration/(strip.numPixels()/2);
   bool temp[strip.numPixels()];
   int  rand;


   for(uint16_t j=0; j< strip.numPixels(); j++){
      if(j%2 == 1){
        temp[j] = true;
      }else{
        temp[j] = false;
      }
   }

   while (elapsed_time < duration)
   {
     rand = abs(random(strip.numPixels() /2 ) * 2);
     if (temp[rand]){
       rand = abs(random(strip.numPixels() /2 ) * 2);
       if (temp[rand]){
         for(uint16_t i=0; i<strip.numPixels(); i+=2){
            if (!temp[i]) {
              rand=i;
              break;
            }
         }
       }
     }
     temp[rand] = true;
     strip.setPixelColor(rand,c_to);
     strip.show();
     delay(tick);

     elapsed_time += tick;
   }


  for(uint16_t j=0; j<strip.numPixels(); j++){
    if(temp[j] == false){
      strip.setPixelColor(j,c_to);
      temp[j] = true;
      strip.show();
      delay(tick);
    }
  }

} //dissolve

/*******************************************************/
void secondHalfDissolve(uint32_t c_to, uint32_t duration)
{
   uint32_t elapsed_time = 0;
   uint32_t tick = duration/(strip.numPixels()/2);
   bool temp[strip.numPixels()];
   int  rand;

   for(uint16_t j=0; j< strip.numPixels(); j++){
      if(j%2 == 0){
        temp[j] = true;
      }else{
        temp[j] = false;
      }
   }


   while (elapsed_time < duration)
   {
     rand = abs(random(strip.numPixels() /2 ) * 2) +1;
     if (temp[rand]){
       rand = abs(random(strip.numPixels() /2 ) * 2) +1;
       if (temp[rand]){
         for(uint16_t i=1; i<strip.numPixels(); i+=2){
            if (!temp[i]) {
              rand=i;
              break;
            }
         }
       }
     }
     temp[rand] = true;
     strip.setPixelColor(rand,c_to);
     strip.show();
     delay(tick);

     elapsed_time += tick;
   }

  for(uint16_t j=0; j<strip.numPixels(); j++){
    if(temp[j] == false){
      strip.setPixelColor(j,c_to);
      temp[j] = true;
      strip.show();
      delay(tick);
    }
  }

} //dissolve

/*******************************************************/
// Transition all lights from color c_from to color c_to
void fade(uint32_t c_from, uint32_t c_to, uint32_t duration)
{
   uint32_t elapsed_time = 0;
   uint32_t temp_color;


   while (elapsed_time < duration)
   {
     temp_color = colorSlope(c_from,c_to,float(elapsed_time)/float(duration));

     for(uint16_t i=0; i<strip.numPixels(); i++)
     { strip.setPixelColor(i,temp_color); }

     strip.show();
     delay(50);
     elapsed_time += 55;

   }
   for(uint16_t i=0; i<strip.numPixels(); i++)
     { strip.setPixelColor(i,c_to); }
   strip.show();

} //fade
/***********************************************************/
// Transition all lights from existing color to color c_to
void transitionFade(uint32_t top, uint32_t middle, uint32_t bottom, uint32_t tick, uint32_t duration)
{
  uint32_t elapsed_time = 0;
  uint32_t temp_color;

  uint32_t next_color;
  uint32_t pos;

  while (elapsed_time < duration)
    {
      for(uint16_t i=0; i<strip.numPixels(); i++){
        pos = float(Positions[i*2+1]);
        if(pos < MAX_Y / 2){
          next_color = colorSlope(top,middle,pos/float(MAX_Y/2));
        } else {
          next_color = colorSlope(middle,bottom,(pos - MAX_Y/2)/float(MAX_Y/2));
        }
        temp_color = colorSlope(strip.getPixelColor(i),next_color,float(elapsed_time)/float(duration));
        strip.setPixelColor(i,temp_color);
      }

      strip.show();
      /* delay(tick); */
      elapsed_time += tick + 5;

    }

} //fade
/***********************************************************/
// Transition all lights from existing color to color c_to
void fadeFromExisting(uint32_t c_to, uint32_t duration)
{
   uint32_t elapsed_time = 0;
   uint32_t temp_color;


   while (elapsed_time < duration)
   {


     for(uint16_t i=0; i<strip.numPixels(); i++){
        temp_color = colorSlope(strip.getPixelColor(i),c_to,float(elapsed_time)/float(duration));
        strip.setPixelColor(i,temp_color);
     }

     strip.show();
     delay(50);
     elapsed_time += 55;

   }
   for(uint16_t i=0; i<strip.numPixels(); i++)
     { strip.setPixelColor(i,c_to); }
   strip.show();

} //fade
/***********************************************************/
// Transition of colors
void transition(uint32_t c_top, uint32_t c_bottom)
{
   uint32_t elapsed_time = 0;
   uint32_t temp_color;

   for(uint16_t i=0; i<strip.numPixels(); i++) {
     temp_color = colorSlope(c_top,c_bottom,float(Positions[i*2+1])/float(MAX_Y));
     strip.setPixelColor(i,temp_color);
   }

   strip.show();
   delay(50);

} //Transition of colors
/***********************************************************/
// verticalTransitionWave of colors
void verticalTransitionWave(uint32_t c_top, uint32_t c_bottom, uint32_t tick, uint32_t duration)
{
    uint32_t elapsed_time = 0;
    uint32_t temp_color;
    float offset = 0;
    while (elapsed_time < duration)
    {
        for(uint16_t i=0; i<strip.numPixels(); i++){
            if(offset > MAX_Y) offset = 0;
            float y_coord = float(Positions[i*2+1]) - offset;
           	float percent = abs(y_coord/float(MAX_Y/2));
            if(percent > 1) {
                percent = 2 - percent;
            }
            temp_color = colorSlope(c_bottom, c_top, percent);
            strip.setPixelColor(i,temp_color);
        }
        offset += 1 ;
        strip.show();
        delay(tick);
        elapsed_time += tick + 5;
    }
} //verticalTransitionWave of colors
/***********************************************************/
// Horiz Wipe from color c_from to color c_to
void horizWipe(boolean left_to_right, uint32_t c_wipe, uint32_t c_orig, uint32_t duration)
{
   uint32_t elapsed_time = 0;
   uint32_t X_temp;


   while (elapsed_time < duration)
   {
     //Locate the wipe X
     X_temp = (uint32_t)(float(elapsed_time)/float(duration)*float(MAX_X));


     for(uint16_t i=0; i<strip.numPixels(); i++)
     { if (left_to_right)
          {if (Positions[i*2] < X_temp ) {strip.setPixelColor(i,c_wipe); } else {strip.setPixelColor(i,c_orig);   }}
       else
          {if (Positions[i*2] > MAX_X - X_temp ) {strip.setPixelColor(i,c_wipe); } else {strip.setPixelColor(i,c_orig);   }}
     }
     strip.show();
     delay(50);
     elapsed_time += 55;
   }
   for(uint16_t i=0; i<strip.numPixels(); i++)
     { strip.setPixelColor(i,c_wipe); }
   strip.show();

} //horizWipe
/***********************************************************/
// Horiz Wipe from color c_from to color c_to
void centerHorizWipe(uint32_t c_wipe, uint32_t c_orig, uint32_t duration)
{
   uint32_t elapsed_time = 0;
   uint32_t X_Lower,X_Upper;


   while (elapsed_time < duration)
   {
     //Locate the wipe X
     X_Lower = (uint32_t)(float(MAX_X/2) - float(elapsed_time)/float(duration)*float(MAX_X)/2);
     X_Upper = (uint32_t)(float(MAX_X/2) + float(elapsed_time)/float(duration)*float(MAX_X)/2);

     for(uint16_t i=0; i<strip.numPixels(); i++)
     { if (Positions[i*2] >= X_Lower && Positions[i*2] <= X_Upper )
           {strip.setPixelColor(i,c_wipe); }
       else
           {strip.setPixelColor(i,c_orig);   }
     }
     strip.show();
     delay(50);
     elapsed_time += 55;
   }
   for(uint16_t i=0; i<strip.numPixels(); i++)
     { strip.setPixelColor(i,c_wipe); }
   strip.show();
} //horizWipe
/***********************************************************/
// Vert Wipe from color c_from to color c_to
void vertWipe(boolean bottom_to_top, uint32_t c_wipe, uint32_t c_orig, uint32_t duration)
{
   uint32_t elapsed_time = 0;
   uint32_t Y_temp;


   while (elapsed_time < duration)
   {
     //Locate the wipe Y
     Y_temp = (uint32_t)(float(elapsed_time)/float(duration)*float(MAX_Y));


     for(uint16_t i=0; i<strip.numPixels(); i++)
     { if (bottom_to_top)
          {if (Positions[i*2+1] < Y_temp ) {strip.setPixelColor(i,c_wipe); } else {strip.setPixelColor(i,c_orig);   }}
       else
          {if (Positions[i*2+1] > MAX_Y - Y_temp ) {strip.setPixelColor(i,c_wipe); } else {strip.setPixelColor(i,c_orig);   }}
     }
     strip.show();
     delay(50);
     elapsed_time += 55;
   }
   for(uint16_t i=0; i<strip.numPixels(); i++)
     { strip.setPixelColor(i,c_wipe); }
   strip.show();

} //vertWipe
/*******************************************************/
// Vert Line across from color c_from to color c_to
void vertLine(boolean bottom_to_top, uint32_t c_wipe, uint32_t c_orig, uint32_t duration)
{
   uint32_t elapsed_time = 0;
   uint32_t Y_temp;


   while (elapsed_time < duration)
   {
     //Locate the wipe Y
     Y_temp = (uint32_t)(float(elapsed_time)/float(duration)*float(MAX_Y));


     for(uint16_t i=0; i<strip.numPixels(); i++)
     { if (bottom_to_top)
          {if (Positions[i*2+1] == Y_temp | Positions[i*2+1] == Y_temp+1) {strip.setPixelColor(i,c_wipe); } else {strip.setPixelColor(i,c_orig);   }}
       else
          {if (Positions[i*2+1] == MAX_Y - Y_temp | Positions[i*2+1] == MAX_Y - Y_temp+1 ) {strip.setPixelColor(i,c_wipe); } else {strip.setPixelColor(i,c_orig);   }}
     }
     strip.show();
     delay(50);
     elapsed_time += 55;
   }
} //vertWipe
/********************************************************/
void vertWave(uint32_t c1, uint32_t c2, uint32_t tick, uint32_t duration)
{
   uint32_t elapsed_time = 0;
   uint32_t ticker = 0;
   while (elapsed_time < duration)
   {
     for(uint16_t i=0; i < LED_COUNT; i++)
     {
       if ((Positions[i*2+1] / 4) % 4 == ticker % 4)
          {strip.setPixelColor(i, c1);}
       else
          {strip.setPixelColor(i, c2);}
     }
     strip.show();
     delay(tick);
     ticker++;
     elapsed_time += tick + 5;
   }
}
/********************************************************/
void vertCenterWave(uint32_t c1, uint32_t c2, uint32_t tick, uint32_t duration)
{
   uint32_t elapsed_time = 0;
   uint32_t ticker = 0;
   while (elapsed_time < duration)
   {
     for(uint16_t i=0; i < LED_COUNT; i++)
     {
       if (((abs(MAX_Y/2 - Positions[i*2+1]) / 3) % 3 == ticker % 3))
          {strip.setPixelColor(i, c1);}
       else
          {strip.setPixelColor(i, c2);}
     }
     strip.show();
     delay(tick);
     ticker++;
     elapsed_time += tick + 5;
   }
}
/********************************************************/
void setBlock(uint32_t block, uint32_t c)
{
  uint32_t y_pos;

  for(uint16_t i=0; i<strip.numPixels();i++) {
    y_pos = Positions[i*2+1];
      if (y_pos/(MAX_Y/6) == block)
        { strip.setPixelColor(i,c); }
    }

  strip.show();

}
/********************************************************/
void shimmer(uint32_t c_base, uint32_t c_shimmer, uint32_t duration, uint32_t amount)
{
   uint32_t shimmer_pixel_num[amount];
   float    shimmer_pixel_percent[amount];
   uint32_t elapsed_time = 0;

   for(uint16_t i=0; i < amount; i++)
   { shimmer_pixel_num[i] = 0; }

   for(uint16_t i=0; i < strip.numPixels(); i++)
   { strip.setPixelColor(i,c_base);   }

   while (elapsed_time < duration)
   {
     // See if we should start a shimmer
     for(uint16_t i=0; i < amount; i++)
     {
       if (shimmer_pixel_num[i] == 0 & random(10) > 8)
       { shimmer_pixel_num[i] = random(199) + 1;
         shimmer_pixel_percent[i] = 0.0;
       }
       if (shimmer_pixel_num[i] > 0)
       {
         if (i% 2 == 0)
         { shimmer_pixel_percent[i] += 0.02; }
         else
         { shimmer_pixel_percent[i] += 0.04; }
         if (shimmer_pixel_percent[i] >= 2.0)
         {
           strip.setPixelColor(shimmer_pixel_num[i],c_base);
           shimmer_pixel_num[i] = 0;
         }
         else
         {
           strip.setPixelColor(shimmer_pixel_num[i],colorSlope(c_shimmer,c_base,abs(1.0 - shimmer_pixel_percent[i])));
         }
       }
     }

     strip.show();
     delay(50);
     elapsed_time += 50 + 5 ;
   }

   for(uint16_t i=0; i < strip.numPixels(); i++)
   { strip.setPixelColor(i,c_base);   }
   strip.show();


}

void initialize(uint32_t color){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
  delay(1000);
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
  delay(1000);
}

// Fill the dots one after the other with a color
void getLocations(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(500);
    strip.setPixelColor(i, strip.Color(0,0,0));
    if(i%10 == 9){
      for(uint16_t j=i-10; j<i; j++){
        strip.setPixelColor(j, c);
      }
      strip.show();
      delay(500);
      for(uint16_t j=i-10; j<i; j++){
        strip.setPixelColor(j, strip.Color(0,0,0));
      }
    }
  }
}

void rainbowLines(uint32_t tick, uint32_t duration, uint16_t num_colors, uint32_t colors[])
{
  uint32_t elapsed_time = 0;
  uint32_t temp_color;
  float offset = 0;

  float multiplier = float(num_colors);
  float max = float(MAX_Y);
  float denominator = max / multiplier;
  float y_coord;
  float percent;
  uint32_t current;
  uint32_t next;
  int intpart;
  while (elapsed_time < duration)
    {
      for(uint16_t i=0; i<strip.numPixels(); i++){
        if(offset > MAX_Y) offset = 0;
        // we want y_coord to wrap around to the top, so when y_coord is less than zero,
        // we need to add MAX_Y to it, that way we don't deal with silly abs()ing stuff
        // and percent will never be greater than 1

        y_coord = float(Positions[i*2+1]) - offset;
        if(y_coord < 0) y_coord = y_coord + MAX_Y;
        percent = y_coord/denominator;

        // we can generailze the percent by dropping the int part of it
        intpart = (int)percent;
        percent = percent - intpart;

        // now, in order to add colors, we can do that, except that there will be a hard-stop
        // at the beginning and end. this means we need to add a third transition back to the first color
        // we should be able to generalize this for the number of colors given
        for(uint16_t j = 1; j <= num_colors; j++){
          current = colors[j-1];
          next = j < num_colors ? colors[j] : colors[0];
          if(y_coord < denominator * j){
            temp_color = next; //colorSlope(current, next, percent);
            break;
          }
        }

        strip.setPixelColor(i,temp_color);
      }
      offset += 1 ;
      strip.show();
      delay(tick);
      elapsed_time += tick + 5;
    }
}
