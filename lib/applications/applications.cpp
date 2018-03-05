#include "applications.h"


#include <debugging.h>
#define DEBUGGING false
#define CONSTRUCTOR_DEBUGGING false
#define ASSERT_CHECK true





namespace LEDArrangement
{



    // Print-Funktion von elSaxoo
    void print_String(LEDMatrix& mat, const String text, const CRGB color, const CRGB background)
    {
        UINT_8 width = mat.matrix_width();
        UINT_8 height = mat.matrix_height();
        int text_length = text.length();

        // Testen ob Submatrix hoch genug ist für die Zeichen
        if(DEBUGGING)    DEBUG(String("Testen ob Submatrix hoch genug ist für die Zeichen") + (char_height <= height ? "true" : "false"));
        if(ASSERT_CHECK)    TEST(char_height <= height);


        // Buchstaben durchlaufen bis das Stringende erreicht wurde
        // oder bis die Breite der SubMatrix erreicht wurde. K ist auch die absolute Reihe
        // in der Submatrix zum setzen der Pixel.
        UINT_8 k = 0;
        for(UINT_8 character = 0; character < text_length && k < width; ++character){
            // Zeichenreihen eines Zeichens durchlaufen bis zum Zeichenende.
            for(UINT_8 i = 0; i < char_width && k < width; ++i){

                // Zeilen innerhalb der Zeichenreihe durchlaufen, um die Pixel von Oben nach unten 
                // in der Zeichenreihe i an der absoluten Stelle k zu setzen.

                const UINT_8 column_bitmap = pgm_read_byte(&font[(UINT_8)(text.charAt(character))][i]);

                for(UINT_8 j = 0; j < char_height; ++j){

                    // Wenn Bit im Zeichenbyte an der Stelle j 1 ist, dann setz meinen Pixel auf color.
                    // An der absoluten Stelle (j,k) in der Submatrix.
                    if((1<<j) & column_bitmap){
                        mat.pixel(j,k) = color;
                    }
                    else{
                        mat.pixel(j,k) = background;                      
                    }
                }
                // Nach jeder Abgeschlossenen Zeichenreihe eine Reihe weitergehen auf der Submatrix.
                ++k;
            }
            // Leerzeile nach dem Buchstaben, indem einfach eine Reihe auf der Submatrix übersprungen wird.
            ++k;
        }
        if(DEBUGGING)    DEBUG("printed " + '"' + text + '"');
        FastLED.show();
    }

    // Print-Funktion von elSaxoo
    // Überladung von print_string für CHSV Farbe

    void print_String(LEDMatrix& mat, const String text, const CHSV color, const CHSV background)
    {
        print_String(mat, text, CRGB(color), CRGB(background));
    }



    // Print-Funktion von SvenJupiter
    void print_char(LEDMatrix& mat, const char character, const CRGB color, const CRGB background)
    {
        // Sicherstellen, das Matrix größ genug ist
        if(DEBUGGING)    DEBUG(String("Testing Matrix height") + (mat.matrix_height() >= char_height ? "true" : "false"));
        if(DEBUGGING)    DEBUG(String("Testing Matrix width") + (mat.matrix_width() >= char_width ? "true" : "false"));
        if(ASSERT_CHECK)    TEST(mat.matrix_height() >= char_height);
        if(ASSERT_CHECK)    TEST(mat.matrix_width() >= char_width);

        // Bitmap aus font-Array ermitteln
        const UINT_8* const character_bitmap = font[(const UINT_8) character]; // Hier wird nur ein Zeiger gespeichert

        // Für jede Spalte der Matrix
        for(UINT_8 j = 0; j < char_width; ++j)
        {

            // Debug Ausgaben
            if(DEBUGGING)    DEBUG("Setting up column " + String(j));

            // Für jede Zeile der Spalte
            for(UINT_8 i = 0; i < char_height; ++i)
            {

                // Debug Ausgaben
               if(DEBUGGING)     DEBUG("Setting up row " + String(i) + "\t" + "Testing: " + String(character_bitmap[j] & (1<<i)) + "\t" + (character_bitmap[j] & (1<<i) ? "Character" : "Backgroung"));

                // Wenn das Bit der font an der Position i gesetzt ist...
                if(character_bitmap[j] & (1<<i))
                {    
                    // ...gehört das Pixel (i,j) zum Buchstaben
                    mat.pixel(i,j) = color;
                }
                else
                {
                    // ...ansonste ist es Hintergrund
                    mat.pixel(i,j) = background;
                }
            }
        }

        // Nachdem die Pixel passen gesetzt wurde
        // kann der Buchstabe angezeigt werden
        FastLED.show();
        if(DEBUGGING)    DEBUG("printed " + character);
    }

    // Print-Funktion von SvenJupiter
    // Überladung von print_char für CHSV Farbe
    void print_char(LEDMatrix& mat, const char character, const CHSV color, const CHSV background)
    {
        print_char(mat, character, CRGB(color), CRGB(background));

    }

    // Print-Funktion von SvenJupiter
    void print_string(LEDMatrix& mat, const char* const text, const CRGB color, const CRGB background, const UINT_8 space_between_characters)
    {
        // Sicherstellen, das Matrix hoch genug für Zeichen ist
        if(DEBUGGING)    DEBUG(String("Testing Matrix height") + (mat.matrix_height() >= char_height ? "true" : "false"));
        if(ASSERT_CHECK)    TEST(mat.matrix_height() >= char_height);

        // Zeilen-Offset für Buchstaben
        UINT_8 colum_offset;

        // Für jeden Buchstaben in text
        for(UINT_8 i = 0; text[i] != '\0'; ++i)
        {
            // Debug Ausgaben
            if(DEBUGGING)    DEBUG("Trying to print "+ String(i+1) + ". char '" + text[i] + "'");

            // Zeilen-Offset für nächsten Buchstabe ermitteln
            colum_offset = i * (char_width + space_between_characters);

            // Debug Ausgaben
            if(DEBUGGING)    DEBUG("Space check");

            // Wenn kein weiterer Buchstabe auf die Matrix passt
            if(((UINT_8)(colum_offset + char_width)) > mat.matrix_width())
            {
                // Debug Ausgaben
                if(DEBUGGING)    DEBUG("No more space available");
                if(DEBUGGING)    DEBUG("Breaking from loop");

                // for-Schleife vorzeitig beenden
                break;
            }
            else
            {               
                // Debug Ausgaben
                if(DEBUGGING)    DEBUG("Space available");
                if(DEBUGGING)    DEBUG("Printing char " + text[i]);

                // Eine Submatrix erstellen
                LEDMatrix sub_mat(mat, char_height, char_width, 0, colum_offset);

                // Buchstaben auf der Submatrix ausgeben
                print_char(sub_mat, text[i], color, background);
            }            
        }

        // Debug Ausgaben
        if(DEBUGGING)    DEBUG("done");
    }


    // Print-Funktion von SvenJupiter
    // Überladung von print_string für CHSV Farbe
    void print_string(LEDMatrix& mat, const char* const text, const CHSV color, const CHSV background, const UINT_8 space_between_characters)
    {
        print_string(mat, text, CRGB(color), CRGB(background), space_between_characters);
    }


    
    // Die Matrix über die serielle Schnittstelle mit Daten versorgen
    void serial_matrix_updater(HardwareSerial& UART, LEDMatrix& mat)
    {

        // Signalisieren, dass Arduino bereit ist
        UART.write(0x05); // ENQ

        while(true)
        {
            // Für jedes Pixel in der Matrix
            for(UINT_16 i = 0; i < mat.number_of_leds(); ++i)
            {
                // Rot einlesen
                while(!UART.available());
                mat[i].r = UART.read();

                // Grün einlesen
                while(!UART.available()); 
                mat[i].g = UART.read();

                // Blau einlesen
                while(!UART.available()); 
                mat[i].b = UART.read();
            }

            // Bild anzeigen
            FastLED.show();

            // Signalisieren, dass Arduino komplettes Bild empfangen hat
            UART.write(0x06); // ACK
        }
    }







} // Ende namespace LEDArrangement