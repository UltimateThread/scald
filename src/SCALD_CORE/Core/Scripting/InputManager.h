#pragma once
#include <Windowing/Inputs/Keyboard.h>
#include <Windowing/Inputs/Mouse.h>
#include <memory>
#include <sol/sol.hpp>

namespace SCALD_CORE {

   class InputManager
   {
   private:
      std::unique_ptr<SCALD_WINDOWING::Inputs::Keyboard> m_pKeyboard;
      std::unique_ptr<SCALD_WINDOWING::Inputs::Mouse> m_pMouse;

      InputManager();
      ~InputManager() = default;
      InputManager(const InputManager&) = delete;
      InputManager& operator=(const InputManager&) = delete;

      static void RegisterLuaKeyNames(sol::state& lua);
      static void RegisterLuaMouseBtnNames(sol::state& lua);

   public:
      static InputManager& GetInstance();
      static void CreateLuaInputBindings(sol::state& lua);

      inline SCALD_WINDOWING::Inputs::Keyboard& GetKeyboard() { return *m_pKeyboard; }
      inline SCALD_WINDOWING::Inputs::Mouse& GetMouse() { return *m_pMouse; }

   };

}
