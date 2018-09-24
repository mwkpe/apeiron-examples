#ifndef EXAMPLE_OPTIONS_H
#define EXAMPLE_OPTIONS_H


#include <cstdint>
#include <string>
#include <string_view>
#include <glm/glm.hpp>


namespace example {


struct Options
{
  bool quit = false;
  bool limit_fps = true;
  bool show_menu = true;
  bool wireframe = false;
  bool lighting = true;
  bool bounding_boxes = true;
  bool ground = true;
  bool road = true;
  bool lane_markings = true;
  int window_width = 1280;
  int window_height = 720;
  int msaa_samples = 4;
  int max_fps = 90;
  float camera_velocity = 10.0f;
  float camera_sensitivity = 0.02f;
  glm::vec4 main_color = {1.0f, 1.0f, 1.0f, 1.0f};
};


Options load_configuration(std::string_view filename);
void save_configuration(const Options& options, std::string_view filename);


}  // namespace example


#endif  // EXAMPLE_OPTIONS_H
