#include "Keyboard.h"
#include <Logger/Logger.h>

namespace SCALD_WINDOWING::Inputs {

   Keyboard::Keyboard()
      : m_mapButtons{ { SCALD_KEY_BACKSPACE, Button{} },
               { SCALD_KEY_TAB, Button{} },
               { SCALD_KEY_CLEAR, Button{} },
               { SCALD_KEY_RETURN, Button{} },
               { SCALD_KEY_PAUSE, Button{} },
               { SCALD_KEY_ESCAPE, Button{} },
               { SCALD_KEY_SPACE, Button{} },
               { SCALD_KEY_EXCLAIM, Button{} },
               { SCALD_KEY_QUOTEDBL, Button{} },
               { SCALD_KEY_HASH, Button{} },
               { SCALD_KEY_DOLLAR, Button{} },
               { SCALD_KEY_AMPERSAND, Button{} },
               { SCALD_KEY_QUOTE, Button{} },
               { SCALD_KEY_LEFTPAREN, Button{} },
               { SCALD_KEY_RIGHTPAREN, Button{} },
               { SCALD_KEY_ASTERISK, Button{} },
               { SCALD_KEY_PLUS, Button{} },
               { SCALD_KEY_COMMA, Button{} },
               { SCALD_KEY_MINUS, Button{} },
               { SCALD_KEY_PERIOD, Button{} },
               { SCALD_KEY_SLASH, Button{} },
               { SCALD_KEY_0, Button{} },
               { SCALD_KEY_1, Button{} },
               { SCALD_KEY_2, Button{} },
               { SCALD_KEY_3, Button{} },
               { SCALD_KEY_4, Button{} },
               { SCALD_KEY_5, Button{} },
               { SCALD_KEY_6, Button{} },
               { SCALD_KEY_7, Button{} },
               { SCALD_KEY_8, Button{} },
               { SCALD_KEY_9, Button{} },
               { SCALD_KEY_COLON, Button{} },
               { SCALD_KEY_SEMICOLON, Button{} },
               { SCALD_KEY_LESS, Button{} },
               { SCALD_KEY_EQUALS, Button{} },
               { SCALD_KEY_GREATER, Button{} },
               { SCALD_KEY_QUESTION, Button{} },
               { SCALD_KEY_AT, Button{} },
               { SCALD_KEY_LEFTBRACKET, Button{} },
               { SCALD_KEY_BACKSLASH, Button{} },
               { SCALD_KEY_RIGHTBRACKET, Button{} },
               { SCALD_KEY_CARET, Button{} },
               { SCALD_KEY_UNDERSCORE, Button{} },
               { SCALD_KEY_BACKQUOTE, Button{} },
               { SCALD_KEY_A, Button{} },
               { SCALD_KEY_B, Button{} },
               { SCALD_KEY_C, Button{} },
               { SCALD_KEY_D, Button{} },
               { SCALD_KEY_E, Button{} },
               { SCALD_KEY_F, Button{} },
               { SCALD_KEY_G, Button{} },
               { SCALD_KEY_H, Button{} },
               { SCALD_KEY_I, Button{} },
               { SCALD_KEY_J, Button{} },
               { SCALD_KEY_K, Button{} },
               { SCALD_KEY_L, Button{} },
               { SCALD_KEY_M, Button{} },
               { SCALD_KEY_N, Button{} },
               { SCALD_KEY_O, Button{} },
               { SCALD_KEY_P, Button{} },
               { SCALD_KEY_Q, Button{} },
               { SCALD_KEY_R, Button{} },
               { SCALD_KEY_S, Button{} },
               { SCALD_KEY_T, Button{} },
               { SCALD_KEY_U, Button{} },
               { SCALD_KEY_V, Button{} },
               { SCALD_KEY_W, Button{} },
               { SCALD_KEY_X, Button{} },
               { SCALD_KEY_Y, Button{} },
               { SCALD_KEY_Z, Button{} },
               { SCALD_KEY_DELETE, Button{} },
               { SCALD_KEY_CAPSLOCK, Button{} },
               { SCALD_KEY_F1, Button{} },
               { SCALD_KEY_F2, Button{} },
               { SCALD_KEY_F3, Button{} },
               { SCALD_KEY_F4, Button{} },
               { SCALD_KEY_F5, Button{} },
               { SCALD_KEY_F6, Button{} },
               { SCALD_KEY_F7, Button{} },
               { SCALD_KEY_F8, Button{} },
               { SCALD_KEY_F9, Button{} },
               { SCALD_KEY_F10, Button{} },
               { SCALD_KEY_F11, Button{} },
               { SCALD_KEY_F12, Button{} },
               { SCALD_KEY_SCROLLOCK, Button{} },
               { SCALD_KEY_PRINTSCREEN, Button{} },
               { SCALD_KEY_INSERT, Button{} },
               { SCALD_KEY_HOME, Button{} },
               { SCALD_KEY_PAGEUP, Button{} },
               { SCALD_KEY_PAGEDOWN, Button{} },
               { SCALD_KEY_END, Button{} },
               { SCALD_KEY_RIGHT, Button{} },
               { SCALD_KEY_LEFT, Button{} },
               { SCALD_KEY_DOWN, Button{} },
               { SCALD_KEY_UP, Button{} },
               { SCALD_KEY_NUMLOCK, Button{} },
               { SCALD_KEY_KP_DIVIDE, Button{} },
               { SCALD_KEY_KP_MULTIPLY, Button{} },
               { SCALD_KEY_KP_MINUS, Button{} },
               { SCALD_KEY_KP_PLUS, Button{} },
               { SCALD_KEY_KP_ENTER, Button{} },
               { SCALD_KEY_KP1, Button{} },
               { SCALD_KEY_KP2, Button{} },
               { SCALD_KEY_KP3, Button{} },
               { SCALD_KEY_KP4, Button{} },
               { SCALD_KEY_KP5, Button{} },
               { SCALD_KEY_KP6, Button{} },
               { SCALD_KEY_KP7, Button{} },
               { SCALD_KEY_KP8, Button{} },
               { SCALD_KEY_KP9, Button{} },
               { SCALD_KEY_KP0, Button{} },
               { SCALD_KEY_KP_PERIOD, Button{} },
               { SCALD_KEY_LCTRL, Button{} },
               { SCALD_KEY_LSHIFT, Button{} },
               { SCALD_KEY_LALT, Button{} },
               { SCALD_KEY_RCTRL, Button{} },
               { SCALD_KEY_RSHIFT, Button{} },
               { SCALD_KEY_RALT, Button{} } }
   {
   }

   void Keyboard::Update()
   {
      for (auto& [key, button] : m_mapButtons)
      {
         button.Reset();
      }
   }

   void Keyboard::OnKeyPressed(int key)
   {
      if (key == KEY_UNKNOWN)
      {
         SCALD_ERROR("Key [{0}] is unknown!", key);
         return;
      }

      auto keyItr = m_mapButtons.find(key);
      if (keyItr == m_mapButtons.end())
      {
         SCALD_ERROR("Key [{0}] does not exist!", key);
         return;
      }

      keyItr->second.Update(true);
   }

   void Keyboard::OnKeyReleased(int key)
   {
      if (key == KEY_UNKNOWN)
      {
         SCALD_ERROR("Key [{0}] is unknown!", key);
         return;
      }

      auto keyItr = m_mapButtons.find(key);
      if (keyItr == m_mapButtons.end())
      {
         SCALD_ERROR("Key [{0}] does not exist!", key);
         return;
      }

      keyItr->second.Update(false);
   }

   const bool Keyboard::IsKeyPressed(int key) const
   {
      if (key == KEY_UNKNOWN)
      {
         SCALD_ERROR("Key [{0}] is unknown!", key);
         return false;
      }

      auto keyItr = m_mapButtons.find(key);
      if (keyItr == m_mapButtons.end())
      {
         SCALD_ERROR("Key [{0}] does not exist!", key);
         return false;
      }

      return keyItr->second.bIsPressed;
   }

   const bool Keyboard::IsKeyJustPressed(int key) const
   {
      if (key == KEY_UNKNOWN)
      {
         SCALD_ERROR("Key [{0}] is unknown!", key);
         return false;
      }

      auto keyItr = m_mapButtons.find(key);
      if (keyItr == m_mapButtons.end())
      {
         SCALD_ERROR("Key [{0}] does not exist!", key);
         return false;
      }

      return keyItr->second.bJustPressed;
   }

   const bool Keyboard::IsKeyJustReleased(int key) const
   {
      if (key == KEY_UNKNOWN)
      {
         SCALD_ERROR("Key [{0}] is unknown!", key);
         return false;
      }

      auto keyItr = m_mapButtons.find(key);
      if (keyItr == m_mapButtons.end())
      {
         SCALD_ERROR("Key [{0}] does not exist!", key);
         return false;
      }

      return keyItr->second.bJustReleased;
   }

}
