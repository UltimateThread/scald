#include "Application.h"
#include <SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Rendering/Essentials/ShaderLoader.h>
#include <Rendering/Essentials/TextureLoader.h>
#include <Logger/Logger.h>
#include <Rendering/Core/Camera2D.h>
#include <Rendering/Essentials/Vertex.h>
#include <entt.hpp>
#include <Core/ECS/Entity.h>
#include <Core/ECS/Components/SpriteComponent.h>
#include <Core/ECS/Components/TransformComponent.h>
#include <Core/ECS/Components/Identification.h>
#include <Core/Resources/AssetManager.h>
#include <Core/Systems/ScriptingSystem.h>
#include <Core/Systems/RenderSystem.h>
#include <Core/Systems/AnimationSystem.h>
#include <Core/Scripting/InputManager.h>
#include <Windowing/Inputs/Keyboard.h>
#include <Windowing/Inputs/Mouse.h>
#include <Windowing/Inputs/Gamepad.h>

namespace SCALD_EDITOR {

   bool Application::Initialize()
   {
      SCALD_INIT_LOGS(true, true);

      // Init SDL
      if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
      {
         std::string error = SDL_GetError();
         std::cout << "Failed to initialize SDL: " << error << "\n";
         return false;
      }

      // Set up OpenGL
      if (SDL_GL_LoadLibrary(NULL) != 0)
      {
         std::string error = SDL_GetError();
         std::cout << "Failed to initialize OpenGL: " << error << "\n";
         return false;
      }

      // Set the OpenGL attributes
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

      // Set the number of bits per channel
      SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
      SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
      SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
      SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
      SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
      SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
      SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

      // Create the window
      m_pWindow = std::make_unique<SCALD_WINDOWING::Window>(
         "Test Window",
         640,
         480,
         SDL_WINDOWPOS_CENTERED,
         SDL_WINDOWPOS_CENTERED,
         true,
         SDL_WINDOW_OPENGL
      );

      if (!m_pWindow->GetWindow())
      {
         std::cout << "Failed to create the window!" << "\n";
         return false;
      }

      // Create OpenGL Context
      m_pWindow->SetGLContext(SDL_GL_CreateContext(m_pWindow->GetWindow().get()));

      if (!m_pWindow->GetGLContext())
      {
         std::string error = SDL_GetError();
         std::cout << "Failed to create OpenGL Context: " << error << "\n";
         return false;
      }

      SDL_GL_MakeCurrent(m_pWindow->GetWindow().get(), m_pWindow->GetGLContext());
      SDL_GL_SetSwapInterval(1);

      // Initialize Glad
      if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0)
      {
         std::cout << "Failed to LoadGL --> GLAD" << std::endl;
         return false;
      }

      // Enable Alpha Blending
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      auto assetManager = std::make_shared<SCALD_RESOURCES::AssetManager>();
      if (!assetManager)
      {
         SCALD_ERROR("Failed to create the asset manager!");
         return false;
      }

      // Create a new entity -- for test
      m_pRegistry = std::make_unique<SCALD_CORE::ECS::Registry>();

      // Create the lua state
      auto lua = std::make_shared<sol::state>();
      if (!lua)
      {
         SCALD_ERROR("Failed to create the lua state!");
         return false;
      }

      lua->open_libraries(sol::lib::base, sol::lib::math, sol::lib::os, sol::lib::table, sol::lib::io, sol::lib::string);

      if (!m_pRegistry->AddToContext<std::shared_ptr<sol::state>>(lua))
      {
         SCALD_ERROR("Failed to add the sol::state to the registry context!");
         return false;
      }

      auto scriptingSystem = std::make_shared<SCALD_CORE::Systems::ScriptingSystem>(*m_pRegistry);
      if (!scriptingSystem)
      {
         SCALD_ERROR("Failed to create the scripting system!");
         return false;
      }

      if (!m_pRegistry->AddToContext<std::shared_ptr<SCALD_CORE::Systems::ScriptingSystem>>(scriptingSystem))
      {
         SCALD_ERROR("Failed to add the scripting system to the registry context!");
         return false;
      }

      auto renderSystem = std::make_shared<SCALD_CORE::Systems::RenderSystem>(*m_pRegistry);
      if (!renderSystem)
      {
         SCALD_ERROR("Failed to create the rendering system!");
         return false;
      }

      if (!m_pRegistry->AddToContext<std::shared_ptr<SCALD_CORE::Systems::RenderSystem>>(renderSystem))
      {
         SCALD_ERROR("Failed to add the render system to the registry context!");
         return false;
      }

      auto animationSystem = std::make_shared<SCALD_CORE::Systems::AnimationSystem>(*m_pRegistry);
      if (!animationSystem)
      {
         SCALD_ERROR("Failed to create the animation system!");
         return false;
      }

      if (!m_pRegistry->AddToContext<std::shared_ptr<SCALD_CORE::Systems::AnimationSystem>>(animationSystem))
      {
         SCALD_ERROR("Failed to add the animation system to the registry context!");
         return false;
      }

      // Create a temp camera
      auto camera = std::make_shared<SCALD_RENDERING::Camera2D>(SCALD_RENDERING::Camera2D{});

      if (!m_pRegistry->AddToContext<std::shared_ptr<SCALD_RESOURCES::AssetManager>>(assetManager))
      {
         SCALD_ERROR("Failed to add the asset manager to the registry context!");
         return false;
      }

      if (!m_pRegistry->AddToContext<std::shared_ptr<SCALD_RENDERING::Camera2D>>(camera))
      {
         SCALD_ERROR("Failed to add the camera to the registry context!");
         return false;
      }

      if (!LoadShaders())
      {
         SCALD_ERROR("Failed to load the shaders!");
         return false;
      }

      SCALD_CORE::Systems::ScriptingSystem::RegisterLuaBindings(*lua, *m_pRegistry);
      SCALD_CORE::Systems::ScriptingSystem::RegisterLuaFunctions(*lua);

      if (!scriptingSystem->LoadMainScript(*lua))
      {
         SCALD_ERROR("Failed to load the main lua script!");
         return false;
      }

      return true;
   }

   bool Application::LoadShaders()
   {
      auto& assetManager = m_pRegistry->GetContext <std::shared_ptr<SCALD_RESOURCES::AssetManager>>();
      if (!assetManager)
      {
         SCALD_ERROR("Failed to get the asset manager from the registry context!");
         return false;
      }

      if (!assetManager->AddShader("basic", "assets/shaders/basicShader.vert", "assets/shaders/basicShader.frag"))
      {
         SCALD_ERROR("Failed to add the shader to the asset manager");
         return false;
      }

      return true;
   }

   void Application::ProcessEvents()
   {
      auto& inputManager = SCALD_CORE::InputManager::GetInstance();
      auto& keyboard = inputManager.GetKeyboard();
      auto& mouse = inputManager.GetMouse();

      // Process events
      while (SDL_PollEvent(&m_Event))
      {
         switch (m_Event.type)
         {
         case SDL_QUIT:
            m_bIsRunning = false;
            break;
         case SDL_KEYDOWN:
            if (m_Event.key.keysym.sym == SDLK_ESCAPE)
               m_bIsRunning = false;
            keyboard.OnKeyPressed(m_Event.key.keysym.sym);
            break;
         case SDL_KEYUP:
            keyboard.OnKeyReleased(m_Event.key.keysym.sym);
            break;
         case SDL_MOUSEBUTTONDOWN:
            mouse.OnBtnPressed(m_Event.button.button);
            break;
         case SDL_MOUSEBUTTONUP:
            mouse.OnBtnReleased(m_Event.button.button);
            break;
         case SDL_MOUSEWHEEL:
            mouse.SetMouseWheelX(m_Event.wheel.x);
            mouse.SetMouseWheelY(m_Event.wheel.y);
            break;
         case SDL_MOUSEMOTION:
            mouse.SetMouseMoving(true);
            break;
         case SDL_CONTROLLERBUTTONDOWN:
            inputManager.GamepadBtnPressed(m_Event);
            break;
         case SDL_CONTROLLERBUTTONUP:
            inputManager.GamepadBtnReleased(m_Event);
            break;
         case SDL_CONTROLLERDEVICEADDED:
            inputManager.AddGamepad(m_Event.jdevice.which);
            break;
         case SDL_CONTROLLERDEVICEREMOVED:
            inputManager.RemoveGamepad(m_Event.jdevice.which);
            break;
         case SDL_JOYAXISMOTION:
            inputManager.GamepadAxisValues(m_Event);
            break;
         case SDL_JOYHATMOTION:
            inputManager.GamepadHatValues(m_Event);
            break;
         default:
            break;
         }
      }
   }

   void Application::Update()
   {
      auto& camera = m_pRegistry->GetContext<std::shared_ptr<SCALD_RENDERING::Camera2D>>();
      if (!camera)
      {
         SCALD_ERROR("Failed to get the camera from the registry context!");
         return;
      }

      camera->Update();

      auto& scriptingSystem = m_pRegistry->GetContext<std::shared_ptr<SCALD_CORE::Systems::ScriptingSystem>>();
      if (!scriptingSystem)
      {
         SCALD_ERROR("Failed to get the scripting system from the registry context!");
         return;
      }

      scriptingSystem->Update();

      auto& animationSystem = m_pRegistry->GetContext<std::shared_ptr<SCALD_CORE::Systems::AnimationSystem>>();
      if (!animationSystem)
      {
         SCALD_ERROR("Failed to get the animation system from the registry context!");
         return;
      }

      animationSystem->Update();

      // Update inputs
      auto& inputManager = SCALD_CORE::InputManager::GetInstance();
      auto& keyboard = inputManager.GetKeyboard();
      keyboard.Update();

      auto& mouse = inputManager.GetMouse();
      mouse.Update();

      inputManager.UpdateGamepads();
   }

   void Application::Render()
   {
      auto& renderSystem = m_pRegistry->GetContext<std::shared_ptr<SCALD_CORE::Systems::RenderSystem>>();

      glViewport(
         0,
         0,
         m_pWindow->GetWidth(),
         m_pWindow->GetHeight()
      );

      glClearColor(255.f, 255.f, 255.f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT);

      auto& scriptingSystem = m_pRegistry->GetContext <std::shared_ptr<SCALD_CORE::Systems::ScriptingSystem>>();
      if (!scriptingSystem)
      {
         SCALD_ERROR("Failed to get the scripting system from the registry context!");
         return;
      }

      scriptingSystem->Render();
      renderSystem->Update();

      SDL_GL_SwapWindow(m_pWindow->GetWindow().get());
   }

   void Application::CleanUp()
   {
      SDL_Quit();
   }

   Application::Application()
      : m_pWindow{ nullptr }, m_pRegistry{ nullptr }, m_Event{}, m_bIsRunning{ true }
   {
   }

   Application& Application::GetInstance()
   {
      static Application app{};
      return app;
   }

   Application::~Application()
   {
   }

   void Application::Run()
   {
      if (!Initialize())
      {
         SCALD_ERROR("Initialization Failed!");
         return;
      }

      unsigned int a = SDL_GetTicks();
      unsigned int b = SDL_GetTicks();
      double delta = 0;

      while (m_bIsRunning)
      {
         a = SDL_GetTicks();
         delta = a - b;

         //if (delta > 1000 / 60.0)
         {
            //std::cout << "fps: " << 1000 / delta << std::endl;

            b = a;

            ProcessEvents();
            Update();
            Render();
         }
      }

      CleanUp();
   }

}
