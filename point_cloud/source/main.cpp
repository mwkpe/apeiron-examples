#include <iostream>
#include <memory>
#ifdef _WIN32
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#endif
#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "engine/error.h"
#include "engine/input.h"
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

  SDL_GetMouseState(&input.mouse_x_abs, &input.mouse_y_abs);
  SDL_GetRelativeMouseState(&input.mouse_x_rel, &input.mouse_y_rel);
  input.mouse_y_rel = -input.mouse_y_rel;  // Make mouse up correspond to camera pitch up

  return input;
}


}  // namespace


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
  disable_dpi_scaling();

  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

  int screen_width = 1280;
  int screen_height = 720;

  auto* window = SDL_CreateWindow("Point cloud", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      screen_width, screen_height, SDL_WINDOW_OPENGL);
  auto context = SDL_GL_CreateContext(window);

  glewExperimental = GL_TRUE;
  if (GLenum status = glewInit(); status != GLEW_OK) {
    std::cerr << reinterpret_cast<const char*>(glewGetErrorString(status));
    std::cin.ignore();  // Keep console open
    return 1;
  }

  SDL_GL_SetSwapInterval(0);
  SDL_CaptureMouse(SDL_TRUE);
  SDL_SetRelativeMouseMode(SDL_TRUE);

  example::World world;
  try {
    world.init(screen_width, screen_height);
  }
  catch (const apeiron::engine::Error& e) {
    std::cerr << e.what() << std::endl;
    std::cin.ignore();  // Keep console open
    return 1;
  }

  auto frame_timer = [last_ticks = SDL_GetTicks()](bool benchmarking) mutable {
    auto current_ticks = SDL_GetTicks();
    auto elapsed = current_ticks - last_ticks;
    if (auto target = 1000u / 144; !benchmarking && elapsed < target) {
      SDL_Delay(target - elapsed);
      current_ticks = SDL_GetTicks();
      elapsed = current_ticks - last_ticks;
    }
    last_ticks = current_ticks;
    return elapsed;
  };

  bool quit = false;
  bool benchmarking = false;
  float benchmark_start_time = 0;
  int benchmark_total_frames = 0;

  while (!quit) {
    auto elapsed = frame_timer(benchmarking);  // May also delay and hence limits fps
    float delta_time = elapsed / 1000.0f;
    auto time = SDL_GetTicks() / 1000.0f;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      quit = event.type == SDL_QUIT;
      switch (event.type) {
        case SDL_KEYDOWN: {
          switch (event.key.keysym.sym) {
            case SDLK_F6: {
              if (!benchmarking) {
                benchmarking = true;
                benchmark_start_time = time;
                benchmark_total_frames = 0;
                std::cout << "Benchmark started... (takes 10s)" << std::endl;
              }
              break;
            }
            case SDLK_ESCAPE:
              quit = true;
              break;
          }
        } break;
      }
    }

    auto input = get_input_state();
    world.update(time, delta_time, &input);

    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    world.render();
    SDL_GL_SwapWindow(window);

    if (benchmarking) {
      benchmark_total_frames++;
      if (time > benchmark_start_time + 10.0f) {
        benchmarking = false;
        std::cout << "Benchmark result: " << benchmark_total_frames / 10 << " fps" << std::endl;
      }
    }
  }

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
