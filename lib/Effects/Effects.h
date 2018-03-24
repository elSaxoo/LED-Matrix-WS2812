#ifndef EFFECTS_H
#define EFFECTS_H

#include <Arduino.h>
#include <LEDMatrix.h>
#include <FontBitmap.h>
namespace LEDArrangement
{

namespace Effects
{


// ---------------- SW_Timer ----------------

class SW_Timer
{
    public:
        SW_Timer(const uint32_t Delay_between_frames, uint32_t currentTime = 0);

        bool test_timer_event(const uint32_t currentTime);

        bool operator()(const uint32_t currentTime) {return test_timer_event(currentTime);}

    private:

        uint32_t delay_between_frames;
        uint32_t lastTime;
};



// ---------------- LED_effect ----------------

class LED_effect // Oberklasse für Effekte
{
	public:
		LED_effect(LEDMatrix& Mat, const uint32_t Delay_between_frames);

		virtual bool setup_LED_Strip() = 0;

		virtual bool render_next_frame() = 0;

		virtual bool update_LEDs(const uint32_t currentTime = 0);

	protected:

		LEDMatrix& mat;
		SW_Timer effect_update_timer;
};



// ---------------- RollingText ----------------
class RollingText : public LED_effect
{
    public:
        RollingText(LEDMatrix& Mat, const uint32_t Delay_between_frames, const String Text,
                    const CRGB Color = CRGB(0, 255, 0), const CRGB Background = CRGB(0, 0, 0), const UINT_8 Space_between_characters = 1, 
                    const LEDArrangement::Direction direction = LEDArrangement::Direction::LEFT, const UINT_8 Edge_offset = 0);

        bool setup_LED_Strip();

		bool render_next_frame();

		bool update_LEDs(const uint32_t currentTime = 0);

    private:

        void update_index_parameter();

        void write_bitmap_in_matrix_column(LEDArrangement::Font::ColumnBitmap& bitmap, UINT_8 column_index);

        // Funktionsparameter
        String text;
        CRGB color;
        CRGB background;
        UINT_8 space_between_characters;
        LEDArrangement::Direction direction;
        UINT_8 edge_offset;

        // Index-Parameter
        uint16_t String_char_index;
        uint8_t Bitmap_column_index;
        LEDArrangement::Font::CharBitmap temp_char_bitmap;
        LEDArrangement::Font::ColumnBitmap temp_column_bitmap;
    

};







} // Ende namespace Effects

} // Ende namespace LEDArrangement

#endif