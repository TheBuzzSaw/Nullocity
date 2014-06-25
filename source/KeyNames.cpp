#include "KeyNames.hpp"

static const KeyName KeyNames[] = {
    {"Return", SDLK_RETURN},
    {"Escape", SDLK_ESCAPE},
    {"Backspace", SDLK_BACKSPACE},
    {"Tab", SDLK_TAB},
    {"Space", SDLK_SPACE},
    {"!", SDLK_EXCLAIM},
    {"\"", SDLK_QUOTEDBL},
    {"#", SDLK_HASH},
    {"%", SDLK_PERCENT},
    {"$", SDLK_DOLLAR},
    {"&", SDLK_AMPERSAND},
    {"'", SDLK_QUOTE},
    {"(", SDLK_LEFTPAREN},
    {")", SDLK_RIGHTPAREN},
    {"*", SDLK_ASTERISK},
    {"+", SDLK_PLUS},
    {",", SDLK_COMMA},
    {"-", SDLK_MINUS},
    {".", SDLK_PERIOD},
    {"/", SDLK_SLASH},
    {"0", SDLK_0},
    {"1", SDLK_1},
    {"2", SDLK_2},
    {"3", SDLK_3},
    {"4", SDLK_4},
    {"5", SDLK_5},
    {"6", SDLK_6},
    {"7", SDLK_7},
    {"8", SDLK_8},
    {"9", SDLK_9},
    {":", SDLK_COLON},
    {";", SDLK_SEMICOLON},
    {"<", SDLK_LESS},
    {"=", SDLK_EQUALS},
    {">", SDLK_GREATER},
    {"?", SDLK_QUESTION},
    {"@", SDLK_AT},
    {"[", SDLK_LEFTBRACKET},
    {"\\", SDLK_BACKSLASH},
    {"]", SDLK_RIGHTBRACKET},
    {"^", SDLK_CARET},
    {"_", SDLK_UNDERSCORE},
    {"`", SDLK_BACKQUOTE},
    {"A", SDLK_a},
    {"B", SDLK_b},
    {"C", SDLK_c},
    {"D", SDLK_d},
    {"E", SDLK_e},
    {"F", SDLK_f},
    {"G", SDLK_g},
    {"H", SDLK_h},
    {"I", SDLK_i},
    {"J", SDLK_j},
    {"K", SDLK_k},
    {"L", SDLK_l},
    {"M", SDLK_m},
    {"N", SDLK_n},
    {"O", SDLK_o},
    {"P", SDLK_p},
    {"Q", SDLK_q},
    {"R", SDLK_r},
    {"S", SDLK_s},
    {"T", SDLK_t},
    {"U", SDLK_u},
    {"V", SDLK_v},
    {"W", SDLK_w},
    {"X", SDLK_x},
    {"Y", SDLK_y},
    {"Z", SDLK_z},
    {"CapsLock", SDLK_CAPSLOCK},
    {"F1", SDLK_F1},
    {"F2", SDLK_F2},
    {"F3", SDLK_F3},
    {"F4", SDLK_F4},
    {"F5", SDLK_F5},
    {"F6", SDLK_F6},
    {"F7", SDLK_F7},
    {"F8", SDLK_F8},
    {"F9", SDLK_F9},
    {"F10", SDLK_F10},
    {"F11", SDLK_F11},
    {"F12", SDLK_F12},
    {"PrintScreen", SDLK_PRINTSCREEN},
    {"ScrollLock", SDLK_SCROLLLOCK},
    {"Pause", SDLK_PAUSE},
    {"Insert", SDLK_INSERT},
    {"Home", SDLK_HOME},
    {"PageUp", SDLK_PAGEUP},
    {"Delete", SDLK_DELETE},
    {"End", SDLK_END},
    {"PageDown", SDLK_PAGEDOWN},
    {"Right", SDLK_RIGHT},
    {"Left", SDLK_LEFT},
    {"Down", SDLK_DOWN},
    {"Up", SDLK_UP},
    {"Numlock", SDLK_NUMLOCKCLEAR},
    {"Keypad /", SDLK_KP_DIVIDE},
    {"Keypad *", SDLK_KP_MULTIPLY},
    {"Keypad -", SDLK_KP_MINUS},
    {"Keypad +", SDLK_KP_PLUS},
    {"Keypad Enter", SDLK_KP_ENTER},
    {"Keypad 1", SDLK_KP_1},
    {"Keypad 2", SDLK_KP_2},
    {"Keypad 3", SDLK_KP_3},
    {"Keypad 4", SDLK_KP_4},
    {"Keypad 5", SDLK_KP_5},
    {"Keypad 6", SDLK_KP_6},
    {"Keypad 7", SDLK_KP_7},
    {"Keypad 8", SDLK_KP_8},
    {"Keypad 9", SDLK_KP_9},
    {"Keypad 0", SDLK_KP_0},
    {"Keypad .", SDLK_KP_PERIOD},
    {"Application", SDLK_APPLICATION},
    {"Power", SDLK_POWER},
    {"Keypad =", SDLK_KP_EQUALS},
    {"F13", SDLK_F13},
    {"F14", SDLK_F14},
    {"F15", SDLK_F15},
    {"F16", SDLK_F16},
    {"F17", SDLK_F17},
    {"F18", SDLK_F18},
    {"F19", SDLK_F19},
    {"F20", SDLK_F20},
    {"F21", SDLK_F21},
    {"F22", SDLK_F22},
    {"F23", SDLK_F23},
    {"F24", SDLK_F24},
    {"Execute", SDLK_EXECUTE},
    {"Help", SDLK_HELP},
    {"Menu", SDLK_MENU},
    {"Select", SDLK_SELECT},
    {"Stop", SDLK_STOP},
    {"Again", SDLK_AGAIN},
    {"Undo", SDLK_UNDO},
    {"Cut", SDLK_CUT},
    {"Copy", SDLK_COPY},
    {"Paste", SDLK_PASTE},
    {"Find", SDLK_FIND},
    {"Mute", SDLK_MUTE},
    {"VolumeUp", SDLK_VOLUMEUP},
    {"VolumeDown", SDLK_VOLUMEDOWN},
    {"Keypad ,", SDLK_KP_COMMA},
    {"Keypad = (AS400)", SDLK_KP_EQUALSAS400},
    {"AltErase", SDLK_ALTERASE},
    {"SysReq", SDLK_SYSREQ},
    {"Cancel", SDLK_CANCEL},
    {"Clear", SDLK_CLEAR},
    {"Prior", SDLK_PRIOR},
    {"Return", SDLK_RETURN2},
    {"Separator", SDLK_SEPARATOR},
    {"Out", SDLK_OUT},
    {"Oper", SDLK_OPER},
    {"Clear / Again", SDLK_CLEARAGAIN},
    {"CrSel", SDLK_CRSEL},
    {"ExSel", SDLK_EXSEL},
    {"Keypad 00", SDLK_KP_00},
    {"Keypad 000", SDLK_KP_000},
    {"ThousandsSeparator", SDLK_THOUSANDSSEPARATOR},
    {"DecimalSeparator", SDLK_DECIMALSEPARATOR},
    {"CurrencyUnit", SDLK_CURRENCYUNIT},
    {"CurrencySubUnit", SDLK_CURRENCYSUBUNIT},
    {"Keypad (", SDLK_KP_LEFTPAREN},
    {"Keypad )", SDLK_KP_RIGHTPAREN},
    {"Keypad {", SDLK_KP_LEFTBRACE},
    {"Keypad }", SDLK_KP_RIGHTBRACE},
    {"Keypad Tab", SDLK_KP_TAB},
    {"Keypad Backspace", SDLK_KP_BACKSPACE},
    {"Keypad A", SDLK_KP_A},
    {"Keypad B", SDLK_KP_B},
    {"Keypad C", SDLK_KP_C},
    {"Keypad D", SDLK_KP_D},
    {"Keypad E", SDLK_KP_E},
    {"Keypad F", SDLK_KP_F},
    {"Keypad XOR", SDLK_KP_XOR},
    {"Keypad ^", SDLK_KP_POWER},
    {"Keypad %", SDLK_KP_PERCENT},
    {"Keypad <", SDLK_KP_LESS},
    {"Keypad >", SDLK_KP_GREATER},
    {"Keypad &", SDLK_KP_AMPERSAND},
    {"Keypad &&", SDLK_KP_DBLAMPERSAND},
    {"Keypad |", SDLK_KP_VERTICALBAR},
    {"Keypad ||", SDLK_KP_DBLVERTICALBAR},
    {"Keypad :", SDLK_KP_COLON},
    {"Keypad #", SDLK_KP_HASH},
    {"Keypad Space", SDLK_KP_SPACE},
    {"Keypad @", SDLK_KP_AT},
    {"Keypad !", SDLK_KP_EXCLAM},
    {"Keypad MemStore", SDLK_KP_MEMSTORE},
    {"Keypad MemRecall", SDLK_KP_MEMRECALL},
    {"Keypad MemClear", SDLK_KP_MEMCLEAR},
    {"Keypad MemAdd", SDLK_KP_MEMADD},
    {"Keypad MemSubtract", SDLK_KP_MEMSUBTRACT},
    {"Keypad MemMultiply", SDLK_KP_MEMMULTIPLY},
    {"Keypad MemDivide", SDLK_KP_MEMDIVIDE},
    {"Keypad +/-", SDLK_KP_PLUSMINUS},
    {"Keypad Clear", SDLK_KP_CLEAR},
    {"Keypad ClearEntry", SDLK_KP_CLEARENTRY},
    {"Keypad Binary", SDLK_KP_BINARY},
    {"Keypad Octal", SDLK_KP_OCTAL},
    {"Keypad Decimal", SDLK_KP_DECIMAL},
    {"Keypad Hexadecimal", SDLK_KP_HEXADECIMAL},
    {"Left Ctrl", SDLK_LCTRL},
    {"Left Shift", SDLK_LSHIFT},
    {"Left Alt", SDLK_LALT},
    {"Left GUI", SDLK_LGUI},
    {"Right Ctrl", SDLK_RCTRL},
    {"Right Shift", SDLK_RSHIFT},
    {"Right Alt", SDLK_RALT},
    {"Right GUI", SDLK_RGUI},
    {"ModeSwitch", SDLK_MODE},
    {"AudioNext", SDLK_AUDIONEXT},
    {"AudioPrev", SDLK_AUDIOPREV},
    {"AudioStop", SDLK_AUDIOSTOP},
    {"AudioPlay", SDLK_AUDIOPLAY},
    {"AudioMute", SDLK_AUDIOMUTE},
    {"MediaSelect", SDLK_MEDIASELECT},
    {"WWW", SDLK_WWW},
    {"Mail", SDLK_MAIL},
    {"Calculator", SDLK_CALCULATOR},
    {"Computer", SDLK_COMPUTER},
    {"AC Search", SDLK_AC_SEARCH},
    {"AC Home", SDLK_AC_HOME},
    {"AC Back", SDLK_AC_BACK},
    {"AC Forward", SDLK_AC_FORWARD},
    {"AC Stop", SDLK_AC_STOP},
    {"AC Refresh", SDLK_AC_REFRESH},
    {"AC Bookmarks", SDLK_AC_BOOKMARKS},
    {"BrightnessDown", SDLK_BRIGHTNESSDOWN},
    {"BrightnessUp", SDLK_BRIGHTNESSUP},
    {"DisplaySwitch", SDLK_DISPLAYSWITCH},
    {"KBDIllumToggle", SDLK_KBDILLUMTOGGLE},
    {"KBDIllumDown", SDLK_KBDILLUMDOWN},
    {"KBDIllumUp", SDLK_KBDILLUMUP},
    {"Eject", SDLK_EJECT},
    {"Sleep", SDLK_SLEEP},
    {nullptr, 0}
    };

const KeyName* GetKeyNames()
{
    return KeyNames;
}