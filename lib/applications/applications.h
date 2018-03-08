#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <Arduino.h>
#include <LEDMatrix.h>

namespace LEDArrangement
{

// Print-Funktion von elSaxoo
void print_String(LEDMatrix &mat, const String text, const CRGB color = CRGB(0, 0, 255), const int8_t shift_horizontal = 0, const bool begin_right, const CRGB background = CRGB(0, 0, 0));

// Überladung von print_String für CHSV Farbe
void print_String(LEDMatrix &mat, const String text, const CHSV color, const int8_t shift_horizontal = 0, const bool begin_right = false, const CHSV background = CHSV(0, 0, 0));

// Print-Funktion von SvenJupiter
void print_char(LEDMatrix &mat, const char character, const CRGB color, const CRGB background = CRGB(0, 0, 0));

// Print-Funktion von SvenJupiter
// Überladung von print_char für CHSV Farbe
void print_char(LEDMatrix &mat, const char character, const CHSV color, const CHSV background = CHSV(0, 0, 0));

// Print-Funktion von SvenJupiter
// Überladung von print_string für CHSV Farbe
void print_string(LEDMatrix &mat, const char *const text, const CRGB color, const CRGB background = CRGB(0, 0, 0), const UINT_8 space_between_characters = 1);

// Print-Funktion von SvenJupiter
// Überladung von print_string für CHSV Farbe
void print_string(LEDMatrix &mat, const char *const text, const CHSV color, const CHSV background = CHSV(0, 0, 0), const UINT_8 space_between_characters = 1);

// Die Matrix über die serielle Schnittstelle mit Daten versorgen
void serial_matrix_updater(HardwareSerial &UART, LEDMatrix &mat);

} // Ende namespace LEDArrangement

#endif
