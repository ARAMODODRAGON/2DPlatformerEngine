#ifndef EVENTS_KEY_CODE_ENUM_H
#define EVENTS_KEY_CODE_ENUM_H
#include "../Common.h"

namespace Events {

	enum class KeyCode : char {
		/// unknown
		UNKNOWN = 0,

		/// symbols
		RETURN = '\r',
		ESCAPE = '\033',
		BACKSPACE = '\b',
		TAB = '\t',
		SPACE = ' ',
		QUOTE = '\'',
		COMMA = ',',
		MINUS = '-',
		PERIOD = '.',
		SLASH = '/',
		SEMICOLON = ';',
		EQUALS = '=',
		
		/// letters
		KEY_A = 'a',
		KEY_B = 'b',
		KEY_C = 'c',
		KEY_D = 'd',
		KEY_E = 'e',
		KEY_F = 'f',
		KEY_G = 'g',
		KEY_H = 'h',
		KEY_I = 'i',
		KEY_J = 'j',
		KEY_K = 'k',
		KEY_L = 'l',
		KEY_M = 'm',
		KEY_N = 'n',
		KEY_O = 'o',
		KEY_P = 'p',
		KEY_Q = 'q',
		KEY_R = 'r',
		KEY_S = 's',
		KEY_T = 't',
		KEY_U = 'u',
		KEY_V = 'v',
		KEY_W = 'w',
		KEY_X = 'x',
		KEY_Y = 'y',
		KEY_Z = 'z',

		/// numbers
		NUM_0 = '0',
		NUM_1 = '1',
		NUM_2 = '2',
		NUM_3 = '3',
		NUM_4 = '4',
		NUM_5 = '5',
		NUM_6 = '6',
		NUM_7 = '7',
		NUM_8 = '8',
		NUM_9 = '9',

		/// TODO: add more keys
	};

}

#endif // !EVENTS_KEY_CODE_ENUM_H