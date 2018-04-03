#ifndef SW_TIMER_H
#define SW_TIMER_H

#include <stdint.h>

namespace LEDArrangement
{

namespace Effects
{

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



} // Ende namespace Effects

} // Ende namespace LEDArrangement

#endif // SW_TIMER_H