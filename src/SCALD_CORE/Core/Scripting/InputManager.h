#pragma once
#include <Windowing/Inputs/Keyboard.h>
#include <memory>
#include <sol/sol.hpp>

namespace SCALD_CORE {

   class InputManager
   {
   private:
      std::unique_ptr<SCALD_WINDOWING::Inputs::Keyboard> m_pKeyboard;

      InputManager();
      ~InputManager() = default;
      InputManager(const InputManager&) = delete;
      InputManager& operator=(const InputManager&) = delete;

      static void RegisterLuaKeyNames(sol::state& lua);

   public:
      static InputManager& GetInstance();
      static void CreateLuaInputBindings(sol::state& lua);

      inline SCALD_WINDOWING::Inputs::Keyboard& GetKeyboard() { return *m_pKeyboard; }

   };

}
