#ifndef DEBUGGING_H
#define DEBUGGING_H

#include <Arduino.h>
#include <assert.h>

#define USE_FUNCTIONS


#ifdef USE_FUNCTIONS

    void ASSERT(const bool test_statement);
    
    void TEST(const bool test_statement); 
    
    void DEBUG(const String text); 


#endif // USE_FUNCTIONS


#ifndef USE_FUNCTIONS

// Macro für assert
#define ASSERT(test_statement) {assert(test_statement);}

// Macro für test
#define TEST(test_statement) {if(!(test_statement)){pinMode(13, OUTPUT); while(true){digitalWrite(13, HIGH); delay(250); digitalWrite(13, LOW); delay(250); } } }

// Macro für Debug-Ausgaben auf dem Serial-Monitor
#define DEBUG(text) {Serial.println(text); delay(10);}

#endif // USE_FUNCTIONS


#endif // DEBUGGING_H