#ifndef LUT_H
#define LUT_H

#define LEFT_SHIFT_KEY 42
#define RIGHT_SHIFT_KEY 54

#include <stdlib.h>

typedef struct lkey {
  int key_code;
  char * key_name;
  char key_value;
  char key_shift_value;
} Linux_Keys;

// Note: The lookup table has to be in ascending order for the starting number.
Linux_Keys linux_lookup_table[] = {
  {0, "KEY_RESERVED", '\0', '\0'}, {1, "KEY_ESC", '\0', '\0'}, {2, "KEY_1", '1', '!'}, {3, "KEY_2", '2', '@'}, {4, "KEY_3", '3', '#'}, {5, "KEY_4", '4', '$'}, {6, "KEY_5",'5', '%'}, {7, "KEY_6", '6', '^'}, {8, "KEY_7", '7', '&'}, {9, "KEY_8", '8', '*'}, 
  {10, "KEY_9", '9', '('}, {11, "KEY_0", '0', ')'}, {12, "KEY_MINUS", '-', '_'}, {13, "KEY_EQUAL", '=', '+'}, {14, "KEY_BACKSPACE", '\0', '\0'}, {15, "KEY_TAB", '\0', '\0'}, {16, "KEY_Q", 'q', 'Q'}, {17, "KEY_W", 'w', 'W'}, {18, "KEY_E", 'e', 'E'}, {19, "KEY_R", 'r', 'R'},
  {20, "KEY_T", 't', 'T'}, {21, "KEY_Y", 'y', 'Y'}, {22, "KEY_U", 'u', 'U'}, {23, "KEY_I", 'i', 'I'}, {24, "KEY_O", 'o', 'O'}, {25, "KEY_P", 'p', 'P'}, {26, "KEY_LEFTBRACE", '[', '{'}, {27, "KEY_RIGHTBRACE", ']', '}'}, {28, "KEY_ENTER", '\0', '\0'}, {29, "KEY_LEFTCTRL", '\0', '\0'},
  {30, "KEY_A", 'a', 'A'}, {31, "KEY_S", 's', 'S'}, {32, "KEY_D", 'd', 'D'}, {33, "KEY_F", 'f', 'F'}, {34, "KEY_G", 'g', 'G'}, {35, "KEY_H", 'h', 'H'}, {36, "KEY_J", 'j', 'J'}, {37, "KEY_K", 'k', 'K'}, {38, "KEY_L", 'l', 'L'}, {39, "KEY_SEMICOLON", ';', ':'},
  {40, "KEY_APOSTROPHE", '\'', '\"'}, {41, "KEY_GRAVE", '`', '~'}, {42, "KEY_LEFTSHIFT", '\0', '\0'}, {43, "KEY_BACKSLASH", '\\', '|'}, {44, "KEY_Z", 'z', 'Z'}, {45, "KEY_X", 'x', 'X'}, {46, "KEY_C", 'c', 'C'}, {47, "KEY_V", 'v', 'V'}, {48, "KEY_B", 'b', 'B'}, {49, "KEY_N", 'n', 'N'},
  {50, "KEY_M", 'm', 'M'}, {51, "KEY_COMMA", ',', '<'}, {52, "KEY_DOT", '.', '>'}, {53, "KEY_SLASH", '/', '?'}, {54, "KEY_RIGHTSHIFT", '\0', '\0'}, {55, "KEY_KPASTERISK", '\0', '\0'}, {56, "KEY_LEFTALT", '\0', '\0'}, {57, "KEY_SPACE", ' ', '\0'}, 
  
  {58, "KEY_CAPSLOCK", '\0', '\0'}, {59, "KEY_F1", '\0', '\0'},
  {60, "KEY_F2", '\0', '\0'}, {61, "KEY_F3", '\0', '\0'}, {62, "KEY_F4", '\0', '\0'}, {63, "KEY_F5", '\0', '\0'}, {64, "KEY_F6", '\0', '\0'}, {65, "KEY_F7", '\0', '\0'}, {66, "KEY_F8", '\0', '\0'}, {67, "KEY_F9", '\0', '\0'}, {68, "KEY_F10", '\0', '\0'}, {69, "KEY_NUMLOCK", '\0', '\0'},
  {70, "KEY_SCROLLLOCK", '\0', '\0'}, {71, "KEY_KP7", '\0', '\0'}, {72, "KEY_KP8", '\0', '\0'}, {73, "KEY_KP9", '\0', '\0'}, {74, "KEY_KPMINUS", '\0', '\0'}, {75, "KEY_KP4", '\0', '\0'}, {76, "KEY_KP5", '\0', '\0'}, {77, "KEY_KP6", '\0', '\0'}, {78, "KEY_KPPLUS", '\0', '\0'}, {79, "KEY_KP1", '\0', '\0'},
  {80, "KEY_KP2", '\0', '\0'}, {81, "KEY_KP3", '\0', '\0'}, {82, "KEY_KP0", '\0', '\0'}, {83, "KEY_KPDOT", '\0', '\0'}, {84, "NONE", '\0', '\0'}, {85, "KEY_ZENKAKUHANKAKU", '\0', '\0'}, {86, "KEY_102ND", '\0', '\0'}, {87, "KEY_F11", '\0', '\0'}, {88, "KEY_F12", '\0', '\0'}, {89, "KEY_RO", '\0', '\0'},
  {90, "KEY_KATAKANA", '\0', '\0'}, {91, "KEY_HIRAGANA", '\0', '\0'}, {92, "KEY_HENKAN", '\0', '\0'}, {93, "KEY_KATAKANAHIRAGANA", '\0', '\0'}, {94, "KEY_MUHENKAN", '\0', '\0'}, {95, "KEY_KPJPCOMMA", '\0', '\0'}, {96, "KEY_KPENTER", '\0', '\0'}, {97, "KEY_RIGHTCTRL", '\0', '\0'}, {98, "KEY_KPSLASH", '\0', '\0'}, {99, "KEY_SYSRQ", '\0', '\0'},
  {100, "KEY_RIGHTALT", '\0', '\0'}, {101, "KEY_LINEFEED", '\0', '\0'}, {102, "KEY_HOME", '\0', '\0'}, {103, "KEY_UP", '\0', '\0'}, {104, "KEY_PAGEUP", '\0', '\0'}, {105, "KEY_LEFT", '\0', '\0'}, {106, "KEY_RIGHT", '\0', '\0'}, {107, "KEY_END", '\0', '\0'}, {108, "KEY_DOWN", '\0', '\0'}, {109, "KEY_PAGEDOWN", '\0', '\0'},
  {110, "KEY_INSERT", '\0', '\0'}, {111, "KEY_DELETE", '\0', '\0'}, {112, "KEY_MACRO", '\0', '\0'}, {113, "KEY_MUTE", '\0', '\0'}, {114, "KEY_VOLUMEDOWN", '\0', '\0'}, {115, "KEY_VOLUMEUP", '\0', '\0'}, {116, "KEY_POWER", '\0', '\0'}, {117, "KEY_KPEQUAL", '\0', '\0'}, {118, "KEY_KPPLUSMINUS", '\0', '\0'}, {119, "KEY_PAUSE", '\0', '\0'},
  {120, "KEY_SCALE", '\0', '\0'}, {121, "KEY_KPCOMMA", '\0', '\0'}, {122, "KEY_HANGEUL", '\0', '\0'}, {123, "KEY_HANJA", '\0', '\0'}, {124, "KEY_YEN", '\0', '\0'}, {125, "KEY_LEFTMETA", '\0', '\0'}, {126, "KEY_RIGHTMETA", '\0', '\0'}, {127, "KEY_COMPOSE", '\0', '\0'}, {128, "KEY_STOP", '\0', '\0'}, {129, "KEY_AGAIN", '\0', '\0'},
  {130, "KEY_PROPS", '\0', '\0'}, {131, "KEY_UNDO", '\0', '\0'}, {132, "KEY_FRONT", '\0', '\0'}, {133, "KEY_COPY", '\0', '\0'}, {134, "KEY_OPEN", '\0', '\0'}, {135, "KEY_PASTE", '\0', '\0'}, {136, "KEY_FIND", '\0', '\0'}, {137, "KEY_CUT", '\0', '\0'}, {138, "KEY_HELP", '\0', '\0'}, {139, "KEY_MENU", '\0', '\0'},
  {140, "KEY_CALC", '\0', '\0'}, {141, "KEY_SETUP", '\0', '\0'}, {142, "KEY_SLEEP", '\0', '\0'}, {143, "KEY_WAKEUP", '\0', '\0'}, {144, "KEY_FILE", '\0', '\0'}, {145, "KEY_SENDFILE", '\0', '\0'}, {146, "KEY_DELETEFILE", '\0', '\0'}, {147, "KEY_XFER", '\0', '\0'}, {148, "KEY_PROG1", '\0', '\0'}, {149, "KEY_PROG2", '\0', '\0'},
  {150, "KEY_WWW", '\0', '\0'}, {151, "KEY_MSDOS", '\0', '\0'}, {152, "KEY_SCREENLOCK", '\0', '\0'}, {153, "KEY_DIRECTION", '\0', '\0'}, {154, "KEY_CYCLEWINDOWS", '\0', '\0'}, {155, "KEY_MAIL", '\0', '\0'}, {156, "KEY_BOOKMARKS", '\0', '\0'}, {157, "KEY_COMPUTER", '\0', '\0'}, {158, "KEY_BACK", '\0', '\0'}, {159, "KEY_FORWARD", '\0', '\0'},
  {160, "KEY_CLOSECD", '\0', '\0'}, {161, "KEY_EJECTCD", '\0', '\0'}, {162, "KEY_EJECTCLOSECD", '\0', '\0'}, {163, "KEY_NEXTSONG", '\0', '\0'}, {164, "KEY_PLAYPAUSE", '\0', '\0'}, {165, "KEY_PREVIOUSSONG", '\0', '\0'}, {166, "KEY_STOPCD", '\0', '\0'}, {167, "KEY_RECORD", '\0', '\0'}, {168, "KEY_REWIND", '\0', '\0'}, {169, "KEY_PHONE", '\0', '\0'},
  {170, "KEY_ISO", '\0', '\0'}, {171, "KEY_CONFIG", '\0', '\0'}, {172, "KEY_HOMEPAGE", '\0', '\0'}, {173, "KEY_REFRESH", '\0', '\0'}, {174, "KEY_EXIT", '\0', '\0'}, {175, "KEY_MOVE", '\0', '\0'}, {176, "KEY_EDIT", '\0', '\0'}, {177, "KEY_SCROLLUP", '\0', '\0'}, {178, "KEY_SCROLLDOWN", '\0', '\0'}, {179, "KEY_KPLEFTPAREN", '\0', '\0'},
  {180, "KEY_KPRIGHTPAREN", '\0', '\0'}, {181, "KEY_NEW", '\0', '\0'}, {182, "KEY_REDO", '\0', '\0'}, {183, "KEY_F13", '\0', '\0'}, {184, "KEY_F14", '\0', '\0'}, {185, "KEY_F15", '\0', '\0'}, {186, "KEY_F16", '\0', '\0'}, {187, "KEY_F17", '\0', '\0'}, {188, "KEY_F18", '\0', '\0'}, {189, "KEY_F19", '\0', '\0'},
  {190, "KEY_F20", '\0', '\0'}, {191, "KEY_F21", '\0', '\0'}, {192, "KEY_F22", '\0', '\0'}, {193, "KEY_F23", '\0', '\0'}, {194, "KEY_F24", '\0', '\0'}, {195, "NONE", '\0', '\0'}, {196, "NONE", '\0', '\0'}, {197, "NONE", '\0', '\0'}, {198, "NONE", '\0', '\0'}, {199, "NONE", '\0', '\0'},
  {200, "KEY_PLAYCD", '\0', '\0'}, {201, "KEY_PAUSECD", '\0', '\0'}, {202, "KEY_PROG3", '\0', '\0'}, {203, "KEY_PROG4", '\0', '\0'}, {204, "KEY_DASHBOARD", '\0', '\0'}, {205, "KEY_SUSPEND", '\0', '\0'}, {206, "KEY_CLOSE", '\0', '\0'}, {207, "KEY_PLAY", '\0', '\0'}, {208, "KEY_FASTFORWARD", '\0', '\0'}, {209, "KEY_BASSBOOST", '\0', '\0'},
  {210, "KEY_PRINT", '\0', '\0'}, {211, "KEY_HP", '\0', '\0'}, {212, "KEY_CAMERA", '\0', '\0'}, {213, "KEY_SOUND", '\0', '\0'}, {214, "KEY_QUESTION", '\0', '\0'}, {215, "KEY_EMAIL", '\0', '\0'}, {216, "KEY_CHAT", '\0', '\0'}, {217, "KEY_SEARCH", '\0', '\0'}, {218, "KEY_CONNECT", '\0', '\0'}, {219, "KEY_FINANCE", '\0', '\0'},
  {220, "KEY_SPORT", '\0', '\0'}, {221, "KEY_SHOP", '\0', '\0'}, {222, "KEY_ALTERASE", '\0', '\0'}, {223, "KEY_CANCEL", '\0', '\0'}, {224, "KEY_BRIGHTNESSDOWN", '\0', '\0'}, {225, "KEY_BRIGHTNESSUP", '\0', '\0'}, {226, "KEY_MEDIA", '\0', '\0'}, {227, "KEY_SWITCHVIDEOMODE", '\0', '\0'}, {228, "KEY_KBDILLUMTOGGLE", '\0', '\0'}, {229, "KEY_KBDILLUMDOWN", '\0', '\0'},
  {230, "KEY_KBDILLUMUP", '\0', '\0'}, {231, "KEY_SEND", '\0', '\0'}, {232, "KEY_REPLY", '\0', '\0'}, {233, "KEY_FORWARDMAIL", '\0', '\0'}, {234, "KEY_SAVE", '\0', '\0'}, {235, "KEY_DOCUMENTS", '\0', '\0'}, {236, "KEY_BATTERY", '\0', '\0'}, {237, "KEY_BLUETOOTH", '\0', '\0'}, {238, "KEY_WLAN", '\0', '\0'}, {239, "KEY_UWB", '\0', '\0'},
  {240, "KEY_UNKNOWN", '\0', '\0'}, {241, "KEY_VIDEO_NEXT", '\0', '\0'}, {242, "KEY_VIDEO_PREV", '\0', '\0'}, {243, "KEY_BRIGHTNESS_CYCLE", '\0', '\0'}, {244, "KEY_BRIGHTNESS_ZERO", '\0', '\0'}, {245, "KEY_DISPLAY_OFF", '\0', '\0'}, {246, "KEY_WWAN", '\0', '\0'}, {247, "KEY_RFKILL", '\0', '\0'}, {248, "KEY_MICMUTE", '\0', '\0'}, {249, "NONE", '\0', '\0'},
  {250, "NONE", '\0', '\0'}, {251, "NONE", '\0', '\0'}, {252, "NONE", '\0', '\0'}, {253, "NONE", '\0', '\0'}, {254, "NONE", '\0', '\0'}, {255, "NONE", '\0', '\0'}, {256, "NONE", '\0', '\0'}, {257, "NONE", '\0', '\0'}, {258, "NONE", '\0', '\0'}, {259, "NONE", '\0', '\0'},  
  {260, "NONE", '\0', '\0'}, {261, "NONE", '\0', '\0'}, {262, "NONE", '\0', '\0'}, {263, "NONE", '\0', '\0'}, {264, "NONE", '\0', '\0'}, {265, "NONE", '\0', '\0'}, {266, "NONE", '\0', '\0'}, {267, "NONE", '\0', '\0'}, {268, "NONE", '\0', '\0'}, {269, "NONE", '\0', '\0'},  
};

static int compare_keys(const void * a, const void * b) {
    // Determine if bsearch has indexed too far into the lookup table.
    return ( *(int*)a - *(int*)b );
}

Linux_Keys * get_linux_value(int key) {
    // Get the starting point into the lookup table to start looping at.
    Linux_Keys key_stroke[1] = {{key}};
    // Use bsearch algorithm to find the correct key that was pressed in the lookup table.
    Linux_Keys * lookup_key = bsearch(key_stroke, linux_lookup_table, (sizeof(linux_lookup_table) / sizeof(linux_lookup_table[0])), sizeof(linux_lookup_table[0]), compare_keys);
    // Return the lookup key.
    return lookup_key ? lookup_key : NULL;
}

#endif