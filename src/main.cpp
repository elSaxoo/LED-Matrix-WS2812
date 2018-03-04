
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

    FastLED.setBrightness(64);
    FastLED.addLeds<NEOPIXEL,PIN>(leds, NUM_LEDS);
    base_mat.all_off();

    Serial.begin(115200);
    delay(100);

    if(DEBUGGING)    
        {DEBUG("Waiting 2 sek...");}
    delay(2000);


    if(DEBUGGING)   
        DEBUG("...setup complete");

}

void loop() {
    // put your main code here, to run repeatedly:

    // Die LED-Matrix testen
    // if(DEBUGGING)    
    //     DEBUG("base self_test");
    // base_mat.self_test();
    // if(DEBUGGING)    DEBUG("all self_test complete");

    // // elSaxoo print-Funktion
    // if(DEBUGGING)   
    //     DEBUG("Testing elSaxoo print-function");
    // LEDArrangement::print_String(sub_mat_time, "15:20", CRGB(255,0,0));
    // delay(5000);

    // // SvenJupiter print-Funktion
    // if(DEBUGGING)    
    //     DEBUG("Testing SvenJupiter print-function");
    // LEDArrangement::print_string(sub_mat_time, "15:20", CRGB(0,255,0));
    // delay(5000);

}

