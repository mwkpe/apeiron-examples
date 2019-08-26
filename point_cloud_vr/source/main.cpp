#include <iostream>
#include <memory>
#include <stdexcept>
#ifdef _WIN32
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#endif
#include "SDL2/SDL.h"
#include "GL/glew.h"
#include <openvr_mingw.h>
#include "engine/input.h"
#include "hmd.h"
#include "world.h"


namespace {


void disable_dpi_scaling()
{
  #ifdef _WIN32
    // Silence gcc >= 8 warning about the winapi function cast
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wcast-function-type"
    enum { PROCESS_DPI_UNAWARE, PROCESS_SYSTEM_DPI_AWARE, PROCESS_PER_MONITOR_DPI_AWARE };
    auto free_module = [](HMODULE module){ FreeLibrary(module); };
    using mp = std::unique_ptr<std::remove_pointer<HMODULE>::type, decltype(free_module)>;
    if (auto shcore = mp{LoadLibrary("Shcore.dll"), free_module}) {
      using fp = HRESULT(WINAPI*)(int);
      if (auto f = reinterpret_cast<fp>(GetProcAddress(shcore.get(), "SetProcessDpiAwareness"))) {
        if (f(PROCESS_SYSTEM_DPI_AWARE) != S_OK) {
          std::cerr << "Could not disable DPI scaling" << std::endl;
        }
      }
    }
    #pragma GCC diagnostic pop
  #endif
}


apeiron::engine::Input get_input_state()
{
  apeiron::engine::Input input;
  const std::uint8_t* kb_state = SDL_GetKeyboardState(nullptr);

  input.forward = kb_state[SDL_SCANCODE_UP] || kb_state[SDL_SCANCODE_W];
  input.backward = kb_state[SDL_SCANCODE_DOWN] || kb_state[SDL_SCANCODE_S];
  input.left = kb_state[SDL_SCANCODE_LEFT] || kb_state[SDL_SCANCODE_A];
  input.right = kb_state[SDL_SCANCODE_RIGHT] || kb_state[SDL_SCANCODE_D];

  return input;
}


}  // namespace


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
  disable_dpi_scaling();

  int window_width = 1280;
  int window_height = 720;
  int msaa_samples = 4;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, msaa_samples);

  auto* companion_window = SDL_CreateWindow("Point cloud VR", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_OPENGL);
  auto context = SDL_GL_CreateContext(companion_window);

  glewExperimental = GL_TRUE;
  if (GLenum status = glewInit(); status != GLEW_OK) {
    std::cerr << reinterpret_cast<const char*>(glewGetErrorString(status));
    std::cin.ignore();  // Keep console open
    return 1;
  }

  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  SDL_GL_SetSwapInterval(1);

  // Init VR system and world
  example::Hmd_settings hmd_settings{2016, 2240, msaa_samples};
  example::Hmd hmd{hmd_settings};
  example::World world;
  try {
    hmd.init();
    world.init(window_width, window_height, &hmd);
  }
  catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    std::cin.ignore();
    return 1;
  }

  auto frame_timer = [last_ticks = SDL_GetTicks()]() mutable {
    auto current_ticks = SDL_GetTicks();
    auto elapsed = current_ticks - last_ticks;
    last_ticks = current_ticks;
    return elapsed;
  };

  bool quit = false;

  while (!quit) {
    auto elapsed = frame_timer();
    float delta_time = elapsed / 1000.0f;
    auto time = SDL_GetTicks() / 1000.0f;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      quit = event.type == SDL_QUIT;
      switch (event.type) {
        case SDL_KEYDOWN: {
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
              quit = true;
              break;
          }
        } break;
      }
    }

    auto input = get_input_state();
    world.update(time, delta_time, &input);
    world.render();

    SDL_GL_SwapWindow(companion_window);
  }

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(companion_window);
  SDL_Quit();

  vr::VR_Shutdown();

  return 0;
}
