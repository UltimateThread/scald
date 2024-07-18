#pragma once
#include "../ECS/Registry.h"
#include <Rendering/Core/BatchRenderer.h>

namespace SCALD_CORE::Systems {

   class RenderSystem
   {
   private:
      SCALD_CORE::ECS::Registry& m_Registry;
      std::unique_ptr<SCALD_RENDERING::BatchRenderer> m_pBatchRenderer;

   public:
      RenderSystem(SCALD_CORE::ECS::Registry& registry);
      ~RenderSystem() = default;

      void Update();

   };

}
