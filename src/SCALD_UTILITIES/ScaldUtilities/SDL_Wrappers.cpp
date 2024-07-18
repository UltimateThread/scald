#include "SDL_Wrappers.h"
#include <iostream>

namespace SCALD_UTIL {

   void SDL_Destroyer::operator()(SDL_Window* window) const
   {
      SDL_DestroyWindow(window);
      std::cout << "Destroyed SDL Window\n";
   }

   void SDL_Destroyer::operator()(SDL_GameController* controller) const
   {
      SDL_GameControllerClose(controller);
      controller = nullptr;
      std::cout << "Closed SDL Game Controller\n";
   }

   void SDL_Destroyer::operator()(SDL_Cursor* cursor) const
   {
   }

   Controller make_shared_controller(SDL_GameController* controller)
   {
      return Controller();
   }

   Cursor make_shared_cursor(SDL_Cursor* cursor)
   {
      return Cursor();
   }

}
