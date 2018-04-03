#include <Arduino.h>
#include <FastLED.h>
#include <LEDMatrix.h>
#include <FontBitmap.h>
#include <applications.h>
#include <RollingText.h>

#include <debugging.h>
#define DEBUGGING false
#define ASSERT_CHECK true

#define NUM_LEDS 300
#define PIN 6
CRGBArray<NUM_LEDS> leds;

// Eine LED-Matrix erstellen
LEDArrangement::LEDMatrix base_mat(leds, 10, 30, LEDArrangement::Wiring_Start_Point::TOP_RIGHT, LEDArrangement::Strip_Orientation::ZIGZAG_HORIZONTAL);

LEDArrangement::LEDMatrix sub_mat_time(base_mat, 8, 30, 1, 0);

LEDArrangement::Effects::RollingText roll_effect(sub_mat_time, 5000/30, String("Hallo"),
                                CRGB(0, 255, 0), CRGB(0, 0, 0), 1,
                                LEDArrangement::Direction::LEFT, 30);

void setup()
{
    // put your setup code here, to run once:
    FastLED.setBrightness(8);
    FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
    base_mat.all_off();

    
    // set time sync provider
    setSyncProvider(LEDArrangement::get_time);
    setSyncInterval(10);


    Serial.begin(115200);
    delay(100);

    if (DEBUGGING)
    {
        DEBUG("Starting Setup...");
    }
    delay(1000);


    // Matrix für Effekt initialisieren
    roll_effect.setup_LED_Matrix();


    if (DEBUGGING)
        DEBUG("...Setup complete");
}

void loop()
{
    // put your main code here, to run repeatedly:

    bool new_frame_available = false;

    // Die aktuelle Zeit in Millisekunden an Effect-Objekt übergeben
    // Objekt prüft selber, ob seit dem letzten Frame genug Zeit vergangen ist
    // Wenn ja wird neues Frame berechent und true zurückgegeben.
    // Wenn nicht wird nur false zurückgegeben.
    new_frame_available = roll_effect.update_frame(millis());


    // Wenn ein neues Frame berechnet wurde 
    if(new_frame_available)
    {
        // an Matrix übertragen
        FastLED.show();
    }

        
    delay(500);
}
