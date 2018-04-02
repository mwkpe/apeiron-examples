#ifndef HMI_OPTIONS_H
#define HMI_OPTIONS_H


#include <string_view>
#include <glm/glm.hpp>


namespace hmi {


struct Options
{
  bool quit = false;
  bool show_gui = true;
  bool wireframe = false;
  bool limit_fps = true;
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


}  // namespace hmi


#endif  // HMI_OPTIONS_H
