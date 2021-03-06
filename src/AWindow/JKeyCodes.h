/**
 * \file JKeyCodes.h
 * \author Jannled
 * \version 0.1
 * \brief Maps platform dependent Keycodes to universal ones. Currently for Linux and Windows
 */

#include "AWindow.h"

#ifndef JKEYCODES_H
#define JKEYCODES_H

/** Number of known Keycodes */
#define JKEY_NUM 102

/** Maximum length of char array with the keycode name */
#define JKEY_NAME 10

/** Type for keycodes */
typedef unsigned int KCode_t;

#ifdef OS_Windows
#include <windows.h>

#define B_LMB          VK_LBUTTON
#define B_RMB          VK_RBUTTON
#define B_WHEEL_UP     VK_MBUTTON
#define B_WHEEL_DOWN   
#define B_WHEEL_CLICK  
#define B_WHEEL_LEFT   
#define B_WHEEL_RIGHT  
#define B_BACK         
#define B_FORWARD      
#define B_SPECIAL      

#define K_ESC        VK_ESCAPE
#define K_F1         VK_F1
#define K_F2         VK_F2
#define K_F3         VK_F3
#define K_F4         VK_F4
#define K_F5         VK_F5
#define K_F6         VK_F6
#define K_F7         VK_F7
#define K_F8         VK_F8
#define K_F9         VK_F9
#define K_F10        VK_F10
#define K_F11        VK_F11
#define K_F12        VK_F12
#define K_CIRC       
#define K_1          '1'
#define K_2          '2'
#define K_3          '3'
#define K_4          '4'
#define K_5          '5'
#define K_6          '6'
#define K_7          '7'
#define K_8          '8'
#define K_9          '9'
#define K_0          '0'
#define K_SZ         
#define K_HC         
#define K_BACKSPACE  
#define K_TAB        
#define K_Q          'Q'
#define K_W          'W'
#define K_E          'E'
#define K_R          'R'
#define K_T          'T'
#define K_Z          'Z'
#define K_U          'U'
#define K_I          'I'
#define K_O          'O'
#define K_P          'P'
#define K_UE         
#define K_PLUS       
#define K_ENTER      
#define K_CAPSLOCK   
#define K_A          'A'
#define K_S          'S'
#define K_D          'D'
#define K_F          'F'
#define K_G          'G'
#define K_H          'H'
#define K_J          'J'
#define K_K          'K'
#define K_L          'L'
#define K_OE         
#define K_AE         
#define K_HASHTAG    
#define K_LSHIFT     
#define K_LESS       
#define K_Y          'Y'
#define K_X          'X'
#define K_C          'C'
#define K_V          'V'
#define K_B          'B'
#define K_N          'N'
#define K_M          'M'
#define K_COMMA      
#define K_DOT        
#define K_MINUS      
#define K_RSHIFT     
#define K_LCTRL      
#define K_ALT        
#define K_SPACEBAR   
#define K_CTRLALT    
#define K_MENU       
#define K_RCTRL      
#define K_ROLL       
#define K_PAUSE      
#define K_INSERT     
#define K_POS1       
#define K_DEL        
#define K_END        
#define K_PAGEUP     
#define K_PAGEDOWN   
#define K_LEFT       VK_LEFT
#define K_RIGHT      VK_RIGHT
#define K_UP         VK_UP
#define K_DOWN       VK_DOWN
#define K_NUMLOCK    
#define K_NUM_MULT   
#define K_NUM_DIV    
#define K_NUM_ADD    
#define K_NUM_SUB    
#define K_NUM_ENT    
#define K_NUM_COMMA  
#define K_NUM_1      VK_NUMPAD_1
#define K_NUM_2      VK_NUMPAD_2
#define K_NUM_3      VK_NUMPAD_3
#define K_NUM_4      VK_NUMPAD_4
#define K_NUM_5      VK_NUMPAD_5
#define K_NUM_6      VK_NUMPAD_6
#define K_NUM_7      VK_NUMPAD_7
#define K_NUM_8      VK_NUMPAD_8
#define K_NUM_9      VK_NUMPAD_9
#define K_NUM_0      VK_NUMPAD_0
#endif

#ifdef OS_Linux
#define XK_MISCELLANY
#define XK_LATIN1
#include <X11/keysymdef.h>

#define B_LMB          1
#define B_RMB          3
#define B_WHEEL_UP     4
#define B_WHEEL_DOWN   5
#define B_WHEEL_CLICK  2
#define B_WHEEL_LEFT   6
#define B_WHEEL_RIGHT  7
#define B_BACK         8
#define B_FORWARD      9
#define B_SPECIAL      10

#define K_ESC        XK_Escape            
#define K_F1         XK_F1
#define K_F2         XK_F2
#define K_F3         XK_F3
#define K_F4         XK_F4
#define K_F5         XK_F5
#define K_F6         XK_F6
#define K_F7         XK_F7
#define K_F8         XK_F8
#define K_F9         XK_F9
#define K_F10        XK_F10
#define K_F11        XK_F11
#define K_F12        XK_F12
#define K_CIRC       XK_dead_circumflex
#define K_1          XK_1
#define K_2          XK_2
#define K_3          XK_3
#define K_4          XK_4
#define K_5          XK_5
#define K_6          XK_6
#define K_7          XK_7
#define K_8          XK_8
#define K_9          XK_9
#define K_0          XK_0
#define K_SZ         XK_ssharp
#define K_ACUTE      XK_dead_acute
#define K_BACKSPACE  XK_BackSpace
#define K_TAB        XK_Tab
#define K_Q          XK_q
#define K_W          XK_w
#define K_E          XK_r
#define K_R          XK_t
#define K_T          XK_z
#define K_Z          XK_u
#define K_U          XK_u
#define K_I          XK_i
#define K_O          XK_o
#define K_P          XK_p
#define K_UE         XK_udiaeresis
#define K_PLUS       XK_plus
#define K_ENTER      XK_Return
#define K_CAPSLOCK   XK_Caps_Lock
#define K_A          XK_a
#define K_S          XK_s
#define K_D          XK_d
#define K_F          XK_f
#define K_G          XK_g
#define K_H          XK_h
#define K_J          XK_j
#define K_K          XK_k
#define K_L          XK_l
#define K_OE         XK_odiaeresis
#define K_AE         XK_adiaeresis
#define K_HASHTAG    XK_numbersign
#define K_LSHIFT     XK_Shift_L
#define K_LESS       XK_less
#define K_Y          XK_y
#define K_X          XK_x
#define K_C          XK_c
#define K_V          XK_v
#define K_B          XK_b
#define K_N          XK_n
#define K_M          XK_m
#define K_COMMA      XK_comma
#define K_DOT        XK_period
#define K_MINUS      XK_minus
#define K_RSHIFT     XK_Shift_R
#define K_LCTRL      XK_Control_L
#define K_ALT        XK_Alt_L
#define K_SPACEBAR   XK_space
#define K_CTRLALT    XK_ISO_Level3_Shift
#define K_MENU       XK_Menu
#define K_RCTRL      XK_Control_R
#define K_ROLL       XK_Scroll_Lock
#define K_PAUSE      XK_Pause
#define K_INSERT     XK_Insert
#define K_POS1       XK_Home
#define K_DEL        XK_Delete
#define K_END        XK_End
#define K_PAGEUP     XK_Page_Up
#define K_PAGEDOWN   XK_Page_Down
#define K_LEFT       XK_Left
#define K_RIGHT      XK_Right
#define K_UP         XK_Up
#define K_DOWN       XK_Down
#define K_NUMLOCK    XK_Num_Lock
#define K_NUM_MULT   XK_KP_Multiply
#define K_NUM_DIV    XK_KP_Divide
#define K_NUM_ADD    XK_KP_Add
#define K_NUM_SUB    XK_KP_Subtract
#define K_NUM_ENT    XK_KP_Enter
#define K_NUM_COMMA  XK_KP_Delete
#define K_NUM_1      XK_KP_End
#define K_NUM_2      XK_KP_Down
#define K_NUM_3      XK_KP_Page_Down
#define K_NUM_4      XK_KP_Left
#define K_NUM_5      XK_KP_Begin
#define K_NUM_6      XK_KP_Right
#define K_NUM_7      XK_KP_Home
#define K_NUM_8      XK_KP_Up
#define K_NUM_9      XK_KP_Page_Up
#define K_NUM_0      XK_KP_Insert
#endif

#endif // JKEYCODES_H