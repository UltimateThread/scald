#include "Entity.h"
#include "Components/Identification.h"
#include "MetaUtilities.h"

namespace SCALD_CORE::ECS {

   Entity::Entity(Registry& registry)
      :Entity(registry, "GameObject", "")
   {
   }

   Entity::Entity(Registry& registry, const std::string& name, const std::string& group)
      : m_Registry{ registry }, m_Entity{ registry.CreateEntity() }, m_sName{ name }, m_sGroup{ group }
   {
      AddComponent<Identification>(Identification{
         .name = name,
         .group = group,
         .entity_id = static_cast<int32_t>(m_Entity)
         }
      );
   }

   Entity::Entity(Registry& registry, const entt::entity& entity)
      : m_Registry{ registry }, m_Entity{ entity }, m_sName{ "" }, m_sGroup{ "" }
   {
      if (HasComponent<Identification>())
      {
         auto id = GetComponent<Identification>();
         m_sName = id.name;
         m_sGroup = id.group;
      }
   }

   void Entity::CreateLuaEntityBind(sol::state& lua, Registry& registry)
   {
      using namespace entt::literals;
      lua.new_usertype<Entity>(
         "Entity",
         sol::call_constructor,
         sol::factories(
            [&](const std::string& name, const std::string& group) {
               return Entity{ registry, name, group };
            },
            [&](std::int32_t id) {
               return Entity{ registry, static_cast<entt::entity>(id) };
            }
         ),
         "add_component", [&](Entity& entity, const sol::table& comp, sol::this_state s) -> sol::object {
            if (!comp.valid())
               return sol::lua_nil_t{};

            const auto component = SCALD_CORE::Utils::InvokeMetaFunction(
               SCALD_CORE::Utils::GetIdType(comp),
               "add_component"_hs,
               entity,
               comp,
               s
            );

            return component ? component.cast<sol::reference>() : sol::lua_nil_t{};
         },
         "has_component", [](Entity& entity, const sol::table& comp) {
            const auto has_component = SCALD_CORE::Utils::InvokeMetaFunction(
               SCALD_CORE::Utils::GetIdType(comp),
               "has_component"_hs,
               entity
            );

            return has_component ? has_component.cast<bool>() : false;
         },
         "get_component", [](Entity& entity, const sol::table& comp, sol::this_state s) {
            const auto component = SCALD_CORE::Utils::InvokeMetaFunction(
               SCALD_CORE::Utils::GetIdType(comp),
               "get_component"_hs,
               entity,
               s
            );

            return component ? component.cast<sol::reference>() : sol::lua_nil_t{};
         },
         "remove_component", [](Entity& entity, const sol::table& comp) {
            const auto component = SCALD_CORE::Utils::InvokeMetaFunction(
               SCALD_CORE::Utils::GetIdType(comp),
               "remove_component"_hs,
               entity
            );

            return component ? component.cast<sol::reference>() : sol::lua_nil_t{};
         },
         "name", &Entity::GetName,
         "group", &Entity::GetGroup,
         "kill", &Entity::Kill,
         "id", [](Entity& entity) { return static_cast<int32_t>(entity.GetEntity()); }
      );
   }

}
