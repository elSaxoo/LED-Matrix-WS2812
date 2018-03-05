#include <Arduino.h>
#include <FastLED.h>
#include <LEDMatrix.h>
#include <applications.h>

#include <debugging.h>
#define DEBUGGING true
#define ASSERT_CHECK true


#define NUM_LEDS 300
#define PIN 6
CRGBArray<NUM_LEDS> leds;


// Eine LED-Matrix erstellen
LEDArrangement::LEDMatrix base_mat(leds, 10, 30, LEDArrangement::Wiring_Start_Point::TOP_RIGHT, LEDArrangement::Strip_Orientation::ZIGZAG_HORIZONTAL);

LEDArrangement::LEDMatrix sub_mat_time(base_mat, 8, 30, 1, 0);


void setup() {
    // put your setup code here, to run once:

    FastLED.setBrightness(8);
    FastLED.addLeds<NEOPIXEL,PIN>(leds, NUM_LEDS);
    base_mat.all_off();

    Serial.begin(115200);
    delay(100);

    if(DEBUGGING)    
        {DEBUG("Waiting 2 sek...");}
    delay(2000);


    if(DEBUGGING)   
        DEBUG("...setup complete");


    // Symbol auf Matrix anzeigen
    LEDArrangement::print_String(sub_mat_time, "abcde", CRGB(0,255,0));
    delay(500);

    // Symbol in Mitte der Matrix schieben
    // sub_mat_time.shift(LEDArrangement::Direction::RIGHT, 15-3) ;
    // FastLED.show();
    // delay(200);


}

void loop() {
    // put your main code here, to run repeatedly:


    // Symbol über Matrix schieben
    for(uint8_t i = 0; i < 60; ++i)
    {
        sub_mat_time.cycle(LEDArrangement::Direction::RIGHT, 1);
        FastLED.show();
        delay(200);
    }

    // Symbol in andere Richtung schieben
    for(uint8_t i = 0; i < 60; ++i)
    {
        sub_mat_time.cycle(LEDArrangement::Direction::LEFT, 1);
        FastLED.show();
        delay(200);
    }

    delay(500);


}

