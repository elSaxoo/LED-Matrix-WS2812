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
    public:
        SlidingText(LEDMatrix& Mat, const uint32_t Delay_between_frames, const String Text,
                    const CRGB Color = CRGB(0, 255, 0), const CRGB Background = CRGB(0, 0, 0), const UINT_8 Space_between_characters = 1, 
                    const LEDArrangement::Direction direction = LEDArrangement::Direction::LEFT, const UINT_8 Edge_offset = 0);

        bool setup_LED_Matrix();

		bool render_next_frame();

		bool update_frame(const uint32_t currentTime = 0);

        const Direction change_direction(const Direction new_dir);
        const Direction change_direction();

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

        // Index-Parameter
        int16_t space_counter;
        int32_t String_char_index;
        int16_t Bitmap_column_index;
        LEDArrangement::Font::CharBitmap temp_char_bitmap;
        LEDArrangement::Font::ColumnBitmap temp_column_bitmap;

        // Status
        bool is_matrix_big_enough_for_text;
        bool is_hole_text_on_matrix;
        bool only_cycle;
        bool roll_out;
    

};


} // Ende namespace Effects

} // Ende namespace LEDArrangement

#endif // SLIDINGTEXT_H
