#ifndef LEDMATRIX_H
#define LEDMATRIX_H


#include <Arduino.h>
//#define __ASSERT_USE_STDERR
#include <stdint.h>
#include <FastLED.h>





namespace LEDArrangement
{

typedef uint8_t UINT_8;
typedef uint16_t UINT_16;

enum class Wiring_Start_Point {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
enum class Strip_Orientation {ALIGN_HORIZONTAL, ZIGZAG_HORIZONTAL, ALIGN_VERTICAL, ZIGZAG_VERTICAL};


// Virtuelle Basis-Klasse füe alle LED-Matrizen
// Definiert einheitlich das Interface über das mit den Matrizen interagiert werden kann
class LEDMatrix
{
    public:

    // Getter-Methoden für Dimensionen der Matrix
    virtual const UINT_8 matrix_width()  const =0;
    virtual const UINT_8 matrix_height() const =0;

    // Berechnet die Position des FastLED-Pixels aus den Matrix-Koordinaten
    virtual UINT_16 calc_pixel_position(const UINT_8 row, const UINT_8 column) const =0;

    // Gibt eine Referenz auf das FastLED-Pixel zurück 
    // Mit dem weitergearbeitet werden kann
    virtual CRGB& pixel(const UINT_8 row, const UINT_8 column) =0;
    virtual const CRGB& const_pixel(const UINT_8 row, const UINT_8 column) const =0;

    // Alle LEDs färben
    virtual void color_all(const CRGB& color) =0;
    virtual void color_all(const CHSV& color) =0;
    virtual void all_off() =0;

    // Zum Testen ob die Matrix richtig arbeitet
    virtual void self_test() =0;



};






} // Ende Namespace


// Unterklassen von LEDMatrix
#include <LEDbaseMatrix.h>
#include <LEDsubMatrix.h>

#endif // LEDMATRIX_H