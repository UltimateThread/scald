#pragma once
#include "../ECS/Registry.h"

namespace SCALD_CORE::Systems {

   class AnimationSystem {
   private:
      SCALD_CORE::ECS::Registry& m_Registry;

   public:
      AnimationSystem(SCALD_CORE::ECS::Registry& registry);
      ~AnimationSystem() = default;

      void Update();

   };

}
