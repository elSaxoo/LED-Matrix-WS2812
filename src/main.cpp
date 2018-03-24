#include <Arduino.h>
#include <FastLED.h>
#include <LEDMatrix.h>
#include <FontBitmap.h>
#include <applications.h>
#include <Effects.h>

#include <debugging.h>
#define DEBUGGING true
#define ASSERT_CHECK true

#define NUM_LEDS 300
#define PIN 6
CRGBArray<NUM_LEDS> leds;

// Eine LED-Matrix erstellen
LEDArrangement::LEDMatrix base_mat(leds, 10, 30, LEDArrangement::Wiring_Start_Point::TOP_RIGHT, LEDArrangement::Strip_Orientation::ZIGZAG_HORIZONTAL);

LEDArrangement::LEDMatrix sub_mat_time(base_mat, 8, 30, 1, 0);

LEDArrangement::Effects::RollingText roll(sub_mat_time, 5000/30, String("Hallo"));

void setup()
{
    // put your setup code here, to run once:

    FastLED.setBrightness(8);
    FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
    base_mat.all_off();

    Serial.begin(115200);
    delay(100);

    if (DEBUGGING)
    {
        DEBUG("Starting Setup...");
    }
    delay(1000);


    // Symbol in Mitte der Matrix schieben
    // sub_mat_time.shift(LEDArrangement::Direction::RIGHT, 15-3) ;
    // FastLED.show();
    // delay(200);

    if(DEBUGGING)
    {
        // [][][]-Operator Test
        // Zugriff über [][][]-Operator ist ineffizient
        // aber einfach
        // siehe "FontBitmap.h" für effizienteren Weg
        for(char test_char = 0; test_char < 127; ++test_char){
            Serial.println(String("Test char = '") + test_char + String("'"));
            for(int i = 0; i < LEDArrangement::Font::font_bitmap[test_char].height(); ++i) {
                for(int j = 0; j < LEDArrangement::Font::font_bitmap[test_char].width(); ++j) {
                    if(LEDArrangement::Font::font_bitmap[test_char][j][i]) {
                        Serial.print("*");
                    }
                    else {
                        Serial.print(" ");
                    }
                }
                Serial.println();
            }
        }

        DEBUG("Font Test");
        // Testen, ob Font-Konstanten richtig aus PROGMEM-Speicher gelesen werden
        // Ausgabe der Konstanten auf dem Serial Moitor
        LEDArrangement::Font::test_PROGMEM_access();
    }

    // Überarbeite print-Funktion testen
    // Achte mal darauf, ob schmalere Buchstaben nun auch weniger Platz einnehmen
    LEDArrangement::print_string(sub_mat_time, "1.Kai!!");
    delay(60000);


    if (DEBUGGING)
        DEBUG("...Setup complete");
}

void loop()
{
    // put your main code here, to run repeatedly:


        
    delay(500);
}
