#include "InputManager.h"
#include <Logger/Logger.h>
#include <ScaldUtilities/SDL_Wrappers.h>

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
      lua.set("KEY_A", SCALD_KEY_A);
      lua.set("KEY_B", SCALD_KEY_B);
      lua.set("KEY_C", SCALD_KEY_C);
      lua.set("KEY_D", SCALD_KEY_D);
      lua.set("KEY_E", SCALD_KEY_E);
      lua.set("KEY_F", SCALD_KEY_F);
      lua.set("KEY_G", SCALD_KEY_G);
      lua.set("KEY_H", SCALD_KEY_H);
      lua.set("KEY_I", SCALD_KEY_I);
      lua.set("KEY_J", SCALD_KEY_J);
      lua.set("KEY_K", SCALD_KEY_K);
      lua.set("KEY_L", SCALD_KEY_L);
      lua.set("KEY_M", SCALD_KEY_M);
      lua.set("KEY_N", SCALD_KEY_N);
      lua.set("KEY_O", SCALD_KEY_O);
      lua.set("KEY_P", SCALD_KEY_P);
      lua.set("KEY_Q", SCALD_KEY_Q);
      lua.set("KEY_R", SCALD_KEY_R);
      lua.set("KEY_S", SCALD_KEY_S);
      lua.set("KEY_T", SCALD_KEY_T);
      lua.set("KEY_U", SCALD_KEY_U);
      lua.set("KEY_V", SCALD_KEY_V);
      lua.set("KEY_W", SCALD_KEY_W);
      lua.set("KEY_X", SCALD_KEY_X);
      lua.set("KEY_Y", SCALD_KEY_Y);
      lua.set("KEY_Z", SCALD_KEY_Z);

      lua.set("KEY_0", SCALD_KEY_0);
      lua.set("KEY_1", SCALD_KEY_1);
      lua.set("KEY_2", SCALD_KEY_2);
      lua.set("KEY_3", SCALD_KEY_3);
      lua.set("KEY_4", SCALD_KEY_4);
      lua.set("KEY_5", SCALD_KEY_5);
      lua.set("KEY_6", SCALD_KEY_6);
      lua.set("KEY_7", SCALD_KEY_7);
      lua.set("KEY_8", SCALD_KEY_8);
      lua.set("KEY_9", SCALD_KEY_9);

      lua.set("KEY_ENTER", SCALD_KEY_RETURN);
      lua.set("KEY_BACKSPACE", SCALD_KEY_BACKSPACE);
      lua.set("KEY_ESC", SCALD_KEY_ESCAPE);
      lua.set("KEY_SPACE", SCALD_KEY_SPACE);
      lua.set("KEY_LCTRL", SCALD_KEY_LCTRL);
      lua.set("KEY_RCTRL", SCALD_KEY_RCTRL);
      lua.set("KEY_LALT", SCALD_KEY_LALT);
      lua.set("KEY_RALT", SCALD_KEY_RALT);
      lua.set("KEY_LSHIFT", SCALD_KEY_LSHIFT);
      lua.set("KEY_RSHIFT", SCALD_KEY_RSHIFT);

      // ==================================================================
      //  Register Punctuation Keys
      // ==================================================================
      lua.set("KEY_COLON", SCALD_KEY_COLON);
      lua.set("KEY_SEMICOLON", SCALD_KEY_SEMICOLON);
      lua.set("KEY_QUOTE", SCALD_KEY_QUOTE);
      lua.set("KEY_BACKQUOTE", SCALD_KEY_BACKQUOTE);
      lua.set("KEY_CARET", SCALD_KEY_CARET);
      lua.set("KEY_UNDERSCORE", SCALD_KEY_UNDERSCORE);
      lua.set("KEY_RIGHTBRACKET", SCALD_KEY_RIGHTBRACKET);
      lua.set("KEY_LEFTBRACKET", SCALD_KEY_LEFTBRACKET);
      lua.set("KEY_SLASH", SCALD_KEY_SLASH);
      lua.set("KEY_ASTERISK", SCALD_KEY_ASTERISK);
      lua.set("KEY_LEFTPAREN", SCALD_KEY_LEFTPAREN);
      lua.set("KEY_RIGHTPAREN", SCALD_KEY_RIGHTPAREN);
      lua.set("KEY_QUESTION", SCALD_KEY_QUESTION);
      lua.set("KEY_AMPERSAND", SCALD_KEY_AMPERSAND);
      lua.set("KEY_DOLLAR", SCALD_KEY_DOLLAR);
      lua.set("KEY_EXCLAIM", SCALD_KEY_EXCLAIM);
      lua.set("KEY_BACKSLASH", SCALD_KEY_BACKSLASH);

      // ==================================================================
      //  Register Function Keys
      // ==================================================================
      lua.set("KEY_F1", SCALD_KEY_F1);
      lua.set("KEY_F2", SCALD_KEY_F2);
      lua.set("KEY_F3", SCALD_KEY_F3);
      lua.set("KEY_F4", SCALD_KEY_F4);
      lua.set("KEY_F5", SCALD_KEY_F5);
      lua.set("KEY_F6", SCALD_KEY_F6);
      lua.set("KEY_F7", SCALD_KEY_F7);
      lua.set("KEY_F8", SCALD_KEY_F8);
      lua.set("KEY_F9", SCALD_KEY_F9);
      lua.set("KEY_F10", SCALD_KEY_F10);
      lua.set("KEY_F11", SCALD_KEY_F11);
      lua.set("KEY_F12", SCALD_KEY_F12);

      // ==================================================================
      // Register Cursor Control Keys
      // ==================================================================
      lua.set("KEY_UP", SCALD_KEY_UP);
      lua.set("KEY_RIGHT", SCALD_KEY_RIGHT);
      lua.set("KEY_DOWN", SCALD_KEY_DOWN);
      lua.set("KEY_LEFT", SCALD_KEY_LEFT);

      // ==================================================================
      // Register Numeric Keypad Keys
      // ==================================================================
      lua.set("KP_KEY_0", SCALD_KEY_KP0);
      lua.set("KP_KEY_1", SCALD_KEY_KP1);
      lua.set("KP_KEY_2", SCALD_KEY_KP2);
      lua.set("KP_KEY_3", SCALD_KEY_KP3);
      lua.set("KP_KEY_4", SCALD_KEY_KP4);
      lua.set("KP_KEY_5", SCALD_KEY_KP5);
      lua.set("KP_KEY_6", SCALD_KEY_KP6);
      lua.set("KP_KEY_7", SCALD_KEY_KP7);
      lua.set("KP_KEY_8", SCALD_KEY_KP8);
      lua.set("KP_KEY_9", SCALD_KEY_KP9);

      lua.set("KP_KEY_DIVIDE", SCALD_KEY_KP_DIVIDE);
      lua.set("KP_KEY_MULTIPLY", SCALD_KEY_KP_MULTIPLY);
      lua.set("KP_KEY_MINUS", SCALD_KEY_KP_MINUS);
      lua.set("KP_KEY_PLUS", SCALD_KEY_KP_PLUS);
      lua.set("KP_KEY_ENTER", SCALD_KEY_KP_ENTER);
      lua.set("KP_KEY_PERIOD", SCALD_KEY_KP_PERIOD);

      lua.set("KEY_NUM_LOCK", SCALD_KEY_NUMLOCK);

      // Adding windows specific keys here for convenience
#ifdef _WIN32
      lua.set("KEY_LWIN", SCALD_KEY_LWIN);
      lua.set("KEY_RWIN", SCALD_KEY_RWIN);
#else
      lua.set("KEY_LGUI", SCALD_KEY_LGUI);
      lua.set("KEY_RGUI", SCALD_KEY_RGUI);
#endif
   }

   void InputManager::RegisterLuaMouseBtnNames(sol::state& lua)
   {
      lua.set("LEFT_BTN", SCALD_MOUSE_LEFT);
      lua.set("MIDDLE_BTN", SCALD_MOUSE_MIDDLE);
      lua.set("RIGHT_BTN", SCALD_MOUSE_RIGHT);
   }

   void InputManager::RegisterLuaGamepadBtnNames(sol::state& lua)
   {
      lua.set("GP_BTN_A", SCALD_GP_BTN_A);
      lua.set("GP_BTN_B", SCALD_GP_BTN_B);
      lua.set("GP_BTN_X", SCALD_GP_BTN_X);
      lua.set("GP_BTN_Y", SCALD_GP_BTN_Y);

      lua.set("GP_BTN_BACK", SCALD_GP_BTN_BACK);
      lua.set("GP_BTN_GUIDE", SCALD_GP_BTN_GUIDE);
      lua.set("GP_BTN_START", SCALD_GP_BTN_START);
      
      lua.set("GP_LSTICK", SCALD_GP_BTN_LSTICK);
      lua.set("GP_RSTICK", SCALD_GP_BTN_RSTICK);
      lua.set("GP_LSHOULDER", SCALD_GP_BTN_LSHOULDER);
      lua.set("GP_RSHOULDER", SCALD_GP_BTN_RSHOULDER);

      lua.set("DPAD_UP", SCALD_GP_BTN_DPAD_UP);
      lua.set("DPAD_DOWN", SCALD_GP_BTN_DPAD_DOWN);
      lua.set("DPAD_LEFT", SCALD_GP_BTN_DPAD_LEFT);
      lua.set("DPAD_RIGHT", SCALD_GP_BTN_DPAD_RIGHT);

      lua.set("AXIS_X1", 0);
      lua.set("AXIS_Y1", 1);
      lua.set("AXIS_X2", 2);
      lua.set("AXIS_Y2", 3);

      // Bottom Triggers
      lua.set("AXIS_Z1", 4);
      lua.set("AXIS_Z2", 5);
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
      RegisterLuaGamepadBtnNames(lua);

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

      lua.new_usertype<SCALD_WINDOWING::Inputs::Gamepad>(
         "Gamepad",
         sol::no_constructor,
         "just_pressed", [&](int index, int btn) {
            auto gamepad = inputManager.GetController(index);
            if (!gamepad)
            {
               SCALD_ERROR("Invalid gamepad index [{}] provided or gamepad is not plugged in!", index);
               return false;
            }
            return gamepad->IsButtonJustPressed(btn);
         },
         "just_released", [&](int index, int btn) {
            auto gamepad = inputManager.GetController(index);
            if (!gamepad)
            {
               SCALD_ERROR("Invalid gamepad index [{}] provided or gamepad is not plugged in!", index);
               return false;
            }
            return gamepad->IsButtonJustReleased(btn);
         },
         "pressed", [&](int index, int btn) {
            auto gamepad = inputManager.GetController(index);
            if (!gamepad)
            {
               SCALD_ERROR("Invalid gamepad index [{}] provided or gamepad is not plugged in!", index);
               return false;
            }
            return gamepad->IsButtonPressed(btn);
         },
         "get_axis_position", [&](int index, int axis) {
            auto gamepad = inputManager.GetController(index);
            if (!gamepad)
            {
               SCALD_ERROR("Invalid gamepad index [{}] provided or gamepad is not plugged in!", index);
               return Sint16{ 0 };
            }
            return gamepad->GetAxisPosition(axis);
         },
         "get_hat_value", [&](int index) {
            auto gamepad = inputManager.GetController(index);
            if (!gamepad)
            {
               SCALD_ERROR("Invalid gamepad index [{}] provided or gamepad is not plugged in!", index);
               return Uint8{ 0 };
            }
            return gamepad->GetJoystickHatValue();
         }
      );
   }

   std::shared_ptr<SCALD_WINDOWING::Inputs::Gamepad> InputManager::GetController(int index)
   {
      auto gamepadItr = m_mapGameControllers.find(index);
      if (gamepadItr == m_mapGameControllers.end())
      {
         SCALD_ERROR("Failed to get gamepad at index [{}] -- Does not exist!", index);
         return nullptr;
      }

      return gamepadItr->second;
   }

   bool InputManager::AddGamepad(Sint32 gamepadID)
   {
      if (m_mapGameControllers.size() >= MAX_CONTROLLERS)
      {
         SCALD_ERROR("Trying to add too many controllers! Max Controllers allowed = {0}", MAX_CONTROLLERS);
         return false;
      }

      std::shared_ptr<SCALD_WINDOWING::Inputs::Gamepad> gamepad{ nullptr };
      try
      {
         gamepad = std::make_shared<SCALD_WINDOWING::Inputs::Gamepad>(std::move(make_shared_controller(SDL_GameControllerOpen(gamepadID))));
      }
      catch (...)
      {
         std::string error{ SDL_GetError() };
         SCALD_ERROR("Failed to Open Gamepad device -- {}", error);
         return false;
      }

      for (int i = 1; i <= MAX_CONTROLLERS; i++)
      {
         if (m_mapGameControllers.contains(i))
            continue;

         m_mapGameControllers.emplace(i, std::move(gamepad));
         SCALD_LOG("Gamepad [{}] was added at index [{}]", gamepadID, i);
         return true;
      }

      SCALD_ASSERT(false && "Failed to add the new controller!");
      SCALD_ERROR("Failed to add the new controller!");
      return false;
   }

   bool InputManager::RemoveGamepad(Sint32 gamepadID)
   {
      auto gamepadRemoved = std::erase_if(m_mapGameControllers,
         [&](auto& gamepad) {
            return gamepad.second->CheckJoystickID(gamepadID);
         }
      );

      if (gamepadRemoved > 0)
      {
         SCALD_LOG("Gamepad Removed -- [{}]", gamepadID);
         return true;
      }

      SCALD_ASSERT(false && "Failed to remove the Gamepad!");
      SCALD_ERROR("Failed to remove the Gamepad! -- [{}]", gamepadID);
      return false;
   }

   void InputManager::GamepadBtnPressed(const SDL_Event& event)
   {
      for (const auto& [index, gamepad] : m_mapGameControllers)
      {
         if (gamepad && gamepad->CheckJoystickID(event.jdevice.which))
         {
            gamepad->OnButtonPressed(event.cbutton.button);
            break;
         }
      }
   }

   void InputManager::GamepadBtnReleased(const SDL_Event& event)
   {
      for (const auto& [index, gamepad] : m_mapGameControllers)
      {
         if (gamepad && gamepad->CheckJoystickID(event.jdevice.which))
         {
            gamepad->OnButtonReleased(event.cbutton.button);
            break;
         }
      }
   }

   void InputManager::GamepadAxisValues(const SDL_Event& event)
   {
      for (const auto& [index, gamepad] : m_mapGameControllers)
      {
         if (gamepad && gamepad->CheckJoystickID(event.jdevice.which))
         {
            gamepad->SetAxisPosition(event.jaxis.axis, event.jaxis.value);
            break;
         }
      }
   }

   void InputManager::GamepadHatValues(const SDL_Event& event)
   {
      for (const auto& [index, gamepad] : m_mapGameControllers)
      {
         if (gamepad && gamepad->CheckJoystickID(event.jdevice.which))
         {
            gamepad->SetJoystickHatValue(event.jhat.value);
            break;
         }
      }
   }

   void InputManager::UpdateGamepads()
   {
      for (const auto& [index, gamepad] : m_mapGameControllers)
      {
         if (gamepad)
            gamepad->Update();
      }
   }

}
