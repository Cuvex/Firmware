#ifndef KEYBOARD_KEY_MAPPING_H
#define KEYBOARD_KEY_MAPPING_H

#include <touchgfx/widgets/Keyboard.hpp>
using namespace touchgfx;

/************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ***************************************************************************** LAYOUT 1 - Teclado alpha/num (alfabético) ************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/
static const Keyboard::KeyMapping keyMappingsAlphaLower[27] =
{
		{ 1, 'q'},  // q
		{ 2, 'w'},  // w
		{ 3, 'e'},  // e
		{ 4, 'r'},  // r
		{ 5, 't'},  // t
		{ 6, 'y'},  // y
		{ 7, 'u'},  // u
		{ 8, 'i'},  // i
		{ 9, 'o'},  // o
		{10, 'p'},  // p
		{11, 'a'},  // a
		{12, 's'},  // s
		{13, 'd'},  // d
		{14, 'f'},  // f
		{15, 'g'},  // g
		{16, 'h'},  // h
		{17, 'j'},  // j
		{18, 'k'},  // k
		{19, 'l'},  // l
		{20, 'z'},  // z
		{21, 'x'},  // x
		{22, 'c'},  // c
		{23, 'v'},  // v
		{24, 'b'},  // b
		{25, 'n'},  // n
		{26, 'm'},  // m
		{27, ' '},  // space
};

static const Keyboard::KeyMappingList keyMappingListAlphaLower =
{
		keyMappingsAlphaLower,
		27
};

static const Keyboard::KeyMapping keyMappingsAlphaUpper[27] =
{
		{ 1, 'Q'},  // Q
		{ 2, 'W'},  // W
		{ 3, 'E'},  // E
		{ 4, 'R'},  // R
		{ 5, 'T'},  // T
		{ 6, 'Y'},  // Y
		{ 7, 'U'},  // U
		{ 8, 'I'},  // I
		{ 9, 'O'},  // O
		{10, 'P'},  // P
		{11, 'A'},  // A
		{12, 'S'},  // S
		{13, 'D'},  // D
		{14, 'F'},  // F
		{15, 'G'},  // G
		{16, 'H'},  // H
		{17, 'J'},  // J
		{18, 'K'},  // K
		{19, 'L'},  // L
		{20, 'Z'},  // Z
		{21, 'X'},  // X
		{22, 'C'},  // C
		{23, 'V'},  // V
		{24, 'B'},  // B
		{25, 'N'},  // N
		{26, 'M'},  // M
		{27, ' '} 	// space
};

static const Keyboard::KeyMappingList keyMappingListAlphaUpper =
{
		keyMappingsAlphaUpper,
		27
};

/************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ***************************************************************************** LAYOUT 2 - Teclado alpha/num (num + simb) ************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/
static const Keyboard::KeyMapping keyMappingsNumLower[26] =
{
		{ 1,  '1'},  // 1
		{ 2,  '2'},  // 2
		{ 3,  '3'},  // 3
		{ 4,  '4'},  // 4
		{ 5,  '5'},  // 5
		{ 6,  '6'},  // 6
		{ 7,  '7'},  // 7
		{ 8,  '8'},  // 8
		{ 9,  '9'},  // 9
		{10,  '0'},  // 0
		{11,  '-'},  // -
		{12,  '/'},  // /
		{13,  ':'},  // :
		{14,  ';'},  // ;
		{15,  '('},  // (
		{16,  ')'},  // )
		{17,  '$'},  // $
		{18,  '&'},  // &
		{19,  '@'},  // @
		{20,  '"'},  // "
		{21,  '.'},  // .
		{22,  ','},  // ,
		{23,  '?'},  // ?
		{24,  '!'},  // !
		{25,  '\''}, // '
		{26,  ' '}   // space
};

static const Keyboard::KeyMappingList keyMappingListNumLower =
{
		keyMappingsNumLower,
		26
};

static const Keyboard::KeyMapping keyMappingsNumUpper[26] =
{
		{1,  '['},  // [
		{2,  ']'},  // ]
		{3,  '{'},  // {
		{4,  '}'},  // }
		{5,  '#'}, 	// #
		{6,  '%'}, 	// %
		{7,  '^'}, 	// ^
		{8,  '*'}, 	// *
		{9,  '+'}, 	// +
		{10, '='}, 	// =
		{11, '_'}, 	// _
		{12, 92},	// \ (unicode - 92)
		{13, '|'}, 	// |
		{14, '~'}, 	// ~
		{15, '<'},  // <
		{16, '>'},  // >
		{17, 163},  // £ (unicode - 163)
		{18, 8364},	// € (unicode - 8364)
		{19, 165}, 	// ¥ (unicode - 165)
		{20, 183}, 	// · (unicode - 183)
		{21, '.'},  // .
		{22, ','},  // ,
		{23, '?'},  // ?
		{24, '!'},  // !
		{25,  '\''},// '
		{26, ' '}   // space
};

static const Keyboard::KeyMappingList keyMappingListNumUpper =
{
		keyMappingsNumUpper,
		26
};

/************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************** LAYOUT 3 - Teclado num **********************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/
static const Keyboard::KeyMapping keyMappingsKeyboardNum[10] =
{
		{ 1,  '1'}, // 1
		{ 2,  '2'}, // 2
		{ 3,  '3'}, // 3
		{ 4,  '4'}, // 4
		{ 5,  '5'}, // 5
		{ 6,  '6'}, // 6
		{ 7,  '7'}, // 7
		{ 8,  '8'}, // 8
		{ 9,  '9'},	// 9
		{10,  '0'} 	// 0
};

static const Keyboard::KeyMappingList keyMappingListKeyboardNum =
{
		keyMappingsKeyboardNum,
		10
};

/************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************** LAYOUT 3 - Teclado num **********************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/
static const Keyboard::KeyMapping keyMappingsBIP39[26] =
{
		{ 1, 'Q'},  // Q
		{ 2, 'W'},  // W
		{ 3, 'E'},  // E
		{ 4, 'R'},  // R
		{ 5, 'T'},  // T
		{ 6, 'Y'},  // Y
		{ 7, 'U'},  // U
		{ 8, 'I'},  // I
		{ 9, 'O'},  // O
		{10, 'P'},  // P
		{11, 'A'},  // A
		{12, 'S'},  // S
		{13, 'D'},  // D
		{14, 'F'},  // F
		{15, 'G'},  // G
		{16, 'H'},  // H
		{17, 'J'},  // J
		{18, 'K'},  // K
		{19, 'L'},  // L
		{20, 'Z'},  // Z
		{21, 'X'},  // X
		{22, 'C'},  // C
		{23, 'V'},  // V
		{24, 'B'},  // B
		{25, 'N'},  // N
		{26, 'M'}   // M
};

static const Keyboard::KeyMappingList keyMappingListBIP39 =
{
		keyMappingsBIP39,
		26
};

#endif






