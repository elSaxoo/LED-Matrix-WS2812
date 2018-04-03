#include "SW_Timer.h"


namespace LEDArrangement
{

namespace Effects
{

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


} // Ende namespace Effects

} // Ende namespace LEDArrangement