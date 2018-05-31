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








enum Emoji
{

    Smilie      = (char) 192,
    Sad_Smilie  = (char) 193,
    Heart       = (char) 194,
    Y           = (char) 195,
    X           = (char) 196,
    Attention   = (char) 197,
    Nr_06       = (char) 198,
    Nr_07       = (char) 199,
    Nr_08       = (char) 200,
    Nr_09       = (char) 201,
    Nr_10       = (char) 202,
    Nr_11       = (char) 203,
    Nr_12       = (char) 204,
    Nr_13       = (char) 205,
    Nr_14       = (char) 206,
    Nr_15       = (char) 207,
    Nr_16       = (char) 208,
    Nr_17       = (char) 209,
    Nr_18       = (char) 210,
    Nr_19       = (char) 211,
    Nr_20       = (char) 212,
    Nr_21       = (char) 213,
    Nr_22       = (char) 214,
    Nr_23       = (char) 215,
    Nr_24       = (char) 216,
    Nr_25       = (char) 217,
    Nr_26       = (char) 218,
    Nr_27       = (char) 219,
    Nr_28       = (char) 220,
    Nr_29       = (char) 221,
    Nr_30       = (char) 222,
    Nr_31       = (char) 223,
    Nr_32       = (char) 224,
    Nr_33       = (char) 225,
    Nr_34       = (char) 226,
    Nr_35       = (char) 227,
    Nr_36       = (char) 228,
    Nr_37       = (char) 229,
    Nr_38       = (char) 230,
    Nr_39       = (char) 231,
    Nr_40       = (char) 232,
    Nr_41       = (char) 233,
    Nr_42       = (char) 234,
    Nr_43       = (char) 235,
    Nr_44       = (char) 236,
    Nr_45       = (char) 237,
    Nr_46       = (char) 238,
    Nr_47       = (char) 239,
    Nr_48       = (char) 240,
    Nr_49       = (char) 241,
    Nr_50       = (char) 242,
    Nr_51       = (char) 243,
    Nr_52       = (char) 244,
    Nr_53       = (char) 245,
    Nr_54       = (char) 246,
    Nr_55       = (char) 247,
    Nr_56       = (char) 248,
    Nr_57       = (char) 249,
    Nr_58       = (char) 250,
    Nr_59       = (char) 251,
    Nr_60       = (char) 252,
    Nr_61       = (char) 253,
    Nr_62       = (char) 254,
    Nr_63       = (char) 255

}; // end enum Emoji


// Zum Testen ob korrekt aus dem PROGMEM-Speicher gelesen wird                // 127 
void test_PROGMEM_access(const char start_char = '\0', const char stop_char = '\x7f');









} // Ende Font namespace

} // Ende LEDArrangement namespace

# endif // FONTBITMAP_H