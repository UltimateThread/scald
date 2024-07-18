#pragma once
#include "GPButton.h"
#include "Button.h"
#include <ScaldUtilities/SDL_Wrappers.h>
#include <map>
#include <string>

namespace SCALD_WINDOWING::Inputs {

   class Gamepad
   {
   private:
      Controller m_pController;
      std::map<int, Button> m_mapButtons;
      SDL_JoystickID m_JoystickID;
      std::map<Uint8, Sint16> m_mapAxisValues;
      Uint8 m_JoystickHatValue;
      std::string m_sName;

   public:
      Gamepad(Controller controller);
      ~Gamepad() = default;

      void Update();
      void OnButtonPressed(int btn);
      void OnButtonReleased(int btn);

      const bool IsButtonPressed(int btn);
      const bool IsButtonJustPressed(int btn);
      const bool IsButtonJustReleased(int btn);

      const bool IsGamepadPresent() const;

      const Sint16 GetAxisPosition(Uint8 axis);
      void SetAxisPosition(Uint8 axis, Sint16 value);

      inline void SetJoystickHatValue(Uint8 value) { m_JoystickHatValue = value; }
      inline const Uint8 GetJoystickHatValue() const { return m_JoystickHatValue; }

      inline const bool CheckJoystickID(SDL_JoystickID joystickID) const { return m_JoystickID == joystickID; }
      inline const std::string& GetName() const { return m_sName; }

   };

}
