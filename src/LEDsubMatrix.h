#ifndef LEDSUBMATRIX_H
#define LEDSUBMATRIX_H

#include "LEDbaseMatrix.h"

#include "Arduino.h"
//#define __ASSERT_USE_STDERR
#include <stdint.h>
#include <assert.h>
#include <FastLED.h>

#define DEBUG true
#define CONSTRUCTOR_DEBUG false

namespace LEDArrangement
{

// Auch mit LEDMatrix-Namen auf LEDsubMatrix-Klasse zugrifen
#define LEDMatrix LEDsubMatrix

// Achtung template-Klasse
// Implementierung aller Methoden findet in der Header-Datei statt
template<typename LED_base_Matrix, UINT_8 width, UINT_8 height>
class LEDsubMatrix
{
    public:
    // Konstruktor
    LEDsubMatrix(LED_base_Matrix& mat, UINT_8 Row_Offset, UINT_8 Column_Offset);


    // Kein Kopierkonstruktor zulassen
    // -> LEDsubMatrix-Objekte könne nicht per call-by-value an Funktion übergeben werden, 
    // nur noch mit call-by-reference (Zeiger oder Referenz)
    template<typename OTHER_BASE_MAT>
    LEDsubMatrix(const LEDsubMatrix<OTHER_BASE_MAT, width, height>&) = delete;
    
    // Zuweisungsoperator
    // Verschiedene SubMatrizen könne einander Zugewiesen werden, solange sie sich nicht überschneiden
    // und die gleiche Größe haben
    template<typename OTHER_BASE_MAT, typename MAT>
    void operator=(const LEDsubMatrix<OTHER_BASE_MAT, width, height>& other_mat);  


    // Getter-Methoden für Dimensionen der Matrix
    const UINT_8 matrix_width()  const {return width;}
    const UINT_8 matrix_height() const {return height;}

    // Getter-Methoden für Offset
    const UINT_8 matrix_row_offset()    const {return row_offset;}
    const UINT_8 matrix_column_offset() const {return column_offset;}

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

    private:

    const UINT_8 row_offset;
    const UINT_8 column_offset;

    LED_base_Matrix& base_matrix;

};




template<typename LED_base_Matrix, UINT_8 width, UINT_8 height>
LEDsubMatrix<LED_base_Matrix, width, height>::LEDsubMatrix(LED_base_Matrix& mat, UINT_8 Row_Offset, UINT_8 Column_Offset)
:
    row_offset(Row_Offset),
    column_offset(Column_Offset),
    base_matrix(mat)
{
    if(CONSTRUCTOR_DEBUG)   Serial.println("sub const");
    if(CONSTRUCTOR_DEBUG)   Serial.print("Cc "); 
    if(CONSTRUCTOR_DEBUG)   Serial.println(this->column_offset + width <= base_matrix.matrix_width());
    if(CONSTRUCTOR_DEBUG)   Serial.print("Rc "); 
    if(CONSTRUCTOR_DEBUG)   Serial.println(this->row_offset + height <= base_matrix.matrix_height());
    if(CONSTRUCTOR_DEBUG) while(Serial.available());
    
    // Parameter überprüfen
    assert(this->column_offset + width <= base_matrix.matrix_width());
    assert(this->row_offset + height <= base_matrix.matrix_height());

}


template<typename LED_base_Matrix, UINT_8 width, UINT_8 height>
template<typename OTHER_BASE_MAT, typename MAT>
void LEDsubMatrix<LED_base_Matrix, width, height>::operator=(const LEDsubMatrix<OTHER_BASE_MAT, width, height>& other_mat)
{

    // Zuwweisung auf sich selbst prüfen
    if (this == &other_mat)
        return

    // Gleiche Dimensionen ist eigentlich durch gleiche Template-Parameter sichergestellt
    assert(this->matrix_width() == other_mat.matrix_width());
    assert(this->matrix_height() == other_mat.matrix_height());

    // Die Matrix mit dem jeweils kleineren und Offset bestimmen
    LEDsubMatrix<MAT, width, height>& min_row_mat = (this->row_offset < other_mat.row_offset ? *this : other_mat);
    LEDsubMatrix<MAT, width, height>& min_column_mat = (this->column_offset < other_mat.column_offset ? *this : other_mat);
    
    // Die Matrix mit dem jeweils größeren Offset bestimmen
    LEDsubMatrix<MAT, width, height>& max_row_mat = (this->row_offset >= other_mat.row_offset ? *this : other_mat);
    LEDsubMatrix<MAT, width, height>& max_column_mat = (this->column_offset >= other_mat.column_offset ? *this : other_mat);

    // Sicherstellen, das die Offsets nicht gleich sind
    assert(this->row_offset != other_mat.row_offset && this->column_offset != other_mat.column_offset);

    // Überlappung prüfen
    bool overlapping;
    // Wenn die eine Matrix komplett links von der anderen liegt
    if(min_row_mat.row_offset + width <= max_row_mat.row_offset)
    {
        overlapping = false;
    }
    else
    {
        // Wenn die eine Matrix komplett über der anderen liegt
        if(min_column_mat.column_offset + height <= max_column_mat.column_offset)
        {
            overlapping = false;
        }
        else
        {
            overlapping = true;
        }
    }
    assert(overlapping == false);

    // Einzelne Pixel kopieren
    for(UINT_8 i = 0; i < height; ++i)
    {
        for(UINT_8 j = 0; j < width; ++j)
        {
            this->pixel(i,j) = other_mat.const_pixel(i,j);
        }
    }

}


template<typename LED_base_Matrix, UINT_8 width, UINT_8 height>
UINT_16 LEDsubMatrix<LED_base_Matrix, width, height>::calc_pixel_position(UINT_8 row, UINT_8 column) const
{
    // Sicherstellen, das gültige Parameter übergeben wurden
    assert(row < height);
    assert(column < width);

    return this->base_matrix.calc_pixel_position(row + this->row_offset, column + this-column_offset);
}


template<typename LED_base_Matrix, UINT_8 width, UINT_8 height>
CRGB& LEDsubMatrix<LED_base_Matrix, width, height>::pixel(UINT_8 row, UINT_8 column)
{
    // Sicherstellen, das gültige Parameter übergeben wurden
    assert(row < height);
    assert(column < width);

    return this->base_matrix.pixel(row + this->row_offset, column + this->column_offset);
}


template<typename LED_base_Matrix, UINT_8 width, UINT_8 height>
const CRGB& LEDsubMatrix<LED_base_Matrix, width, height>::const_pixel(UINT_8 row, UINT_8 column) const
{
    // Sicherstellen, das gültige Parameter übergeben wurden
    assert(row < height);
    assert(column < width);

    return this->base_matrix.const_pixel(row + this->row_offset, column + this->column_offset);
}


template<typename LED_base_Matrix, UINT_8 width, UINT_8 height>
void LEDsubMatrix<LED_base_Matrix, width, height>::color_all(const CRGB& color)
{
    for(UINT_8 i = 0; i < height; i++)
    {
        for(UINT_8 j = 0; j < width; j++)
        {
            this->pixel(i,j) = color;
        }
    }
}


template<typename LED_base_Matrix, UINT_8 width, UINT_8 height>
void LEDsubMatrix<LED_base_Matrix, width, height>::color_all(const CHSV& color)
{
    // Farbe von HSV nach RGB konvertieren
    // und Methode erneut aufrufen
    this->color_all(CRGB(color));
}


template<typename LED_base_Matrix, UINT_8 width, UINT_8 height>
void LEDsubMatrix<LED_base_Matrix, width, height>::all_off()
{
    this->color_all(CRGB(0,0,0));
}


template<typename LED_base_Matrix, UINT_8 width, UINT_8 height>
void LEDsubMatrix<LED_base_Matrix, width, height>::self_test()
{
    const uint32_t delay_time_ms = 15000/300 * ((width*height)/(this->base_matrix.matrix_width()*this->base_matrix.matrix_height()));
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
            if(DEBUG)   Serial.print("subLED "); if(DEBUG)   Serial.print(i); if(DEBUG)   Serial.print('x'); if(DEBUG)   Serial.print(j); if(DEBUG)   Serial.println(" red");
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
            if(DEBUG)   Serial.print("subLED "); if(DEBUG)   Serial.print(i); if(DEBUG)   Serial.print('x'); if(DEBUG)   Serial.print(j); if(DEBUG)   Serial.println(" green");
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
            if(DEBUG)   Serial.print("subLED "); if(DEBUG)   Serial.print(i); if(DEBUG)   Serial.print('x'); if(DEBUG)   Serial.print(j); if(DEBUG)   Serial.println(" blue");
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
            if(DEBUG)   Serial.print("subLED "); if(DEBUG)   Serial.print(i); if(DEBUG)   Serial.print('x'); if(DEBUG)   Serial.print(j); if(DEBUG)   Serial.println(" white");
            delay(delay_time_ms);
        }
    }

    delay(2000);
    this->all_off();
    FastLED.show();

}


} // Ende namespace LEDArrangement

#endif