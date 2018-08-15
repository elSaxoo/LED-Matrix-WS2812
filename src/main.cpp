#include <Arduino.h>
#include <FastLED.h>
#include <LEDMatrix.h>
#include <FontBitmap.h>
#include <applications.h>
#include <SlidingText.h>
#include <Rainbow.h>

#include <debugging.h>
#define DEBUGGING false
#define ASSERT_CHECK true

#define KR 
// #define JS


// Kai
#ifdef KR
    #define NUM_LEDS (10 * 30)
    #define PIN 21
#endif

// Jesko
#ifdef JS
    #define NUM_LEDS (2 * 8 * 32)
    #define PIN 21
#endif

// CRGB Array anlegen
// CRGBArray<NUMBER_OF_LEDS> leds;
CRGB leds[NUM_LEDS]; // Kein Template Parameter :-)

// Für Jessica, 
// das 'J' steht für Jessica
const char jessica_text[] = {'K', '+', 'J', '=', LEDArrangement::Font::Emoji::Heart};


// Emoji Test
const char emoji_text[] = {
    LEDArrangement::Font::Emoji::Smilie,
    LEDArrangement::Font::Emoji::Sad_Smilie,
    LEDArrangement::Font::Emoji::Heart,
    LEDArrangement::Font::Emoji::Y,
    LEDArrangement::Font::Emoji::X,
    LEDArrangement::Font::Emoji::Attention,
    0
};
const String emoji_string(emoji_text);

// Test Text
const char test_text[] = "Kai ist cool";
const String test_string(test_text);


// Eine LED-Matrix erstellen // Kai
#ifdef KR
LEDArrangement::LEDMatrix base_mat(leds, 10, 30, LEDArrangement::Wiring_Start_Point::TOP_RIGHT, LEDArrangement::Strip_Orientation::ZIGZAG_HORIZONTAL);
LEDArrangement::LEDMatrix sub_mat(base_mat, 8, 30, 1, 0);
#endif

// Eine LED-Matrix erstellen // Jesko
// Jesko
#ifdef JS
LEDArrangement::LEDMatrix base_mat(leds, 8, 2*32, LEDArrangement::Wiring_Start_Point::BOTTOM_RIGHT, LEDArrangement::Strip_Orientation::ZIGZAG_VERTICAL);
LEDArrangement::LEDMatrix sub_mat(base_mat, 8, 2*32, 0, 0);
#endif

// LED-Effekt anlegen
LEDArrangement::Effects::SlidingText roll_effect(sub_mat, 2400/30, test_string,
                                CRGB(0, 255, 0), CRGB(0, 0, 0), 1,
                                LEDArrangement::Direction::RIGHT, 0, 
                                20 + LEDArrangement::Effects::SlidingText::TextEnd + LEDArrangement::Effects::SlidingText::MatrixWidth,
                                true);

// LED-Effekt anlegen
LEDArrangement::Effects::Rainbow rainbow_effect(base_mat, 5100/255, 
                                1, 1,
                                8, 25,
                                0, 0,
                                255, 255);



void setup()
{
    // put your setup code here, to run once:
    FastLED.setBrightness(8);
    FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
    base_mat.all_off();

    // set time sync provider
    // setSyncProvider(LEDArrangement::get_time);
    // setSyncInterval(10);


    if (DEBUGGING)
    {
        // Serielle Verbindung starten 
        Serial.begin(115200);
        delay(100);

        DEBUG("Starting Setup...");
    }
    delay(1000);
    

    // // Selbsttest LED-Strip
    // LEDArrangement::led_strip_self_test(leds, NUM_LEDS);
    // delay(2000);
    // base_mat.all_off();


    // // Emoji Test
    // FastLED.setBrightness(64);
    // LEDArrangement::print_string(sub_mat, emoji_text, CRGB(0, 255, 0), CRGB(0, 0, 0), 1);
    // // FastLED.show(); in print-Befehl enthalten
    // delay(10000);
    // FastLED.setBrightness(8);



    // Matrix für Effekt initialisieren
    // roll_effect.setup();

    rainbow_effect.auto_scale_kx_ky(false, true);
    rainbow_effect.setup();
    
    // an Matrix übertragen
    FastLED.show();
    delay(2000);

    if (DEBUGGING)
        DEBUG("...Setup complete");
}

bool text_changed = false;

void loop()
{
    // put your main code here, to run repeatedly:

    bool new_frame_available = false;

    // Die aktuelle Zeit in Millisekunden an Effect-Objekt übergeben
    // Objekt prüft selber, ob seit dem letzten Frame genug Zeit vergangen ist
    // Wenn ja wird neues Frame berechent und true zurückgegeben.
    // Wenn nicht wird nur false zurückgegeben.
    // new_frame_available = roll_effect.update_frame(millis());
    new_frame_available = rainbow_effect.update_frame(millis());


    // Wenn ein neues Frame berechnet wurde 
    if(new_frame_available)
    {
        // an Matrix übertragen
        FastLED.show();
    }

    if (millis() > 16750 && !text_changed)
    {
        roll_effect.set_text(String(emoji_text), true);
        text_changed = true;
    }
}
