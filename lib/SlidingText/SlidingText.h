#ifndef SLIDINGTEXT_H
#define SLIDINGTEXT_H

#include <Arduino.h>
#include <LEDMatrix.h>
#include <Effects.h>
#include <FontBitmap.h>
namespace LEDArrangement
{

namespace Effects
{



// ---------------- SlidingText ----------------
class SlidingText : public LED_effect
{
    private:

        static const uint32_t text_end_offset = ((uint32_t)1 << 31); // Wert wichtig nicht ändern
        static const uint32_t matrix_width_offset = ((uint32_t)1 << 30); // Wert wichtig nicht ändern
    
    public:

        static const uint32_t TextEnd = text_end_offset;
        static const uint32_t MatrixWidth = matrix_width_offset;

        SlidingText(LEDMatrix& Mat, const uint32_t Delay_between_frames, const String Text,
                    const CRGB Color = CRGB(0, 255, 0), const CRGB Background = CRGB(0, 0, 0), const UINT_8 Space_between_characters = 1, 
                    const LEDArrangement::Direction direction = LEDArrangement::Direction::LEFT, 
                    const UINT_8 Edge_offset = 0, const uint32_t Slide_to = TextEnd + MatrixWidth,
                    const bool Auto_repeat = false);

        bool setup();

		bool render_next_frame();

		bool update_frame(const uint32_t currentTime = 0);

        const Direction change_direction(const Direction new_dir);
        const Direction change_direction();


        // Setter
        SlidingText& set_text(const String text);
        SlidingText& set_color(const CRGB color);
        SlidingText& set_background(const CRGB background);
        SlidingText& set_space_between_characters(const UINT_8 space_between_characters);
        SlidingText& set_direction(const LEDArrangement::Direction direction);
        SlidingText& set_edge_offset(const UINT_8 edge_offset);
        SlidingText& set_slide_to(const uint32_t slide_to);
        SlidingText& set_auto_repeat(const bool auto_repeat);

        // Getter
        String get_text() const;
        CRGB get_color() const;
        CRGB get_background() const;
        UINT_8 get_space_between_characters() const;
        LEDArrangement::Direction get_direction() const;
        UINT_8 get_edge_offset() const;
        uint32_t get_slide_to() const;
        bool get_auto_repeat() const;


    private:

        bool update_index_parameter_and_bitmaps();

        bool reset_index_parameter_and_bitmaps();

        void write_bitmap_in_matrix_column(const LEDArrangement::Font::ColumnBitmap& bitmap, const UINT_8 column_index);

        // Funktionsparameter
        String text;
        CRGB color;
        CRGB background;
        UINT_8 space_between_characters;
        LEDArrangement::Direction direction;
        UINT_8 edge_offset;
        uint32_t slide_to;
        bool auto_repeat;

        // Index-Parameter
        int16_t space_counter;
        int32_t String_char_index;
        int16_t Bitmap_column_index;
        LEDArrangement::Font::CharBitmap temp_char_bitmap;
        LEDArrangement::Font::ColumnBitmap temp_column_bitmap;

        // Status
        // bool is_matrix_big_enough_for_text;
        // bool is_hole_text_on_matrix;
        bool only_cycle;
        bool slide_out;
        uint32_t slide_counter;
    

};


} // Ende namespace Effects

} // Ende namespace LEDArrangement

#endif // SLIDINGTEXT_H
