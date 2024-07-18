#pragma once
#include <SDL.h>
/*
 *  The key numbers are defined based on SDLK key code values
 */

constexpr int KEY_UNKNOWN = -1;

constexpr int SCALD_KEY_BACKSPACE = SDLK_BACKSPACE;
constexpr int SCALD_KEY_TAB = SDLK_TAB;
constexpr int SCALD_KEY_CLEAR = SDLK_CLEAR;
constexpr int SCALD_KEY_RETURN = SDLK_RETURN;
constexpr int SCALD_KEY_PAUSE = SDLK_PAUSE;
constexpr int SCALD_KEY_ESCAPE = SDLK_ESCAPE;
constexpr int SCALD_KEY_SPACE = SDLK_SPACE;
constexpr int SCALD_KEY_EXCLAIM = SDLK_EXCLAIM;
constexpr int SCALD_KEY_QUOTEDBL = SDLK_QUOTEDBL;
constexpr int SCALD_KEY_HASH = SDLK_HASH;
constexpr int SCALD_KEY_DOLLAR = SDLK_DOLLAR;
constexpr int SCALD_KEY_AMPERSAND = SDLK_AMPERSAND;
constexpr int SCALD_KEY_QUOTE = SDLK_QUOTE;
constexpr int SCALD_KEY_LEFTPAREN = SDLK_LEFTPAREN;
constexpr int SCALD_KEY_RIGHTPAREN = SDLK_RIGHTPAREN;
constexpr int SCALD_KEY_ASTERISK = SDLK_ASTERISK;
constexpr int SCALD_KEY_PLUS = SDLK_PLUS;
constexpr int SCALD_KEY_COMMA = SDLK_COMMA;
constexpr int SCALD_KEY_MINUS = SDLK_MINUS;
constexpr int SCALD_KEY_PERIOD = SDLK_PERIOD;
constexpr int SCALD_KEY_SLASH = SDLK_SLASH;

constexpr int SCALD_KEY_0 = SDLK_0;
constexpr int SCALD_KEY_1 = SDLK_1;
constexpr int SCALD_KEY_2 = SDLK_2;
constexpr int SCALD_KEY_3 = SDLK_3;
constexpr int SCALD_KEY_4 = SDLK_4;
constexpr int SCALD_KEY_5 = SDLK_5;
constexpr int SCALD_KEY_6 = SDLK_6;
constexpr int SCALD_KEY_7 = SDLK_7;
constexpr int SCALD_KEY_8 = SDLK_8;
constexpr int SCALD_KEY_9 = SDLK_9;

constexpr int SCALD_KEY_COLON = SDLK_COLON;
constexpr int SCALD_KEY_SEMICOLON = SDLK_SEMICOLON;
constexpr int SCALD_KEY_LESS = SDLK_LESS;
constexpr int SCALD_KEY_EQUALS = SDLK_EQUALS;
constexpr int SCALD_KEY_GREATER = SDLK_GREATER;
constexpr int SCALD_KEY_QUESTION = SDLK_QUESTION;
constexpr int SCALD_KEY_AT = SDLK_AT;

constexpr int SCALD_KEY_LEFTBRACKET = SDLK_LEFTBRACKET;
constexpr int SCALD_KEY_BACKSLASH = SDLK_BACKSLASH;
constexpr int SCALD_KEY_RIGHTBRACKET = SDLK_RIGHTBRACKET;
constexpr int SCALD_KEY_CARET = SDLK_CARET;
constexpr int SCALD_KEY_UNDERSCORE = SDLK_UNDERSCORE;
constexpr int SCALD_KEY_BACKQUOTE = SDLK_BACKQUOTE;
constexpr int SCALD_KEY_A = SDLK_a;
constexpr int SCALD_KEY_B = SDLK_b;
constexpr int SCALD_KEY_C = SDLK_c;
constexpr int SCALD_KEY_D = SDLK_d;
constexpr int SCALD_KEY_E = SDLK_e;
constexpr int SCALD_KEY_F = SDLK_f;
constexpr int SCALD_KEY_G = SDLK_g;
constexpr int SCALD_KEY_H = SDLK_h;
constexpr int SCALD_KEY_I = SDLK_i;
constexpr int SCALD_KEY_J = SDLK_j;
constexpr int SCALD_KEY_K = SDLK_k;
constexpr int SCALD_KEY_L = SDLK_l;
constexpr int SCALD_KEY_M = SDLK_m;
constexpr int SCALD_KEY_N = SDLK_n;
constexpr int SCALD_KEY_O = SDLK_o;
constexpr int SCALD_KEY_P = SDLK_p;
constexpr int SCALD_KEY_Q = SDLK_q;
constexpr int SCALD_KEY_R = SDLK_r;
constexpr int SCALD_KEY_S = SDLK_s;
constexpr int SCALD_KEY_T = SDLK_t;
constexpr int SCALD_KEY_U = SDLK_u;
constexpr int SCALD_KEY_V = SDLK_v;
constexpr int SCALD_KEY_W = SDLK_w;
constexpr int SCALD_KEY_X = SDLK_x;
constexpr int SCALD_KEY_Y = SDLK_y;
constexpr int SCALD_KEY_Z = SDLK_z;

constexpr int SCALD_KEY_DELETE = SDLK_DELETE;
constexpr int SCALD_KEY_CAPSLOCK = SDLK_CAPSLOCK;

constexpr int SCALD_KEY_F1 = SDLK_F1;
constexpr int SCALD_KEY_F2 = SDLK_F2;
constexpr int SCALD_KEY_F3 = SDLK_F3;
constexpr int SCALD_KEY_F4 = SDLK_F4;
constexpr int SCALD_KEY_F5 = SDLK_F5;
constexpr int SCALD_KEY_F6 = SDLK_F6;
constexpr int SCALD_KEY_F7 = SDLK_F7;
constexpr int SCALD_KEY_F8 = SDLK_F8;
constexpr int SCALD_KEY_F9 = SDLK_F9;
constexpr int SCALD_KEY_F10 = SDLK_F10;
constexpr int SCALD_KEY_F11 = SDLK_F11;
constexpr int SCALD_KEY_F12 = SDLK_F12;

constexpr int SCALD_KEY_PRINTSCREEN = SDLK_PRINTSCREEN;
constexpr int SCALD_KEY_SCROLLOCK = SDLK_SCROLLLOCK;

constexpr int SCALD_KEY_INSERT = SDLK_INSERT;
constexpr int SCALD_KEY_HOME = SDLK_HOME;
constexpr int SCALD_KEY_PAGEUP = SDLK_PAGEUP;
constexpr int SCALD_KEY_END = SDLK_END;
constexpr int SCALD_KEY_PAGEDOWN = SDLK_PAGEDOWN;

constexpr int SCALD_KEY_RIGHT = SDLK_RIGHT;
constexpr int SCALD_KEY_LEFT = SDLK_LEFT;
constexpr int SCALD_KEY_DOWN = SDLK_DOWN;
constexpr int SCALD_KEY_UP = SDLK_UP;

constexpr int SCALD_KEY_NUMLOCK = SDLK_NUMLOCKCLEAR;
constexpr int SCALD_KEY_KP_DIVIDE = SDLK_KP_DIVIDE;
constexpr int SCALD_KEY_KP_MULTIPLY = SDLK_KP_MULTIPLY;
constexpr int SCALD_KEY_KP_MINUS = SDLK_KP_MINUS;
constexpr int SCALD_KEY_KP_PLUS = SDLK_KP_PLUS;
constexpr int SCALD_KEY_KP_ENTER = SDLK_KP_ENTER;

constexpr int SCALD_KEY_KP1 = SDLK_KP_1;
constexpr int SCALD_KEY_KP2 = SDLK_KP_2;
constexpr int SCALD_KEY_KP3 = SDLK_KP_3;
constexpr int SCALD_KEY_KP4 = SDLK_KP_4;
constexpr int SCALD_KEY_KP5 = SDLK_KP_5;
constexpr int SCALD_KEY_KP6 = SDLK_KP_6;
constexpr int SCALD_KEY_KP7 = SDLK_KP_7;
constexpr int SCALD_KEY_KP8 = SDLK_KP_8;
constexpr int SCALD_KEY_KP9 = SDLK_KP_9;
constexpr int SCALD_KEY_KP0 = SDLK_KP_0;

constexpr int SCALD_KEY_KP_PERIOD = SDLK_KP_PERIOD;

constexpr int SCALD_KEY_LCTRL = SDLK_LCTRL;
constexpr int SCALD_KEY_LSHIFT = SDLK_LSHIFT;
constexpr int SCALD_KEY_LALT = SDLK_LALT;
constexpr int SCALD_KEY_RCTRL = SDLK_RCTRL;
constexpr int SCALD_KEY_RSHIFT = SDLK_RSHIFT;
constexpr int SCALD_KEY_RALT = SDLK_RALT;

// Put windows naming specific keys here
#ifdef _WIN32
constexpr int SCALD_KEY_LWIN = SDLK_LGUI;
constexpr int SCALD_KEY_RWIN = SDLK_RGUI;
#else
constexpr int SCALD_KEY_LGUI = SDLK_LGUI;
constexpr int SCALD_KEY_RGUI = SDLK_RGUI;
#endif
