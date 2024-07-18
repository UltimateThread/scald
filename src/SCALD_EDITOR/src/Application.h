#pragma once
#include <glad/glad.h>
#include <Windowing/Window/Window.h>
#include <Core/ECS/Registry.h>

namespace SCALD_EDITOR {

   class Application
   {
   private:
      std::unique_ptr<SCALD_WINDOWING::Window> m_pWindow;
      std::unique_ptr<SCALD_CORE::ECS::Registry> m_pRegistry;

      SDL_Event m_Event;
      bool m_bIsRunning;

      bool Initialize();
      bool LoadShaders();

      void ProcessEvents();
      void Update();
      void Render();

      void CleanUp();

      Application();

   public:
      static Application& GetInstance();
      ~Application();

      void Run();

   };

}
