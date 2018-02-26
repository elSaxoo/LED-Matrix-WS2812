#include <Arduino.h>
#include <FastLED.h>
#include "LEDbaseMatrix.h"
#include "LEDsubMatrix.h"


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

  FastLED.setBrightness(128);
  FastLED.addLeds<NEOPIXEL,PIN>(leds, NUM_LEDS);

  base_mat = base_mat;

  base_mat.all_off();
  FastLED.show();

  delay(1000);

    // Den LED-Streifen testen
    base_mat.strip_test();


}

void loop() {
  // put your main code here, to run repeatedly:

  //sub_mat1 = sub_mat0;
  // sub_mat2 = sub_mat1;

  // Die LED-Matrix testen
  base_mat.self_test();

  // Die Sub-Matrizen testen
  sub_mat0.self_test();
  sub_mat1.self_test();
  sub_mat2.self_test();


}
