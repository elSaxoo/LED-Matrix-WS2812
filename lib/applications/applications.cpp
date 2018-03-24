#include "applications.h"

#include <FontBitmap.h>
#include <TimeLib.h>

#include <debugging.h>
#define DEBUGGING false
#define CONSTRUCTOR_DEBUGGING false
#define ASSERT_CHECK true

namespace LEDArrangement
{

time_t get_time(){
    Serial.write(0xFF);
    while(Serial.available() < 4);
    
    time_t time_now = 0;
    for(uint8_t i = 0; i < 4; ++i){
        time_now = (time_now<<8) | Serial.read();
    }
    
    while(Serial.available()){
       Serial.read(); 
    }

    return time_now;
}

void print_char(LEDMatrix &mat, const Font::CharBitmap &character_bitmap, const CRGB color, const CRGB background)
{
    // Sicherstellen, das Matrix größ genug ist
    if (DEBUGGING)
        DEBUG(String("Testing Matrix height ") + (mat.matrix_height() >= character_bitmap.height() ? "true" : "false"));
    if (DEBUGGING)
        DEBUG(String("Testing Matrix width ") + (mat.matrix_width() >= character_bitmap.width() ? "true" : "false"));
    if (ASSERT_CHECK)
        TEST(mat.matrix_height() >= character_bitmap.height());
    if (ASSERT_CHECK)
        TEST(mat.matrix_width() >= character_bitmap.width());

    // Für jede Spalte der Matrix
    for (UINT_8 j = 0; j < character_bitmap.width(); ++j)
    {

        // Column-Bitmap-Wert aus Flashspeicher holen
        const Font::ColumnBitmap column_bitmap(character_bitmap[j]); // Hier wird Wert aus Flash-Speicher geladen

        // Debug Ausgaben
        if (DEBUGGING)
        {
            DEBUG("Setting up column " + String(j) + "\t");
            Serial.println(column_bitmap, HEX);
        }

        // Für jede Zeile der Spalte
        for (UINT_8 i = 0; i < character_bitmap.height(); ++i)
        {

            // Debug Ausgaben
            if (DEBUGGING)
                DEBUG("Setting up row " + String(i) + "\t" + "Testing: " + String(column_bitmap[i]) + "\t" + (column_bitmap[i] ? "Character" : "Backgroung"));

            // Wenn das Bit der font an der Position i gesetzt ist...
            if (column_bitmap[i])
            {
                // ...gehört das Pixel (i,j) zum Buchstaben
                mat.pixel(i, j) = color;
            }
            else
            {
                // ...ansonste ist es Hintergrund
                mat.pixel(i, j) = background;
            }
        }
    }

    // Nachdem die Pixel passen gesetzt wurde
    // kann der Buchstabe angezeigt werden
    FastLED.show();
}

void print_char(LEDMatrix &mat, const char character, const CRGB color, const CRGB background)
{
    // Char-Bitmap aus Flashspeicher holen
    const Font::CharBitmap character_bitmap(Font::font_bitmap[character]); // Hier wird nur ein Zeiger geladen

    if (DEBUGGING)
        DEBUG(String("Printing char " + character));

    // Zeichen ausgeben
    print_char(mat, character_bitmap, color, background);

    if (DEBUGGING)
        DEBUG("printed " + character);
}

// Überladung von print_char für CHSV Farbe
void print_char(LEDMatrix &mat, const char character, const CHSV color, const CHSV background)
{
    print_char(mat, character, CRGB(color), CRGB(background));
}

void print_string(LEDMatrix &mat, const char *const text, const CRGB color, const CRGB background, const UINT_8 space_between_characters)
{

    // Sicherstellen, das Matrix hoch genug für Zeichen ist
    if (DEBUGGING)
        DEBUG(String("Testing Matrix height \t") + (mat.matrix_height() >= 8 ? "true" : "false"));
    if (ASSERT_CHECK)
        TEST(mat.matrix_height() >= 8);

    // Zeilen-Offset für Buchstaben
    UINT_8 colum_offset = 0;

    // Für jeden Buchstaben in text
    for (UINT_8 i = 0; text[i] != '\0'; ++i)
    {
        // Debug Ausgaben
        if (DEBUGGING)
            DEBUG("Trying to print " + String(i + 1) + ". char \t'" + text[i] + "'");

        // Char-Bitmap aus Flashspeicher holen
        const Font::CharBitmap character_bitmap(Font::font_bitmap[text[i]]); // Hier wird nur ein Zeiger geladen

        // Debug Ausgaben
        if (DEBUGGING)
            DEBUG("Space check");

        // Wenn kein weiterer Buchstabe auf die Matrix passt
        if (((UINT_8)(colum_offset + character_bitmap.width())) > mat.matrix_width())
        {
            // Debug Ausgaben
            if (DEBUGGING)
                DEBUG("No more space available - Breaking from loop");

            // for-Schleife vorzeitig beenden
            break;
        }
        else
        {
            // Debug Ausgaben
            if (DEBUGGING)
                DEBUG("Space available");
            if (DEBUGGING)
                DEBUG("Printing char " + text[i]);

            // Eine Submatrix erstellen
            LEDMatrix sub_mat(mat, character_bitmap.height(), character_bitmap.width(), 0, colum_offset);

            // Buchstaben auf der Submatrix ausgeben
            print_char(sub_mat, character_bitmap, color, background);

            // Zeilen-Offset für nächsten Buchstabe ermitteln
            colum_offset += character_bitmap.width() + space_between_characters;
        }
    }

    // Debug Ausgaben
    if (DEBUGGING)
        DEBUG("done");
}

// Überladung von print_string für CHSV Farbe
void print_string(LEDMatrix &mat, const char *const text, const CHSV color, const CHSV background, const UINT_8 space_between_characters)
{
    print_string(mat, text, CRGB(color), CRGB(background), space_between_characters);
}





// Die Matrix über die serielle Schnittstelle mit Daten versorgen
void serial_matrix_updater(HardwareSerial &UART, LEDMatrix &mat)
{

    // Signalisieren, dass Arduino bereit ist
    UART.write(0x05); // ENQ

    while (true)
    {
        // Für jedes Pixel in der Matrix
        for (UINT_16 i = 0; i < mat.number_of_leds(); ++i)
        {
            // Rot einlesen
            while (!UART.available())
                ;
            mat[i].r = UART.read();

            // Grün einlesen
            while (!UART.available())
                ;
            mat[i].g = UART.read();

            // Blau einlesen
            while (!UART.available())
                ;
            mat[i].b = UART.read();
        }

        // Bild anzeigen
        FastLED.show();

        // Signalisieren, dass Arduino komplettes Bild empfangen hat
        UART.write(0x06); // ACK
    }
}

} // Ende namespace LEDArrangement