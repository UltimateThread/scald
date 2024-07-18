#include "Gamepad.h"
#include <Logger/Logger.h>

namespace SCALD_WINDOWING::Inputs {

   Gamepad::Gamepad(Controller controller)
      : m_pController{ std::move(controller) },
      m_mapButtons{
         {SCALD_GP_BTN_A, Button{}},
         {SCALD_GP_BTN_B, Button{}},
         {SCALD_GP_BTN_X, Button{}},
         {SCALD_GP_BTN_Y, Button{}},
         {SCALD_GP_BTN_BACK, Button{}},
         {SCALD_GP_BTN_GUIDE, Button{}},
         {SCALD_GP_BTN_START, Button{}},
         {SCALD_GP_BTN_LSTICK, Button{}},
         {SCALD_GP_BTN_RSTICK, Button{}},
         {SCALD_GP_BTN_LSHOULDER, Button{}},
         {SCALD_GP_BTN_RSHOULDER, Button{}},
         {SCALD_GP_BTN_DPAD_UP, Button{}},
         {SCALD_GP_BTN_DPAD_DOWN, Button{}},
         {SCALD_GP_BTN_DPAD_LEFT, Button{}},
         {SCALD_GP_BTN_DPAD_RIGHT, Button{}},
      },
      m_JoystickID{ -1 },
      m_mapAxisValues{
         {0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0},
      },
      m_JoystickHatValue{ SCALD_HAT_CENTERED }
   {
      SDL_Joystick* joystick = SDL_GameControllerGetJoystick(m_pController.get());
      if (!m_pController || !joystick)
         throw("Controller or Joystick we nullptr");

      m_JoystickID = SDL_JoystickInstanceID(joystick);
      m_sName = std::string{ SDL_JoystickName(joystick) };

      auto num_axis = SDL_JoystickNumAxes(joystick);
      auto num_balls = SDL_JoystickNumBalls(joystick);
      auto num_hats = SDL_JoystickNumHats(joystick);
      auto num_buttons = SDL_JoystickNumButtons(joystick);

      SCALD_LOG("Gamepad name: {0}", m_sName);
      SCALD_LOG("Gamepad joystickID: {0}", m_JoystickID);
      SCALD_LOG("Gamepad num axis: {0}", num_axis);
      SCALD_LOG("Gamepad num balls: {0}", num_balls);
      SCALD_LOG("Gamepad num hats: {0}", num_hats);
      SCALD_LOG("Gamepad num buttons: {0}", num_buttons);
   }

   void Gamepad::Update()
   {
      for (auto& [btn, button] : m_mapButtons)
         button.Reset();
   }

   void Gamepad::OnButtonPressed(int btn)
   {
      if (btn == SCALD_GP_BTN_UNKNOWN)
      {
         SCALD_ERROR("Gamepad button [{0}] is unknown!", btn);
         return;
      }

      auto btnItr = m_mapButtons.find(btn);
      if (btnItr == m_mapButtons.end())
      {
         SCALD_ERROR("Gamepad button [{0}] does not exist!", btn);
         return;
      }

      btnItr->second.Update(true);
   }

   void Gamepad::OnButtonReleased(int btn)
   {
      if (btn == SCALD_GP_BTN_UNKNOWN)
      {
         SCALD_ERROR("Gamepad button [{0}] is unknown!", btn);
         return;
      }

      auto btnItr = m_mapButtons.find(btn);
      if (btnItr == m_mapButtons.end())
      {
         SCALD_ERROR("Gamepad button [{0}] does not exist!", btn);
         return;
      }

      btnItr->second.Update(false);
   }

   const bool Gamepad::IsButtonPressed(int btn)
   {
      if (btn == SCALD_GP_BTN_UNKNOWN)
      {
         SCALD_ERROR("Gamepad button [{0}] is unknown!", btn);
         return false;
      }

      auto btnItr = m_mapButtons.find(btn);
      if (btnItr == m_mapButtons.end())
      {
         SCALD_ERROR("Gamepad button [{0}] does not exist!", btn);
         return false;
      }

      return btnItr->second.bIsPressed;
   }

   const bool Gamepad::IsButtonJustPressed(int btn)
   {
      if (btn == SCALD_GP_BTN_UNKNOWN)
      {
         SCALD_ERROR("Gamepad button [{0}] is unknown!", btn);
         return false;
      }

      auto btnItr = m_mapButtons.find(btn);
      if (btnItr == m_mapButtons.end())
      {
         SCALD_ERROR("Gamepad button [{0}] does not exist!", btn);
         return false;
      }

      return btnItr->second.bJustPressed;
   }

   const bool Gamepad::IsButtonJustReleased(int btn)
   {
      if (btn == SCALD_GP_BTN_UNKNOWN)
      {
         SCALD_ERROR("Gamepad button [{0}] is unknown!", btn);
         return false;
      }

      auto btnItr = m_mapButtons.find(btn);
      if (btnItr == m_mapButtons.end())
      {
         SCALD_ERROR("Gamepad button [{0}] does not exist!", btn);
         return false;
      }

      return btnItr->second.bJustReleased;
   }

   const bool Gamepad::IsGamepadPresent() const
   {
      return m_pController != nullptr && SDL_NumJoysticks() > 0;
   }

   const Sint16 Gamepad::GetAxisPosition(Uint8 axis)
   {
      auto axisItr = m_mapAxisValues.find(axis);
      if (axisItr == m_mapAxisValues.end())
      {
         SCALD_ERROR("Axis [{0}] does not exist!", axis);
         return 0;
      }

      return axisItr->second;
   }

   void Gamepad::SetAxisPosition(Uint8 axis, Sint16 value)
   {
      auto axisItr = m_mapAxisValues.find(axis);
      if (axisItr == m_mapAxisValues.end())
      {
         SCALD_ERROR("Axis [{0}] does not exist!", axis);
         return;
      }

      axisItr->second = value;
   }

}
