#pragma once
#include "../ECS/Registry.h"
#include <sol/sol.hpp>

namespace SCALD_CORE::Systems {

   class ScriptingSystem {
   private:
      SCALD_CORE::ECS::Registry& m_Registry;
      bool m_bMainLoaded;

   public:
      ScriptingSystem(SCALD_CORE::ECS::Registry& registry);
      ~ScriptingSystem() = default;

      bool LoadMainScript(sol::state& lua);
      void Update();
      void Render();

      static void RegisterLuaBindings(sol::state& lua, SCALD_CORE::ECS::Registry& registry);
      static void RegisterLuaFunctions(sol::state& lua);

   };

}
