#include "debugging.h"

#ifdef USE_FUNCTIONS

void ASSERT(const bool test_statement)
{
    assert(test_statement);
}

void TEST(const bool test_statement)
{
    if (!(test_statement))
    {
        pinMode(13, OUTPUT);
        while (true)
        {
            digitalWrite(13, HIGH);
            delay(200);
            digitalWrite(13, LOW);
            delay(200);
        }
    }
}

void DEBUG(const String text)
{
    Serial.println(text);
    delay(10);
}

#endif // USE_FUNCTIONS