

#include <Arduino.h>
#include <FastLED.h>
#include <LEDbaseMatrix.h>
#include <LEDsubMatrix.h>
#include <applications.h>

#define DEBUG true



const uint16_t NUM_LEDS = 300;
const uint8_t PIN = 6;
CRGBArray<NUM_LEDS> leds;

// Eine LED-Matrix erstellen
LEDArrangement::LEDbaseMatrix<10, 30> base_mat(leds, LEDArrangement::Wiring_Start_Point::TOP_RIGHT, LEDArrangement::Strip_Orientation::ZIGZAG_HORIZONTAL);

LEDArrangement::LEDsubMatrix<8, 30> sub_mat_time(base_mat, 1, 0);


void setup() {
    // put your setup code here, to run once:

    Serial.begin(57600);
    delay(100);

    if(DEBUG)   Serial.println("Hello...");

    if(DEBUG)   Serial.println("Waiting 2 sek...");
    delay(2000);


    // if(DEBUG) Serial.println("Init FastLED");
    // FastLED.setBrightness(64);
    // FastLED.addLeds<NEOPIXEL,PIN>(leds, NUM_LEDS);

    // //base_mat = base_mat;


    // if(DEBUG) Serial.println("base all_off");
    // base_mat.all_off();
    // FastLED.show();

    // delay(1000);

    // // Den LED-Streifen testen
    // if(DEBUG) Serial.println("base strip_test");
    // base_mat.strip_test();


    if(DEBUG) Serial.println("...setup complete");

}

void loop() {
    // put your main code here, to run repeatedly:

    // Die LED-Matrix testen
    //if(DEBUG) Serial.println("base self_test");
    // base_mat.self_test();
    //if(DEBUG) Serial.println("all self_test complete");

    // elSaxoo print-Funktion
    if(DEBUG)   Serial.println("Testing elSaxoo print-function");
    LEDArrangement::print_String(sub_mat_time, "15:20", CRGB(255,0,0));
    delay(5000);

    // SvenJupiter print-Funktion
    if(DEBUG)   Serial.println("Testing SvenJupiter print-function");
    LEDArrangement::print_string(sub_mat_time, "15:20", CRGB(0,255,0));
    delay(5000);

}
