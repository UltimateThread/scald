#include "AssetManager.h"
#include <Rendering/Essentials/TextureLoader.h>
#include <Rendering/Essentials/ShaderLoader.h>
#include <Logger/Logger.h>

namespace SCALD_RESOURCES {

   bool AssetManager::AddTexture(const std::string& textureName, const std::string& texturePath, bool pixelArt)
   {
      // Check to see if the texture already exists
      if (m_mapTextures.find(textureName) != m_mapTextures.end())
      {
         SCALD_ERROR("Failed to add texture [{0}] -- Already exists!", textureName);
         return false;
      }

      auto texture = std::move(SCALD_RENDERING::TextureLoader::Create(
         pixelArt ? SCALD_RENDERING::Texture::TextureType::PIXEL : SCALD_RENDERING::Texture::TextureType::BLENDED,
         texturePath
      ));

      if (!texture)
      {
         SCALD_ERROR("Failed to load texture [{0}] at path [{1}]", textureName, texturePath);
         return false;
      }

      m_mapTextures.emplace(textureName, std::move(texture));

      return true;
   }

   const SCALD_RENDERING::Texture& AssetManager::GetTexture(const std::string& textureName)
   {
      auto textureIter = m_mapTextures.find(textureName);
      if (textureIter == m_mapTextures.end())
      {
         SCALD_ERROR("Failed to get texture [{0}] -- Does not exist!", textureName);
         return SCALD_RENDERING::Texture();
      }

      return *textureIter->second;
   }

   bool AssetManager::AddShader(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
   {
      // Check if the shader already exists
      if (m_mapShaders.find(shaderName) != m_mapShaders.end())
      {
         SCALD_ERROR("Failed to add shader [{0}] -- Shader already exists!", shaderName);
         return false;
      }

      // Create and load the shader
      auto shader = std::move(SCALD_RENDERING::ShaderLoader::Create(vertexPath, fragmentPath));
      if (!shader)
      {
         SCALD_ERROR("Failed to load shader [{0}] at vert path [{1}] and frag path [{2}]", shaderName, vertexPath, fragmentPath);
         return false;
      }

      m_mapShaders.emplace(shaderName, std::move(shader));

      return true;
   }

   SCALD_RENDERING::Shader& AssetManager::GetShader(const std::string& shaderName)
   {
      auto shaderIter = m_mapShaders.find(shaderName);
      if (shaderIter == m_mapShaders.end())
      {
         SCALD_ERROR("Failed to get shader [{0}] -- Does not exist!", shaderName);
         SCALD_RENDERING::Shader shader{};
         return shader;
      }

      return *shaderIter->second;
   }

   void AssetManager::CreateLuaAssetManager(sol::state& lua, SCALD_CORE::ECS::Registry& registry)
   {
      auto& assetManager = registry.GetContext<std::shared_ptr<AssetManager>>();
      if (!assetManager)
      {
         SCALD_ERROR("Failed to bind the asset manager to lua - Does not exist in the registry!");
         return;
      }

      lua.new_usertype<AssetManager>(
         "AssetManager",
         sol::no_constructor,
         "add_texture", [&](const std::string& assetName, const std::string& filepath, bool pixelArt)
         {
            return assetManager->AddTexture(assetName, filepath, pixelArt);
         }
      );
   }

}
