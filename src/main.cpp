#include <Arduino.h>
#include <FastLED.h>
#include "LEDbaseMatrix.h"
#include "LEDsubMatrix.h"

#define DEBUG true



const uint16_t NUM_LEDS = 300;
const uint8_t PIN = 6;
CRGBArray<NUM_LEDS> leds;

// Eine LED-Matrix erstellen
LEDArrangement::LEDbaseMatrix<30, 10> base_mat(leds, LEDArrangement::Wiring_Start_Point::TOP_RIGHT, LEDArrangement::Strip_Orientation::ZIGZAG_HORIZONTAL);

LEDArrangement::LEDMatrix<LEDArrangement::LEDbaseMatrix<30, 10>, 10, 10> sub_mat0(base_mat, 0, 0);
LEDArrangement::LEDMatrix<LEDArrangement::LEDbaseMatrix<30, 10>, 10, 10> sub_mat1(base_mat, 0, 10);
LEDArrangement::LEDMatrix<LEDArrangement::LEDbaseMatrix<30, 10>, 10, 10> sub_mat2(base_mat, 0, 20);


void setup() {
    // put your setup code here, to run once:

    Serial.begin(57600);
    delay(100);

    
    if(DEBUG) Serial.println("Init FastLED");
    FastLED.setBrightness(64);
    FastLED.addLeds<NEOPIXEL,PIN>(leds, NUM_LEDS);
  
    //base_mat = base_mat;
  
  
    if(DEBUG) Serial.println("base all_off");
    base_mat.all_off();
    FastLED.show();
  
    delay(1000);

    // Den LED-Streifen testen
    if(DEBUG) Serial.println("base strip_test");
    base_mat.strip_test();


  if(DEBUG) Serial.println("setup complete");

}

void loop() {
  // put your main code here, to run repeatedly:

  // Die LED-Matrix testen
  if(DEBUG) Serial.println("base self_test");
  base_mat.self_test();

  // Die Sub-Matrizen testen
  if(DEBUG) Serial.println("mat0 self_test");
  sub_mat0.self_test();

  if(DEBUG) Serial.println("mat1 self_test");
  sub_mat1.self_test();

  if(DEBUG) Serial.println("mat2 self_test");
  sub_mat2.self_test();

  if(DEBUG) Serial.println("all self_test complete");

}