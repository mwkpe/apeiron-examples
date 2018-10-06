#ifndef EXAMPLE_CHESS_OPTIONS_H
#define EXAMPLE_CHESS_OPTIONS_H


#include <cstdint>
#include <string>
#include <string_view>
#include <glm/glm.hpp>


namespace example::chess {


struct Options
{
  bool quit = false;
  bool limit_fps = true;
  bool show_menu = true;
  bool wireframe = false;
  bool lighting = true;
  bool show_light = false;
  bool show_axes = false;
  bool show_ground = false;
  int window_width = 1280;
  int window_height = 720;
  int msaa_samples = 4;
  int max_fps = 90;
  float camera_velocity = 10.0f;
  float camera_sensitivity = 0.02f;
  glm::vec4 main_color = {1.0f, 1.0f, 1.0f, 1.0f};
  glm::vec4 white_color = {0.775f, 0.775f, 0.775f, 1.0f};//{0.882f, 0.156f, 0.521f, 1.0f};
  glm::vec4 black_color = {0.325f, 0.325f, 0.325f, 1.0f};//{0.0f, 0.576f, 0.768f, 1.0f};
};


Options load_configuration(std::string_view filename);
void save_configuration(const Options& options, std::string_view filename);


}  // namespace example::chess


#endif  // EXAMPLE_CHESS_OPTIONS_H
