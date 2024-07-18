#include "ScriptingSystem.h"
#include "../ECS/Components/ScriptComponent.h"
#include "../ECS/Components/TransformComponent.h"
#include "../ECS/Components/SpriteComponent.h"
#include "../ECS/Components/AnimationComponent.h"
#include "../ECS/Entity.h"
#include <Logger/Logger.h>
#include "../Scripting/GlmLuaBindings.h"
#include "../Scripting/InputManager.h"
#include "../Resources/AssetManager.h"

namespace SCALD_CORE::Systems {

   ScriptingSystem::ScriptingSystem(SCALD_CORE::ECS::Registry& registry)
      : m_Registry{ registry }, m_bMainLoaded{ false }
   {
   }

   bool ScriptingSystem::LoadMainScript(sol::state& lua)
   {
      try
      {
         auto result = lua.safe_script_file("./assets/scripts/main.lua");
      }
      catch (const sol::error& error)
      {
         SCALD_ERROR("Error loading the main lua script: {0}", error.what());
         return false;
      }

      sol::table main_lua = lua["main"];
      sol::optional<sol::table> bUpdateExists = main_lua[1];
      if (bUpdateExists == sol::nullopt)
      {
         SCALD_ERROR("There is now update function in main.lua!");
         return false;
      }

      sol::table update_script = main_lua[1];
      sol::function update = update_script["update"];

      sol::optional<sol::table> bRenderExists = main_lua[2];
      if (bRenderExists == sol::nullopt)
      {
         SCALD_ERROR("There is now render function in main.lua!");
         return false;
      }

      sol::table render_script = main_lua[2];
      sol::function render = render_script["render"];

      SCALD_CORE::ECS::Entity mainLuaScript{ m_Registry, "main_script", "" };
      mainLuaScript.AddComponent<SCALD_CORE::ECS::ScriptComponent>(
         SCALD_CORE::ECS::ScriptComponent{
            .update = update,
            .render = render
         }
      );

      m_bMainLoaded = true;

      return true;
   }

   void ScriptingSystem::Update()
   {
      if (!m_bMainLoaded)
      {
         SCALD_ERROR("Main lua script has not been loaded!");
         return;
      }

      auto view = m_Registry.GetRegistry().view<SCALD_CORE::ECS::ScriptComponent>();
      for (const auto& entity : view)
      {
         SCALD_CORE::ECS::Entity ent{ m_Registry, entity };
         if (ent.GetName() != "main_script")
            continue;

         auto& script = ent.GetComponent<SCALD_CORE::ECS::ScriptComponent>();
         auto error = script.update(entity);
         if (!error.valid())
         {
            sol::error err = error;
            SCALD_ERROR("Error running the Update script: {0}", err.what());
         }
      }
   }

   void ScriptingSystem::Render()
   {
      if (!m_bMainLoaded)
      {
         SCALD_ERROR("Main lua script has not been loaded!");
         return;
      }

      auto view = m_Registry.GetRegistry().view<SCALD_CORE::ECS::ScriptComponent>();
      for (const auto& entity : view)
      {
         SCALD_CORE::ECS::Entity ent{ m_Registry, entity };
         if (ent.GetName() != "main_script")
            continue;

         auto& script = ent.GetComponent<SCALD_CORE::ECS::ScriptComponent>();
         auto error = script.render(entity);
         if (!error.valid())
         {
            sol::error err = error;
            SCALD_ERROR("Error running the Render script: {0}", err.what());
         }
      }
   }

   void ScriptingSystem::RegisterLuaBindings(sol::state& lua, SCALD_CORE::ECS::Registry& registry)
   {
      SCALD_CORE::Scripting::GLMBindings::CreateGLMBindings(lua);
      SCALD_CORE::InputManager::CreateLuaInputBindings(lua);
      SCALD_RESOURCES::AssetManager::CreateLuaAssetManager(lua, registry);

      SCALD_CORE::ECS::Registry::CreateLuaRegistryBind(lua, registry);
      SCALD_CORE::ECS::Entity::CreateLuaEntityBind(lua, registry);
      SCALD_CORE::ECS::TransformComponent::CreateLuaTransformBind(lua);
      SCALD_CORE::ECS::SpriteComponent::CreateSpriteLuaBind(lua, registry);
      SCALD_CORE::ECS::AnimationComponent::CreateAnimationLuaBind(lua);

      SCALD_CORE::ECS::Entity::RegisterMetaComponent<SCALD_CORE::ECS::TransformComponent>();
      SCALD_CORE::ECS::Entity::RegisterMetaComponent<SCALD_CORE::ECS::SpriteComponent>();
      SCALD_CORE::ECS::Entity::RegisterMetaComponent<SCALD_CORE::ECS::AnimationComponent>();

      SCALD_CORE::ECS::Registry::RegisterMetaComponent<SCALD_CORE::ECS::TransformComponent>();
      SCALD_CORE::ECS::Registry::RegisterMetaComponent<SCALD_CORE::ECS::SpriteComponent>();
      SCALD_CORE::ECS::Registry::RegisterMetaComponent<SCALD_CORE::ECS::AnimationComponent>();
   }

   void ScriptingSystem::RegisterLuaFunctions(sol::state& lua)
   {
      lua.set_function(
         "run_script", [&](const std::string& path)
         {
            try
            {
               lua.safe_script_file(path);
            }
            catch (const sol::error& error)
            {
               SCALD_ERROR("Error loading lua script: {}", error.what());
               return false;
            }

            return true;
         }
      );
   }

}
