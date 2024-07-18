#include "Window.h"
#include <iostream>

namespace SCALD_WINDOWING {

   void Window::CreateNewWindow(Uint32 flags)
   {
      m_pWindow = WindowPtr(SDL_CreateWindow(
         m_sTitle.c_str(),
         m_XPos,
         m_YPos,
         m_Width,
         m_Height,
         flags
      ));

      // Check to see if the window was created correctly
      if (!m_pWindow)
      {
         std::string error = SDL_GetError();
         std::cout << "Failed to create the window: " << error << "\n";
      }
   }

   Window::Window(const std::string title, int width, int height, int xPos, int yPos, bool vsync, Uint32 flags)
      : m_pWindow{ nullptr }, m_GLContext{}, m_sTitle{ title }, m_Width{ width }, m_Height{ height }, m_XPos{ xPos }, m_YPos{ yPos }, m_WindowFlags{ flags }
   {
      CreateNewWindow(flags);

      // Enable v-sync
      if (vsync)
      {
         if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"))
            std::cout << "Failed to enable VSYNC!\n";
      }
      std::cout << "Window Created Successfully!\n";
   }

   Window::~Window()
   {
   }

   void Window::SetWindowName(const std::string& name)
   {
      m_sTitle = name;
      SDL_SetWindowTitle(m_pWindow.get(), name.c_str());
   }

}
