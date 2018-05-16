#include <SlidingText.h>


namespace LEDArrangement
{

namespace Effects
{


// ---------------- SlidingText ----------------

SlidingText::SlidingText(LEDMatrix& Mat, const uint32_t Delay_between_frames, const String Text,
        const CRGB Color, const CRGB Background, const UINT_8 Space_between_characters, 
        const LEDArrangement::Direction direction, const UINT_8 Edge_offset, const int32_t Repeat_at)
:
LED_effect(Mat, Delay_between_frames),
text(Text),
color(Color), 
background(Background), 
space_between_characters(Space_between_characters), 
direction(direction), 
edge_offset(Edge_offset),
repeat_at(Repeat_at),
//
space_counter(0),
String_char_index(0),
Bitmap_column_index(0),
temp_char_bitmap(LEDArrangement::Font::font_bitmap['K']),
temp_column_bitmap(0),
//
is_matrix_big_enough_for_text(false),
is_hole_text_on_matrix(false),
only_cycle(false),
roll_out(false)
{
    edge_offset = (edge_offset < mat.matrix_width()) ? edge_offset : mat.matrix_width();

    if (Repeat_at < 0)
    {
        repeat_at = Repeat_at + negative_base_offsett + mat.matrix_width();
    }

    String_char_index = (direction == LEDArrangement::Direction::LEFT) ? 0 : text.length() - 1;
    temp_char_bitmap = LEDArrangement::Font::font_bitmap[text.charAt(String_char_index)];

    Bitmap_column_index = (direction == LEDArrangement::Direction::LEFT) ? 0 : temp_char_bitmap.width() - 1;
    temp_column_bitmap = LEDArrangement::Font::ColumnBitmap(temp_char_bitmap[Bitmap_column_index]);

}

bool SlidingText::setup_LED_Matrix()
{
    switch(direction)
    {
        case Direction::RIGHT:

            for(UINT_8 i = 0; i < mat.matrix_width(); ++i)
                {
                    // Alles vorher ist Hintergrund
                    if(i < mat.matrix_width() - this->edge_offset)
                    {
                        // Pixel auf Hintergrungfarbe setzen mithilfe von leerer Bitmap
                        this->write_bitmap_in_matrix_column(LEDArrangement::Font::ColumnBitmap(0),  mat.matrix_width() - 1 - i);
                    }
                    //
                    // Ab hier kommt Text
                    else if(i >= mat.matrix_width() - this->edge_offset && !(this->is_hole_text_on_matrix))
                    {
                        // Buchstaben Spalte für Spalte in Matrix schreiben
                        this->write_bitmap_in_matrix_column(this->temp_column_bitmap, mat.matrix_width() - 1 - i);

                        // Falls das Ende des Text erreicht wird, gibt die Funktion true zurück
                        this->is_hole_text_on_matrix = this->update_index_parameter_and_bitmaps();

                        // Falls der ganze Text auf die Matrix passt
                        if(this->is_hole_text_on_matrix)
                        {
                            only_cycle = true; // Für Später in render_next_frame Methode
                        }
                    }
                    //
                    // Alles nachher ist Hintergrung
                    else if(this->is_hole_text_on_matrix && i >= mat.matrix_width() - this->edge_offset)
                    {
                        // Pixel auf Hintergrungfarbe setzen mithilfe von leerer Bitmap
                        this->write_bitmap_in_matrix_column(LEDArrangement::Font::ColumnBitmap(0), mat.matrix_width() - 1 - i);
                    }
                }
            
            break;
        case Direction::LEFT:
        default:

            for(UINT_8 i = 0; i < mat.matrix_width(); ++i)
            {
                // Alles vorher ist Hintergrund
                if(i < mat.matrix_width() - this->edge_offset)
                {
                    // Pixel auf Hintergrungfarbe setzen mithilfe von leerer Bitmap
                    this->write_bitmap_in_matrix_column(LEDArrangement::Font::ColumnBitmap(0), i);
                }
                //
                // Ab hier kommt Text
                else if(i >= mat.matrix_width() - this->edge_offset && !(this->is_hole_text_on_matrix))
                {
                    // Buchstaben Spalte für Spalte in Matrix schreiben
                    this->write_bitmap_in_matrix_column(this->temp_column_bitmap, i);

                    // Falls das Ende des Text erreicht wird, gibt die Funktion true zurück
                    this->is_hole_text_on_matrix = this->update_index_parameter_and_bitmaps();

                    // Falls der ganze Text auf die Matrix passt
                    if(this->is_hole_text_on_matrix)
                    {
                        only_cycle = true; // Für Später in render_next_frame Methode
                    }
                }
                //
                // Alles nachher ist Hintergrung
                else if(this->is_hole_text_on_matrix && i >= mat.matrix_width() - this->edge_offset)
                {
                    // Pixel auf Hintergrungfarbe setzen mithilfe von leerer Bitmap
                    this->write_bitmap_in_matrix_column(LEDArrangement::Font::ColumnBitmap(0), i);
                }
            }

            break;
        }

    return true;
}

bool SlidingText::render_next_frame()
{
    // Falls der ganze Text auf die Matrix passt
    if(this->only_cycle)
    {
        // Nur Rotieren lassen
        mat.cycle(this->direction, 1);
    }
    else
    {
        // Text spaltenweise über Matrix schieben
        mat.shift(this->direction, 1);

        // Neue Spalten-Bitmap in Matrix schreiben
        this->write_bitmap_in_matrix_column(this->temp_column_bitmap, ((this->direction == Direction::LEFT) ? mat.matrix_width() - 1 : 0));
        
        // Die nächste Spalten-Bitmap laden
        this->update_index_parameter_and_bitmaps();
    }
    
    return true;
}


bool SlidingText::update_frame(const uint32_t currentTime)
{
    if (effect_update_timer(currentTime))
    {
        return	render_next_frame();
    }
    else
    {
        return false;
    }
}


const Direction SlidingText::change_direction(const Direction new_dir)
{
    this->direction = new_dir;
    this->update_index_parameter_and_bitmaps();

    return this->direction;
}
const Direction SlidingText::change_direction()
{
    return this->change_direction((this->direction == Direction::LEFT ? Direction::RIGHT : Direction::LEFT));   
}


bool SlidingText::update_index_parameter_and_bitmaps()
{
    // könnte nutzlich sein
    bool loopback = false; 
    bool load_space_bitmap = false;

    switch(this->direction)
    {
        case Direction::RIGHT:
            
            // Spaltenindex um 1 verringern
            this->Bitmap_column_index -= 1;

            // Wenn der Spaltenindex kleiner Null ist
            if(this->Bitmap_column_index < 0)
            {
                // Leere Spalten zwischen Buchstaben einfügen
                this->space_counter -= 1;
                load_space_bitmap = true;

                // Wenn genug Platz zwischen Buchstaben ist
                if(this->space_counter < 0)
                {
                    // Index für Buchstaben um 1 verringer
                    this->String_char_index -= 1;

                    // Wenn der Buchstabenindex kleiner Null ist
                    if(this->String_char_index < 0)
                    {
                        // Index auf Ende des Text zurücksetzen
                        this->String_char_index = this->text.length() - 1;

                        // Index auf Anfang des Text zurückgesetzt
                        loopback = true;
                    }

                    // neue CharBitmap laden
                    this->temp_char_bitmap = LEDArrangement::Font::font_bitmap[text.charAt(this->String_char_index)];

                    // Zähler für leere Zeichen zurücksetzen
                    this->space_counter = this->space_between_characters;
                    load_space_bitmap = false;

                    // Spaltenindex auf Ende der CharBitmap zurücksetzen
                    this->Bitmap_column_index = this->temp_char_bitmap.width() - 1;
                }
            }

            // Neue ColumnBitmap laden
            if( ! load_space_bitmap)
            {
                this->temp_column_bitmap = LEDArrangement::Font::ColumnBitmap(this->temp_char_bitmap[this->Bitmap_column_index]);
            }
            else
            {
                this->temp_column_bitmap = LEDArrangement::Font::ColumnBitmap(0);
            }

            break;

        case Direction::LEFT:
        default:

            // Spaltenindex um 1 erhöhen
            this->Bitmap_column_index += 1;

            // Wenn der Spaltenindex größer gleich der Breite der CharBitmap
            if(this->Bitmap_column_index >= this->temp_char_bitmap.width())
            {
                // Leere Spalten zwischen Buchstaben einfügen
                this->space_counter += 1;
                load_space_bitmap = true;

                // Wenn genug Platz zwischen Buchstaben ist
                if(this->space_counter > this->space_between_characters)
                {
                    // Index für Buchstaben um 1 erhöhen
                    this->String_char_index += 1;

                    // Wenn der Buchstabenindex größer gleich der Länge des Text ist
                    if(this->String_char_index >= this->text.length())
                    {
                        // Index auf Anfang des Text zurücksetzen
                        this->String_char_index = 0;

                        // Index auf Anfang des Text zurückgesetzt
                        loopback = true;
                    }

                    // neue CharBitmap laden
                    this->temp_char_bitmap = LEDArrangement::Font::font_bitmap[text.charAt(this->String_char_index)];  

                    // Zähler für leere Zeichen zurücksetzen
                    this->space_counter = 0;
                    load_space_bitmap = false;

                    // Spaltenindex auf 0 zurücksetzen
                    this->Bitmap_column_index = 0;     
                }    
            }

            // Neue ColumnBitmap laden
            if( ! load_space_bitmap)
            {
                this->temp_column_bitmap = LEDArrangement::Font::ColumnBitmap(this->temp_char_bitmap[this->Bitmap_column_index]);
            }
            else
            {
                this->temp_column_bitmap = LEDArrangement::Font::ColumnBitmap(0);
            }

            break;
    }

    return loopback;     
}

bool reset_index_parameter_and_bitmaps()
{
    this->slide_counter = 0;

    switch(this->direction)
    {
        case Direction::RIGHT:
            
            // Space Counter zurücksetzen 
            this->space_counter = 0;
            
            // Index für Zeichen zurücksetzen
            this->String_char_index = this->text.lenght() - 1;
            // Bitmap von neuem Zeichen laden
            this->temp_char_bitmap =  LEDArrangement::Font::font_bitmap[text.charAt(this->String_char_index)];

            // Index für Column-Bitmap zurücksetzen 
            this->Bitmap_column_index = this->temp_char_bitmap.width() - 1;
            // Neue Bitmap laden
            this->temp_column_bitmap = temp_char_bitmap[this->Bitmap_column_index];
            
            break;

        case Direction::LEFT:
        default:

            // Space Counter zurücksetzen 
            this->space_counter = 0;

            // Index für Zeichen zurücksetzen
            this->String_char_index = 0;
            // Bitmap von neuem Zeichen laden
            this->temp_char_bitmap =  LEDArrangement::Font::font_bitmap[text.charAt(this->String_char_index)];

            // Index für Column-Bitmap zurücksetzen 
            this->Bitmap_column_index = 0;
            // Neue Bitmap laden
            this->temp_column_bitmap = temp_char_bitmap[this->Bitmap_column_index];
            
            break;
    }
}


void SlidingText::write_bitmap_in_matrix_column(const LEDArrangement::Font::ColumnBitmap& bitmap, const UINT_8 column_index)
{
    // Für jede Zeile des Spalten-Vektors
    for(uint8_t i = 0; i < bitmap.length(); ++i)
    {
        // Wenn das Bit gesetzt ist...
        if(bitmap[i])
        {
            // ...gehört das Pixel der Matrix zum Buchstaben
            mat.pixel(i, column_index) = this->color;
        }
        else
        {
            // ...ansonsten ist es Hintergrund
            mat.pixel(i, column_index) = this->background;
        }
    }
}







} // Ende namespace Effects

} // Ende namespace LEDArrangement
