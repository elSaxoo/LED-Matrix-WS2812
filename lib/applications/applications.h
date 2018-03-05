#ifndef APPLICATIONS_H
#define APPLICATIONS_H


#include <LEDMatrix.h>


#define DEBUG true
#define CONSTRUCTOR_DEBUG false
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
    const PROGMEM uint8_t font[128][char_width] = {
        {0x6C,0x82,0x82,0x6C,0x00}, // 7-Segment 0
        {0x00,0x00,0x00,0x6C,0x00}, // 7-Segment 1
        {0x60,0x92,0x92,0x0C,0x00}, // 7-Segment 2
        {0x00,0x92,0x92,0x6C,0x00}, // 7-Segment 3
        {0x0C,0x10,0x10,0x6C,0x00}, // 7-Segment 4
        {0x0C,0x92,0x92,0x60,0x00}, // 7-Segment 5
        {0x6C,0x92,0x92,0x60,0x80}, // 7-Segment 6
        {0x00,0x02,0x02,0x6C,0x00}, // 7-Segment 7
        {0x6C,0x92,0x92,0x6C,0x00}, // 7-Segment 8
        {0x0C,0x92,0x92,0x6C,0x80}, // 7-Segment 9
        {0x6C,0x12,0x12,0x6C,0x00}, // 7-Segment A
        {0x6C,0x90,0x90,0x60,0x00}, // 7-Segment B
        {0x6C,0x82,0x82,0x00,0x00}, // 7-Segment C
        {0x60,0x90,0x90,0x6C,0x00}, // 7-Segment D
        {0x6C,0x92,0x92,0x00,0x00}, // 7-Segment E
        {0x6C,0x12,0x12,0x00,0x00}, // 7-Segment F
        {0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00,0x00},

        {0x00,0x00,0x00,0x00,0x00},	// SPACE

        {0x00,0x00,0x4F,0x00,0x00},	// !
        {0x00,0x07,0x00,0x07,0x00},	// "
        {0x14,0x7F,0x14,0x7F,0x14},	// #
        {0x24,0x2A,0x7F,0x2A,0x12},	// $
        {0x23,0x13,0x08,0x64,0x62},	// %
        {0x36,0x49,0x55,0x22,0x50},	// &
        {0x00,0x05,0x03,0x00,0x00},	// '
        {0x00,0x1C,0x22,0x41,0x00},	// (
        {0x00,0x41,0x22,0x1C,0x00},	// )
        {0x14,0x08,0x3E,0x08,0x14},	// *
        {0x08,0x08,0x3E,0x08,0x08},	// +
        {0x00,0x50,0x30,0x00,0x00},	// ,
        {0x08,0x08,0x08,0x08,0x08},	// -
        {0x00,0x60,0x60,0x00,0x00},	// .
        {0x20,0x10,0x08,0x04,0x02},	// /

        {0x3E,0x51,0x49,0x45,0x3E},	// 0
        {0x00,0x42,0x7F,0x40,0x00},	// 1
        {0x42,0x61,0x51,0x49,0x46},	// 2
        {0x21,0x41,0x45,0x4B,0x31},	// 3
        {0x18,0x14,0x12,0x7F,0x10},	// 4
        {0x27,0x45,0x45,0x45,0x39},	// 5
        {0x3C,0x4A,0x49,0x49,0x30},	// 6
        {0x01,0x71,0x09,0x05,0x03},	// 7
        {0x36,0x49,0x49,0x49,0x36},	// 8
        {0x06,0x49,0x49,0x29,0x1E},	// 9

        {0x36,0x36,0x00,0x00,0x00},	// :
        {0x56,0x36,0x00,0x00,0x00},	// ;
        {0x08,0x14,0x22,0x41,0x00},	// <
        {0x14,0x14,0x14,0x14,0x14},	// =
        {0x00,0x41,0x22,0x14,0x08},	// >
        {0x02,0x01,0x51,0x09,0x06},	// ?
        {0x30,0x49,0x79,0x41,0x3E},	// @

        {0x7E,0x11,0x11,0x11,0x7E},	// A
        {0x7F,0x49,0x49,0x49,0x36},	// B
        {0x3E,0x41,0x41,0x41,0x22},	// C
        {0x7F,0x41,0x41,0x22,0x1C},	// D
        {0x7F,0x49,0x49,0x49,0x41},	// E
        {0x7F,0x09,0x09,0x09,0x01},	// F
        {0x3E,0x41,0x49,0x49,0x7A},	// G
        {0x7F,0x08,0x08,0x08,0x7F},	// H
        {0x00,0x41,0x7F,0x41,0x00},	// I
        {0x20,0x40,0x41,0x3F,0x01},	// J
        {0x7F,0x08,0x14,0x22,0x41},	// K
        {0x7F,0x40,0x40,0x40,0x40},	// L
        {0x7F,0x02,0x0C,0x02,0x7F},	// M
        {0x7F,0x04,0x08,0x10,0x7F},	// N
        {0x3E,0x41,0x41,0x41,0x3E},	// O
        {0x7F,0x09,0x09,0x09,0x06},	// P
        {0x3E,0x41,0x51,0x21,0x5E},	// Q
        {0x7F,0x09,0x19,0x29,0x46},	// R
        {0x46,0x49,0x49,0x49,0x31},	// S
        {0x01,0x01,0x7F,0x01,0x01},	// T
        {0x3F,0x40,0x40,0x40,0x3F},	// U
        {0x1F,0x20,0x40,0x20,0x1F},	// V
        {0x3F,0x40,0x30,0x40,0x3F},	// W
        {0x63,0x14,0x08,0x14,0x63},	// X
        {0x07,0x08,0x70,0x08,0x07},	// Y
        {0x61,0x51,0x49,0x45,0x43},	// Z

        {0x00,0x7F,0x41,0x41,0x00},	// [
        {0x02,0x04,0x08,0x10,0x20},	// backslash
        {0x00,0x41,0x41,0x7F,0x00},	// ]
        {0x04,0x02,0x01,0x02,0x04},	// ^
        {0x40,0x40,0x40,0x40,0x40},	// _
        {0x00,0x01,0x02,0x04,0x00},	// `

        {0x20,0x54,0x54,0x54,0x78},	// a
        {0x7F,0x50,0x48,0x48,0x30},	// b
        {0x38,0x44,0x44,0x44,0x20},	// c
        {0x38,0x44,0x44,0x48,0x7F},	// d
        {0x38,0x54,0x54,0x54,0x18},	// e
        {0x08,0x7E,0x09,0x01,0x02},	// f
        {0x0C,0x52,0x52,0x52,0x3E},	// g
        {0x7F,0x08,0x04,0x04,0x78},	// h
        {0x00,0x44,0x7D,0x40,0x00},	// i
        {0x20,0x40,0x44,0x3D,0x00},	// j
        {0x7F,0x10,0x28,0x44,0x00},	// k
        {0x00,0x41,0x7F,0x40,0x00},	// l
        {0x78,0x04,0x58,0x44,0x78},	// m
        {0x7C,0x08,0x04,0x04,0x78},	// n
        {0x38,0x44,0x44,0x44,0x38},	// o
        {0x7C,0x14,0x14,0x14,0x08},	// p
        {0x08,0x14,0x14,0x18,0x7C},	// q
        {0x7C,0x08,0x04,0x04,0x08},	// r
        {0x48,0x54,0x54,0x54,0x20},	// s
        {0x04,0x3F,0x44,0x40,0x20},	// t
        {0x3C,0x40,0x40,0x20,0x7C},	// u
        {0x1C,0x20,0x40,0x20,0x1C},	// v
        {0x3C,0x40,0x30,0x40,0x3C},	// w
        {0x44,0x28,0x10,0x28,0x44},	// x
        {0x0C,0x50,0x50,0x50,0x3C},	// y
        {0x44,0x64,0x54,0x4C,0x44},	// z

        {0x00,0x08,0x36,0x41,0x00},	// {
        {0x00,0x00,0x7F,0x00,0x00},	// |
        {0x00,0x41,0x36,0x08,0x00},	// }
        {0x0C,0x02,0x0C,0x10,0x0C},	// ~
    };



    // Printing strings as ASCII at the matrix
    void print_String(LEDMatrix& mat, const String text, const CRGB color, const CRGB background = CRGB(0,0,0))
    {
        UINT_8 width = mat.matrix_width();
        UINT_8 height = mat.matrix_height();
        int text_length = text.length();

        // Testen ob Submatrix hoch genug ist für die Zeichen
        if(ASSERT_CHECK)    assert(char_height <= height);

        // Fill background with backgroundcolor
        mat.color_all(background);

        // Buchstaben durchlaufen bis das Stringende erreicht wurde
        // oder bis die Breite der SubMatrix erreicht wurde. K ist auch die absolute Reihe
        // in der Submatrix zum setzen der Pixel.
        UINT_8 k = 0;
        for(UINT_8 character = 0; character < text_length && k < width; ++character){

            // Zeichenreihen eines Zeichens durchlaufen bis zum Zeichenende.
            for(UINT_8 i = 0; i < char_width && k < width; ++i){

                // Zeilen innerhalb der Zeichenreihe durchlaufen, um die Pixel von Oben nach unten 
                // in der Zeichenreihe i an der absoluten Stelle k zu setzen.
                for(UINT_8 j = 0; j < char_height; ++j){

                    // Wenn Bit im Zeichenbyte an der Stelle j 1 ist, dann setz meinen Pixel auf color.
                    // An der absoluten Stelle (j,k) in der Submatrix.
                    if((1<<j) & font[(UINT_8)text.charAt(character)][i]){
                        mat.pixel(j,k) = color;
                    }
                }
                // Nach jeder Abgeschlossenen Zeichenreihe eine Reihe weitergehen auf der Submatrix.
                ++k;
            }
            // Leerzeile nach dem Buchstaben, indem einfach eine Reihe auf der Submatrix übersprungen wird.
            ++k;
        }
        if(DEBUG) Serial.println("printed " + '"' + text + '"');
        FastLED.show();
    }

    // Überladung von print_string für CHSV Farbe
    void print_String(LEDMatrix& mat, const String text, const CHSV color, const CHSV background = CHSV(0,0,0))
    {
        print_String(mat, text, CRGB(color), CRGB(background));
    }



    // Printing character as ASCII at the matrix
    void print_char(LEDMatrix& mat, const char character, const CRGB color, const CRGB background = CRGB(0,0,0))
    {
        // Sicherstellen, das Matrix größ genug ist
        if(ASSERT_CHECK)    assert(mat.matrix_height() >= char_height);
        if(ASSERT_CHECK)    assert(mat.matrix_width() >= char_width);

        // Bitmap aus font-Array ermitteln
        const UINT_8* const character_bitmap = font[(const UINT_8) character]; // Hier wird nur ein Zeiger gespeichert

        // Für jede Spalte der Matrix
        for(UINT_8 j = 0; j < char_width; ++j)
        {

            // Debug Ausgaben
            if(DEBUG)   Serial.println("Setting up column " + String(j));

            // Für jede Zeile der Spalte
            for(UINT_8 i = 0; i < char_height; ++i)
            {

                // Debug Ausgaben
                if(DEBUG)   Serial.print("Setting up row " + String(i) + "\t");

                // Debug Ausgaben
                if(DEBUG)   Serial.print("Testing: " + String(character_bitmap[j] & (1<<i)) + "\t");

                // Wenn das Bit der font an der Position i gesetzt ist...
                if(character_bitmap[j] & (1<<i))
                {
                    // Debug Ausgaben
                    if(DEBUG)   Serial.println("Character");

                    // ...gehört das Pixel (i,j) zum Buchstaben
                    mat.pixel(i,j) = color;
                }
                else
                {
                    // Debug Ausgaben
                    if(DEBUG)   Serial.println("Background");

                    // ...ansonsten ist es Hintergrund
                    mat.pixel(i,j) = background;
                }
            }
        }

        // Nachdem die Pixel passen gesetzt wurde
        // kann der Buchstabe angezeigt werden
        if(DEBUG) Serial.println("printed " + character);
        FastLED.show();
    }

    // Print-Funktion von SvenJupiter
    // Überladung von print_char für CHSV Farbe
    void print_char(LEDMatrix& mat, const char character, const CHSV color, const CHSV background = CHSV(0,0,0))
    {
        print_char(mat, character, CRGB(color), CRGB(background));

    }

    // Print-Funktion von SvenJupiter
    void print_string(LEDMatrix& mat, const char* const text, const CRGB color, const CRGB background = CRGB(0,0,0), const UINT_8 space_between_characters = 1)
    {
        // Sicherstellen, das Matrix hoch genug für Zeichen ist
        if(ASSERT_CHECK)    assert(mat.matrix_height() >= char_height);

        // Zeilen-Offset für Buchstaben
        UINT_8 colum_offset;

        // Für jeden Buchstaben in text
        for(UINT_8 i = 0; text[i] != '\0'; ++i)
        {
            // Debug Ausgaben
            if(DEBUG)   Serial.println("Trying to print "+ String(i+1) + ". char '" + text[i] + "'");

            // Zeilen-Offset für nächsten Buchstabe ermitteln
            colum_offset = i * (char_width + space_between_characters);

            // Debug Ausgaben
            if(DEBUG)   Serial.println("Space check");

            // Wenn kein weiterer Buchstabe auf die Matrix passt
            if(colum_offset + char_width > mat.matrix_width())
            {
                // Debug Ausgaben
                if(DEBUG)   Serial.println("No more space available");
                if(DEBUG)   Serial.println("Breaking from loop");

                // for-Schleife vorzeitig beenden
                break;
            }
            else
            {               
                // Debug Ausgaben
                if(DEBUG)   Serial.println("Space available");
                if(DEBUG)   Serial.println("Printing char " + text[i]);

                // Eine Submatrix erstellen
                LEDsubMatrix<char_height, char_width> sub_mat(mat, 0, colum_offset);

                // Buchstaben auf der Submatrix ausgeben
                print_char(sub_mat, text[i], color, background);
            }            
        }

        // Debug Ausgaben
        if(DEBUG)   Serial.println("done");
    }


    // Print-Funktion von SvenJupiter
    // Überladung von print_string für CHSV Farbe
    void print_string(LEDMatrix& mat, const char* const text, const CHSV color, const CHSV background = CHSV(0,0,0), const UINT_8 space_between_characters = 1)
    {
        print_string(mat, text, CRGB(color), CRGB(background), space_between_characters);
    }








} // Ende namespace LEDArrangement

#endif
