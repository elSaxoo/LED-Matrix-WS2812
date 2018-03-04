#include "LEDMatrix.h"
#include <debugging.h>

#define DEBUGGING false
#define CONSTRUCTOR_DEBUGGING false
#define ASSERT_CHECK true


namespace LEDArrangement
{


// Konstruktor
LEDMatrix::LEDMatrix(CRGBArray<STRIP_LENGTH>& leds, const UINT_16 Height, const UINT_16 Width, const Wiring_Start_Point Wiring_start_point, const Strip_Orientation Strip_orientation)
:
    mat_type(MatrixType::BASE_MATRIX),
    complete_strip(leds),
    base_height(Height),
    base_width(Width),
    sub_height(Height),
    sub_width(Width),
    row_offset(0),
    column_offset(0),
    wiring_start_point(Wiring_start_point),
    strip_orientation(Strip_orientation)
{
    if(CONSTRUCTOR_DEBUGGING)   DEBUG(String("baseMatrix ") + String(base_height) + "x" + String(base_width));

    // Parametercheck
    if(ASSERT_CHECK)
    {
        ASSERT(base_height > 0);
        ASSERT(base_width > 0);
        ASSERT(sub_height > 0);
        ASSERT(sub_width > 0);
    }
}

// Sub-Matrix Konstruktor
LEDMatrix::LEDMatrix(LEDMatrix& Base_mat, const UINT_16 Height, const UINT_16 Width, const UINT_16 Row_offset, const UINT_16 Column_offset)
:
    mat_type(MatrixType::SUB_MATRIX),
    complete_strip(Base_mat.complete_strip),
    base_height(Base_mat.base_height),
    base_width(Base_mat.base_width),
    sub_height(Height),
    sub_width(Width),
    row_offset(Base_mat.row_offset + Row_offset),
    column_offset(Base_mat.column_offset + Column_offset),
    wiring_start_point(Base_mat.wiring_start_point),
    strip_orientation(Base_mat.strip_orientation)
{
    if(CONSTRUCTOR_DEBUGGING)   DEBUG(String("subMatrix ") + String(sub_height) + "x" + String(sub_width));

    // Parametercheck
    if(ASSERT_CHECK)
    {
        ASSERT(base_height > 0);
        ASSERT(base_width > 0);
        ASSERT(sub_height > 0);
        ASSERT(sub_width > 0);
    }

    // Dimensionscheck
    if(ASSERT_CHECK)    ASSERT(row_offset + sub_height <= base_height);
    if(ASSERT_CHECK)    ASSERT(column_offset + sub_width <= base_width);

}

// Vector Konstruktor
LEDMatrix::LEDMatrix(LEDMatrix& Base_mat, const MatrixType Type, const UINT_16 Offset)
:
    mat_type(Type == MatrixType::ROW_VECTOR ? MatrixType::ROW_VECTOR : MatrixType::COLUMN_VECTOR),
    complete_strip(Base_mat.complete_strip),
    base_height(Base_mat.base_height),
    base_width(Base_mat.base_width),
    sub_height(Type == MatrixType::ROW_VECTOR ? 1 : Base_mat.sub_height),
    sub_width(Type == MatrixType::COLUMN_VECTOR ? 1 : Base_mat.sub_width),
    row_offset(Type == MatrixType::ROW_VECTOR ? Offset : Base_mat.row_offset),
    column_offset(Type == MatrixType::COLUMN_VECTOR ? Offset : Base_mat.column_offset),
    wiring_start_point(Base_mat.wiring_start_point),
    strip_orientation(Base_mat.strip_orientation)
{
    if(CONSTRUCTOR_DEBUGGING)   DEBUG(String("vectorMatrix ") + String(sub_height) + "x" + String(sub_width));

    // Sicherstellen, das richtiger Typ an Konstruktor übergeben wurde
    if(ASSERT_CHECK)    ASSERT(Type == MatrixType::ROW_VECTOR || Type == MatrixType::COLUMN_VECTOR);

    // Parametercheck
    if(ASSERT_CHECK)
    {
        ASSERT(base_height > 0);
        ASSERT(base_width > 0);
        ASSERT(sub_height > 0);
        ASSERT(sub_width > 0);
    }

}

// Kopierkonstuktor
LEDMatrix::LEDMatrix(LEDMatrix& other_mat)
:
    mat_type(other_mat.mat_type),
    complete_strip(other_mat.complete_strip),
    base_height(other_mat.base_height),
    base_width(other_mat.base_width),
    sub_height(other_mat.sub_height),
    sub_width(other_mat.sub_width),
    row_offset(other_mat.row_offset),
    column_offset(other_mat.column_offset),
    wiring_start_point(other_mat.wiring_start_point),
    strip_orientation(other_mat.strip_orientation)
{
    if(CONSTRUCTOR_DEBUGGING)   DEBUG(String(" copy Matrix ") + String(sub_height) + "x" + String(sub_width));

    // Referenz-Check
    if(CONSTRUCTOR_DEBUGGING)   DEBUG(String(" Referenz-Check: ") + (&this->complete_strip == &other_mat.complete_strip ? "true" : "false"));
    if(ASSERT_CHECK)    ASSERT(&this->complete_strip == &other_mat.complete_strip);
}

// Zuweisungsoperator
void LEDMatrix::operator=(LEDMatrix& other_mat)
{

    if(DEBUGGING)   DEBUG(String("Dimesionscheck height ") + (this->matrix_height() == other_mat.matrix_height() ? "true" : "false" ));
    if(DEBUGGING)   DEBUG(String("Dimesionscheck width ") + (this->matrix_width() == other_mat.matrix_width() ? "true" : "false" ));

    // Dimesionscheck
    if(ASSERT_CHECK)    TEST(this->matrix_height() == other_mat.matrix_height());
    if(ASSERT_CHECK)    TEST(this->matrix_width() == other_mat.matrix_width());

    
    // Pixelfarben kopieren
    for(UINT_16 i = 0; i < this->matrix_height(); ++i)
        for(UINT_16 j = 0; j < this->matrix_width(); ++j)
            this->pixel(i, j) = other_mat.pixel(i, j);

}


// Berechnet die Position des FastLED-Pixels aus den Matrix-Koordinaten 
UINT_16 LEDMatrix::calc_pixel_position(const INT_16 row, const INT_16 column) const
{

    // Von Sub-Matrix-Koordinaten in Base-Matrix-Koordinaten umrechnen
    UINT_16 row_index = this->row_offset + (row % this->sub_height);
    UINT_16 column_index = this->column_offset + (column % this->sub_width);

    // Sicherstellen, das gültige Parameter übergeben wurden
    if(DEBUGGING)    DEBUG(String("Matrix calc_pixel_position row check") + (row_index < (this->base_height) ? "true" : "false"));
    if(DEBUGGING)    DEBUG(String("Matrix calc_pixel_position column check") + (column_index < (this->base_width) ? "true" : "false"));

    if(ASSERT_CHECK)    TEST(row_index < (this->base_height));
    if(ASSERT_CHECK)    TEST(column_index < (this->base_width));

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

                    led_position = row_index*(this->base_width) + column_index;
                    break;

                case Strip_Orientation::ZIGZAG_HORIZONTAL:
                    
                    led_position = row_index*(this->base_width) + (row_index % 2 == 0 ? column_index : (this->base_width)-1-column_index);
                    break;
                
                case Strip_Orientation::ALIGN_VERTICAL:
                    
                    led_position = row_index + column_index*(this->base_height);
                    break;
                
                case Strip_Orientation::ZIGZAG_VERTICAL:
                    
                    led_position = (column_index % 2 == 0 ? row_index : (this->base_height)-1-row_index) + column_index*(this->base_height);
                    break;
                
                default:
                    // Ungültige Position übergeben
                    led_position =  (this->base_width) * (this->base_height);
                    break;            
            }
            break;
        case Wiring_Start_Point::TOP_RIGHT:
            switch(this->strip_orientation)
            {
                case Strip_Orientation::ALIGN_HORIZONTAL:

                    led_position = row_index*(this->base_width) +  ((this->base_width)-1-column_index);
                    break;

                case Strip_Orientation::ZIGZAG_HORIZONTAL:

                    led_position = row_index*(this->base_width) + (row_index % 2 == 0 ? (this->base_width)-1-column_index : column_index);
                    break;

                case Strip_Orientation::ALIGN_VERTICAL:
                    
                    led_position = row_index + ((this->base_width)-1-column_index)*(this->base_height);
                    break;

                case Strip_Orientation::ZIGZAG_VERTICAL:

                    led_position = (((this->base_width)-1-column_index) % 2 == 0 ? row_index : (this->base_height)-1-row_index) + ((this->base_width)-1-column_index)*(this->base_height);
                    break;

                default:
                    // Ungültige Position übergeben
                    led_position =  (this->base_width) * (this->base_height);
                    break;
            }
            break;
        case Wiring_Start_Point::BOTTOM_LEFT:
            switch(this->strip_orientation)
            {
                case Strip_Orientation::ALIGN_HORIZONTAL:

                    led_position = ((this->base_height)-1-row_index)*(this->base_width) + column_index;
                    break;

                case Strip_Orientation::ZIGZAG_HORIZONTAL:

                    led_position = ((this->base_height)-1-row_index)*(this->base_width) + (((this->base_height)-1-row_index) % 2 == 0 ? column_index : (this->base_width)-1-column_index);
                    break;

                case Strip_Orientation::ALIGN_VERTICAL:

                    led_position = ((this->base_height)-1-row_index) + column_index*(this->base_height);
                    break;

                case Strip_Orientation::ZIGZAG_VERTICAL:

                    led_position = (column_index % 2 == 0 ? ((this->base_height)-1-row_index) : row_index) + column_index*(this->base_height);
                    break;

                default:
                    // Ungültige Position übergeben
                    led_position =  (this->base_width) * (this->base_height);
                    break;
            }
            break;
        case Wiring_Start_Point::BOTTOM_RIGHT:
            switch(this->strip_orientation)
            {
                case Strip_Orientation::ALIGN_HORIZONTAL:

                    led_position = ((this->base_height)-1-row_index)*(this->base_width) + ((this->base_width)-1-column_index);
                    break;

                case Strip_Orientation::ZIGZAG_HORIZONTAL:

                    led_position = ((this->base_height)-1-row_index)*(this->base_width) + (((this->base_height)-1-row_index) % 2 == 0 ? ((this->base_width)-1-column_index) : column_index);
                    break;

                case Strip_Orientation::ALIGN_VERTICAL:

                    led_position = ((this->base_height)-1-row_index) + ((this->base_width)-1-column_index)*(this->base_height);
                    break;

                case Strip_Orientation::ZIGZAG_VERTICAL:

                    led_position = (((this->base_width)-1-column_index) % 2 == 0 ? ((this->base_height)-1-row_index) : row_index)+ ((this->base_width)-1-column_index)*(this->base_height);
                    break;

                default:
                    // Ungültige Position übergeben
                    led_position =  (this->base_width) * (this->base_height);
                    break;
            }
            break;
        default:
            // Ungültige Position übergeben
            led_position =  (this->base_width) * (this->base_height);
            break;
    }

    // Berechnete Position auf Gültigkeit prüfen
    if(DEBUGGING)    DEBUG(String("Check if LED-Position is valid") + String(led_position) + (led_position < (this->base_width)*(this->base_height) ? "true" : "false"));
    if(ASSERT_CHECK)    TEST(led_position < (this->base_width)*(this->base_height));

    // FastLED-Pixel-Referenz zurückgeben
    return led_position;
}


// Gibt eine Referenz auf das FastLED-Pixel zurück 
// Mit dem weitergearbeitet werden kann
// z.B this->pixel(0,0) = CRGB(255,0,0) // Pixel (0,0) der Matrix die Farbe Rot zuweisen
// z.B this->pixel(0,0) = this->pixel(9,29) // Pixel (0,0) auf die gleiche Farbe setzen wie Pixel(9,29)
CRGB& LEDMatrix::pixel(const INT_16 row, const INT_16 column)
{
    return this->complete_strip[this->calc_pixel_position(row, column)];
}

// Gibt eine Referenz auf ein konstantes FastLED-Pixel zurück 
// Mit dem weitergearbeitet werden kann
// z.B this->pixel(0,0) = CRGB(255,0,0) // Pixel (0,0) der Matrix die Farbe Rot zuweisen
// z.B this->pixel(0,0) = this->const_pixel(9,29) // Pixel (0,0) auf die gleiche Farbe setzen wie Pixel(9,29)
const CRGB& LEDMatrix::const_pixel(const INT_16 row, const INT_16 column) const
{
    // Referenz wird beim Rückgeben in konstante Referent gecastet
    return this->complete_strip[this->calc_pixel_position(row, column)];
}

// für []-Operator
CRGB& LEDMatrix::pixel(const INT_16 index)
{
    switch(this->mat_type)
    {
        case MatrixType::ROW_VECTOR:
            // Index gibt Spalte an
            return this->complete_strip[this->calc_pixel_position(0, index)];

        case MatrixType::COLUMN_VECTOR:
            // Index gibt Zeile an
            return this->complete_strip[this->calc_pixel_position(index, 0)];
        
        case MatrixType::BASE_MATRIX:
        case MatrixType::SUB_MATRIX:
        default:
            // default
            return this->complete_strip[this->calc_pixel_position((index % (this->number_of_leds())) / this->sub_width, (index % (this->number_of_leds())) % this->sub_width)];
    }
}

// für []-Operator
const CRGB& LEDMatrix::const_pixel(const INT_16 index) const
{
    switch(this->mat_type)
    {
        case MatrixType::ROW_VECTOR:
            // Index gibt Spalte an
            // Referenz wird beim Rückgeben in konstante Referent gecastet
            return this->complete_strip[this->calc_pixel_position(0, index)];

        case MatrixType::COLUMN_VECTOR:
            // Index gibt Zeile an
            // Referenz wird beim Rückgeben in konstante Referent gecastet
            return this->complete_strip[this->calc_pixel_position(index, 0)];
        
        case MatrixType::BASE_MATRIX:
        case MatrixType::SUB_MATRIX:
        default:
            // default
            // Referenz wird beim Rückgeben in konstante Referent gecastet
            return this->complete_strip[this->calc_pixel_position((index % (this->number_of_leds())) / this->sub_width, (index % (this->number_of_leds())) % this->sub_width)];
    }
}


// Alle LEDs färben - RGB
void LEDMatrix::color_all(const CRGB& color)
{
    for(UINT_16 i = 0; i < this->number_of_leds(); ++i)
        this->pixel(i) = color;
}
 
// Alle LEDs färben - HSV
void LEDMatrix::color_all(const CHSV& color)
{
    this->color_all(CRGB(color));
}

// Alle LEDs ausschalten
void LEDMatrix::all_off()
{
    this->color_all(CRGB(0,0,0));
    FastLED.show();
}

// Zum Testen ob die Matrix richtig arbeitet
void LEDMatrix::self_test()
{

    const uint32_t delay_time_ms = 15000/this->number_of_leds();
    // erst alle ausschalten
    this->all_off();


    // Nacheinander Rot Färben
    const CRGB red = CRGB(255,0,0);
    for(UINT_16 i = 0; i < this->sub_height; ++i)
    {
        for(UINT_16 j = 0; j < this->sub_width; ++j)
        {
            this->pixel(i,j) = red;
            FastLED.show();
            if(DEBUGGING)    DEBUG("LED " + String(i) + "x" + String(j) + " red");
            delay(delay_time_ms);
        }
    }

    // Nacheinander Grün Färben
    const CRGB green = CRGB(0,255,0);
    for(UINT_16 i = 0; i < this->sub_height; ++i)
    {
        for(UINT_16 j = 0; j < this->sub_width; ++j)
        {
            this->pixel(i,j) = green;
            FastLED.show();
            if(DEBUGGING)    DEBUG("LED " + String(i) + "x" + String(j) + " green");
            delay(delay_time_ms);
        }
    }

    // Nacheinander Blau Färben
    const CRGB blue = CRGB(0,0,255);
    for(UINT_16 i = 0; i < this->sub_height; ++i)
    {
        for(UINT_16 j = 0; j < this->sub_width; ++j)
        {
            this->pixel(i,j) = blue;
            FastLED.show();
            if(DEBUGGING)    DEBUG("LED " + String(i) + "x" + String(j) + " blue");
            delay(delay_time_ms);
        }
    }

    // Nacheinander Weiß Färben
    const CRGB white = CRGB(255,255,255);
    for(UINT_16 i = 0; i < this->number_of_leds(); ++i)
    {    
        this->pixel(i) = white;
        FastLED.show();
        if(DEBUGGING)    DEBUG("LED " + String(i) + " white");
        delay(delay_time_ms);

    }

    delay(5000);
    this->all_off();

}



}   // Ende namespace LEDArrangement