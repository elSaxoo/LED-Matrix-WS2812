#include "FontBitmap.h"

namespace LEDArrangement
{


namespace Font
{


// Die einzelnen Bitmaps
const PROGMEM uint8_t char_bitmap_000[] = {0x36, 0x41, 0x41, 0x36};          // 7-Segment 0
const PROGMEM uint8_t char_bitmap_001[] = {0x36};                            // 7-Segment 1
const PROGMEM uint8_t char_bitmap_002[] = {0x30, 0x49, 0x49, 0x06};          // 7-Segment 2
const PROGMEM uint8_t char_bitmap_003[] = {0x49, 0x49, 0x36};                // 7-Segment 3
const PROGMEM uint8_t char_bitmap_004[] = {0x06, 0x08, 0x08, 0x36};          // 7-Segment 4
const PROGMEM uint8_t char_bitmap_005[] = {0x06, 0x49, 0x49, 0x30};          // 7-Segment 5
const PROGMEM uint8_t char_bitmap_006[] = {0x36, 0x49, 0x49, 0x30, 0x40};    // 7-Segment 6
const PROGMEM uint8_t char_bitmap_007[] = {0x01, 0x01, 0x036};               // 7-Segment 7
const PROGMEM uint8_t char_bitmap_008[] = {0x36, 0x49, 0x49, 0x36};          // 7-Segment 8
const PROGMEM uint8_t char_bitmap_009[] = {0x06, 0x49, 0x49, 0x36, 0x40};    // 7-Segment 9
const PROGMEM uint8_t char_bitmap_010[] = {0x36, 0x09, 0x09, 0x36};          // 7-Segment A
const PROGMEM uint8_t char_bitmap_011[] = {0x36, 0x48, 0x48, 0x30};          // 7-Segment B
const PROGMEM uint8_t char_bitmap_012[] = {0x36, 0x41, 0x41};                // 7-Segment C
const PROGMEM uint8_t char_bitmap_013[] = {0x30, 0x48, 0x48, 0x36};          // 7-Segment D
const PROGMEM uint8_t char_bitmap_014[] = {0x36, 0x49, 0x49};                // 7-Segment E
const PROGMEM uint8_t char_bitmap_015[] = {0x36, 0x09, 0x09};                // 7-Segment F
const PROGMEM uint8_t char_bitmap_016[] = {0x00, 0x00, 0x00, 0x00, 0x00};   
const PROGMEM uint8_t char_bitmap_017[] = {0x00, 0x00, 0x00, 0x00, 0x00};   
const PROGMEM uint8_t char_bitmap_018[] = {0x00, 0x00, 0x00, 0x00, 0x00};   
const PROGMEM uint8_t char_bitmap_019[] = {0x00, 0x00, 0x00, 0x00, 0x00};   
const PROGMEM uint8_t char_bitmap_020[] = {0x00, 0x00, 0x00, 0x00, 0x00};   
const PROGMEM uint8_t char_bitmap_021[] = {0x00, 0x00, 0x00, 0x00, 0x00};   
const PROGMEM uint8_t char_bitmap_022[] = {0x00, 0x00, 0x00, 0x00, 0x00};   
const PROGMEM uint8_t char_bitmap_023[] = {0x00, 0x00, 0x00, 0x00, 0x00};   
const PROGMEM uint8_t char_bitmap_024[] = {0x00, 0x00, 0x00, 0x00, 0x00};   
const PROGMEM uint8_t char_bitmap_025[] = {0x00, 0x00, 0x00, 0x00, 0x00};   
const PROGMEM uint8_t char_bitmap_026[] = {0x00, 0x00, 0x00, 0x00, 0x00};   
const PROGMEM uint8_t char_bitmap_027[] = {0x00, 0x00, 0x00, 0x00, 0x00};   
const PROGMEM uint8_t char_bitmap_028[] = {0x00, 0x00, 0x00, 0x00, 0x00};   
const PROGMEM uint8_t char_bitmap_029[] = {0x00, 0x00, 0x00, 0x00, 0x00};   
const PROGMEM uint8_t char_bitmap_030[] = {0x00, 0x00, 0x00, 0x00, 0x00};   
const PROGMEM uint8_t char_bitmap_031[] = {0x00, 0x00, 0x00, 0x00, 0x00};   
const PROGMEM uint8_t char_bitmap_032[] = {0x00, 0x00, 0x00, 0x00, 0x00};    // SPACE
const PROGMEM uint8_t char_bitmap_033[] = {0x4F};                            // !
const PROGMEM uint8_t char_bitmap_034[] = {0x07, 0x00, 0x07};                // "
const PROGMEM uint8_t char_bitmap_035[] = {0x14, 0x7F, 0x14, 0x7F, 0x14};    // #
const PROGMEM uint8_t char_bitmap_036[] = {0x24, 0x2A, 0x7F, 0x2A, 0x12};    // $
const PROGMEM uint8_t char_bitmap_037[] = {0x23, 0x13, 0x08, 0x64, 0x62};    // %
const PROGMEM uint8_t char_bitmap_038[] = {0x36, 0x49, 0x55, 0x22, 0x50};    // &
const PROGMEM uint8_t char_bitmap_039[] = {0x05, 0x03};                      // '
const PROGMEM uint8_t char_bitmap_040[] = {0x1C, 0x22, 0x41};                // (
const PROGMEM uint8_t char_bitmap_041[] = {0x41, 0x22, 0x1C};                // )
const PROGMEM uint8_t char_bitmap_042[] = {0x14, 0x08, 0x3E, 0x08, 0x14};    // *
const PROGMEM uint8_t char_bitmap_043[] = {0x08, 0x08, 0x3E, 0x08, 0x08};    // +
const PROGMEM uint8_t char_bitmap_044[] = {0x50, 0x30};                      // ,
const PROGMEM uint8_t char_bitmap_045[] = {0x08, 0x08, 0x08, 0x08, 0x08};    // -
const PROGMEM uint8_t char_bitmap_046[] = {0x60, 0x60};                      // .
const PROGMEM uint8_t char_bitmap_047[] = {0x20, 0x10, 0x08, 0x04, 0x02};    // /
const PROGMEM uint8_t char_bitmap_048[] = {0x3E, 0x51, 0x49, 0x45, 0x3E};    // 0
const PROGMEM uint8_t char_bitmap_049[] = {0x42, 0x7F, 0x40};                // 1
const PROGMEM uint8_t char_bitmap_050[] = {0x42, 0x61, 0x51, 0x49, 0x46};    // 2
const PROGMEM uint8_t char_bitmap_051[] = {0x21, 0x41, 0x45, 0x4B, 0x31};    // 3
const PROGMEM uint8_t char_bitmap_052[] = {0x18, 0x14, 0x12, 0x7F, 0x10};    // 4
const PROGMEM uint8_t char_bitmap_053[] = {0x27, 0x45, 0x45, 0x45, 0x39};    // 5
const PROGMEM uint8_t char_bitmap_054[] = {0x3C, 0x4A, 0x49, 0x49, 0x30};    // 6
const PROGMEM uint8_t char_bitmap_055[] = {0x01, 0x71, 0x09, 0x05, 0x03};    // 7
const PROGMEM uint8_t char_bitmap_056[] = {0x36, 0x49, 0x49, 0x49, 0x36};    // 8
const PROGMEM uint8_t char_bitmap_057[] = {0x06, 0x49, 0x49, 0x29, 0x1E};    // 9
const PROGMEM uint8_t char_bitmap_058[] = {0x36, 0x36};                      // :
const PROGMEM uint8_t char_bitmap_059[] = {0x56, 0x36};                      // ;
const PROGMEM uint8_t char_bitmap_060[] = {0x08, 0x14, 0x22, 0x41};          // <
const PROGMEM uint8_t char_bitmap_061[] = {0x14, 0x14, 0x14, 0x14, 0x14};    // =
const PROGMEM uint8_t char_bitmap_062[] = {0x41, 0x22, 0x14, 0x08};          // >
const PROGMEM uint8_t char_bitmap_063[] = {0x02, 0x01, 0x51, 0x09, 0x06};    // ?
const PROGMEM uint8_t char_bitmap_064[] = {0x30, 0x49, 0x79, 0x41, 0x3E};    // @
const PROGMEM uint8_t char_bitmap_065[] = {0x7E, 0x11, 0x11, 0x11, 0x7E};    // A
const PROGMEM uint8_t char_bitmap_066[] = {0x7F, 0x49, 0x49, 0x49, 0x36};    // B
const PROGMEM uint8_t char_bitmap_067[] = {0x3E, 0x41, 0x41, 0x41, 0x22};    // C
const PROGMEM uint8_t char_bitmap_068[] = {0x7F, 0x41, 0x41, 0x22, 0x1C};    // D
const PROGMEM uint8_t char_bitmap_069[] = {0x7F, 0x49, 0x49, 0x49, 0x41};    // E
const PROGMEM uint8_t char_bitmap_070[] = {0x7F, 0x09, 0x09, 0x09, 0x01};    // F
const PROGMEM uint8_t char_bitmap_071[] = {0x3E, 0x41, 0x49, 0x49, 0x7A};    // G
const PROGMEM uint8_t char_bitmap_072[] = {0x7F, 0x08, 0x08, 0x08, 0x7F};    // H
const PROGMEM uint8_t char_bitmap_073[] = {0x41, 0x7F, 0x41};                // I
const PROGMEM uint8_t char_bitmap_074[] = {0x20, 0x40, 0x41, 0x3F, 0x01};    // J
const PROGMEM uint8_t char_bitmap_075[] = {0x7F, 0x08, 0x14, 0x22, 0x41};    // K
const PROGMEM uint8_t char_bitmap_076[] = {0x7F, 0x40, 0x40, 0x40, 0x40};    // L
const PROGMEM uint8_t char_bitmap_077[] = {0x7F, 0x02, 0x0C, 0x02, 0x7F};    // M
const PROGMEM uint8_t char_bitmap_078[] = {0x7F, 0x04, 0x08, 0x10, 0x7F};    // N
const PROGMEM uint8_t char_bitmap_079[] = {0x3E, 0x41, 0x41, 0x41, 0x3E};    // O
const PROGMEM uint8_t char_bitmap_080[] = {0x7F, 0x09, 0x09, 0x09, 0x06};    // P
const PROGMEM uint8_t char_bitmap_081[] = {0x3E, 0x41, 0x51, 0x21, 0x5E};    // Q
const PROGMEM uint8_t char_bitmap_082[] = {0x7F, 0x09, 0x19, 0x29, 0x46};    // R
const PROGMEM uint8_t char_bitmap_083[] = {0x46, 0x49, 0x49, 0x49, 0x31};    // S
const PROGMEM uint8_t char_bitmap_084[] = {0x01, 0x01, 0x7F, 0x01, 0x01};    // T
const PROGMEM uint8_t char_bitmap_085[] = {0x3F, 0x40, 0x40, 0x40, 0x3F};    // U
const PROGMEM uint8_t char_bitmap_086[] = {0x1F, 0x20, 0x40, 0x20, 0x1F};    // V
const PROGMEM uint8_t char_bitmap_087[] = {0x3F, 0x40, 0x30, 0x40, 0x3F};    // W
const PROGMEM uint8_t char_bitmap_088[] = {0x63, 0x14, 0x08, 0x14, 0x63};    // X
const PROGMEM uint8_t char_bitmap_089[] = {0x07, 0x08, 0x70, 0x08, 0x07};    // Y
const PROGMEM uint8_t char_bitmap_090[] = {0x61, 0x51, 0x49, 0x45, 0x43};    // Z
const PROGMEM uint8_t char_bitmap_091[] = {0x7F, 0x41, 0x41};                // [
const PROGMEM uint8_t char_bitmap_092[] = {0x02, 0x04, 0x08, 0x10, 0x20};    // backslash
const PROGMEM uint8_t char_bitmap_093[] = {0x41, 0x41, 0x7F};                // ]
const PROGMEM uint8_t char_bitmap_094[] = {0x04, 0x02, 0x01, 0x02, 0x04};    // ^
const PROGMEM uint8_t char_bitmap_095[] = {0x40, 0x40, 0x40, 0x40, 0x40};    // _
const PROGMEM uint8_t char_bitmap_096[] = {0x01, 0x02, 0x04};                // `
const PROGMEM uint8_t char_bitmap_097[] = {0x20, 0x54, 0x54, 0x54, 0x78};    // a
const PROGMEM uint8_t char_bitmap_098[] = {0x7F, 0x50, 0x48, 0x48, 0x30};    // b
const PROGMEM uint8_t char_bitmap_099[] = {0x38, 0x44, 0x44, 0x44, 0x20};    // c
const PROGMEM uint8_t char_bitmap_100[] = {0x38, 0x44, 0x44, 0x48, 0x7F};    // d
const PROGMEM uint8_t char_bitmap_101[] = {0x38, 0x54, 0x54, 0x54, 0x18};    // e
const PROGMEM uint8_t char_bitmap_102[] = {0x08, 0x7E, 0x09, 0x01, 0x02};    // f
const PROGMEM uint8_t char_bitmap_103[] = {0x0C, 0x52, 0x52, 0x52, 0x3E};    // g
const PROGMEM uint8_t char_bitmap_104[] = {0x7F, 0x08, 0x04, 0x04, 0x78};    // h
const PROGMEM uint8_t char_bitmap_105[] = {0x44, 0x7D, 0x40};                // i
const PROGMEM uint8_t char_bitmap_106[] = {0x20, 0x40, 0x44, 0x3D};          // j
const PROGMEM uint8_t char_bitmap_107[] = {0x7F, 0x10, 0x28, 0x44};          // k
const PROGMEM uint8_t char_bitmap_108[] = {0x41, 0x7F, 0x40};                // l
const PROGMEM uint8_t char_bitmap_109[] = {0x78, 0x04, 0x58, 0x04, 0x78};    // m
const PROGMEM uint8_t char_bitmap_110[] = {0x7C, 0x08, 0x04, 0x04, 0x78};    // n
const PROGMEM uint8_t char_bitmap_111[] = {0x38, 0x44, 0x44, 0x44, 0x38};    // o
const PROGMEM uint8_t char_bitmap_112[] = {0x7C, 0x14, 0x14, 0x14, 0x08};    // p
const PROGMEM uint8_t char_bitmap_113[] = {0x08, 0x14, 0x14, 0x18, 0x7C};    // q
const PROGMEM uint8_t char_bitmap_114[] = {0x7C, 0x08, 0x04, 0x04, 0x08};    // r
const PROGMEM uint8_t char_bitmap_115[] = {0x48, 0x54, 0x54, 0x54, 0x20};    // s
const PROGMEM uint8_t char_bitmap_116[] = {0x04, 0x3F, 0x44, 0x40, 0x20};    // t
const PROGMEM uint8_t char_bitmap_117[] = {0x3C, 0x40, 0x40, 0x20, 0x7C};    // u
const PROGMEM uint8_t char_bitmap_118[] = {0x1C, 0x20, 0x40, 0x20, 0x1C};    // v
const PROGMEM uint8_t char_bitmap_119[] = {0x3C, 0x40, 0x30, 0x40, 0x3C};    // w
const PROGMEM uint8_t char_bitmap_120[] = {0x44, 0x28, 0x10, 0x28, 0x44};    // x
const PROGMEM uint8_t char_bitmap_121[] = {0x0C, 0x50, 0x50, 0x50, 0x3C};    // y
const PROGMEM uint8_t char_bitmap_122[] = {0x44, 0x64, 0x54, 0x4C, 0x44};    // z
const PROGMEM uint8_t char_bitmap_123[] = {0x08, 0x36, 0x41};                // {
const PROGMEM uint8_t char_bitmap_124[] = {0x7F};                            // |
const PROGMEM uint8_t char_bitmap_125[] = {0x41, 0x36, 0x080};               // }
const PROGMEM uint8_t char_bitmap_126[] = {0x0C, 0x02, 0x0C, 0x10, 0x0C};    // ~
const PROGMEM uint8_t char_bitmap_127[] = {0x00, 0x00, 0x00, 0x00, 0x00};    // DEL

// 128 bis 191 Sonderzeichen
const PROGMEM uint8_t char_bitmap_128[] = {};
const PROGMEM uint8_t char_bitmap_129[] = {};
const PROGMEM uint8_t char_bitmap_130[] = {};
const PROGMEM uint8_t char_bitmap_131[] = {};
const PROGMEM uint8_t char_bitmap_132[] = {};
const PROGMEM uint8_t char_bitmap_133[] = {};
const PROGMEM uint8_t char_bitmap_134[] = {};
const PROGMEM uint8_t char_bitmap_135[] = {};
const PROGMEM uint8_t char_bitmap_136[] = {};
const PROGMEM uint8_t char_bitmap_137[] = {};
const PROGMEM uint8_t char_bitmap_138[] = {};
const PROGMEM uint8_t char_bitmap_139[] = {};
const PROGMEM uint8_t char_bitmap_140[] = {};
const PROGMEM uint8_t char_bitmap_141[] = {};
const PROGMEM uint8_t char_bitmap_142[] = {};
const PROGMEM uint8_t char_bitmap_143[] = {};
const PROGMEM uint8_t char_bitmap_144[] = {};
const PROGMEM uint8_t char_bitmap_145[] = {};
const PROGMEM uint8_t char_bitmap_146[] = {};
const PROGMEM uint8_t char_bitmap_147[] = {};
const PROGMEM uint8_t char_bitmap_148[] = {};
const PROGMEM uint8_t char_bitmap_149[] = {};
const PROGMEM uint8_t char_bitmap_150[] = {};
const PROGMEM uint8_t char_bitmap_151[] = {};
const PROGMEM uint8_t char_bitmap_152[] = {};
const PROGMEM uint8_t char_bitmap_153[] = {};
const PROGMEM uint8_t char_bitmap_154[] = {};
const PROGMEM uint8_t char_bitmap_155[] = {};
const PROGMEM uint8_t char_bitmap_156[] = {};
const PROGMEM uint8_t char_bitmap_157[] = {};
const PROGMEM uint8_t char_bitmap_158[] = {};
const PROGMEM uint8_t char_bitmap_159[] = {};
const PROGMEM uint8_t char_bitmap_160[] = {};
const PROGMEM uint8_t char_bitmap_161[] = {};
const PROGMEM uint8_t char_bitmap_162[] = {};
const PROGMEM uint8_t char_bitmap_163[] = {};
const PROGMEM uint8_t char_bitmap_164[] = {};
const PROGMEM uint8_t char_bitmap_165[] = {};
const PROGMEM uint8_t char_bitmap_166[] = {};
const PROGMEM uint8_t char_bitmap_167[] = {};
const PROGMEM uint8_t char_bitmap_168[] = {};
const PROGMEM uint8_t char_bitmap_169[] = {};
const PROGMEM uint8_t char_bitmap_170[] = {};
const PROGMEM uint8_t char_bitmap_171[] = {};
const PROGMEM uint8_t char_bitmap_172[] = {};
const PROGMEM uint8_t char_bitmap_173[] = {};
const PROGMEM uint8_t char_bitmap_174[] = {};
const PROGMEM uint8_t char_bitmap_175[] = {};
const PROGMEM uint8_t char_bitmap_176[] = {};
const PROGMEM uint8_t char_bitmap_177[] = {};
const PROGMEM uint8_t char_bitmap_178[] = {};
const PROGMEM uint8_t char_bitmap_179[] = {};
const PROGMEM uint8_t char_bitmap_180[] = {};
const PROGMEM uint8_t char_bitmap_181[] = {};
const PROGMEM uint8_t char_bitmap_182[] = {};
const PROGMEM uint8_t char_bitmap_183[] = {};
const PROGMEM uint8_t char_bitmap_184[] = {};
const PROGMEM uint8_t char_bitmap_185[] = {};
const PROGMEM uint8_t char_bitmap_186[] = {};
const PROGMEM uint8_t char_bitmap_187[] = {};
const PROGMEM uint8_t char_bitmap_188[] = {};
const PROGMEM uint8_t char_bitmap_189[] = {};
const PROGMEM uint8_t char_bitmap_190[] = {};
const PROGMEM uint8_t char_bitmap_191[] = {};

// 192 bis 255 Emoji
const PROGMEM uint8_t char_bitmap_192[] = {0x26, 0x46, 0x58, 0x46, 0x26}; // Smilie
const PROGMEM uint8_t char_bitmap_193[] = {0x46, 0x26, 0x38, 0x26, 0x46}; // Sad Smilie
const PROGMEM uint8_t char_bitmap_194[] = {0x0C, 0x12, 0x24, 0x12,0x0C}; // Heart
const PROGMEM uint8_t char_bitmap_195[] = {0x18, 0x30, 0x18, 0x0c, 0x06}; // y
const PROGMEM uint8_t char_bitmap_196[] = {0x41, 0x36, 0x08, 0x36, 0x41}; // X
const PROGMEM uint8_t char_bitmap_197[] = {0x03, 0x67, 0x6F, 0x67, 0x03}; // !
const PROGMEM uint8_t char_bitmap_198[] = {};
const PROGMEM uint8_t char_bitmap_199[] = {};
const PROGMEM uint8_t char_bitmap_200[] = {};
const PROGMEM uint8_t char_bitmap_201[] = {};
const PROGMEM uint8_t char_bitmap_202[] = {};
const PROGMEM uint8_t char_bitmap_203[] = {};
const PROGMEM uint8_t char_bitmap_204[] = {};
const PROGMEM uint8_t char_bitmap_205[] = {};
const PROGMEM uint8_t char_bitmap_206[] = {};
const PROGMEM uint8_t char_bitmap_207[] = {};
const PROGMEM uint8_t char_bitmap_208[] = {};
const PROGMEM uint8_t char_bitmap_209[] = {};
const PROGMEM uint8_t char_bitmap_210[] = {};
const PROGMEM uint8_t char_bitmap_211[] = {};
const PROGMEM uint8_t char_bitmap_212[] = {};
const PROGMEM uint8_t char_bitmap_213[] = {};
const PROGMEM uint8_t char_bitmap_214[] = {};
const PROGMEM uint8_t char_bitmap_215[] = {};
const PROGMEM uint8_t char_bitmap_216[] = {};
const PROGMEM uint8_t char_bitmap_217[] = {};
const PROGMEM uint8_t char_bitmap_218[] = {};
const PROGMEM uint8_t char_bitmap_219[] = {};
const PROGMEM uint8_t char_bitmap_220[] = {};
const PROGMEM uint8_t char_bitmap_221[] = {};
const PROGMEM uint8_t char_bitmap_222[] = {};
const PROGMEM uint8_t char_bitmap_223[] = {};
const PROGMEM uint8_t char_bitmap_224[] = {};
const PROGMEM uint8_t char_bitmap_225[] = {};
const PROGMEM uint8_t char_bitmap_226[] = {};
const PROGMEM uint8_t char_bitmap_227[] = {};
const PROGMEM uint8_t char_bitmap_228[] = {};
const PROGMEM uint8_t char_bitmap_229[] = {};
const PROGMEM uint8_t char_bitmap_230[] = {};
const PROGMEM uint8_t char_bitmap_231[] = {};
const PROGMEM uint8_t char_bitmap_232[] = {};
const PROGMEM uint8_t char_bitmap_233[] = {};
const PROGMEM uint8_t char_bitmap_234[] = {};
const PROGMEM uint8_t char_bitmap_235[] = {};
const PROGMEM uint8_t char_bitmap_236[] = {};
const PROGMEM uint8_t char_bitmap_237[] = {};
const PROGMEM uint8_t char_bitmap_238[] = {};
const PROGMEM uint8_t char_bitmap_239[] = {};
const PROGMEM uint8_t char_bitmap_240[] = {};
const PROGMEM uint8_t char_bitmap_241[] = {};
const PROGMEM uint8_t char_bitmap_242[] = {};
const PROGMEM uint8_t char_bitmap_243[] = {};
const PROGMEM uint8_t char_bitmap_244[] = {};
const PROGMEM uint8_t char_bitmap_245[] = {};
const PROGMEM uint8_t char_bitmap_246[] = {};
const PROGMEM uint8_t char_bitmap_247[] = {};
const PROGMEM uint8_t char_bitmap_248[] = {};
const PROGMEM uint8_t char_bitmap_249[] = {};
const PROGMEM uint8_t char_bitmap_250[] = {};
const PROGMEM uint8_t char_bitmap_251[] = {};
const PROGMEM uint8_t char_bitmap_252[] = {};
const PROGMEM uint8_t char_bitmap_253[] = {};
const PROGMEM uint8_t char_bitmap_254[] = {};
const PROGMEM uint8_t char_bitmap_255[] = {};




// Array mit Länge der Zeichen
const PROGMEM uint8_t char_width_array[] = {

//  0 bis 127
//  0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    4, 1, 4, 3, 4, 4, 5, 3, 4, 5,   // 0
    4, 4, 3, 4, 3, 3, 5, 5, 5, 5,   // 1
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5,   // 2
    5, 5, 2, 1, 3, 5, 5, 5, 5, 2,   // 3
    3, 3, 5, 5, 2, 5, 2, 5, 5, 3,   // 4
    5, 5, 5, 5, 5, 5, 5, 5, 2, 2,   // 5
    4, 5, 4, 5, 5, 5, 5, 5, 5, 5,   // 6
    5, 5, 5, 3, 5, 5, 5, 5, 5, 5,   // 7
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5,   // 8
    5, 3, 5, 3, 5, 5, 3, 5, 5, 5,   // 9
    5, 5, 5, 5, 5, 3, 4, 4, 3, 5,   // 10
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5,   // 11
    5, 5, 5, 3, 1, 3, 5, 5,         // 12

//  128 bis 191 Sonderzeichen
//  0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                            0, 0,   // 12   
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // 13
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // 14
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // 15
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // 16
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // 17
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // 18
    0, 0,                           // 19
    
//  192 bis 255 Emoji
//  0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
          5, 5, 5, 5, 5, 5, 0, 0,   // 19
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // 20
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // 21
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // 22
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // 23
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // 24
    0, 0, 0, 0, 0, 0                // 25

};


// PROGMEM Macro plaziert Array in ROM-Speicher
const PROGMEM uint8_t* const font_bitmap_array[] = {

    char_bitmap_000,
    char_bitmap_001,
    char_bitmap_002,
    char_bitmap_003,
    char_bitmap_004,
    char_bitmap_005,
    char_bitmap_006,
    char_bitmap_007,
    char_bitmap_008,
    char_bitmap_009,
    char_bitmap_010,
    char_bitmap_011,
    char_bitmap_012,
    char_bitmap_013,
    char_bitmap_014,
    char_bitmap_015,
    char_bitmap_016,
    char_bitmap_017,
    char_bitmap_018,
    char_bitmap_019,
    char_bitmap_020,
    char_bitmap_021,
    char_bitmap_022,
    char_bitmap_023,
    char_bitmap_024,
    char_bitmap_025,
    char_bitmap_026,
    char_bitmap_027,
    char_bitmap_028,
    char_bitmap_029,
    char_bitmap_030,
    char_bitmap_031,
    char_bitmap_032,
    char_bitmap_033,
    char_bitmap_034,
    char_bitmap_035,
    char_bitmap_036,
    char_bitmap_037,
    char_bitmap_038,
    char_bitmap_039,
    char_bitmap_040,
    char_bitmap_041,
    char_bitmap_042,
    char_bitmap_043,
    char_bitmap_044,
    char_bitmap_045,
    char_bitmap_046,
    char_bitmap_047,
    char_bitmap_048,
    char_bitmap_049,
    char_bitmap_050,
    char_bitmap_051,
    char_bitmap_052,
    char_bitmap_053,
    char_bitmap_054,
    char_bitmap_055,
    char_bitmap_056,
    char_bitmap_057,
    char_bitmap_058,
    char_bitmap_059,
    char_bitmap_060,
    char_bitmap_061,
    char_bitmap_062,
    char_bitmap_063,
    char_bitmap_064,
    char_bitmap_065,
    char_bitmap_066,
    char_bitmap_067,
    char_bitmap_068,
    char_bitmap_069,
    char_bitmap_070,
    char_bitmap_071,
    char_bitmap_072,
    char_bitmap_073,
    char_bitmap_074,
    char_bitmap_075,
    char_bitmap_076,
    char_bitmap_077,
    char_bitmap_078,
    char_bitmap_079,
    char_bitmap_080,
    char_bitmap_081,
    char_bitmap_082,
    char_bitmap_083,
    char_bitmap_084,
    char_bitmap_085,
    char_bitmap_086,
    char_bitmap_087,
    char_bitmap_088,
    char_bitmap_089,
    char_bitmap_090,
    char_bitmap_091,
    char_bitmap_092,
    char_bitmap_093,
    char_bitmap_094,
    char_bitmap_095,
    char_bitmap_096,
    char_bitmap_097,
    char_bitmap_098,
    char_bitmap_099,
    char_bitmap_100,
    char_bitmap_101,
    char_bitmap_102,
    char_bitmap_103,
    char_bitmap_104,
    char_bitmap_105,
    char_bitmap_106,
    char_bitmap_107,
    char_bitmap_108,
    char_bitmap_109,
    char_bitmap_110,
    char_bitmap_111,
    char_bitmap_112,
    char_bitmap_113,
    char_bitmap_114,
    char_bitmap_115,
    char_bitmap_116,
    char_bitmap_117,
    char_bitmap_118,
    char_bitmap_119,
    char_bitmap_120,
    char_bitmap_121,
    char_bitmap_122,
    char_bitmap_123,
    char_bitmap_124,
    char_bitmap_125,
    char_bitmap_126,
    char_bitmap_127,
    char_bitmap_128,
    char_bitmap_129,
    char_bitmap_130,
    char_bitmap_131,
    char_bitmap_132,
    char_bitmap_133,
    char_bitmap_134,
    char_bitmap_135,
    char_bitmap_136,
    char_bitmap_137,
    char_bitmap_138,
    char_bitmap_139,
    char_bitmap_140,
    char_bitmap_141,
    char_bitmap_142,
    char_bitmap_143,
    char_bitmap_144,
    char_bitmap_145,
    char_bitmap_146,
    char_bitmap_147,
    char_bitmap_148,
    char_bitmap_149,
    char_bitmap_150,
    char_bitmap_151,
    char_bitmap_152,
    char_bitmap_153,
    char_bitmap_154,
    char_bitmap_155,
    char_bitmap_156,
    char_bitmap_157,
    char_bitmap_158,
    char_bitmap_159,
    char_bitmap_160,
    char_bitmap_161,
    char_bitmap_162,
    char_bitmap_163,
    char_bitmap_164,
    char_bitmap_165,
    char_bitmap_166,
    char_bitmap_167,
    char_bitmap_168,
    char_bitmap_169,
    char_bitmap_170,
    char_bitmap_171,
    char_bitmap_172,
    char_bitmap_173,
    char_bitmap_174,
    char_bitmap_175,
    char_bitmap_176,
    char_bitmap_177,
    char_bitmap_178,
    char_bitmap_179,
    char_bitmap_180,
    char_bitmap_181,
    char_bitmap_182,
    char_bitmap_183,
    char_bitmap_184,
    char_bitmap_185,
    char_bitmap_186,
    char_bitmap_187,
    char_bitmap_188,
    char_bitmap_189,
    char_bitmap_190,
    char_bitmap_191,
    char_bitmap_192,
    char_bitmap_193,
    char_bitmap_194,
    char_bitmap_195,
    char_bitmap_196,
    char_bitmap_197,
    char_bitmap_198,
    char_bitmap_199,
    char_bitmap_200,
    char_bitmap_201,
    char_bitmap_202,
    char_bitmap_203,
    char_bitmap_204,
    char_bitmap_205,
    char_bitmap_206,
    char_bitmap_207,
    char_bitmap_208,
    char_bitmap_209,
    char_bitmap_210,
    char_bitmap_211,
    char_bitmap_212,
    char_bitmap_213,
    char_bitmap_214,
    char_bitmap_215,
    char_bitmap_216,
    char_bitmap_217,
    char_bitmap_218,
    char_bitmap_219,
    char_bitmap_220,
    char_bitmap_221,
    char_bitmap_222,
    char_bitmap_223,
    char_bitmap_224,
    char_bitmap_225,
    char_bitmap_226,
    char_bitmap_227,
    char_bitmap_228,
    char_bitmap_229,
    char_bitmap_230,
    char_bitmap_231,
    char_bitmap_232,
    char_bitmap_233,
    char_bitmap_234,
    char_bitmap_235,
    char_bitmap_236,
    char_bitmap_237,
    char_bitmap_238,
    char_bitmap_239,
    char_bitmap_240,
    char_bitmap_241,
    char_bitmap_242,
    char_bitmap_243,
    char_bitmap_244,
    char_bitmap_245,
    char_bitmap_246,
    char_bitmap_247,
    char_bitmap_248,
    char_bitmap_249,
    char_bitmap_250,
    char_bitmap_251,
    char_bitmap_252,
    char_bitmap_253,
    char_bitmap_254,
    char_bitmap_255

};




// ------- ColumnBitmap -------

// Konstruktor
ColumnBitmap::ColumnBitmap(const uint8_t Column_bitmap)
:
    column_bitmap(Column_bitmap)
{}

//  Kopierkonstuktor
ColumnBitmap::ColumnBitmap(const ColumnBitmap& Column_Bitmap)
:
    column_bitmap(Column_Bitmap.column_bitmap)
{}

// Zuweisungsoperator
void ColumnBitmap::operator=(const ColumnBitmap& Column_Bitmap)
{
    this->column_bitmap = Column_Bitmap.column_bitmap;
}

// Prüfen ob Bit gesetzt ist
const bool ColumnBitmap::get_row_bit(const uint8_t row_index) const
{
    return (this->column_bitmap & (1 << (row_index % 8)) ? true : false);
}



// ------- CharBitmap -------

// Konstruktor
CharBitmap::CharBitmap(const uint8_t* const Char_bitmap, const UINT_8 Width)
:
    char_bitmap(Char_bitmap),
    char_width(Width)
{}

//  Kopierkonstuktor
CharBitmap::CharBitmap(const CharBitmap& Char_Bitmap)
:
    char_bitmap(Char_Bitmap.char_bitmap),
    char_width(Char_Bitmap.char_width)
{}

// Zuweisungsoperator
void CharBitmap::operator=(const CharBitmap& Char_Bitmap)
{
    this->char_bitmap = Char_Bitmap.char_bitmap;
    this->char_width = Char_Bitmap.char_width;
}

// column_bitmap aus PROGMEM-Speicher holen
const ColumnBitmap CharBitmap::get_column_bitmap(const uint8_t column_index) const
{
    return pgm_read_byte(&(this->char_bitmap[column_index % this->char_width]));
}



// ------- FontBitmap -------

// Konstruktor
FontBitmap::FontBitmap(const String Text)
:
    text(Text)
{}

// Kopierkonstruktor
FontBitmap::FontBitmap(const FontBitmap& other)
:
    text(other.text)
{}

// Zuweisungsoperator
void FontBitmap::operator=(const FontBitmap& other)
{
    this->text = other.text;
}

// Länge eines Textes in Pixeln berechnen
const uint32_t FontBitmap::length_of(const String text, const uint8_t space_between_characters)
{
    uint32_t length = 0;
    for(uint32_t i = 0; i < text.length(); ++i)
    {
        length += FontBitmap::get_char_bitmap(text.charAt(i)).width();
        length += (i < text.length() -1) ? space_between_characters : 0;
    }
    return length;
}


// char_bitmap aus PRGOMEM-Speicher holen
const CharBitmap FontBitmap::get_char_bitmap(const char character_index)
{
    return CharBitmap(
    (const uint8_t* const)  pgm_read_word(&font_bitmap_array[((const uint8_t)character_index) % 256]), // Zeiger sind 2 Byte groß
                            pgm_read_byte(&char_width_array[((const uint8_t)character_index) % 256])
    );
}

// Zum Testen ob korrekt aus dem PROGMEM-Speicher gelesen wird
void test_PROGMEM_access(const char start_char, const char stop_char)
{
    // Für alle Zeichen im Interval [start_char; stop_char]
    for(int16_t c = start_char; c <= stop_char; ++c)
    {
        // Zeichen ausgeben 
        ((c >= ' ' && c <= '~') ? Serial.print(String("'") + (char)c + String("'\t")) : Serial.print(" " + String(c) + " \t"));

        // Bitmap des Zeichen holen
        CharBitmap cb(font_bitmap[(char) c]);

        // Bitmap-Array formatiert als HEX-Zahlen ausgeben
        Serial.print("{ ");
        for(uint8_t i = 0; i < cb.width(); ++i)
        {
            Serial.print("0x");
            Serial.print((uint8_t)cb[i], HEX);
            (i+1 < cb.width() ? Serial.print(",\t") : 0);
        }
        Serial.println(" }");
    }
}


} // Ende Font namespace

} // Ende LEDArrangement namespace