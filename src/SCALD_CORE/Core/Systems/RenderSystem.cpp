#include "RenderSystem.h"
#include "../Resources/AssetManager.h"
#include "../ECS/Components/SpriteComponent.h"
#include "../ECS/Components/TransformComponent.h"
#include <Rendering/Core/Camera2D.h>
#include <Rendering/Essentials/Shader.h>
#include <Logger/Logger.h>

namespace SCALD_CORE::Systems {

   RenderSystem::RenderSystem(SCALD_CORE::ECS::Registry& registry)
      : m_Registry{ registry }, m_pBatchRenderer{ nullptr }
   {
      m_pBatchRenderer = std::make_unique<SCALD_RENDERING::BatchRenderer>();
   }

   void RenderSystem::Update()
   {
      auto& camera = m_Registry.GetContext<std::shared_ptr<SCALD_RENDERING::Camera2D>>();
      auto& assetManager = m_Registry.GetContext<std::shared_ptr<SCALD_RESOURCES::AssetManager>>();

      auto& spriteShader = assetManager->GetShader("basic");
      auto cameraMatrix = camera->GetCameraMatrix();

      if (spriteShader.ShaderProgramID() == 0)
      {
         SCALD_ERROR("Sprite shader program has not been set correctly!");
         return;
      }

      // Enable the shader
      spriteShader.Enable();
      spriteShader.SetUniformMat4("uProjection", cameraMatrix);

      m_pBatchRenderer->Begin();
      auto view = m_Registry.GetRegistry().view<SCALD_CORE::ECS::SpriteComponent, SCALD_CORE::ECS::TransformComponent>();

      for (const auto& entity : view)
      {
         const auto& transform = view.get<SCALD_CORE::ECS::TransformComponent>(entity);
         const auto& sprite = view.get<SCALD_CORE::ECS::SpriteComponent>(entity);

         if (sprite.texture_name.empty())
            continue;

         const auto& texture = assetManager->GetTexture(sprite.texture_name);
         if (texture.GetID() == 0)
         {
            SCALD_ERROR("Texture [{0}] was not created correctly!", sprite.texture_name);
            continue;
         }

         glm::vec4 spriteRect{ transform.position.x, transform.position.y, sprite.width, sprite.height };
         glm::vec4 uvRect{ sprite.uvs.u, sprite.uvs.v, sprite.uvs.uv_width, sprite.uvs.uv_height };

         glm::mat4 model{ 1.f };

         if (transform.rotation > 0.f || transform.rotation < 0.f ||
            transform.scale.x > 1.f || transform.scale.x < 1.f ||
            transform.scale.y > 1.f || transform.scale.y < 1.f)
         {
            model = glm::translate(model, glm::vec3{ transform.position, 0.f });
            model = glm::translate(model, glm::vec3{ (sprite.width * transform.scale.x) * 0.5f, (sprite.height * transform.scale.y) * 0.5f, 0.f });

            model = glm::rotate(model, glm::radians(transform.rotation), glm::vec3{ 0.f, 0.f, 1.f });
            model = glm::translate(model, glm::vec3{ (sprite.width * transform.scale.x) * -0.5f, (sprite.height * transform.scale.y) * -0.5f, 0.f });

            model = glm::scale(model, glm::vec3{ transform.scale, 1.f });

            model = glm::translate(model, glm::vec3{ -transform.position, 0.f });
         }

         m_pBatchRenderer->AddSprite(spriteRect, uvRect, texture.GetID(), sprite.layer, model, sprite.color);
      }

      m_pBatchRenderer->End();
      m_pBatchRenderer->Render();

      spriteShader.Disable();
   }

}
