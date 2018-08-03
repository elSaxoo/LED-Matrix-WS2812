#include <SlidingText.h>


#include <debugging.h>
#define DEBUGGING false
#define ASSERT_CHECK true

namespace LEDArrangement
{

namespace Effects
{


// ---------------- SlidingText ----------------

SlidingText::SlidingText(LEDMatrix& Mat, const uint32_t Delay_between_frames, const String Text,
        const CRGB Color, const CRGB Background, const UINT_8 Space_between_characters, 
        const LEDArrangement::Direction direction, 
        const UINT_8 Edge_offset, const uint32_t Slide_to,
        const bool Auto_repeat)
:
LED_effect(Mat, Delay_between_frames),
text(Text),
color(Color), 
background(Background), 
space_between_characters(Space_between_characters), 
direction(direction), 
edge_offset(Edge_offset),
slide_to(Slide_to),
auto_repeat(Auto_repeat),
//
space_counter(0),
String_char_index(0),
Bitmap_column_index(0),
temp_char_bitmap(LEDArrangement::Font::FontBitmap::of('K')),
temp_column_bitmap(0),
//
// is_matrix_big_enough_for_text(false),
// is_hole_text_on_matrix(false),
only_cycle(false),
slide_out(false),
slide_counter(0)
{

    this->set_edge_offset(Edge_offset);

    this->set_slide_to(slide_to);
    
    String_char_index = (direction == LEDArrangement::Direction::LEFT) ? 0 : text.length() - 1;
    temp_char_bitmap = LEDArrangement::Font::font_bitmap[text.charAt(String_char_index)];

    Bitmap_column_index = (direction == LEDArrangement::Direction::LEFT) ? 0 : temp_char_bitmap.width() - 1;
    temp_column_bitmap = LEDArrangement::Font::ColumnBitmap(temp_char_bitmap[Bitmap_column_index]);

}

bool SlidingText::setup()
{
    // Matrix mit Hintergrundfarbe einfärben 
    this->mat.color_all(this->background);

    // interne Parameter zurücksetzen
    this->reset_index_parameter_and_bitmaps();

    // Die ersten x Frames berechnen
    for(UINT_8 i = 0; i < this->edge_offset; ++i)
    {
        this->render_next_frame();
    }

   return true;
}

bool SlidingText::render_next_frame()
{
    if (DEBUGGING)
    {
        DEBUG(this->text);
        DEBUG(String("String_char_index: ") + String(String_char_index));
        DEBUG(String("Bitmap_column_index: ") + String(Bitmap_column_index));
        DEBUG(String("space_counter: ") + String(space_counter));
        DEBUG(String("slide_out: ") + String(slide_out));
        DEBUG(String("slide_counter: ") + String(slide_counter));
        DEBUG(String("slide_to: ") + String(slide_to));
        DEBUG();
    }


    // Nur Rotieren lassen
    if(this->only_cycle)
    {
        // Nur Rotieren lassen
        mat.cycle(this->direction, 1);
        return true;
    }
    else
    {
        if (this->slide_counter >= this->slide_to)
        {
            // Wenn der Text automatisch wiederholt werden soll
            if (this->auto_repeat == true)
            {
                this->reset_index_parameter_and_bitmaps();
            }
        }

        if (this->slide_counter < this->slide_to)
        {
            // Text spaltenweise über Matrix schieben
            mat.shift(this->direction, 1);

            if (this->slide_out == false)
            {
                // Neue Spalten-Bitmap in Matrix schreiben
                this->write_bitmap_in_matrix_column(this->temp_column_bitmap, ((this->direction == Direction::LEFT) ? mat.matrix_width() - 1 : 0));
                
                // Die nächste Spalten-Bitmap laden
                this->slide_out = this->update_index_parameter_and_bitmaps();
            }
            else
            {
                // Leere Spalten-Bitmap in Matrix schreiben
                this->write_bitmap_in_matrix_column(LEDArrangement::Font::ColumnBitmap(0), ((this->direction == Direction::LEFT) ? mat.matrix_width() - 1 : 0));
            }

            // Zähler erhöhen
            this->slide_counter += 1;

            // Matrix hat sich geändert
            return true;
        }
        else
        {
            // Matrix hat sich nicht geändert
            return false;
        }
    }   
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

bool SlidingText::reset_index_parameter_and_bitmaps()
{
    this->slide_counter = 0;
    this->slide_out = false;

    // Space Counter zurücksetzen 
    this->space_counter = 0;

    switch(this->direction)
    {
        case Direction::RIGHT:
            
            // Index für Zeichen zurücksetzen
            this->String_char_index = this->text.length() - 1;
            // Bitmap von neuem Zeichen laden
            this->temp_char_bitmap =  LEDArrangement::Font::font_bitmap[text.charAt(this->String_char_index)];

            // Index für Column-Bitmap zurücksetzen 
            this->Bitmap_column_index = this->temp_char_bitmap.width() - 1;
            // Neue Bitmap laden
            this->temp_column_bitmap = temp_char_bitmap[this->Bitmap_column_index];
            
            break;

        case Direction::LEFT:
        default:

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
    return true;
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


// Setter

SlidingText& SlidingText::set_text(const String text)
{
    return this->set_text(text, false, this->TextEnd + this->MatrixWidth);
}
SlidingText& SlidingText::set_text(const String text, const uint32_t slide_to)
{
    return this->set_text(text, false, slide_to);
}
SlidingText& SlidingText::set_text(const String text, const bool reset)
{
    return this->set_text(text, reset, this->TextEnd + this->MatrixWidth);
}
SlidingText& SlidingText::set_text(const String text, const uint32_t slide_to, const bool reset)
{
    return this->set_text(text, reset, slide_to);
}
SlidingText& SlidingText::set_text(const String text, const bool reset, const uint32_t slide_to)
{

    if(DEBUGGING)
    {
        DEBUG("OLD: " + this->text);
        DEBUG("NEW: " + text);
    }

    this->text = text;

    if(DEBUGGING)
    {
        DEBUG("CHANGED: " + this->text);
        delay(10000);
    }

    this->set_slide_to(slide_to);
    this->reset_index_parameter_and_bitmaps();
    if(reset) this->setup(); 
    return *this;
}

SlidingText& SlidingText::set_color(const CRGB color) 
{
    this->color = color;
    return *this;
}

SlidingText& SlidingText::set_background(const CRGB background) 
{
    this->background = background;
    return *this;
}

SlidingText& SlidingText::set_space_between_characters(const UINT_8 space_between_characters) 
{
    this->space_between_characters = space_between_characters;
    return *this;
}

SlidingText& SlidingText::set_direction(const LEDArrangement::Direction direction) 
{
    this->direction = direction;
    return *this;
}

SlidingText& SlidingText::set_edge_offset(const UINT_8 edge_offset) 
{
    this->edge_offset = (edge_offset < mat.matrix_width()) ? edge_offset : mat.matrix_width();
    return *this;
}

SlidingText& SlidingText::set_slide_to(const uint32_t slide_to) 
{

    this->slide_to = slide_to;

    // Wenn automatisch das Ende des Text ausgewält werden soll
    if(this->text_end_offset & slide_to)
    {
        this->slide_to &= ~(this->text_end_offset);
        this->slide_to += LEDArrangement::Font::FontBitmap::length_of(this->text, this->space_between_characters);
    }
    // Wenn automatisch das Ende der Matrix ausgewält werden soll
    if(this->matrix_width_offset & slide_to)
    {
        this->slide_to &= ~(this->matrix_width_offset);
        this->slide_to += this->mat.matrix_width();
    }

    return *this;
}

SlidingText& SlidingText::set_auto_repeat(const bool auto_repeat) 
{
    this->auto_repeat = auto_repeat;
    return *this;
}


// Getter
String SlidingText::get_text() const
{
    return this->text;
}

CRGB SlidingText::get_color() const
{
    return this->color;
}

CRGB SlidingText::get_background() const
{
    return this->background;
}

UINT_8 SlidingText::get_space_between_characters() const
{
    return this->space_between_characters;
}

LEDArrangement::Direction SlidingText::get_direction() const
{
    return this->direction;
}

UINT_8 SlidingText::get_edge_offset() const
{
    return this->edge_offset;
}

uint32_t SlidingText::get_slide_to() const
{
    return this->slide_to;
}

bool SlidingText::get_auto_repeat() const
{
    return this->auto_repeat;
}




} // Ende namespace Effects

} // Ende namespace LEDArrangement
