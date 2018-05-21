#ifndef FONTBITMAP_H
#define FONTBITMAP_H

#include <LEDMatrix.h>


namespace LEDArrangement
{

namespace Font
{
// Implementierung fehlt noch


// Hilfsklasse für [][][]-Operator
class ColumnBitmap
{
public:

    // Konstruktor
    ColumnBitmap(const uint8_t Column_bitmap);

    //  Kopierkonstuktor
    ColumnBitmap(const ColumnBitmap& Column_Bitmap);

    // Zuweisungsoperator
    void operator=(const ColumnBitmap& Column_Bitmap);

    // Höhe des Zeichens in Pixel
    const uint8_t length() const {return 8;}

    // Prüfen ob Bit gesetzt ist
    const bool get_row_bit(const uint8_t row_index) const;

    // []-Operator
    const bool operator[](const uint8_t row_index) const {return get_row_bit(row_index);}

    //implicit conversion
    operator uint8_t() const {return column_bitmap;}
 

private:

    uint8_t column_bitmap;

};


// Hilfsklasse für [][]-Operator
class CharBitmap
{

public:

    // Konstruktor
    CharBitmap(const uint8_t* const Char_bitmap, const uint8_t Width);

    //  Kopierkonstuktor
    CharBitmap(const CharBitmap& Char_Bitmap);

    // Zuweisungsoperator
    void operator=(const CharBitmap& Char_Bitmap);

    // column_bitmap aus PROGMEM-Speicher holen
    const ColumnBitmap get_column_bitmap(const uint8_t column_index) const;

    // Breite des Zeichens in Pixel
    const uint8_t width() const {return char_width;}

    // Höhe des Zeichens in Pixel
    const uint8_t height() const {return 8;}

    // []-Operator
    const ColumnBitmap operator[](const uint8_t column_index) const {return get_column_bitmap(column_index);}   


private:

    const uint8_t* char_bitmap;
    uint8_t char_width;
        
};


// Klasse regelt zugriff auf PROGMEM-Speicher
class FontBitmap
{

public:

    // Konstruktor
    FontBitmap(const String Text = String(""));

    // Kopierkonstruktor
    FontBitmap(const FontBitmap& other);

    // Zuweisungsoperator
    void operator=(const FontBitmap& other);

    // uint8_t get_column_bitmap(char character_index, uint8_t column_index) const;
    // uint8_t get_char_width(char character_index) const;

    // Länge eines Textes in Pixeln berechnen
    static const uint32_t length_of(const String text, const uint8_t space_between_characters = 1);

    // char_bitmap aus PRGOMEM-Speicher holen
    static const CharBitmap get_char_bitmap(const char character_index);

    // char_bitmap aus PRGOMEM-Speicher holen
    const CharBitmap get_char_bitmap_by_index(const uint32_t index) const { return get_char_bitmap(this->text.charAt(index));}

    // char_bitmap aus PRGOMEM-Speicher holen
    static const CharBitmap of(const char character_index) { return get_char_bitmap(character_index);}

    // char_bitmap aus PRGOMEM-Speicher holen
    static const FontBitmap of(const String text) { return FontBitmap(text);}

    // Länge eines Textes in Pixeln berechnen
    const uint32_t length(const uint8_t space_between_characters = 1) const { return length_of(this->text, space_between_characters);}

    // []-Operator überladen
    const CharBitmap operator[](const char character_index) const {return get_char_bitmap(character_index);}
    const CharBitmap operator[](const uint32_t index) const {return get_char_bitmap_by_index(index);}

private:
    String text;

}; 

// ein konstantes Objekt, 
// um mit der Klasse arbeiten zu können
// ohne vorher ein extra Objekt angelegt zu haben.
const FontBitmap font_bitmap;

/*
theoretisch ist es jetzt möglich mit 
    Font::font_bitmap[character][column_index][row_index] (!!! Index Reihnefolge beachten, anders als bei Matrix) 
auf die einzelnen Bits zuzugreifen.
z.B Font::font_bitmap['A'][2][3] ist das Bit in der 3. Reihe und 2. Spalte (von Null gezählt) des Buchstaben 'A'.

allerdings ist es ineffizient mit einer doppelten for-Schleife über das 2D-Array zu iterieren...
    
    for(int i = 0; i < Font::font_bitmap['A'].height(); ++i) {
        
        for(int j = 0; j < Font::font_bitmap['A'].width(); ++j) {
        
            if(Font::font_bitmap['A'][j][i]) {
                mat.pixel(i, j) = color;
            }
            else {
                mat.pixel(i, j) = background;
            }
        }
    }

...da mit jedem Schleifendurchlauf die Werten neu aus dem Flash-Speicher gelesen werde müssen.
Besser ist, Werte zwischenzuspeichern

    // Zeiger auf Buchstabenbitmap laden und zwischenspeichern
    const Font::CharBitmap char_bitmap(Font::font_bitmap['A']);
    
    // jetzt erste for-Schleife
    for(int j = 0; j < char_bitmap.width(); ++j) {
        
        // Wert für Spaltenbitmap aus Flash-Speicher laden
        const Font::ColumnBitmap column_bitmap(char_bitmap[j]);

        // jetzt zweite for-Schleife
        for(int i = 0; i < char_bitmap.height(); ++i) {
            
            if(column_bitmap[i]) {
                mat.pixel(i, j) = color;
            }
            else {
                mat.pixel(i, j) = background;
            }
        }
    }

*/
        



// Zum Testen ob korrekt aus dem PROGMEM-Speicher gelesen wird                // 127 
void test_PROGMEM_access(const char start_char = '\0', const char stop_char = '\x7f');









} // Ende Font namespace

} // Ende LEDArrangement namespace

# endif // FONTBITMAP_H