#include "applications.h"

#include <FontBitmap.h>

#include <debugging.h>
#define DEBUGGING false
#define CONSTRUCTOR_DEBUGGING false
#define ASSERT_CHECK true

namespace LEDArrangement
    {

// Die erste Dimension des Arrays stellt den Integer Wert des Zeichens dar.
// Die zweite Dimension des Arrays stellt die 5 Reihen eines Zeichens dar.
// In jeder Reihe sind 8 Werte gespeichert, die jeder für eine Zeile stehen.
// Die Zeilen werden von oben nach unten gezählt, während die Bits im Byte der Reihe
// von rechts nach links zu lesen sind.
//
//  |-Zeichen-|
//  |-| Reihe
//   X X X X X
//   X X X X X
//   X X X X X
//   X X X X X
//   X X X X X
//   X X X X X
//   X X X X X
//   X X X X X

#define char_height 8
#define char_width 5

// PROGMEM Macro plaziert Array in ROM-Speicher
const PROGMEM UINT_8 font[128][char_width + 1] = {
    {0x6C, 0x82, 0x82, 0x6C, 0x00, 4}, // 7-Segment 0
    {0x00, 0x00, 0x00, 0x6C, 0x00, 4}, // 7-Segment 1
    {0x60, 0x92, 0x92, 0x0C, 0x00, 4}, // 7-Segment 2
    {0x00, 0x92, 0x92, 0x6C, 0x00, 4}, // 7-Segment 3
    {0x0C, 0x10, 0x10, 0x6C, 0x00, 4}, // 7-Segment 4
    {0x0C, 0x92, 0x92, 0x60, 0x00, 4}, // 7-Segment 5
    {0x6C, 0x92, 0x92, 0x60, 0x80, 5}, // 7-Segment 6
    {0x00, 0x02, 0x02, 0x6C, 0x00, 4}, // 7-Segment 7
    {0x6C, 0x92, 0x92, 0x6C, 0x00, 4}, // 7-Segment 8
    {0x0C, 0x92, 0x92, 0x6C, 0x80, 5}, // 7-Segment 9
    {0x6C, 0x12, 0x12, 0x6C, 0x00, 4}, // 7-Segment A
    {0x6C, 0x90, 0x90, 0x60, 0x00, 4}, // 7-Segment B
    {0x6C, 0x82, 0x82, 0x00, 0x00, 4}, // 7-Segment C
    {0x60, 0x90, 0x90, 0x6C, 0x00, 4}, // 7-Segment D
    {0x6C, 0x92, 0x92, 0x00, 0x00, 4}, // 7-Segment E
    {0x6C, 0x12, 0x12, 0x00, 0x00, 4}, // 7-Segment F
    {0x00, 0x00, 0x00, 0x00, 0x00, 5},
    {0x00, 0x00, 0x00, 0x00, 0x00, 5},
    {0x00, 0x00, 0x00, 0x00, 0x00, 5},
    {0x00, 0x00, 0x00, 0x00, 0x00, 5},
    {0x00, 0x00, 0x00, 0x00, 0x00, 5},
    {0x00, 0x00, 0x00, 0x00, 0x00, 5},
    {0x00, 0x00, 0x00, 0x00, 0x00, 5},
    {0x00, 0x00, 0x00, 0x00, 0x00, 5},
    {0x00, 0x00, 0x00, 0x00, 0x00, 5},
    {0x00, 0x00, 0x00, 0x00, 0x00, 5},
    {0x00, 0x00, 0x00, 0x00, 0x00, 5},
    {0x00, 0x00, 0x00, 0x00, 0x00, 5},
    {0x00, 0x00, 0x00, 0x00, 0x00, 5},
    {0x00, 0x00, 0x00, 0x00, 0x00, 5},
    {0x00, 0x00, 0x00, 0x00, 0x00, 5},
    {0x00, 0x00, 0x00, 0x00, 0x00, 5},
    {0x00, 0x00, 0x00, 0x00, 0x00, 5}, // SPACE
    {0x4F, 0x00, 0x00, 0x00, 0x00, 1}, // !
    {0x07, 0x00, 0x07, 0x00, 0x00, 3}, // "
    {0x14, 0x7F, 0x14, 0x7F, 0x14, 5}, // #
    {0x24, 0x2A, 0x7F, 0x2A, 0x12, 5}, // $
    {0x23, 0x13, 0x08, 0x64, 0x62, 5}, // %
    {0x36, 0x49, 0x55, 0x22, 0x50, 5}, // &
    {0x05, 0x03, 0x00, 0x00, 0x00, 2}, // '
    {0x1C, 0x22, 0x41, 0x00, 0x00, 3}, // (
    {0x41, 0x22, 0x1C, 0x00, 0x00, 3}, // )
    {0x14, 0x08, 0x3E, 0x08, 0x14, 5}, // *
    {0x08, 0x08, 0x3E, 0x08, 0x08, 5}, // +
    {0x50, 0x30, 0x00, 0x00, 0x00, 2}, // ,
    {0x08, 0x08, 0x08, 0x08, 0x08, 5}, // -
    {0x60, 0x60, 0x00, 0x00, 0x00, 2}, // .
    {0x20, 0x10, 0x08, 0x04, 0x02, 5}, // /
    {0x3E, 0x51, 0x49, 0x45, 0x3E, 5}, // 0
    {0x42, 0x7F, 0x40, 0x00, 0x00, 3}, // 1
    {0x42, 0x61, 0x51, 0x49, 0x46, 5}, // 2
    {0x21, 0x41, 0x45, 0x4B, 0x31, 5}, // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10, 5}, // 4
    {0x27, 0x45, 0x45, 0x45, 0x39, 5}, // 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30, 5}, // 6
    {0x01, 0x71, 0x09, 0x05, 0x03, 5}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36, 5}, // 8
    {0x06, 0x49, 0x49, 0x29, 0x1E, 5}, // 9
    {0x36, 0x36, 0x00, 0x00, 0x00, 2}, // :
    {0x56, 0x36, 0x00, 0x00, 0x00, 2}, // ;
    {0x08, 0x14, 0x22, 0x41, 0x00, 4}, // <
    {0x14, 0x14, 0x14, 0x14, 0x14, 5}, // =
    {0x41, 0x22, 0x14, 0x08, 0x00, 4}, // >
    {0x02, 0x01, 0x51, 0x09, 0x06, 5}, // ?
    {0x30, 0x49, 0x79, 0x41, 0x3E, 5}, // @
    {0x7E, 0x11, 0x11, 0x11, 0x7E, 5}, // A
    {0x7F, 0x49, 0x49, 0x49, 0x36, 5}, // B
    {0x3E, 0x41, 0x41, 0x41, 0x22, 5}, // C
    {0x7F, 0x41, 0x41, 0x22, 0x1C, 5}, // D
    {0x7F, 0x49, 0x49, 0x49, 0x41, 5}, // E
    {0x7F, 0x09, 0x09, 0x09, 0x01, 5}, // F
    {0x3E, 0x41, 0x49, 0x49, 0x7A, 5}, // G
    {0x7F, 0x08, 0x08, 0x08, 0x7F, 5}, // H
    {0x41, 0x7F, 0x41, 0x00, 0x00, 3}, // I
    {0x20, 0x40, 0x41, 0x3F, 0x01, 5}, // J
    {0x7F, 0x08, 0x14, 0x22, 0x41, 5}, // K
    {0x7F, 0x40, 0x40, 0x40, 0x40, 5}, // L
    {0x7F, 0x02, 0x0C, 0x02, 0x7F, 5}, // M
    {0x7F, 0x04, 0x08, 0x10, 0x7F, 5}, // N
    {0x3E, 0x41, 0x41, 0x41, 0x3E, 5}, // O
    {0x7F, 0x09, 0x09, 0x09, 0x06, 5}, // P
    {0x3E, 0x41, 0x51, 0x21, 0x5E, 5}, // Q
    {0x7F, 0x09, 0x19, 0x29, 0x46, 5}, // R
    {0x46, 0x49, 0x49, 0x49, 0x31, 5}, // S
    {0x01, 0x01, 0x7F, 0x01, 0x01, 5}, // T
    {0x3F, 0x40, 0x40, 0x40, 0x3F, 5}, // U
    {0x1F, 0x20, 0x40, 0x20, 0x1F, 5}, // V
    {0x3F, 0x40, 0x30, 0x40, 0x3F, 5}, // W
    {0x63, 0x14, 0x08, 0x14, 0x63, 5}, // X
    {0x07, 0x08, 0x70, 0x08, 0x07, 5}, // Y
    {0x61, 0x51, 0x49, 0x45, 0x43, 5}, // Z
    {0x7F, 0x41, 0x41, 0x00, 0x00, 3}, // [
    {0x02, 0x04, 0x08, 0x10, 0x20, 5}, // backslash
    {0x41, 0x41, 0x7F, 0x00, 0x00, 3}, // ]
    {0x04, 0x02, 0x01, 0x02, 0x04, 5}, // ^
    {0x40, 0x40, 0x40, 0x40, 0x40, 5}, // _
    {0x01, 0x02, 0x04, 0x00, 0x00, 3}, // `
    {0x20, 0x54, 0x54, 0x54, 0x78, 5}, // a
    {0x7F, 0x50, 0x48, 0x48, 0x30, 5}, // b
    {0x38, 0x44, 0x44, 0x44, 0x20, 5}, // c
    {0x38, 0x44, 0x44, 0x48, 0x7F, 5}, // d
    {0x38, 0x54, 0x54, 0x54, 0x18, 5}, // e
    {0x08, 0x7E, 0x09, 0x01, 0x02, 5}, // f
    {0x0C, 0x52, 0x52, 0x52, 0x3E, 5}, // g
    {0x7F, 0x08, 0x04, 0x04, 0x78, 5}, // h
    {0x44, 0x7D, 0x40, 0x00, 0x00, 3}, // i
    {0x20, 0x40, 0x44, 0x3D, 0x00, 4}, // j
    {0x7F, 0x10, 0x28, 0x44, 0x00, 4}, // k
    {0x41, 0x7F, 0x40, 0x00, 0x00, 3}, // l
    {0x78, 0x04, 0x58, 0x04, 0x78, 5}, // m
    {0x7C, 0x08, 0x04, 0x04, 0x78, 5}, // n
    {0x38, 0x44, 0x44, 0x44, 0x38, 5}, // o
    {0x7C, 0x14, 0x14, 0x14, 0x08, 5}, // p
    {0x08, 0x14, 0x14, 0x18, 0x7C, 5}, // q
    {0x7C, 0x08, 0x04, 0x04, 0x08, 5}, // r
    {0x48, 0x54, 0x54, 0x54, 0x20, 5}, // s
    {0x04, 0x3F, 0x44, 0x40, 0x20, 5}, // t
    {0x3C, 0x40, 0x40, 0x20, 0x7C, 5}, // u
    {0x1C, 0x20, 0x40, 0x20, 0x1C, 5}, // v
    {0x3C, 0x40, 0x30, 0x40, 0x3C, 5}, // w
    {0x44, 0x28, 0x10, 0x28, 0x44, 5}, // x
    {0x0C, 0x50, 0x50, 0x50, 0x3C, 5}, // y
    {0x44, 0x64, 0x54, 0x4C, 0x44, 5}, // z
    {0x08, 0x36, 0x41, 0x00, 0x00, 3}, // {
    {0x7F, 0x00, 0x00, 0x00, 0x00, 1}, // |
    {0x41, 0x36, 0x08, 0x00, 0x00, 3}, // }


    {0x0C, 0x02, 0x0C, 0x10, 0x0C, 5}  // ~
};

// Show string on a Matrix
// TODO: Migrate to class, then the char_lengths are read only once and can be saved.
void show_string(LEDMatrix &mat, const String text, const CRGB color, const int8_t shift_horizontal, const bool begin_right, const CRGB background)
{
    UINT_8 width = mat.matrix_width();
    UINT_8 height = mat.matrix_height();
    int8_t text_length = 1;
    if (text.length() > 1){
        text_length = text.length();
    }
    
    // Testen ob Submatrix hoch genug ist für die Zeichen
    if (DEBUGGING)
        DEBUG(String("Testen ob Submatrix hoch genug ist für die Zeichen") + (char_height <= height ? "true" : "false"));
    if (ASSERT_CHECK)
        TEST(char_height <= height);

    // Liste anlegen mit Längen der Zeichen.
    int8_t char_lengths[text_length] = {};
    for(int8_t i = 0; i < text_length; ++i){
        char_lengths[i] = pgm_read_byte(&font[i][char_width]);
        
    }

    UINT_8 k = 0;
    UINT_8 character = 0;
    UINT_8 offset_in_first_character = shift_horizontal;
    // Set first character and first row.
    for(UINT_8 i = 0; offset_in_first_character - char_lengths[i] >= 0 && i < text_length; ++i){
        offset_in_first_character -= char_lengths[i];
        character = i;
    }
    // Text scrolling in by the right side.
    if(begin_right == true){
        if(shift_horizontal < width){
           k = width - shift_horizontal; 
        }
    }
    // fill all pixel with background
    mat.color_all(background);

    // Buchstaben durchlaufen bis das Stringende erreicht wurde
    // oder bis die Breite der SubMatrix erreicht wurde. K ist auch die absolute Reihe
    // in der Submatrix zum setzen der Pixel.
    bool first = true;
    while (character < text_length && k < width)
    {
        int8_t i = 0;
        if(first){
            i = offset_in_first_character;
            first = false;
        }
        // Zeichenreihen eines Zeichens durchlaufen bis zum Zeichenende.
        while (i < char_lengths[character] && k < width)
        {
        
            // Zeilen innerhalb der Zeichenreihe durchlaufen, um die Pixel von Oben nach unten
            // in der Zeichenreihe i an der absoluten Stelle k zu setzen.
            const UINT_8 column_bitmap = pgm_read_byte(&font[(UINT_8)(text.charAt(character))][i]);
            for (UINT_8 j = 0; j < char_height; ++j)
            {
                // Wenn Bit im Zeichenbyte an der Stelle j 1 ist, dann setz meinen Pixel auf color.
                // An der absoluten Stelle (j,k) in der Submatrix.
                if((1<<j) & column_bitmap)
                {
                    mat.pixel(j, k) = color;
                }
            }
            // Nach jeder Abgeschlossenen Zeichenreihe eine Reihe weitergehen auf der Submatrix.
            ++k;
            ++i;
        }
        // Leerzeile nach dem Buchstaben, indem einfach eine Reihe auf der Submatrix übersprungen wird.
        ++k;
        ++character;
    }
    if (DEBUGGING)
        DEBUG("printed " + '"' + text + '"');
    FastLED.show();
}

// Überladung von show_string für CHSV Farbe
    
void show_string(LEDMatrix &mat, const String text, const CHSV color, const int8_t shift_horizontal, const bool begin_right, const CHSV background)
{
    show_string(mat, text, CRGB(color), shift_horizontal, begin_right, CRGB(background));
}








// Print-Funktion von SvenJupiter
void print_char(LEDMatrix &mat, const Font::CharBitmap& character_bitmap, const CRGB color, const CRGB background)
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
        for (UINT_8 i = 0; i < char_height; ++i)
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

// Print-Funktion von SvenJupiter
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

// Print-Funktion von SvenJupiter
// Überladung von print_char für CHSV Farbe
void print_char(LEDMatrix &mat, const char character, const CHSV color, const CHSV background)
{
    print_char(mat, character, CRGB(color), CRGB(background));
}



// Print-Funktion von SvenJupiter
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

// Print-Funktion von SvenJupiter
// Überladung von print_string für CHSV Farbe
void print_string(LEDMatrix &mat, const char *const text, const CHSV color, const CHSV background, const UINT_8 space_between_characters)
{
    print_string(mat, text, CRGB(color), CRGB(background), space_between_characters);
}


// Lauftext
void print_rolling_String(LEDMatrix &mat, const String text, const uint16_t delay_between_frames_ms, 
    const CRGB color, const CRGB background, const UINT_8 space_between_characters, 
    const Direction direction, const UINT_8 edge_offset)
{

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