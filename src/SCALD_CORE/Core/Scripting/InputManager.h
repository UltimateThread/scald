#pragma once
#include <Windowing/Inputs/Keyboard.h>
#include <Windowing/Inputs/Mouse.h>
#include <Windowing/Inputs/Gamepad.h>
#include <memory>
#include <sol/sol.hpp>

constexpr int MAX_CONTROLLERS = 4;

namespace SCALD_CORE {

   class InputManager
   {
   private:
      std::unique_ptr<SCALD_WINDOWING::Inputs::Keyboard> m_pKeyboard;
      std::unique_ptr<SCALD_WINDOWING::Inputs::Mouse> m_pMouse;
      std::map<int, std::shared_ptr<SCALD_WINDOWING::Inputs::Gamepad>> m_mapGameControllers;

      InputManager();
      ~InputManager() = default;
      InputManager(const InputManager&) = delete;
      InputManager& operator=(const InputManager&) = delete;

      static void RegisterLuaKeyNames(sol::state& lua);
      static void RegisterLuaMouseBtnNames(sol::state& lua);
      static void RegisterLuaGamepadBtnNames(sol::state& lua);

   public:
      static InputManager& GetInstance();
      static void CreateLuaInputBindings(sol::state& lua);

      inline SCALD_WINDOWING::Inputs::Keyboard& GetKeyboard() { return *m_pKeyboard; }
      inline SCALD_WINDOWING::Inputs::Mouse& GetMouse() { return *m_pMouse; }
      inline std::map<int, std::shared_ptr<SCALD_WINDOWING::Inputs::Gamepad>>& GetControllers() { return m_mapGameControllers; }

      std::shared_ptr<SCALD_WINDOWING::Inputs::Gamepad> GetController(int index);

      bool AddGamepad(Sint32 gamepadID);
      bool RemoveGamepad(Sint32 gamepadID);
      void GamepadBtnPressed(const SDL_Event& event);
      void GamepadBtnReleased(const SDL_Event& event);
      void GamepadAxisValues(const SDL_Event& event);
      void GamepadHatValues(const SDL_Event& event);
      void UpdateGamepads();

   };

}
