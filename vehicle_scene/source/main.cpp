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
#include "options.h"
#include "menu.h"
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

  example::Options options;
  try {
    options = example::load_configuration("config.json");
  }
  catch (const apeiron::engine::Error& e) {
    std::cout << e.what() << std::endl;
  }

  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, options.msaa_samples);

  auto* window = SDL_CreateWindow("Vehicle scene", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, options.window_width, options.window_height, SDL_WINDOW_OPENGL);
  auto context = SDL_GL_CreateContext(window);

  glewExperimental = GL_TRUE;
  if (GLenum status = glewInit(); status != GLEW_OK) {
    std::cerr << reinterpret_cast<const char*>(glewGetErrorString(status));
    std::cin.ignore();  // Keep console open
    return 1;
  }

  SDL_GL_SetSwapInterval(0);

  example::World world(&options);
  example::Menu menu(window, context);
  try {
    world.init();
    menu.init();
    menu.setup(&options);
  }
  catch (const apeiron::engine::Error& e) {
    std::cerr << e.what() << std::endl;
    std::cin.ignore();  // Keep console open
    return 1;
  }

  auto frame_timer = [&options, last_ticks = SDL_GetTicks()](bool benchmarking) mutable {
    auto current_ticks = SDL_GetTicks();
    auto elapsed = current_ticks - last_ticks;
    if (auto target = 1000u / options.max_fps; !benchmarking && options.limit_fps && elapsed < target) {
      SDL_Delay(target - elapsed);
      current_ticks = SDL_GetTicks();
      elapsed = current_ticks - last_ticks;
    }
    last_ticks = current_ticks;
    return elapsed;
  };

  int camera_position = 1;
  bool benchmarking = false;
  float benchmark_start_time = 0;
  int benchmark_total_frames = 0;

  while (!options.quit) {
    auto elapsed = frame_timer(benchmarking);  // May also delay and hence limits fps
    float delta_time = elapsed / 1000.0f;
    auto time = SDL_GetTicks() / 1000.0f;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (options.show_menu) {
        menu.process(&event);
      }
      options.quit = event.type == SDL_QUIT;
      switch (event.type) {
        case SDL_KEYDOWN: {
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
              options.quit = true;
              break;
            case SDLK_F1:
              options.show_menu = !options.show_menu;
              if (options.show_menu) {
                SDL_CaptureMouse(SDL_FALSE);
                SDL_SetRelativeMouseMode(SDL_FALSE);
              }
              else {
                SDL_GetRelativeMouseState(nullptr, nullptr);  // Prevent erroneous movement
                SDL_CaptureMouse(SDL_TRUE);
                SDL_SetRelativeMouseMode(SDL_TRUE);
              }
              break;
            case SDLK_F2:
              options.wireframe = !options.wireframe;
              break;
            case SDLK_F4:
              world.set_camera(camera_position++);
              if (camera_position > 1)
                camera_position = 0;
              break;
            case SDLK_F6:
              if (!benchmarking) {
                benchmarking = true;
                benchmark_start_time = time;
                benchmark_total_frames = 0;
                std::cout << "Benchmark started... (takes 10s)" << std::endl;
              }
              break;
          }
        } break;
      }
    }

    if (!options.show_menu) {
      auto input = get_input_state();
      world.update(time, delta_time, &input);
    }
    else {  // imgui handles input
      world.update(time, delta_time);
    }

    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    world.render();
    if (options.show_menu) {
      menu.build(&options, time);
      menu.render();
    }

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

  example::save_configuration(options, "config.json");

  return 0;
}
