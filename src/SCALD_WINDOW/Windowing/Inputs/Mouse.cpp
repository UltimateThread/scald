#include "Mouse.h"
#include <SDL.h>
#include <Logger/Logger.h>

namespace SCALD_WINDOWING::Inputs {

   void Mouse::Update()
   {
      for (auto& [btn, button] : m_mapButtons)
      {
         button.Reset();
      }

      m_WheelX = 0;
      m_WheelY = 0;
      m_bMouseMoving = false;
   }

   void Mouse::OnBtnPressed(int btn)
   {
      if (btn == SCALD_MOUSE_UNKNOWN)
      {
         SCALD_ERROR("Mouse Button [{0}] is unknown!", btn);
         return;
      }

      auto btnItr = m_mapButtons.find(btn);
      if (btnItr == m_mapButtons.end())
      {
         SCALD_ERROR("Mouse Button [{0}] does not exist!", btn);
         return;
      }

      btnItr->second.Update(true);
   }

   void Mouse::OnBtnReleased(int btn)
   {
      if (btn == SCALD_MOUSE_UNKNOWN)
      {
         SCALD_ERROR("Mouse Button [{0}] is unknown!", btn);
         return;
      }

      auto btnItr = m_mapButtons.find(btn);
      if (btnItr == m_mapButtons.end())
      {
         SCALD_ERROR("Mouse Button [{0}] does not exist!", btn);
         return;
      }

      btnItr->second.Update(false);
   }

   const bool Mouse::IsBtnPressed(int btn) const
   {
      if (btn == SCALD_MOUSE_UNKNOWN)
      {
         SCALD_ERROR("Mouse Button [{0}] is unknown!", btn);
         return false;
      }

      auto btnItr = m_mapButtons.find(btn);
      if (btnItr == m_mapButtons.end())
      {
         SCALD_ERROR("Mouse Button [{0}] does not exist!", btn);
         return false;
      }

      return btnItr->second.bIsPressed;
   }

   const bool Mouse::IsBtnJustPressed(int btn) const
   {
      if (btn == SCALD_MOUSE_UNKNOWN)
      {
         SCALD_ERROR("Mouse Button [{0}] is unknown!", btn);
         return false;
      }

      auto btnItr = m_mapButtons.find(btn);
      if (btnItr == m_mapButtons.end())
      {
         SCALD_ERROR("Mouse Button [{0}] does not exist!", btn);
         return false;
      }

      return btnItr->second.bJustPressed;
   }

   const bool Mouse::IsBtnJustReleased(int btn) const
   {
      if (btn == SCALD_MOUSE_UNKNOWN)
      {
         SCALD_ERROR("Mouse Button [{0}] is unknown!", btn);
         return false;
      }

      auto btnItr = m_mapButtons.find(btn);
      if (btnItr == m_mapButtons.end())
      {
         SCALD_ERROR("Mouse Button [{0}] does not exist!", btn);
         return false;
      }

      return btnItr->second.bJustReleased;
   }

   std::tuple<int, int> Mouse::GetMouseScreenPosition()
   {
      SDL_GetMouseState(&m_X, &m_Y);
      return std::make_tuple(m_X, m_Y);
   }

}
