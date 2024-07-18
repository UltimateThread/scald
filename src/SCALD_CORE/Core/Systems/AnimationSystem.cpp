#include "AnimationSystem.h"
#include "../ECS/Components/AnimationComponent.h"
#include "../ECS/Components/SpriteComponent.h"
#include "../ECS/Components/TransformComponent.h"
#include <SDL.h>

namespace SCALD_CORE::Systems {

   AnimationSystem::AnimationSystem(SCALD_CORE::ECS::Registry& registry)
      : m_Registry{registry}
   {
      
   }

   void AnimationSystem::Update()
   {
      auto view = m_Registry.GetRegistry().view<SCALD_CORE::ECS::AnimationComponent, SCALD_CORE::ECS::SpriteComponent, SCALD_CORE::ECS::TransformComponent>();

      for (auto entity : view)
      {
         const auto& transform = view.get<SCALD_CORE::ECS::TransformComponent>(entity);
         auto& sprite = view.get<SCALD_CORE::ECS::SpriteComponent>(entity);
         auto& animation = view.get<SCALD_CORE::ECS::AnimationComponent>(entity);

         // Get the current frame
         animation.currentFrame = (SDL_GetTicks() * animation.frameRate / 1000) % animation.numFrames;

         if (animation.bVertical)
         {
            sprite.uvs.v = animation.currentFrame * sprite.uvs.uv_height;
            sprite.uvs.u = animation.frameOffset * sprite.uvs.uv_width;
         }
         else
         {
            sprite.uvs.u = (animation.currentFrame * sprite.uvs.uv_width) + (animation.frameOffset * sprite.uvs.uv_width);
         }
      }
   }

}
