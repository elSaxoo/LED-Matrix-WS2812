#include <Effects.h>


namespace LEDArrangement
{

namespace Effects
{

// ---------------- LED_effect ----------------

LED_effect::LED_effect(LEDMatrix& Mat, const uint32_t Delay_between_frames)
:
    mat(Mat),
    effect_update_timer(Delay_between_frames)
    {}

bool LED_effect::update_frame(const uint32_t currentTime)
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







} // Ende namespace Effects

} // Ende namspace LEDArrangement