#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define LED_COUNT 200

#define MAX 192
#define LONG_WAIT 180000
#define SHORT_WAIT 30000
#define LONG_TRANS 20000
#define SHORT_TRANS 5000
//
//#define LONG_WAIT 18000
//#define SHORT_WAIT 3000
//#define LONG_TRANS 2000
//#define SHORT_TRANS 500

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
#define MAX_X 18
#define MAX_Y 30

uint32_t red = strip.Color(MAX,0,0);
uint32_t green = strip.Color(0,MAX,0);
uint32_t blue = strip.Color(0,0,MAX);
uint32_t cyan = strip.Color(0,MAX,MAX);
uint32_t yellow = strip.Color(MAX,MAX,0);
uint32_t magenta = strip.Color(MAX,0,MAX);
uint32_t white = strip.Color(MAX,MAX,MAX);
uint32_t black = strip.Color(0,0,0);
uint32_t silver = strip.Color(MAX-40,MAX-40,MAX-20);

//Define the X,Y positions of each pixel.  The first array element is the X 
//coordinate of the first LED in the string, the second array element is the
//Y coordinate of the first LED.   The third array element is the X position of
//the second LED, etc...
byte Positions[LED_COUNT*2] =
{        
 7, 6,  7, 7,  6, 7,  5, 8,  4, 6,  3, 7,  3, 6,  2, 6,  3, 6,  1, 7,   // 0 - 9
 1, 8,  2, 9,  2,10,  2,11,  2,12,  4,12,  4,12,  4,13,  4,12,  5,12,   //10 - 19
 5,10,  6, 9,  7,10,  8,12,  8,11,  8,13,  8,13,  8,15,  7,14,  6,13,   //20 - 29
 6,15,  5,14,  3,15,  3,14,  3,14,  4,17,  5,16,  4,16,  5,16,  7,17,   //30 - 39
 7,17,  9,16,  9,16, 10,18,  9,19,  8,20,  8,19,  7,18,  6,20,  6,18,   //40 - 49
 5,17,  4,17,  4,17,  6,18,  4,18,  4,18,  6,20,  6,22,  6,22,  7,20,   //50 - 59
 6,20,  8,21,  8,22,  8,22, 10,22, 10,23, 10,24,  9,24,  7,24,  8,23,   //60 - 69
 6,23,  7,23,  6,23,  5,23,  6,22,  5,21,  7,24,  6,22,  6,24,  7,25,   //70 - 79
 6,25,  7,26,  7,27,  7,27,  7,26,  9,26,  9,27,  9,28,  9,28,  8,28,   //80 - 89
 8,28,  8,27,  7,26,  7,26,  6,26,  8,28,  8,28,  9,30,  9,30,  9,30,   //90 - 99
12,30, 12,29, 12,28, 13,28, 13,28, 13,27, 12,26, 11,27, 10,26, 12,25,   //100-109
11,24, 12,24, 14,24, 14,25, 14,24, 14,23, 14,23, 15,22, 15,22, 13,22,   //110-119
13,23, 13,22, 12,22, 13,22, 11,22, 11,22, 10,21, 11,21, 11,22, 12,21,   //120-129
14,21, 13,20, 14,21, 14,21, 15,22, 16,21, 17,21, 18,19, 18,18, 16,17,   //130-139
16,16, 16,16, 16,18, 16,18, 14,18, 15,19, 14,18, 12,19, 11,18, 11,18,   //140-149
11,15, 10,15, 10,16, 12,15, 12,14, 13,15, 13,15, 14,15, 15,15, 16,15,   //150-159
16,15, 17,16, 17,14, 17,14, 16,14, 18,13, 17,12, 18,11, 18,11, 15,11,   //160-169
15,10, 14,10, 14,11, 13,11, 13,12, 11,11, 11, 9,  9, 9,  9, 8,  7, 9,   //170-179
 7, 7,  8, 6,  9, 8, 11, 6, 12, 6, 13, 7, 14, 7, 16, 8, 16, 8, 16,10,   //180-189
16,10, 18, 9, 17, 8, 19,12, 20, 9, 19, 7, 19, 7, 18, 7, 18, 6, 17, 5    //190-199
};


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // uncomment to gather led positions (manual process):
  // initialize(strip.Color(255,255,255));
  // initialize(strip.Color(255,255,255));
  // initialize(strip.Color(255,255,255));
  // getLocations(strip.Color(255, 255, 255));
  

     Serial.println("Solid");
     solid(red);
     delay(SHORT_WAIT);

     Serial.println("Dissolve Even");
     firstHalfDissolve(green,SHORT_TRANS);
     delay(LONG_WAIT);

     Serial.println("Dissolve");
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
    
     Serial.println("vertWave");
     vertWave(green,blue,1000,LONG_TRANS);
     delay(SHORT_WAIT);
    
////     Serial.println("vertCenterWave");
////     vertCenterWave(strip.Color(255,255,0),strip.Color(0,255,255),150,5000); 
////     delay(3000);
    
     Serial.println("transition");
     transition(blue, green);
     delay(SHORT_WAIT);
    
////     Serial.println("setBlock");
////     setBlock(3,strip.Color(255,255,255));
////     delay(3000);
    
    Serial.println("Shimmer");
    shimmer(red, green,LONG_TRANS,25);
    fade(red, green, SHORT_TRANS);
    shimmer(green, red,LONG_TRANS,25);
    fade(green, red, SHORT_TRANS);

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
// Transition of colors
void transition(uint32_t c_top, uint32_t c_bottom)
{
   uint32_t elapsed_time = 0;
   uint32_t temp_color;
   
   for(uint16_t i=0; i<strip.numPixels(); i++)
     { temp_color = colorSlope(c_top,c_bottom,float(Positions[i*2+1])/float(MAX_Y));        
       strip.setPixelColor(i,temp_color); }
     
   strip.show();     
   delay(50); 
      
} //Transition of colors
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
/*******************************************************/
// Lights up each light in the strip one-by-one, used to
// define pixel positions
void getLocation(uint32_t loc) {
  uint32_t signal = loc;
  
  for(uint16_t i=0; i<strip.numPixels();i++) {
    strip.setPixelColor(i,strip.Color(0,0,0)); 
  }
  
  while(signal > 0)
  {
    
    if (signal >= 10)
    { for(uint16_t i=0; i< 10; i++)
      {strip.setPixelColor(loc*10+i,strip.Color(255,0,0));}
      signal -= 10;
    }
    else
    { for(uint16_t i=0; i< 10; i++)
      {strip.setPixelColor(loc*10+i,strip.Color(255,255,255));}
      signal -= 1;
    }
  
    strip.show();
    delay(500);
    for(uint16_t i=0; i<strip.numPixels();i++) {
      strip.setPixelColor(i,strip.Color(0,0,0)); 
    }
    strip.show();
    delay(500); 
  } //while on signal
  
  for(uint16_t i=0; i < 10; i++)
  {
    strip.setPixelColor(loc*10+i,strip.Color(255,255,255));
    strip.show();
    delay(1000);
    strip.setPixelColor(loc*10+i,strip.Color(0,0,0));
    
    
    
  }
  
} //setupWipe()
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

