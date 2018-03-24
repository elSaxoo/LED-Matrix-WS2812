#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <Arduino.h>
#include <LEDMatrix.h>

namespace LEDArrangement
{

void print_char(LEDMatrix &mat, const char character, const CRGB color = CRGB(255, 0, 0), const CRGB background = CRGB(0, 0, 0));

// Überladung von print_char für CHSV Farbe
void print_char(LEDMatrix &mat, const char character, const CHSV color, const CHSV background = CHSV(0, 0, 0));

// Überladung von print_string für CHSV Farbe
void print_string(LEDMatrix &mat, const char *const text, const CRGB color = CRGB(0, 255, 0), const CRGB background = CRGB(0, 0, 0), const UINT_8 space_between_characters = 1);

// Überladung von print_string für CHSV Farbe
void print_string(LEDMatrix &mat, const char *const text, const CHSV color, const CHSV background = CHSV(0, 0, 0), const UINT_8 space_between_characters = 1);

// Lauftext
void print_rolling_String(LEDMatrix &mat, const String text, const uint16_t delay_between_frames_ms = 166, 
    const CRGB color = CRGB(0, 255, 0), const CRGB background = CRGB(0, 0, 0), const UINT_8 space_between_characters = 1, 
    const Direction direction = Direction::LEFT, const UINT_8 edge_offset = 0);

// Die Matrix über die serielle Schnittstelle mit Daten versorgen
void serial_matrix_updater(HardwareSerial &UART, LEDMatrix &mat);

} // Ende namespace LEDArrangement

#endif
