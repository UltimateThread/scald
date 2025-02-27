#pragma once
#include <Rendering/Essentials/Vertex.h>
#include <sol/sol.hpp>
#include "../Registry.h"

namespace SCALD_CORE::ECS {

   struct UVs
   {
      float u{ 0.f }, v{ 0.f }, uv_width{ 0.f }, uv_height{ 0.f };
   };

   struct SpriteComponent
   {
      float width{ 0.f }, height{ 0.f };
      UVs uvs{ .u = 0.f, .v = 0.f, .uv_width = 0.f, .uv_height = 0.f };

      SCALD_RENDERING::Color color{ .r = 255, .g = 255, .b = 255, .a = 255 };
      int start_x{ 0 }, start_y{ 0 }, layer{ 0 };

      std::string texture_name{ "" };

      void generate_uvs(int textureWidth, int textureHeight)
      {
         uvs.uv_width = width / textureWidth;
         uvs.uv_height = height / textureHeight;

         uvs.u = start_x * uvs.uv_width;
         uvs.v = start_y * uvs.uv_height;
      }

      static void CreateSpriteLuaBind(sol::state& lua, SCALD_CORE::ECS::Registry& registry);
   };

}
