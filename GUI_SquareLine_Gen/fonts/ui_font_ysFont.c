/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: --bpp 1 --size 20 --font D:/Users/hhj/Documents/Codes/STM/SquareLine/assets/ys.ttf -o D:/Users/hhj/Documents/Codes/STM/SquareLine/assets\ui_font_ysFont.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_YSFONT
#define UI_FONT_YSFONT 1
#endif

#if UI_FONT_YSFONT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xee, 0xee, 0xee, 0xee, 0xee, 0xe0, 0x6f, 0xf6,

    /* U+0022 "\"" */
    0xef, 0xdf, 0xbf, 0x7c, 0xc0,

    /* U+0023 "#" */
    0xf, 0x78, 0x1e, 0x70, 0x38, 0xe0, 0x73, 0xc7,
    0xff, 0xe3, 0xce, 0x7, 0x1c, 0xe, 0x38, 0x1c,
    0xe1, 0xff, 0xf8, 0xe3, 0x81, 0xc7, 0x3, 0x9c,
    0x7, 0x38, 0xc, 0x60, 0x0,

    /* U+0024 "$" */
    0xe, 0x3, 0x83, 0xf9, 0x86, 0xe0, 0xbc, 0xf,
    0xc1, 0xfc, 0x3f, 0x81, 0xf0, 0x3d, 0x7, 0x61,
    0xcf, 0xe0, 0xe0, 0x38,

    /* U+0025 "%" */
    0x38, 0x1e, 0x36, 0xf, 0x31, 0x8f, 0x18, 0xc7,
    0xc, 0x67, 0x3, 0x67, 0x0, 0xe7, 0x80, 0x7,
    0x9c, 0x3, 0x9b, 0x3, 0x98, 0xc3, 0xcc, 0x63,
    0xc6, 0x33, 0xc1, 0xb1, 0xc0, 0x71, 0xc0, 0x0,

    /* U+0026 "&" */
    0x1f, 0xc0, 0x38, 0xe0, 0x38, 0xe0, 0x1c, 0xc0,
    0xf, 0x80, 0xe, 0x0, 0x3f, 0xf, 0x77, 0x8e,
    0xe3, 0x8c, 0xe3, 0xcc, 0xe1, 0xf8, 0xe1, 0xf0,
    0xe0, 0xf0, 0x70, 0xf9, 0x3f, 0xbe,

    /* U+0027 "'" */
    0xff, 0xfc,

    /* U+0028 "(" */
    0x4, 0x18, 0x71, 0xc7, 0xe, 0x38, 0x70, 0xe1,
    0xc3, 0x87, 0xe, 0xe, 0x1c, 0x3c, 0x38, 0x38,
    0x30,

    /* U+0029 ")" */
    0x40, 0xe1, 0xe1, 0xc1, 0xc3, 0x83, 0x87, 0xe,
    0x1c, 0x38, 0x70, 0xe3, 0x87, 0x1c, 0x38, 0xe1,
    0x80,

    /* U+002A "*" */
    0x1c, 0xe, 0x37, 0xff, 0xf7, 0xf1, 0xf1, 0xdc,
    0xc6, 0x0, 0x0,

    /* U+002B "+" */
    0xe, 0x1, 0xc0, 0x38, 0x7, 0xf, 0xfe, 0x1c,
    0x3, 0x80, 0x70, 0xe, 0x1, 0xc0,

    /* U+002C "," */
    0xef, 0xf3, 0x64,

    /* U+002D "-" */
    0xff, 0x80,

    /* U+002E "." */
    0xff, 0xf0,

    /* U+002F "/" */
    0x7, 0x7, 0xe, 0xe, 0xe, 0x1c, 0x1c, 0x1c,
    0x38, 0x38, 0x78, 0x70, 0x70, 0xf0, 0xe0,

    /* U+0030 "0" */
    0x1f, 0x83, 0x9c, 0x70, 0xe6, 0x6, 0xe0, 0x7e,
    0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x7e, 0x7, 0xe0,
    0x76, 0x6, 0x70, 0xe3, 0x9c, 0x1f, 0x80,

    /* U+0031 "1" */
    0x4, 0x77, 0xff, 0x1c, 0x71, 0xc7, 0x1c, 0x71,
    0xc7, 0x1c, 0x71, 0xc6,

    /* U+0032 "2" */
    0x1f, 0x7, 0xfc, 0x7b, 0xcf, 0x1e, 0xe0, 0xee,
    0xe, 0x1, 0xe0, 0x3c, 0x7, 0x81, 0xf0, 0x3c,
    0x7, 0x80, 0xf0, 0xf, 0x0, 0xff, 0xe0,

    /* U+0033 "3" */
    0x3f, 0xe, 0x3b, 0x83, 0xf0, 0x70, 0xe, 0x3,
    0x83, 0xe0, 0xe, 0x0, 0xe0, 0x1f, 0x83, 0xf0,
    0x7f, 0x1c, 0xff, 0x8f, 0xc0,

    /* U+0034 "4" */
    0x1, 0xc0, 0xf, 0x0, 0x7c, 0x1, 0xf0, 0xd,
    0xc0, 0x77, 0x3, 0x9c, 0xc, 0x70, 0x71, 0xc3,
    0x87, 0xf, 0xff, 0xc0, 0x70, 0x1, 0xc0, 0x7,
    0x0, 0x18, 0x0,

    /* U+0035 "5" */
    0x1f, 0xc6, 0x0, 0xc0, 0x18, 0x3, 0x0, 0x60,
    0x1f, 0xe3, 0xe, 0x0, 0xe0, 0x1f, 0x83, 0xf0,
    0x7e, 0xe, 0xe3, 0x8f, 0xc0,

    /* U+0036 "6" */
    0x3, 0x0, 0xf0, 0x1c, 0x3, 0x80, 0x78, 0x7,
    0x0, 0xff, 0x8f, 0xe, 0xe0, 0x6e, 0x7, 0xe0,
    0x7e, 0x7, 0xe0, 0x76, 0xe, 0x30, 0xe1, 0xf8,

    /* U+0037 "7" */
    0xff, 0xf8, 0xe, 0x1, 0xc0, 0x3c, 0x3, 0x80,
    0x78, 0x7, 0x80, 0x70, 0xf, 0x0, 0xf0, 0xe,
    0x0, 0xe0, 0xe, 0x0, 0xe0, 0x1c, 0x0,

    /* U+0038 "8" */
    0x1f, 0xc1, 0xc7, 0x1c, 0x1c, 0xe0, 0xe7, 0x87,
    0x3e, 0x70, 0xff, 0x7, 0xfc, 0x7b, 0xf7, 0x87,
    0xb8, 0x1d, 0xc0, 0xee, 0x7, 0x38, 0x70, 0x7f,
    0x0,

    /* U+0039 "9" */
    0x1f, 0xe, 0x3b, 0x83, 0x70, 0x7e, 0xf, 0xc1,
    0xf8, 0x3b, 0x8f, 0x3f, 0xe0, 0x38, 0x7, 0x1,
    0xc0, 0x70, 0x3c, 0x7, 0x0,

    /* U+003A ":" */
    0xff, 0x80, 0x0, 0xff, 0x80,

    /* U+003B ";" */
    0xff, 0x80, 0x0, 0xff, 0xb4, 0x0,

    /* U+003C "<" */
    0x0, 0xc0, 0xf0, 0xfc, 0xfc, 0xfc, 0x3c, 0x7,
    0xc0, 0x7c, 0x7, 0xc0, 0x70, 0x4,

    /* U+003D "=" */
    0xff, 0x80, 0x0, 0x0, 0xf, 0xf8,

    /* U+003E ">" */
    0xc0, 0x3c, 0xf, 0xc0, 0xfc, 0xf, 0xc0, 0xf0,
    0xf8, 0xf8, 0xf8, 0x38, 0x8, 0x0,

    /* U+003F "?" */
    0x3f, 0x1c, 0x6e, 0x1f, 0x87, 0xe1, 0xc0, 0xf0,
    0x78, 0x3c, 0xe, 0x3, 0x80, 0xe0, 0x0, 0x0,
    0x7, 0x81, 0xe0, 0x78,

    /* U+0040 "@" */
    0x3, 0xfc, 0x3, 0x83, 0xc3, 0x80, 0x39, 0xc7,
    0xc6, 0x77, 0x39, 0xf9, 0x8e, 0x7e, 0x7, 0x9f,
    0x8f, 0xe7, 0xef, 0x39, 0xfb, 0x8e, 0xee, 0xe7,
    0xf1, 0xdf, 0xf8, 0x70, 0x19, 0x8e, 0x0, 0xc1,
    0xe0, 0xe0, 0xf, 0xe0,

    /* U+0041 "A" */
    0x7, 0x80, 0x1e, 0x0, 0x7c, 0x3, 0xf0, 0xd,
    0xc0, 0x77, 0x81, 0xde, 0x6, 0x38, 0x38, 0xf0,
    0xe3, 0xc3, 0xff, 0x1c, 0x1e, 0x60, 0x39, 0x80,
    0xfc, 0x1, 0xc0,

    /* U+0042 "B" */
    0xff, 0xc7, 0xe, 0x70, 0x77, 0x7, 0x70, 0x77,
    0x7, 0x70, 0xe7, 0xf8, 0x70, 0xe7, 0x7, 0x70,
    0x77, 0x7, 0x70, 0x77, 0xe, 0x7f, 0xc0,

    /* U+0043 "C" */
    0x0, 0x0, 0x7f, 0x86, 0x1c, 0x60, 0x67, 0x1,
    0xf0, 0x3, 0x80, 0x1c, 0x0, 0xe0, 0x7, 0x0,
    0x38, 0x1, 0xc0, 0x7, 0x0, 0x38, 0xc, 0xe0,
    0xe1, 0xfc,

    /* U+0044 "D" */
    0xff, 0xc1, 0xc3, 0x87, 0x7, 0x1c, 0xe, 0x70,
    0x1d, 0xc0, 0x77, 0x1, 0xdc, 0x7, 0x70, 0x1d,
    0xc0, 0x77, 0x3, 0x9c, 0xe, 0x70, 0x71, 0xc3,
    0x87, 0xf8, 0x0,

    /* U+0045 "E" */
    0xff, 0xe7, 0x1, 0x70, 0x7, 0x0, 0x70, 0x7,
    0x0, 0x7f, 0xe7, 0x0, 0x70, 0x7, 0x0, 0x70,
    0x7, 0x0, 0x70, 0x7, 0x1, 0x7f, 0xe0,

    /* U+0046 "F" */
    0xff, 0xee, 0x5, 0xc0, 0x38, 0x7, 0x0, 0xe0,
    0x1f, 0xf3, 0x80, 0x70, 0xe, 0x1, 0xc0, 0x38,
    0x7, 0x0, 0xe0, 0x18, 0x0,

    /* U+0047 "G" */
    0x0, 0x8, 0x1f, 0xe1, 0xc3, 0x8e, 0x6, 0x78,
    0x1b, 0xc0, 0xf, 0x0, 0x3c, 0x0, 0xf0, 0x3,
    0xc1, 0xff, 0x3, 0xbc, 0xe, 0x78, 0x39, 0xe0,
    0xe3, 0xc3, 0x83, 0xfc,

    /* U+0048 "H" */
    0xf0, 0x3b, 0x81, 0xdc, 0xe, 0xe0, 0x77, 0x3,
    0xb8, 0x1d, 0xff, 0xee, 0x7, 0x70, 0x3b, 0x81,
    0xdc, 0xe, 0xe0, 0x77, 0x3, 0xb8, 0x1d, 0x80,
    0xc0,

    /* U+0049 "I" */
    0xfb, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0x9c, 0xe7,
    0x3b, 0xe0,

    /* U+004A "J" */
    0x7c, 0x71, 0xc7, 0x1c, 0x71, 0xc7, 0x1c, 0x71,
    0xc7, 0x1c, 0x71, 0xc7, 0x1c, 0xe3, 0x18,

    /* U+004B "K" */
    0xf0, 0xf8, 0xe1, 0xc1, 0xc3, 0x3, 0x8e, 0x7,
    0x38, 0xe, 0xe0, 0x1d, 0xc0, 0x3f, 0xc0, 0x7f,
    0xc0, 0xf7, 0x81, 0xc7, 0x83, 0x87, 0x7, 0xf,
    0xe, 0xf, 0x18, 0xf, 0x0,

    /* U+004C "L" */
    0xf0, 0xe, 0x1, 0xc0, 0x38, 0x7, 0x0, 0xe0,
    0x1c, 0x3, 0x80, 0x70, 0xe, 0x1, 0xc0, 0x38,
    0x7, 0x0, 0xe0, 0x1f, 0xf8,

    /* U+004D "M" */
    0x7e, 0x3, 0xcf, 0x80, 0xf3, 0xf0, 0x3c, 0xfc,
    0x1f, 0x3f, 0x87, 0xcf, 0xe3, 0xf3, 0xbc, 0xdc,
    0xef, 0x37, 0x39, 0xdd, 0xce, 0x7e, 0x73, 0x9f,
    0x9c, 0xe3, 0xc7, 0x38, 0xf1, 0xce, 0x1c, 0x73,
    0x6, 0xc,

    /* U+004E "N" */
    0x7c, 0x1f, 0x1f, 0x7, 0xf, 0x83, 0x87, 0xe1,
    0xc3, 0xb8, 0xe1, 0xde, 0x70, 0xe7, 0x38, 0x71,
    0xdc, 0x38, 0xfe, 0x1c, 0x3f, 0xe, 0xf, 0x87,
    0x7, 0xc3, 0x81, 0xe1, 0xc0, 0x70, 0x80, 0x38,

    /* U+004F "O" */
    0x7, 0xc0, 0x38, 0xe0, 0xc0, 0x63, 0x80, 0xee,
    0x0, 0xdc, 0x1, 0xf8, 0x3, 0xf0, 0x7, 0xe0,
    0xf, 0xc0, 0x1d, 0x80, 0x33, 0x80, 0xe3, 0x1,
    0x83, 0x8e, 0x3, 0xf0, 0x0,

    /* U+0050 "P" */
    0xff, 0x87, 0xe, 0x70, 0x77, 0x7, 0x70, 0x77,
    0x7, 0x70, 0x77, 0xe, 0x7f, 0x87, 0x0, 0x70,
    0x7, 0x0, 0x70, 0x6, 0x0, 0x40, 0x0,

    /* U+0051 "Q" */
    0xf, 0xc0, 0x7f, 0xe1, 0xe1, 0xe3, 0x81, 0xef,
    0x1, 0xdc, 0x3, 0xf8, 0x7, 0xf0, 0xf, 0xe0,
    0x1f, 0xc0, 0x3f, 0x80, 0x7b, 0x81, 0xe3, 0x3,
    0xc3, 0xf, 0x1, 0xf8, 0x0, 0xf0, 0x0, 0xf0,
    0x0, 0xf0, 0x0, 0x30,

    /* U+0052 "R" */
    0xff, 0xc0, 0xe1, 0xc1, 0xc3, 0xc3, 0x87, 0x87,
    0xf, 0xe, 0x1e, 0x1c, 0x78, 0x3f, 0xe0, 0x73,
    0xc0, 0xe3, 0xc1, 0xc7, 0x83, 0x87, 0x87, 0xf,
    0xe, 0xf, 0x18, 0xf, 0x0,

    /* U+0053 "S" */
    0x0, 0x43, 0xf9, 0x87, 0x70, 0x6e, 0x5, 0xe0,
    0x3f, 0x3, 0xf8, 0x3f, 0xc3, 0xf8, 0x1f, 0x81,
    0xf0, 0xf, 0x81, 0xd8, 0x71, 0xf8,

    /* U+0054 "T" */
    0xff, 0xfa, 0x1e, 0x10, 0x78, 0x1, 0xe0, 0x7,
    0x80, 0x1e, 0x0, 0x78, 0x1, 0xe0, 0x7, 0x80,
    0x1e, 0x0, 0x78, 0x1, 0xe0, 0x7, 0x80, 0x1c,
    0x0, 0x40, 0x0,

    /* U+0055 "U" */
    0xfc, 0x7f, 0x78, 0x1c, 0x70, 0x1c, 0x70, 0x1c,
    0x70, 0x1c, 0x70, 0x1c, 0x70, 0x1c, 0x70, 0x1c,
    0x70, 0x1c, 0x70, 0x1c, 0x70, 0x1c, 0x70, 0x1c,
    0x38, 0x38, 0x1c, 0x30, 0xf, 0xc0,

    /* U+0056 "V" */
    0xfc, 0x1f, 0x7c, 0xe, 0x3c, 0xc, 0x3c, 0x1c,
    0x1c, 0x18, 0x1e, 0x18, 0x1e, 0x30, 0xe, 0x30,
    0xf, 0x30, 0x7, 0x60, 0x7, 0x60, 0x7, 0xe0,
    0x3, 0xc0, 0x3, 0xc0, 0x1, 0x80,

    /* U+0057 "W" */
    0xfe, 0x0, 0xfb, 0xc0, 0xc3, 0x8f, 0xe, 0x1c,
    0x78, 0x78, 0xc3, 0xc3, 0xc6, 0xe, 0x3e, 0x70,
    0x79, 0xfb, 0x83, 0xdf, 0xdc, 0xe, 0xce, 0xc0,
    0x7e, 0x7e, 0x3, 0xf1, 0xf0, 0xf, 0xf, 0x80,
    0x78, 0x7c, 0x3, 0xc1, 0xc0, 0xc, 0xe, 0x0,

    /* U+0058 "X" */
    0xf8, 0x7c, 0x78, 0x70, 0xf9, 0xc0, 0xf3, 0x80,
    0xfe, 0x1, 0xf8, 0x1, 0xf0, 0x3, 0xe0, 0x7,
    0xc0, 0x1f, 0xc0, 0x77, 0x80, 0xc7, 0x83, 0x87,
    0x8e, 0xf, 0x18, 0xf, 0x80,

    /* U+0059 "Y" */
    0xf8, 0x79, 0xe0, 0xc3, 0x86, 0xf, 0x18, 0x1c,
    0xc0, 0x7b, 0x0, 0xf8, 0x3, 0xe0, 0x7, 0x0,
    0x1c, 0x0, 0x70, 0x1, 0xc0, 0x7, 0x0, 0x1c,
    0x0, 0x60, 0x0,

    /* U+005A "Z" */
    0x7f, 0xf8, 0x1e, 0x3, 0xe0, 0x3c, 0x7, 0xc0,
    0xf8, 0xf, 0x81, 0xf0, 0x1f, 0x3, 0xe0, 0x3e,
    0x7, 0xc0, 0x7c, 0xf, 0x80, 0xff, 0xf0,

    /* U+005B "[" */
    0xff, 0x8e, 0x38, 0xe3, 0x8e, 0x38, 0xe3, 0x8e,
    0x38, 0xe3, 0x8e, 0x38, 0xe3, 0xf0,

    /* U+005C "\\" */
    0xe1, 0xc1, 0x83, 0x87, 0xe, 0xe, 0x1c, 0x38,
    0x70, 0x70, 0xe1, 0xc1, 0xc3, 0x80,

    /* U+005D "]" */
    0xfc, 0x71, 0xc7, 0x1c, 0x71, 0xc7, 0x1c, 0x71,
    0xc7, 0x1c, 0x71, 0xc7, 0x1f, 0xf0,

    /* U+005E "^" */
    0x0, 0x18, 0x3c, 0x7e, 0x66, 0xc7,

    /* U+005F "_" */
    0xff, 0xc0,

    /* U+0060 "`" */
    0xf7, 0x9c, 0x63, 0x8c,

    /* U+0061 "a" */
    0x3e, 0x3c, 0xce, 0x3b, 0x8e, 0xf, 0x9f, 0xef,
    0x3b, 0x8e, 0xe3, 0xb8, 0xe7, 0xdc,

    /* U+0062 "b" */
    0x30, 0x1e, 0x1, 0xc0, 0x38, 0x7, 0x0, 0xff,
    0x1e, 0x73, 0x86, 0x70, 0xee, 0x1d, 0xc3, 0xb8,
    0x77, 0xe, 0xe1, 0x9c, 0x73, 0xf8,

    /* U+0063 "c" */
    0x1f, 0x1c, 0x77, 0xf, 0x83, 0xe0, 0x38, 0xe,
    0x3, 0xc0, 0x78, 0xdf, 0xe1, 0xf0,

    /* U+0064 "d" */
    0x1, 0xc0, 0xf0, 0x1c, 0x7, 0x1, 0xcf, 0xf7,
    0x1f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1,
    0xf8, 0x77, 0x1c, 0xff,

    /* U+0065 "e" */
    0x1f, 0xe, 0x71, 0x87, 0x70, 0xfe, 0x1f, 0xff,
    0xf8, 0x7, 0x0, 0x70, 0x4f, 0xf8, 0x7c, 0x0,

    /* U+0066 "f" */
    0x0, 0x3, 0xe1, 0xdc, 0x67, 0x38, 0xe, 0xf,
    0xf8, 0xe0, 0x38, 0xe, 0x3, 0x80, 0xe0, 0x38,
    0xe, 0x3, 0x80, 0xe0, 0x20, 0x0,

    /* U+0067 "g" */
    0x0, 0x47, 0xf9, 0xcf, 0x70, 0xee, 0x1d, 0xc3,
    0x9c, 0xe1, 0xf8, 0x60, 0x1c, 0x3, 0x80, 0x3f,
    0xc6, 0x1f, 0xc1, 0xf8, 0x3f, 0x8e, 0x3f, 0x80,

    /* U+0068 "h" */
    0x70, 0x1e, 0x1, 0xc0, 0x38, 0x7, 0x0, 0xff,
    0x1e, 0x33, 0x87, 0x70, 0xee, 0x1d, 0xc3, 0xb8,
    0x77, 0xe, 0xe1, 0xdc, 0x3b, 0x87,

    /* U+0069 "i" */
    0x37, 0x73, 0x3, 0xf7, 0x77, 0x77, 0x77, 0x77,

    /* U+006A "j" */
    0x1c, 0x71, 0xc2, 0x0, 0x37, 0xc7, 0x1c, 0x71,
    0xc7, 0x1c, 0x71, 0xc7, 0x1c, 0x71, 0xce, 0x70,

    /* U+006B "k" */
    0xf0, 0x7, 0x0, 0x70, 0x7, 0x0, 0x70, 0x7,
    0x3e, 0x71, 0xc7, 0x38, 0x77, 0x7, 0xe0, 0x7f,
    0x7, 0xf8, 0x73, 0x87, 0x3c, 0x71, 0xe4, 0xf,

    /* U+006C "l" */
    0x71, 0xe1, 0xc3, 0x87, 0xe, 0x1c, 0x38, 0x70,
    0xe1, 0xc3, 0x87, 0xf, 0xcf, 0x0,

    /* U+006D "m" */
    0xff, 0xbe, 0x38, 0xf1, 0x9c, 0x70, 0xee, 0x38,
    0x77, 0x1c, 0x3b, 0x8e, 0x1d, 0xc7, 0xe, 0xe3,
    0x87, 0x71, 0xc3, 0xb8, 0xe1, 0xdc, 0x70, 0xe0,

    /* U+006E "n" */
    0xff, 0x8f, 0x39, 0xc3, 0xb8, 0x77, 0xe, 0xe1,
    0xdc, 0x3b, 0x87, 0x70, 0xee, 0x1d, 0xc3, 0x0,

    /* U+006F "o" */
    0x1f, 0xe, 0x39, 0x87, 0x70, 0x7e, 0xf, 0xc1,
    0xf8, 0x3f, 0x7, 0x61, 0xce, 0x38, 0x7c, 0x0,

    /* U+0070 "p" */
    0xff, 0x8e, 0x39, 0xc3, 0x38, 0x77, 0xe, 0xe1,
    0xdc, 0x3b, 0x87, 0x70, 0xcf, 0x39, 0xfe, 0x38,
    0x7, 0x0, 0xe0, 0x1c, 0x3, 0x0,

    /* U+0071 "q" */
    0x1f, 0xee, 0x39, 0x87, 0x70, 0xee, 0x1d, 0xc3,
    0xb8, 0x77, 0xe, 0x61, 0xce, 0x38, 0xff, 0x0,
    0xe0, 0x1c, 0x3, 0x80, 0x70, 0xc,

    /* U+0072 "r" */
    0xf7, 0x9e, 0x67, 0x1d, 0xc0, 0x70, 0x1c, 0x7,
    0x1, 0xc0, 0x70, 0x1c, 0x6, 0x0,

    /* U+0073 "s" */
    0x3e, 0x9c, 0x77, 0xd, 0xe0, 0x7f, 0xf, 0xe0,
    0xfc, 0xf, 0x41, 0xde, 0xe1, 0xf0,

    /* U+0074 "t" */
    0x0, 0x38, 0x78, 0x38, 0xff, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x1f,

    /* U+0075 "u" */
    0x30, 0x7e, 0x3d, 0xc3, 0xb8, 0x77, 0xe, 0xe1,
    0xdc, 0x3b, 0x87, 0x70, 0xee, 0x3c, 0xfb, 0x80,

    /* U+0076 "v" */
    0xfc, 0xf7, 0x86, 0x38, 0x63, 0x8c, 0x3c, 0xc1,
    0xc8, 0x1d, 0x80, 0xf8, 0xf, 0x0, 0x70, 0x7,
    0x0,

    /* U+0077 "w" */
    0xfc, 0x3, 0xde, 0x18, 0xe3, 0x8e, 0x30, 0xe3,
    0xcc, 0x3d, 0xf3, 0x7, 0x7f, 0x81, 0xf3, 0xe0,
    0x7c, 0xf8, 0xe, 0x1c, 0x3, 0x87, 0x0, 0xc1,
    0x80,

    /* U+0078 "x" */
    0xf1, 0xe7, 0x98, 0x3f, 0x81, 0xf0, 0x1e, 0x0,
    0xf0, 0x1f, 0x3, 0xf8, 0x33, 0xc6, 0x3c, 0xe1,
    0xf0,

    /* U+0079 "y" */
    0xfc, 0xfb, 0xc3, 0xe, 0x18, 0x79, 0x81, 0xcc,
    0xe, 0xc0, 0x3e, 0x1, 0xf0, 0xf, 0x0, 0x38,
    0x1, 0x80, 0x1c, 0x0, 0xe0, 0xe, 0x0, 0x70,
    0xe, 0x0,

    /* U+007A "z" */
    0x7f, 0xc8, 0x78, 0x1f, 0x7, 0xc0, 0xf0, 0x3e,
    0x7, 0x81, 0xf0, 0x7c, 0xf, 0x81, 0xff, 0x0,

    /* U+007B "{" */
    0x7, 0x1f, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c,
    0x3c, 0x38, 0xf0, 0x38, 0x3c, 0x3c, 0x3c, 0x3c,
    0x3c, 0x3c, 0x1f, 0x7,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,

    /* U+007D "}" */
    0xe0, 0xf8, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c,
    0x3c, 0x1c, 0xf, 0x1c, 0x3c, 0x3c, 0x3c, 0x3c,
    0x3c, 0x3c, 0xf8, 0xe0,

    /* U+007E "~" */
    0x0, 0x3, 0xf8, 0xdf, 0xff, 0x9f, 0xe0, 0x1e,
    0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 96, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 160, .box_w = 4, .box_h = 16, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 9, .adv_w = 131, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 14, .adv_w = 258, .box_w = 15, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 43, .adv_w = 194, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 63, .adv_w = 300, .box_w = 17, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 95, .adv_w = 261, .box_w = 16, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 125, .adv_w = 79, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 127, .adv_w = 122, .box_w = 7, .box_h = 19, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 144, .adv_w = 123, .box_w = 7, .box_h = 19, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 161, .adv_w = 152, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 172, .adv_w = 206, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 186, .adv_w = 96, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 189, .adv_w = 172, .box_w = 9, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 191, .adv_w = 101, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 193, .adv_w = 137, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 208, .adv_w = 237, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 231, .adv_w = 126, .box_w = 6, .box_h = 16, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 243, .adv_w = 205, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 266, .adv_w = 212, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 287, .adv_w = 233, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 314, .adv_w = 212, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 335, .adv_w = 220, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 359, .adv_w = 188, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 382, .adv_w = 216, .box_w = 13, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 407, .adv_w = 204, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 428, .adv_w = 106, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 433, .adv_w = 115, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 439, .adv_w = 194, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 177, .box_w = 9, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 459, .adv_w = 193, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 473, .adv_w = 197, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 493, .adv_w = 326, .box_w = 18, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 529, .adv_w = 213, .box_w = 14, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 556, .adv_w = 223, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 579, .adv_w = 231, .box_w = 13, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 605, .adv_w = 249, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 632, .adv_w = 204, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 655, .adv_w = 189, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 676, .adv_w = 247, .box_w = 14, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 704, .adv_w = 251, .box_w = 13, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 729, .adv_w = 124, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 739, .adv_w = 115, .box_w = 6, .box_h = 20, .ofs_x = -1, .ofs_y = -6},
    {.bitmap_index = 754, .adv_w = 234, .box_w = 15, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 783, .adv_w = 190, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 804, .adv_w = 309, .box_w = 18, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 838, .adv_w = 264, .box_w = 17, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 870, .adv_w = 258, .box_w = 15, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 899, .adv_w = 217, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 922, .adv_w = 257, .box_w = 15, .box_h = 19, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 958, .adv_w = 231, .box_w = 15, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 987, .adv_w = 195, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1009, .adv_w = 220, .box_w = 14, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1036, .adv_w = 260, .box_w = 16, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1066, .adv_w = 248, .box_w = 16, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1096, .adv_w = 334, .box_w = 21, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1136, .adv_w = 234, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1165, .adv_w = 215, .box_w = 14, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1192, .adv_w = 214, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1215, .adv_w = 142, .box_w = 6, .box_h = 18, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 1229, .adv_w = 123, .box_w = 7, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1243, .adv_w = 143, .box_w = 6, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1257, .adv_w = 187, .box_w = 8, .box_h = 6, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 1263, .adv_w = 190, .box_w = 10, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1265, .adv_w = 142, .box_w = 5, .box_h = 6, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 1269, .adv_w = 182, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1283, .adv_w = 199, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1305, .adv_w = 186, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1319, .adv_w = 205, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1339, .adv_w = 186, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1355, .adv_w = 165, .box_w = 10, .box_h = 17, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1377, .adv_w = 193, .box_w = 11, .box_h = 17, .ofs_x = 1, .ofs_y = -6},
    {.bitmap_index = 1401, .adv_w = 198, .box_w = 11, .box_h = 16, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1423, .adv_w = 107, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1431, .adv_w = 108, .box_w = 6, .box_h = 21, .ofs_x = -1, .ofs_y = -6},
    {.bitmap_index = 1447, .adv_w = 203, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1471, .adv_w = 116, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1485, .adv_w = 298, .box_w = 17, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1509, .adv_w = 204, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1525, .adv_w = 199, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1541, .adv_w = 204, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = -6},
    {.bitmap_index = 1563, .adv_w = 205, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = -6},
    {.bitmap_index = 1585, .adv_w = 166, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1599, .adv_w = 167, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1613, .adv_w = 147, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1628, .adv_w = 208, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1644, .adv_w = 193, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1661, .adv_w = 286, .box_w = 18, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1686, .adv_w = 189, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1703, .adv_w = 197, .box_w = 13, .box_h = 16, .ofs_x = 0, .ofs_y = -6},
    {.bitmap_index = 1729, .adv_w = 176, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1745, .adv_w = 155, .box_w = 8, .box_h = 20, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1765, .adv_w = 109, .box_w = 3, .box_h = 19, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 1773, .adv_w = 156, .box_w = 8, .box_h = 20, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1793, .adv_w = 243, .box_w = 13, .box_h = 5, .ofs_x = 1, .ofs_y = 5}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 2, 3, 4, 5, 6,
    7, 8, 9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22,
    23, 24, 25, 26, 0, 0, 0, 0,
    0, 0, 27, 28, 29, 30, 31, 32,
    33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48,
    49, 50, 51, 52, 0, 0, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 2, 3, 4, 5, 6,
    7, 8, 9, 10, 11, 4, 12, 11,
    13, 8, 13, 14, 15, 16, 17, 18,
    19, 20, 21, 22, 0, 0, 0, 0,
    0, 0, 23, 24, 25, 26, 27, 28,
    29, 30, 31, 32, 24, 33, 34, 35,
    36, 37, 38, 39, 40, 41, 42, 43,
    43, 44, 45, 46, 0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    30, 0, 15, 0, 0, 7, 12, 0,
    21, 7, 7, 0, 15, 7, 14, -39,
    0, -12, -18, 20, -34, 24, 20, 10,
    17, 16, 17, 0, 17, 11, 6, 10,
    10, 7, 7, 16, 11, 17, 7, 19,
    0, 11, 0, 23, 0, 21, 14, 14,
    23, 14, 13, 14, 22, 14, 13, 13,
    15, 14, 23, 16, 17, -8, 8, -12,
    -11, 0, -13, 9, 13, 17, 21, 19,
    20, 12, 15, 19, 12, 8, 19, 12,
    12, 20, 12, 20, 12, 13, 12, 11,
    9, 0, 0, 0, 16, 12, 15, 12,
    11, 13, 16, 12, 13, 13, 13, 12,
    16, 14, 21, 0, 11, 11, 11, 11,
    11, 14, 16, 15, 11, 12, 11, 16,
    11, 17, 13, 14, 17, 9, 9, 10,
    0, 10, 0, 17, 15, 0, 11, 10,
    9, 9, 0, 13, 26, 12, 11, 13,
    27, 12, 9, 8, 13, 11, 27, 13,
    14, -18, 9, -15, -14, -11, -22, 0,
    10, 15, 19, 17, 18, 8, 10, 16,
    12, 11, 17, 14, 12, 17, 13, 16,
    11, 13, 15, 14, 12, 0, 11, 10,
    18, 17, 17, 19, 18, 17, 14, 19,
    14, 15, 20, 18, 18, 21, 15, 10,
    8, 16, 16, 12, 16, 14, 15, 20,
    0, 0, 0, 7, 8, 22, 9, 7,
    21, 0, 0, 0, 0, 0, 0, 14,
    0, 0, -18, 8, -20, 11, -17, 13,
    20, 15, 13, 13, 19, 14, 12, 13,
    15, 15, 21, 16, 16, 18, 12, 23,
    24, 18, 24, 14, 0, 16, 0, 0,
    0, 0, 0, 18, 7, 7, 18, -7,
    -7, 0, -8, 0, -7, 0, 7, 0,
    -9, -18, -12, 0, 0, 17, 22, 17,
    16, 21, 23, 17, 15, 15, 18, 17,
    23, 19, 13, 0, 11, 0, 0, 0,
    0, 0, 13, 23, 16, 15, 15, 0,
    12, 21, 16, 0, 21, 14, 12, 14,
    13, 15, 14, 12, 0, 13, 0, 0,
    0, 0, 0, 23, 20, 28, 26, 23,
    21, 27, 30, 20, 28, 32, 21, 29,
    13, 0, 25, 0, 0, 0, 0, 0,
    0, 26, 11, 11, 11, 0, 8, 27,
    21, 12, 26, 16, 16, 10, 15, 12,
    13, 0, 17, 17, 0, 0, 0, 0,
    15, 0, 13, 8, 0, 0, 15, 6,
    9, 9, 7, 8, 14, 8, 11, 0,
    0, 13, 13, 11, 14, 12, 8, 12,
    8, 0, 7, 0, 11, 13, 14, 8,
    12, 11, 12, 0, 14, 0, 14, 11,
    10, 9, 0, 11, -6, 0, 6, 24,
    18, 30, 28, 25, 19, 30, 35, 31,
    31, 36, 19, 31, 12, 0, 24, 0,
    0, 0, 0, 0, 0, 28, 10, 10,
    9, 0, 12, 29, 24, 27, 27, 17,
    17, 8, 21, 11, 13, 0, 17, 17,
    0, 7, 0, 0, 34, 10, 0, 10,
    8, 12, 0, 11, 25, 11, 12, 10,
    0, 12, 0, 0, 0, 12, 12, 23,
    14, 27, 14, 13, 0, 0, 0, 0,
    16, 15, 0, 0, 11, 8, 7, 0,
    9, 0, 7, 11, -7, 0, -29, 27,
    -27, 23, 32, 9, 0, 9, 8, 10,
    0, 9, 15, 0, 10, 9, 0, 11,
    19, -50, -8, -57, -48, 19, -48, 26,
    24, 12, 13, 13, 12, 0, 19, 13,
    7, 0, 11, 10, 10, 12, 10, 14,
    10, 25, 0, 7, -32, 22, -36, 23,
    0, 23, 19, 29, 27, 24, 20, 29,
    32, 25, 29, 35, 20, 30, 12, 0,
    25, 0, 0, 0, 0, 0, 0, 26,
    10, 10, 10, 0, 10, 28, 23, 18,
    27, 16, 16, 9, 18, 11, 12, 0,
    18, 18, 0, 0, 0, 0, 0, 11,
    16, 13, 11, 12, 19, 12, 13, 11,
    12, 13, 18, 14, 11, 6, 11, 19,
    19, 14, 21, 8, 0, 13, 8, 7,
    7, 0, 8, 15, 19, 0, 16, 14,
    14, 0, 16, 8, 9, 0, 16, 16,
    0, 0, 0, 0, 0, 11, 24, 11,
    10, 12, 25, 11, 9, 6, 11, 10,
    25, 12, 14, -17, 7, -15, -12, -11,
    -21, 0, 9, 14, 18, 16, 16, 8,
    9, 15, 11, 10, 16, 14, 14, 15,
    13, 15, 11, 12, 14, 13, 12, 0,
    11, 11, -15, 11, 22, 11, 9, 11,
    22, 10, 8, 7, 12, 10, 22, 12,
    17, 0, 9, 0, 0, -12, 0, 0,
    0, 13, 0, 0, 0, 18, 0, 15,
    12, 13, 15, 14, 14, 0, 13, 0,
    13, 8, 18, 15, 20, 14, 19, 8,
    7, 13, 25, 12, 11, 13, 27, 12,
    12, 15, 12, 11, 27, 13, 14, -19,
    8, -16, -15, -6, -23, 0, 10, 15,
    18, 17, 18, 7, 17, 16, 11, 15,
    17, 12, 13, 17, 14, 16, 10, 12,
    14, 13, 12, 0, 11, 10, 36, 6,
    9, 6, 0, 9, 9, 8, 26, 7,
    9, 7, 10, 9, 15, -19, 0, -23,
    -21, 26, -22, 29, 15, 12, 0, 0,
    0, 0, 18, 13, 8, 8, 0, 11,
    11, 0, 14, 0, 12, 11, 0, 0,
    0, 29, 0, 25, 15, 14, 20, 14,
    12, 15, 20, 14, 14, 12, 15, 13,
    20, 15, 16, 0, 9, 0, 0, 0,
    0, 10, 14, 18, 19, 17, 19, 13,
    12, 19, 11, 10, 19, 8, 8, 17,
    8, 18, 8, 12, 9, 7, 0, 0,
    0, 0, -27, 18, 0, 20, 18, 18,
    8, 19, 17, 18, 20, 20, 7, 21,
    18, 23, 17, 28, 29, 12, 29, 19,
    -39, 11, -33, -37, -35, -9, -22, 3,
    3, 3, 22, -33, -34, -35, -33, -36,
    -32, -25, 0, -31, -44, -45, -45, -41,
    0, 12, 15, 13, 11, 13, 18, 13,
    11, 12, 13, 14, 17, 15, 8, 8,
    12, 20, 20, 15, 22, 0, 0, 14,
    0, 0, 0, 0, 0, 15, 0, 0,
    17, 9, 9, 0, 7, 0, 0, 0,
    11, 11, 0, 0, 0, 0, 0, 32,
    0, 34, 31, 32, 7, 32, 31, 32,
    33, 34, 7, 35, 12, 30, 32, 41,
    41, 36, 42, 26, -18, 34, -17, -17,
    -17, 0, -23, 36, 17, 15, 36, -11,
    -11, -17, -12, -18, -13, -14, 0, -11,
    0, -9, 0, -14, -9, 22, 11, 23,
    21, 22, 10, 22, 21, 22, 23, 23,
    10, 25, 7, 19, 22, 30, 30, 25,
    32, 14, -12, 24, -7, -7, 0, 0,
    -9, 26, 7, 7, 27, -7, -7, -8,
    -9, -8, -9, -6, 0, -7, 0, -7,
    0, -6, 28, 16, 0, 17, 15, 16,
    0, 16, 19, 18, 18, 18, 0, 18,
    0, 10, 12, 21, 21, 21, 23, 25,
    8, 19, -8, 0, -8, 0, 10, 20,
    0, 0, 19, 0, 0, -9, 0, 0,
    0, 0, -7, -9, -30, 21, -25, 17,
    -18, 34, 0, 35, 33, 34, 0, 34,
    32, 34, 35, 36, 0, 36, 11, 29,
    33, 42, 42, 37, 44, 24, -25, 36,
    -28, -24, -27, 0, -25, 37, 16, 16,
    38, -18, -17, -28, -19, -28, -20, -20,
    0, -17, -8, -13, -9, -23, 22, 12,
    0, 14, 12, 13, 9, 14, 11, 15,
    15, 15, 12, 15, 16, 0, 8, 13,
    14, 11, 15, 13, 13, 16, 0, 0,
    0, 0, 0, 17, 0, 0, 17, 0,
    0, 0, 0, 0, 0, 13, 0, 0,
    -17, 8, -18, 11, 25, 15, 17, 15,
    13, 18, 17, 17, 15, 20, 18, 15,
    18, 18, 12, -39, 0, -31, -28, 15,
    -35, 18, 17, 20, 19, 18, 19, 7,
    22, 21, 16, 16, 8, 19, 19, 17,
    24, 17, 18, 13, 0, 0, -8, 18,
    -10, 16, 17, 13, 27, 13, 11, 13,
    27, 12, 11, 9, 13, 12, 28, 14,
    17, -47, 8, -25, -21, -6, -35, 0,
    17, 16, 25, 23, 25, 11, 17, 17,
    10, 10, 18, 13, 13, 24, 12, 24,
    13, 18, 8, 12, 0, 7, 0, 9,
    14, 8, 27, 8, 0, 8, 27, 7,
    0, 0, 8, 7, 28, 9, 10, -50,
    0, -25, -22, 0, -31, 0, 15, 11,
    18, 16, 17, 8, 16, 12, 13, 11,
    12, 14, 11, 16, 13, 16, 11, 20,
    11, 15, 0, 9, 0, 12, 7, 28,
    22, 34, 33, 29, 24, 34, 37, 32,
    35, 41, 23, 36, 17, 0, 30, 0,
    0, 0, 7, 0, 9, 32, 14, 13,
    13, 0, 14, 33, 28, 21, 32, 20,
    20, 12, 21, 14, 15, 9, 22, 21,
    0, 8, 0, 0, 15, 11, 28, 10,
    9, 11, 27, 10, 9, 7, 11, 9,
    28, 11, 10, -46, 7, -26, -21, 0,
    -34, 0, 16, 13, 26, 23, 25, 0,
    16, 15, 11, 10, 15, 14, 14, 24,
    14, 23, 14, 18, 0, 13, 0, 7,
    0, 10, -11, 28, 21, 29, 27, 28,
    23, 28, 27, 28, 30, 30, 22, 31,
    28, 34, 27, 37, 38, 31, 38, 30,
    -10, 30, -14, -13, -14, 19, -11, 33,
    21, 21, 32, 13, 12, -16, 11, -15,
    10, 0, 19, 13, 21, 15, 20, 0,
    24, 11, 24, 14, 13, 18, 23, 17,
    14, 18, 18, 16, 25, 18, 17, -8,
    0, -16, -14, 14, -20, 17, 20, 20,
    11, 11, 10, 12, 22, 22, 14, 22,
    18, 14, 14, 9, 23, 12, 15, 11,
    11, 15, 11, 19, 19, 22, 14, 18,
    21, 18, 16, 19, 22, 18, 19, 18,
    19, 18, 23, 19, 12, -33, 7, -32,
    -27, 0, -29, 0, 15, 21, 20, 20,
    20, 14, 16, 23, 10, 23, 20, 8,
    7, 19, 9, 21, 7, 14, 15, 12,
    0, 0, 0, 9, 10, 24, 25, 28,
    27, 25, 26, 28, 31, 37, 29, 33,
    26, 30, 16, 0, 25, 0, 0, 0,
    0, 0, 11, 27, 17, 16, 16, 0,
    13, 28, 28, 21, 28, 19, 19, 15,
    19, 17, 15, 10, 24, 20, 6, 0,
    0, 7, 12, 23, 22, 28, 26, 24,
    23, 28, 38, 35, 29, 33, 24, 29,
    14, 0, 21, 0, 0, 0, 0, 7,
    10, 27, 14, 14, 14, 0, 16, 28,
    27, 30, 27, 19, 19, 13, 25, 15,
    14, 9, 21, 19, 0, 10, 0, 8,
    33, 8, 15, 8, 0, 12, 15, 11,
    23, 9, 12, 10, 15, 12, 14, -46,
    0, -22, -21, 23, -26, 26, 15, 14,
    0, 0, 0, 12, 18, 16, 10, 12,
    9, 13, 12, 0, 14, 7, 12, 12,
    11, 14, 16, 25, 15, 26, 28, 7,
    14, 6, 0, 9, 13, 7, 15, 0,
    7, 0, 14, 8, 11, -15, -10, -10,
    -10, 17, -9, 22, 18, 11, 11, 6,
    11, 0, 12, 12, 0, 0, 7, 10,
    10, 10, 10, 7, 11, 19, 0, 0,
    -7, 20, -11, 20, 12, 13, 18, 13,
    11, 14, 19, 13, 21, 13, 14, 12,
    20, 14, 9, -35, 0, -33, -28, 0,
    -29, 0, 12, 16, 18, 17, 18, 0,
    16, 18, 11, 15, 15, 11, 10, 16,
    12, 19, 9, 12, 19, 12, 0, 0,
    0, 8, 14, 18, 21, 18, 17, 20,
    22, 19, 23, 18, 20, 18, 22, 20,
    12, -34, 6, -31, -26, 0, -28, 0,
    14, 22, 20, 19, 19, 14, 17, 23,
    10, 24, 20, 11, 7, 18, 12, 20,
    7, 13, 15, 12, 0, 0, 0, 9,
    18, 14, 27, 14, 12, 15, 27, 14,
    14, 10, 14, 13, 28, 15, 18, -44,
    9, -27, -22, 0, -36, 0, 18, 17,
    27, 25, 27, 8, 16, 18, 12, 9,
    19, 15, 15, 26, 14, 26, 15, 20,
    8, 14, 0, 0, 0, 9, 17, 12,
    26, 12, 11, 13, 26, 12, 9, 9,
    12, 11, 27, 13, 17, -48, 7, -26,
    -22, 0, -36, 0, 17, 15, 25, 23,
    24, 9, 18, 16, 10, 9, 17, 12,
    13, 23, 12, 24, 13, 18, 7, 12,
    0, 7, 0, 10, 8, 19, 21, 19,
    17, 20, 23, 20, 18, 0, 20, 19,
    22, 20, 18, -54, 8, -23, -22, 0,
    -31, 0, 7, 23, 14, 10, 14, 12,
    13, 24, 7, 13, 21, 9, 9, 13,
    7, 11, 7, 8, 11, 10, 15, 16,
    14, 8, -10, 0, 25, 0, 0, 0,
    26, 0, 0, 0, 0, 0, 26, 0,
    10, -54, 0, -20, -18, -36, -30, -34,
    10, 8, 14, 12, 13, 12, 10, 9,
    9, 12, 10, 10, 10, 12, 9, 12,
    10, 15, 13, 12, 12, 0, 11, 9,
    15, 9, 20, 8, 7, 10, 20, 8,
    15, 6, 9, 7, 20, 10, 21, -47,
    0, -26, -19, 0, -32, 8, 15, 12,
    15, 14, 14, 13, 12, 13, 11, 13,
    13, 12, 12, 13, 12, 14, 11, 13,
    13, 12, 7, 10, 0, 9, 20, 6,
    15, 6, 0, 8, 17, 7, 10, 0,
    7, 0, 16, 8, 13, -30, 0, -20,
    -19, 8, -25, 15, 10, 10, 0, 0,
    0, 17, 0, 12, 12, 14, 8, 16,
    16, 0, 15, 0, 12, 10, 17, 13,
    18, 15, 17, 11, 8, 20, 20, 20,
    19, 21, 21, 21, 26, 19, 22, 20,
    21, 22, 11, -46, 8, -31, -28, 0,
    -40, 0, 9, 24, 14, 13, 14, 0,
    14, 26, 19, 20, 22, 17, 17, 13,
    19, 14, 12, 8, 23, 19, 0, 6,
    0, 0, 0, 0, 19, 0, 0, 0,
    20, 0, 0, 0, 0, 0, 20, 0,
    17, -58, 0, -15, -14, -25, -22, -18,
    0, 0, 0, 0, 0, 22, 0, 6,
    15, 14, 7, 17, 16, 0, 15, 0,
    15, 0, 20, 17, 23, 17, 22, 8,
    0, 0, 20, 0, 0, 0, 21, 0,
    0, 0, 0, 0, 21, 0, 18, -57,
    0, -13, -13, -21, -21, -19, 0, 0,
    0, 0, 0, 23, 0, 7, 16, 15,
    8, 18, 18, 0, 16, 0, 15, 0,
    22, 18, 25, 18, 23, 9, 29, 0,
    13, 0, 0, 7, 12, 0, 19, 0,
    7, 0, 14, 7, 15, -52, 0, -21,
    -21, 19, -28, 21, 10, 9, 0, 0,
    0, 21, 12, 11, 9, 12, 9, 12,
    11, 0, 12, 0, 8, 9, 14, 14,
    17, 21, 16, 18, 0, 0, 21, 0,
    0, 0, 22, 0, 0, 0, 0, 0,
    22, 0, 19, -56, 0, -12, -12, -27,
    -20, -18, 0, 7, 0, 0, 0, 24,
    0, 8, 17, 16, 9, 19, 19, 0,
    17, 0, 16, 0, 23, 19, 26, 19,
    24, 10, 18, 6, 17, 6, 0, 7,
    18, 7, 12, 0, 7, 0, 18, 8,
    15, -53, 0, -22, -21, 0, -30, 13,
    12, 10, 0, 0, 0, 14, 10, 11,
    12, 13, 11, 15, 14, 0, 14, 0,
    15, 13, 18, 14, 16, 13, 15, 11
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 52,
    .right_class_cnt     = 46,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_ysFont = {
#else
lv_font_t ui_font_ysFont = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 23,          /*The maximum line height required by the font*/
    .base_line = 6,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -6,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_YSFONT*/

