#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <Arduino.h>
//#define __ASSERT_USE_STDERR
#include <stdint.h>
#include <FastLED.h>



#define STRIP_LENGTH 300



namespace LEDArrangement
{

typedef uint8_t UINT_8;
typedef uint16_t UINT_16;

typedef int8_t INT_8;
typedef int16_t INT_16;

enum class Wiring_Start_Point {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
enum class Strip_Orientation {ALIGN_HORIZONTAL, ZIGZAG_HORIZONTAL, ALIGN_VERTICAL, ZIGZAG_VERTICAL};
enum class MatrixType {BASE_MATRIX, SUB_MATRIX, ROW_VECTOR, COLUMN_VECTOR};


// Virtuelle Basis-Klasse füe alle LED-Matrizen
// Definiert einheitlich das Interface über das mit den Matrizen interagiert werden kann
class LEDMatrix
{

public:

    // Konstruktor
    LEDMatrix(CRGBArray<STRIP_LENGTH>& leds, const UINT_16 Height, const UINT_16 Width, const Wiring_Start_Point Wiring_start_point, const Strip_Orientation Strip_orientation);

    // Sub-Matrix Konstruktor
    LEDMatrix(LEDMatrix& Base_mat, const UINT_16 Height, const UINT_16 Width, const UINT_16 Row_offset, const UINT_16 Column_offset);

    // Vector Konstruktor
    LEDMatrix(LEDMatrix& Base_mat, const MatrixType Type, const UINT_16 Offset);


    // Kopierkonstuktor
    LEDMatrix(LEDMatrix& other_mat);

    // Zuweisungsoperator
    void operator=(LEDMatrix& other_mat);

    // Getter-Methoden für Dimensionen der Matrix
    const UINT_16 matrix_width()  const {return sub_width;}
    const UINT_16 matrix_height() const {return sub_height;}
    const UINT_16 number_of_leds() const {return sub_height * sub_width;}

    // Getter-Methoden für Offset
    const UINT_16 matrix_row_offset()    const {return row_offset;}
    const UINT_16 matrix_column_offset() const {return column_offset;}

    // Getter-Methoden für Hardware-Eigenschaften
    CRGBArray<STRIP_LENGTH>& matrix_complete_strip() const {return complete_strip;}
    const Wiring_Start_Point matrix_wiring_start_point() const {return wiring_start_point;}
    const Strip_Orientation matrix_strip_orientation() const {return strip_orientation;}

    // Getter-Methoden
    const MatrixType matrix_type() const {return mat_type;}

    // Berechnet die Position des FastLED-Pixels aus den Matrix-Koordinaten
    UINT_16 calc_pixel_position(const INT_16 row, const INT_16 column) const;

    // Gibt eine Referenz auf das FastLED-Pixel zurück 
    // Mit dem weitergearbeitet werden kann
    CRGB& pixel(const INT_16 row, const INT_16 column);
    const CRGB& const_pixel(const INT_16 row, const INT_16 column) const;

    // Einzelne Zeile/ Spalte der Matrix zurückgeben
    // LEDMatrix get_row(const UINT_16 row);
    // LEDMatrix get_column(const UINT_16 column);

    // für []-Operator
    CRGB& pixel(const INT_16 index);
    const CRGB& const_pixel(const INT_16 index) const;

    // []-Operator
    CRGB& operator[](const INT_16 index) {return this->pixel(index);}


    // Alle LEDs färben
    void color_all(const CRGB& color);
    void color_all(const CHSV& color);
    void all_off();

    // Zum Testen ob die Matrix richtig arbeitet
    void self_test();

private:

    // Könnte nützlich werden
    const MatrixType mat_type;

    // Referenz auf das FastLED-Objekt
    CRGBArray<STRIP_LENGTH>& complete_strip;


    // Die Dimensionen der Matrix
    const UINT_16 base_height;
    const UINT_16 base_width;

    const UINT_16 sub_height;
    const UINT_16 sub_width;

    const UINT_16 row_offset;
    const UINT_16 column_offset;

    // Die Ecke an der die Datenleitung angeschlossen ist
    const Wiring_Start_Point wiring_start_point;

    // Die Orientierung der einzelen Reihen
    const Strip_Orientation strip_orientation;




};






} // Ende Namespace


#endif // LEDMATRIX_H