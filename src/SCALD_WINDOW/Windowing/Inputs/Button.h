#pragma once

namespace SCALD_WINDOWING::Inputs {

   struct Button
   {
      bool bIsPressed{ false }, bJustPressed{ false }, bJustReleased{ false };
      void Update(bool bPressed);
      void Reset();
   };

}
