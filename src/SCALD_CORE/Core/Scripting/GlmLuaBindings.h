#pragma once
#include <sol/sol.hpp>

namespace SCALD_CORE::Scripting {

   struct GLMBindings
   {
      static void CreateGLMBindings(sol::state& lua);
   };

}
