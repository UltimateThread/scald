#include "InputManager.h"

namespace SCALD_CORE {

   InputManager::InputManager()
      : m_pKeyboard{ std::make_unique<SCALD_WINDOWING::Inputs::Keyboard>() }, m_pMouse{ std::make_unique<SCALD_WINDOWING::Inputs::Mouse>() }
   {

   }

   void InputManager::RegisterLuaKeyNames(sol::state& lua)
   {
      // ==================================================================
      // Register Typewriter Keys
      // ==================================================================
      lua.set("KEY_A", SCION_KEY_A);
      lua.set("KEY_B", SCION_KEY_B);
      lua.set("KEY_C", SCION_KEY_C);
      lua.set("KEY_D", SCION_KEY_D);
      lua.set("KEY_E", SCION_KEY_E);
      lua.set("KEY_F", SCION_KEY_F);
      lua.set("KEY_G", SCION_KEY_G);
      lua.set("KEY_H", SCION_KEY_H);
      lua.set("KEY_I", SCION_KEY_I);
      lua.set("KEY_J", SCION_KEY_J);
      lua.set("KEY_K", SCION_KEY_K);
      lua.set("KEY_L", SCION_KEY_L);
      lua.set("KEY_M", SCION_KEY_M);
      lua.set("KEY_N", SCION_KEY_N);
      lua.set("KEY_O", SCION_KEY_O);
      lua.set("KEY_P", SCION_KEY_P);
      lua.set("KEY_Q", SCION_KEY_Q);
      lua.set("KEY_R", SCION_KEY_R);
      lua.set("KEY_S", SCION_KEY_S);
      lua.set("KEY_T", SCION_KEY_T);
      lua.set("KEY_U", SCION_KEY_U);
      lua.set("KEY_V", SCION_KEY_V);
      lua.set("KEY_W", SCION_KEY_W);
      lua.set("KEY_X", SCION_KEY_X);
      lua.set("KEY_Y", SCION_KEY_Y);
      lua.set("KEY_Z", SCION_KEY_Z);

      lua.set("KEY_0", SCION_KEY_0);
      lua.set("KEY_1", SCION_KEY_1);
      lua.set("KEY_2", SCION_KEY_2);
      lua.set("KEY_3", SCION_KEY_3);
      lua.set("KEY_4", SCION_KEY_4);
      lua.set("KEY_5", SCION_KEY_5);
      lua.set("KEY_6", SCION_KEY_6);
      lua.set("KEY_7", SCION_KEY_7);
      lua.set("KEY_8", SCION_KEY_8);
      lua.set("KEY_9", SCION_KEY_9);

      lua.set("KEY_ENTER", SCION_KEY_RETURN);
      lua.set("KEY_BACKSPACE", SCION_KEY_BACKSPACE);
      lua.set("KEY_ESC", SCION_KEY_ESCAPE);
      lua.set("KEY_SPACE", SCION_KEY_SPACE);
      lua.set("KEY_LCTRL", SCION_KEY_LCTRL);
      lua.set("KEY_RCTRL", SCION_KEY_RCTRL);
      lua.set("KEY_LALT", SCION_KEY_LALT);
      lua.set("KEY_RALT", SCION_KEY_RALT);
      lua.set("KEY_LSHIFT", SCION_KEY_LSHIFT);
      lua.set("KEY_RSHIFT", SCION_KEY_RSHIFT);

      // ==================================================================
      //  Register Punctuation Keys
      // ==================================================================
      lua.set("KEY_COLON", SCION_KEY_COLON);
      lua.set("KEY_SEMICOLON", SCION_KEY_SEMICOLON);
      lua.set("KEY_QUOTE", SCION_KEY_QUOTE);
      lua.set("KEY_BACKQUOTE", SCION_KEY_BACKQUOTE);
      lua.set("KEY_CARET", SCION_KEY_CARET);
      lua.set("KEY_UNDERSCORE", SCION_KEY_UNDERSCORE);
      lua.set("KEY_RIGHTBRACKET", SCION_KEY_RIGHTBRACKET);
      lua.set("KEY_LEFTBRACKET", SCION_KEY_LEFTBRACKET);
      lua.set("KEY_SLASH", SCION_KEY_SLASH);
      lua.set("KEY_ASTERISK", SCION_KEY_ASTERISK);
      lua.set("KEY_LEFTPAREN", SCION_KEY_LEFTPAREN);
      lua.set("KEY_RIGHTPAREN", SCION_KEY_RIGHTPAREN);
      lua.set("KEY_QUESTION", SCION_KEY_QUESTION);
      lua.set("KEY_AMPERSAND", SCION_KEY_AMPERSAND);
      lua.set("KEY_DOLLAR", SCION_KEY_DOLLAR);
      lua.set("KEY_EXCLAIM", SCION_KEY_EXCLAIM);
      lua.set("KEY_BACKSLASH", SCION_KEY_BACKSLASH);

      // ==================================================================
      //  Register Function Keys
      // ==================================================================
      lua.set("KEY_F1", SCION_KEY_F1);
      lua.set("KEY_F2", SCION_KEY_F2);
      lua.set("KEY_F3", SCION_KEY_F3);
      lua.set("KEY_F4", SCION_KEY_F4);
      lua.set("KEY_F5", SCION_KEY_F5);
      lua.set("KEY_F6", SCION_KEY_F6);
      lua.set("KEY_F7", SCION_KEY_F7);
      lua.set("KEY_F8", SCION_KEY_F8);
      lua.set("KEY_F9", SCION_KEY_F9);
      lua.set("KEY_F10", SCION_KEY_F10);
      lua.set("KEY_F11", SCION_KEY_F11);
      lua.set("KEY_F12", SCION_KEY_F12);

      // ==================================================================
      // Register Cursor Control Keys
      // ==================================================================
      lua.set("KEY_UP", SCION_KEY_UP);
      lua.set("KEY_RIGHT", SCION_KEY_RIGHT);
      lua.set("KEY_DOWN", SCION_KEY_DOWN);
      lua.set("KEY_LEFT", SCION_KEY_LEFT);

      // ==================================================================
      // Register Numeric Keypad Keys
      // ==================================================================
      lua.set("KP_KEY_0", SCION_KEY_KP0);
      lua.set("KP_KEY_1", SCION_KEY_KP1);
      lua.set("KP_KEY_2", SCION_KEY_KP2);
      lua.set("KP_KEY_3", SCION_KEY_KP3);
      lua.set("KP_KEY_4", SCION_KEY_KP4);
      lua.set("KP_KEY_5", SCION_KEY_KP5);
      lua.set("KP_KEY_6", SCION_KEY_KP6);
      lua.set("KP_KEY_7", SCION_KEY_KP7);
      lua.set("KP_KEY_8", SCION_KEY_KP8);
      lua.set("KP_KEY_9", SCION_KEY_KP9);

      lua.set("KP_KEY_DIVIDE", SCION_KEY_KP_DIVIDE);
      lua.set("KP_KEY_MULTIPLY", SCION_KEY_KP_MULTIPLY);
      lua.set("KP_KEY_MINUS", SCION_KEY_KP_MINUS);
      lua.set("KP_KEY_PLUS", SCION_KEY_KP_PLUS);
      lua.set("KP_KEY_ENTER", SCION_KEY_KP_ENTER);
      lua.set("KP_KEY_PERIOD", SCION_KEY_KP_PERIOD);

      lua.set("KEY_NUM_LOCK", SCION_KEY_NUMLOCK);

      // Adding windows specific keys here for convenience
#ifdef _WIN32
      lua.set("KEY_LWIN", SCION_KEY_LWIN);
      lua.set("KEY_RWIN", SCION_KEY_RWIN);
#else
      lua.set("KEY_LGUI", SCION_KEY_LGUI);
      lua.set("KEY_RGUI", SCION_KEY_RGUI);
#endif
   }

   void InputManager::RegisterLuaMouseBtnNames(sol::state& lua)
   {
      lua.set("LEFT_BTN", SCALD_MOUSE_LEFT);
      lua.set("MIDDLE_BTN", SCALD_MOUSE_MIDDLE);
      lua.set("RIGHT_BTN", SCALD_MOUSE_RIGHT);
   }

   InputManager& InputManager::GetInstance()
   {
      static InputManager instance{};
      return instance;
   }

   void InputManager::CreateLuaInputBindings(sol::state& lua)
   {
      RegisterLuaKeyNames(lua);
      RegisterLuaMouseBtnNames(lua);

      auto& inputManager = GetInstance();
      auto& keyboard = inputManager.GetKeyboard();

      lua.new_usertype<SCALD_WINDOWING::Inputs::Keyboard>(
         "Keyboard",
         sol::no_constructor,
         "just_pressed", [&](int key) { return keyboard.IsKeyJustPressed(key); },
         "just_released", [&](int key) { return keyboard.IsKeyJustReleased(key); },
         "pressed", [&](int key) { return keyboard.IsKeyPressed(key); }
      );

      auto& mouse = inputManager.GetMouse();

      lua.new_usertype<SCALD_WINDOWING::Inputs::Mouse>(
         "Mouse",
         sol::no_constructor,
         "just_pressed", [&](int btn) { return mouse.IsBtnJustPressed(btn); },
         "just_released", [&](int btn) { return mouse.IsBtnJustReleased(btn); },
         "pressed", [&](int btn) { return mouse.IsBtnPressed(btn); },
         "screen_position", [&]() { return mouse.GetMouseScreenPosition(); },
         "wheel_x", [&]() { return mouse.GetMouseWheelX(); },
         "wheel_y", [&]() { return mouse.GetMouseWheelY(); }
      );
   }

}
