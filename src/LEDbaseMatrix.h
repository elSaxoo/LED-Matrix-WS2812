#ifndef LEDBASEMATRIX_H
#define LEDBASEMATRIX_H

#include "Arduino.h"
//#define __ASSERT_USE_STDERR
#include <stdint.h>
#include <assert.h>
#include <FastLED.h>

#define DEBUG true
#define CONSTRUCTOR_DEBUG false

namespace LEDArrangement
{

typedef uint8_t UINT_8;
typedef uint16_t UINT_16;

enum class Wiring_Start_Point {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
enum class Strip_Orientation {ALIGN_HORIZONTAL, ZIGZAG_HORIZONTAL, ALIGN_VERTICAL, ZIGZAG_VERTICAL};


// Achtung template-Klasse
// Implementierung aller Methoden findet in der Header-Datei statt
template<UINT_8 width, UINT_8 height>
class LEDbaseMatrix
{
    public:
   
    // Konstruktor
    LEDbaseMatrix(CRGBArray<width * height>& leds, Wiring_Start_Point wiring_start_point, Strip_Orientation strip_orientation);

    // Kein Kopierkonstruktor zulassen
    // -> LEDbaseMatrix-Objekte können nicht per call-by-value an Funktion übergeben werden,
    // nur noch mit call-by-reference (Zeiger oder Referenz)
    LEDbaseMatrix(const LEDbaseMatrix<width, height>&) = delete;

    
    // Zuweisungsoperator
    // Verschiedene baseMatrizen könne einander Zugewiesen werden, solange sie verschiedene FastLED-Referenzen haben
    // und die gleiche Größe haben
    void operator=(const LEDbaseMatrix<width, height>& other_mat);


    // Getter-Methoden für Dimensionen der Matrix
    const UINT_8 matrix_width()  const {return width;}
    const UINT_8 matrix_height() const {return height;}

    // Berechnet die Position des FastLED-Pixels aus den Matrix-Koordinaten
    UINT_16 calc_pixel_position(UINT_8 row, UINT_8 column) const;

    // Gibt eine Referenz auf das FastLED-Pixel zurück 
    // Mit dem weitergearbeitet werden kann
    // z.B this->pixel(0,0) = CRGB(255,0,0) // Pixel (0,0) der Matrix die Farbe Rot zuweisen
    // z.B this->pixel(0,0) = this->pixel(9,29) // Pixel (0,0) auf die gleiche Farbe setzen wie Pixel(9,29)
    CRGB& pixel(UINT_8 row, UINT_8 column);
    const CRGB& const_pixel(UINT_8 row, UINT_8 column) const;

    // Zum Testen ob alle LEDs funktionieren
    // Nachdem die Methoden ausgeführt wurden, muss FastLED.show() aufgerufen werden,
    // damit der LED-Streifen die neue Farb-Konfiguration auch anzeigt.
    void color_all(const CRGB& color);
    void color_all(const CHSV& color);
    void all_off();

    // Zum Testen ob die Matrix richtig arbeitet
    // Steuert die einzelnen Pixel Reihe für Reihe
    // Mit den Farbe Rot, Grün, Blau, Weiß an.
    // Beim Selbst-Test auf Reihenfolge achten, mit der sich die LED anschalten
    void self_test();

    // Zum Testen ob alle LEDs des LED-Streifen funktionieren
    // LEDs werden in der Reihenfolge getestet, wie sie im Streifen verdrahtet sind
    void strip_test();

    private:

    // Die Ecke an der die Datenleitung angeschlossen ist
    const Wiring_Start_Point wiring_start_point;

    // Die Orientierung der einzelen Reihen
    const Strip_Orientation strip_orientation;

    // Referenz auf das FastLED-Objekt
    CRGBArray<width * height>& complete_strip;

}; // End of Class


template<UINT_8 width, UINT_8 height>
LEDbaseMatrix<width, height>::LEDbaseMatrix(CRGBArray<width * height>& leds, Wiring_Start_Point wiring_start_point, Strip_Orientation strip_orientation)
:
    wiring_start_point(wiring_start_point),
    strip_orientation(strip_orientation),
    complete_strip(leds)
{
    if(CONSTRUCTOR_DEBUG)   Serial.println("base const");
    // Parameter überprüfen
    this->complete_strip[width*height - 1] = this->complete_strip[width*height - 1]; // Falls LED-Streifen zu kurz Fehler beim Zugriff auf LED-Array
}

template<UINT_8 width, UINT_8 height>
void LEDbaseMatrix<width, height>::operator=(const LEDbaseMatrix<width, height>& other_mat)
{
    // Zuwweisung auf sich selbst prüfen
    if (this == &other_mat)
        return

    // Gleiche Dimensionen ist eigentlich durch gleiche Template-Parameter sichergestellt
    assert(this->matrix_width() == other_mat.matrix_width());
    assert(this->matrix_height() == other_mat.matrix_height());

    // Sicherstellen, dass die baseMatrizen Referenzen auf verschiedene FastLED-Arrays haben
    assert(&(this->complete_strip) != &(other_mat.complete_strip));

    // Einzelne Pixel Kopieren
    for(UINT_8 i = 0; i < height; ++i)
    {
        for(UINT_8 j = 0; j < width; ++j)
        {
            this->pixel(i,j) = other_mat.const_pixel(i,j);
        }
    }

}

// Berechnet die Position des FastLED-Pixels aus den Matrix-Koordinaten
template<UINT_8 width, UINT_8 height>
UINT_16 LEDbaseMatrix<width, height>::calc_pixel_position(UINT_8 row, UINT_8 column) const
{
    // Sicherstellen, das gültige Parameter übergeben wurden
    assert(row < height);
    assert(column < width);

    // LED-Position, die zu den Matrix-Koordinaten gehört
    // wird in switch-case-Statement berechnet
    UINT_16 led_position = 0;

    // Doppelter switch-case um alle möglichen Hardware-Konfigurationen abzudecken
    switch (this->wiring_start_point)
    {
        case Wiring_Start_Point::TOP_LEFT:
            switch(this->strip_orientation)
            {
                case Strip_Orientation::ALIGN_HORIZONTAL:

                    led_position = row*width + column;
                    break;

                case Strip_Orientation::ZIGZAG_HORIZONTAL:
                    
                    led_position = row*width + (row % 2 == 0 ? column : width-1-column);
                    break;
                
                case Strip_Orientation::ALIGN_VERTICAL:
                    
                    led_position = row + column*height;
                    break;
                
                case Strip_Orientation::ZIGZAG_VERTICAL:
                    
                    led_position = (column % 2 == 0 ? row : height-1-row) + column*height;
                    break;
                
                default:
                    // Ungültige Position übergeben
                    led_position =  width * height;
                    break;            
            }
            break;
        case Wiring_Start_Point::TOP_RIGHT:
            switch(this->strip_orientation)
            {
                case Strip_Orientation::ALIGN_HORIZONTAL:

                    led_position = row*width +  (width-1-column);
                    break;

                case Strip_Orientation::ZIGZAG_HORIZONTAL:

                    led_position = row*width + (row % 2 == 0 ? width-1-column : column);
                    break;

                case Strip_Orientation::ALIGN_VERTICAL:
                    
                    led_position = row + (width-1-column)*height;
                    break;

                case Strip_Orientation::ZIGZAG_VERTICAL:

                    led_position = ((width-1-column) % 2 == 0 ? row : height-1-row) + (width-1-column)*height;
                    break;

                default:
                    // Ungültige Position übergeben
                    led_position =  width * height;
                    break;
            }
            break;
        case Wiring_Start_Point::BOTTOM_LEFT:
            switch(this->strip_orientation)
            {
                case Strip_Orientation::ALIGN_HORIZONTAL:

                    led_position = (height-1-row)*width + column;
                    break;

                case Strip_Orientation::ZIGZAG_HORIZONTAL:

                    led_position = (height-1-row)*width + ((height-1-row) % 2 == 0 ? column : width-1-column);
                    break;

                case Strip_Orientation::ALIGN_VERTICAL:

                    led_position = (height-1-row) + column*height;
                    break;

                case Strip_Orientation::ZIGZAG_VERTICAL:

                    led_position = (column % 2 == 0 ? (height-1-row) : row) + column*height;
                    break;

                default:
                    // Ungültige Position übergeben
                    led_position =  width * height;
                    break;
            }
            break;
        case Wiring_Start_Point::BOTTOM_RIGHT:
            switch(this->strip_orientation)
            {
                case Strip_Orientation::ALIGN_HORIZONTAL:

                    led_position = (height-1-row)*width + (width-1-column);
                    break;

                case Strip_Orientation::ZIGZAG_HORIZONTAL:

                    led_position = (height-1-row)*width + ((height-1-row) % 2 == 0 ? (width-1-column) : column);
                    break;

                case Strip_Orientation::ALIGN_VERTICAL:

                    led_position = (height-1-row) + (width-1-column)*height;
                    break;

                case Strip_Orientation::ZIGZAG_VERTICAL:

                    led_position = ((width-1-column) % 2 == 0 ? (height-1-row) : row)+ (width-1-column)*height;
                    break;

                default:
                    // Ungültige Position übergeben
                    led_position =  width * height;
                    break;
            }
            break;
        default:
            // Ungültige Position übergeben
            led_position =  width * height;
            break;
    }

    // Berechnete Position auf Gültigkeit prüfen
    assert(led_position < width*height);

    // FastLED-Pixel-Referenz zurückgeben
    return led_position;
}

// Gibt eine Referenz auf das FastLED-Pixel zurück 
// Mit dem weitergearbeitet werden kann
// z.B this->pixel(0,0) = CRGB(255,0,0) // Pixel (0,0) der Matrix die Farbe Rot zuweisen
// z.B this->pixel(0,0) = this->pixel(9,29) // Pixel (0,0) auf die gleiche Farbe setzen wie Pixel(9,29)
template<UINT_8 width, UINT_8 height>
CRGB& LEDbaseMatrix<width, height>::pixel(UINT_8 row, UINT_8 column)
{
    return this->complete_strip[this->calc_pixel_position(row, column)];
}

// Gibt eine Referenz auf ein konstantes FastLED-Pixel zurück 
// Mit dem weitergearbeitet werden kann
// z.B this->pixel(0,0) = CRGB(255,0,0) // Pixel (0,0) der Matrix die Farbe Rot zuweisen
// z.B this->pixel(0,0) = this->const_pixel(9,29) // Pixel (0,0) auf die gleiche Farbe setzen wie Pixel(9,29)
template<UINT_8 width, UINT_8 height>
const CRGB& LEDbaseMatrix<width, height>::const_pixel(UINT_8 row, UINT_8 column) const
{
    // Referenz wird beim Rückgeben in konstante Referent gecastet
    return this->complete_strip[this->calc_pixel_position(row, column)];
}


template<UINT_8 width, UINT_8 height>
void LEDbaseMatrix<width, height>::color_all(const CRGB& color)
{
    for(UINT_16 i=0; i < width*height; ++i)
    {
        this->complete_strip[i] = color;
    }
}


template<UINT_8 width, UINT_8 height>
void LEDbaseMatrix<width, height>::color_all(const CHSV& color)
{
    // Farbe von HSV nach RGB konvertieren
    // und Methode erneut aufrufen
    this->color_all(CRGB(color));
}


template<UINT_8 width, UINT_8 height>
void LEDbaseMatrix<width, height>::all_off()
{
    // Alle LED auf schwarz setzen
    this->color_all(CRGB(0,0,0));
}


template<UINT_8 width, UINT_8 height>
void LEDbaseMatrix<width, height>::self_test()
{
    const uint32_t delay_time_ms = 15000/300;
    // erst alle ausschalten
    this->all_off();


    // Nacheinander Rot Färben
    const CRGB red = CRGB(255,0,0);
    for(UINT_8 i=0; i < height; ++i)
    {
        for(UINT_8 j = 0; j < width; ++j)
        {
            this->pixel(i,j) = red;
            FastLED.show();
            if(DEBUG)   Serial.print("baseLED "); if(DEBUG)   Serial.print(i); if(DEBUG)   Serial.print('x'); if(DEBUG)   Serial.print(j); if(DEBUG)   Serial.println(" red");
            delay(delay_time_ms);
        }
    }

    // Nacheinander Grün Färben
    const CRGB green = CRGB(0,255,0);
    for(UINT_8 i=0; i < height; ++i)
    {
        for(UINT_8 j = 0; j < width; ++j)
        {
            this->pixel(i,j) = green;
            FastLED.show();
            if(DEBUG)   Serial.print("baseLED "); if(DEBUG)   Serial.print(i); if(DEBUG)   Serial.print('x'); if(DEBUG)   Serial.print(j); if(DEBUG)   Serial.println(" green");
            delay(delay_time_ms);
        }
    }

    // Nacheinander Blau Färben
    const CRGB blue = CRGB(0,0,255);
    for(UINT_8 i=0; i < height; ++i)
    {
        for(UINT_8 j = 0; j < width; ++j)
        {
            this->pixel(i,j) = blue;
            FastLED.show();
            if(DEBUG)   Serial.print("baseLED "); if(DEBUG)   Serial.print(i); if(DEBUG)   Serial.print('x'); if(DEBUG)   Serial.print(j); if(DEBUG)   Serial.println(" blue");
            delay(delay_time_ms);
        }
    }

    // Nacheinander Weiß Färben
    const CRGB white = CRGB(255,255,255);
    for(UINT_8 i=0; i < height; ++i)
    {
        for(UINT_8 j = 0; j < width; ++j)
        {
            this->pixel(i,j) = white;
            FastLED.show();
            if(DEBUG)   Serial.print("baseLED "); if(DEBUG)   Serial.print(i); if(DEBUG)   Serial.print('x'); if(DEBUG)   Serial.print(j); if(DEBUG)   Serial.println(" white");
            delay(delay_time_ms);
        }
    }

    delay(5000);
    this->all_off();
    FastLED.show();

}


template<UINT_8 width, UINT_8 height>
void LEDbaseMatrix<width, height>::strip_test()
{

    const uint32_t delay_time_ms = 15000/300;
    // erst alle ausschalten
    this->all_off();

    // Rot
    const CRGB red = CRGB(255,0,0);
    for(UINT_16 i = 0; i < width*height; ++i)
    {
        this->complete_strip[i] = red;
        FastLED.show();
        if(DEBUG)   Serial.print("LED "); if(DEBUG)   Serial.print(i); if(DEBUG)   Serial.println(" red");
        delay(delay_time_ms);
    }

    // Grün
    const CRGB green = CRGB(0,255,0);
    for(UINT_16 i = 0; i < width*height; ++i)
    {
        this->complete_strip[i] = green;
        FastLED.show();
        if(DEBUG)   Serial.print("LED "); if(DEBUG)   Serial.print(i); if(DEBUG)   Serial.println(" green");
        delay(delay_time_ms);
    }

    // Blau
    const CRGB blue = CRGB(0,0,255);
    for(UINT_16 i = 0; i < width*height; ++i)
    {
        this->complete_strip[i] = blue;
        FastLED.show();
        if(DEBUG)   Serial.print("LED "); if(DEBUG)   Serial.print(i); if(DEBUG)   Serial.println(" blue");
        delay(delay_time_ms);
    }

    // Weiß
    const CRGB white = CRGB(255,255,255);
    for(UINT_16 i = 0; i < width*height; ++i)
    {
        this->complete_strip[i] = white;
        FastLED.show();
        if(DEBUG)   Serial.print("LED "); if(DEBUG)   Serial.print(i); if(DEBUG)   Serial.println(" white");
        delay(delay_time_ms);
    }

    delay(5000);
    this->all_off();
    FastLED.show();

}




} // Ende namespace LEDArrangement

#endif