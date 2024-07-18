#include "TextureLoader.h"
#include <SOIL/SOIL.h>
#include <Logger/Logger.h>

namespace SCALD_RENDERING {

   bool TextureLoader::LoadTexture(const std::string& filepath, GLuint& id, int& width, int& height, bool blended)
   {
      int channels = 0;

      unsigned char* image = SOIL_load_image(
         filepath.c_str(),
         &width,
         &height,
         &channels,
         SOIL_LOAD_AUTO
      );

      // Check to see if the image loading was successful
      if (!image)
      {
         SCALD_ERROR("SOIL failed to load image [{0}] -- {1}", filepath, SOIL_last_result());
         return false;
      }

      GLint format = GL_RGBA;

      switch (channels)
      {
      case 3: format = GL_RGB; break;
      case 4: format = GL_RGBA; break;
      }

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

      if (!blended)
      {
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      }
      else
      {
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      }

      glTexImage2D(
         GL_TEXTURE_2D,       // target            -- Specifies the target texture
         0,                   // level             -- Level of detail. 0 is the base image level
         format,              // internal format   -- The number of color components
         width,               // width             -- Width of the texture image
         height,              // height            -- Height of the texture image
         0,                   // border            
         format,              // format            -- Format of the pixel data
         GL_UNSIGNED_BYTE,    // type              -- The data type of the pixel data
         image                // data
      );

      // Delete the image data from SOIL
      SOIL_free_image_data(image);

      return true;
   }

   std::shared_ptr<Texture> TextureLoader::Create(Texture::TextureType type, const std::string& texturePath)
   {
      GLuint id;
      int width, height;

      glGenTextures(1, &id);
      glBindTexture(GL_TEXTURE_2D, id);

      switch (type)
      {
      case Texture::TextureType::PIXEL:
         LoadTexture(texturePath, id, width, height, false);
         break;
      case Texture::TextureType::BLENDED:
         LoadTexture(texturePath, id, width, height, true);
         break;
      // TODO: Add other texture types for loading as needed -- Ex Framebuffer texture
      default:
         assert(false && "The current type is not defined, please use a defined texture type!");
         return nullptr;
      }

      return std::make_shared<Texture>(id, width, height, type, texturePath);
   }

}
