#include <Effects.h>



namespace LEDArrangement
{

namespace Effects
{

// ---------------- SW_Timer ----------------

SW_Timer::SW_Timer(const uint32_t Delay_between_frames, uint32_t currentTime)
:
    delay_between_frames(Delay_between_frames),
    lastTime(currentTime)
    {}

bool SW_Timer::test_timer_event(const uint32_t currentTime)
{
    if (currentTime - lastTime >= delay_between_frames)
    {
        lastTime = currentTime;
        return true;
    }
    else
    {
        return false;
    }
}



// ---------------- LED_effect ----------------

LED_effect::LED_effect(LEDMatrix& Mat, const uint32_t Delay_between_frames)
:
    mat(Mat),
    effect_update_timer(Delay_between_frames)
    {}

bool LED_effect::update_LEDs(const uint32_t currentTime)
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



// ---------------- RollingText ----------------

RollingText::RollingText(LEDMatrix& Mat, const uint32_t Delay_between_frames, const String Text,
        const CRGB Color, const CRGB Background, const UINT_8 Space_between_characters, 
        const LEDArrangement::Direction direction, const UINT_8 Edge_offset)
:
LED_effect(Mat, Delay_between_frames),
text(Text),
color(Color), 
background(Background), 
space_between_characters(Space_between_characters), 
direction(direction), 
edge_offset(Edge_offset),
//
String_char_index(0),
Bitmap_column_index(0),
temp_char_bitmap(LEDArrangement::Font::font_bitmap['K']),
temp_column_bitmap(0)
{

    String_char_index = (direction == LEDArrangement::Direction::LEFT) ? 0 : text.length() -1;
    temp_char_bitmap = LEDArrangement::Font::font_bitmap[text.charAt(String_char_index)];

    Bitmap_column_index = (direction == LEDArrangement::Direction::LEFT) ? 0 : temp_char_bitmap.width()-1;
    temp_column_bitmap = LEDArrangement::Font::ColumnBitmap(temp_char_bitmap[Bitmap_column_index]);

}

bool RollingText::setup_LED_Strip()
{
    return false;
}

bool RollingText::render_next_frame()
{
    return false;
}

bool RollingText::update_LEDs(const uint32_t currentTime)
{
    return false;
}







// Später

// // Lauftext
// void print_rolling_String(LEDMatrix &mat, const String text, const uint16_t delay_between_frames_ms, 
//     const CRGB color, const CRGB background, const UINT_8 space_between_characters, 
//     const Direction direction, const UINT_8 edge_offset)
// {

//     UINT_8 column_offset;

//     switch(direction)
//     {
//         case Direction::RIGHT:
            
//             break;
//         case Direction::LEFT:
//         default:

//             // Für alle Buchstaben
//             for(uint16_t char_index = 0; char_index < text.length(); ++char_index)
//             {
//                 const CharBitmap ch_bitmap(Font::font_bitmap[text.CharAt(char_index)]);

//                 // Für alle Zeilen der Bitmap
//                 for(uint8_t j = 0; j < ch_bitmap.width())
//                 {
//                     const ColumnBitmap col_bitmap(ch_bitmap[j]);

//                     // Werten in Matrix schreiben
//                     for(uint8_t i = 0; i < ch_bitmap.height(); ++i)
//                     {
                        
//                     }
//                 }
//                 // Offset-Zeilen mit Buchstabe beschreiben
//                 if(edge_offset > 0)
//                 {
//                     for(UINT_8 i = 0; i < edge_offset; ++i)
//                     column_offset = mat.matrix_width() - 1 - edge_offset;
//                 }
//                 else
//                 {
                    
//                 }
//             }



//             break;


//     }
// }

} // Ende namespace Effects

} // Ende namspace LEDArrangement