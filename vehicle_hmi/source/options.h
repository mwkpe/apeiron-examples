#ifndef HMI_OPTIONS_H
#define HMI_OPTIONS_H


#include <cstdint>
#include <string>
#include <string_view>
#include <glm/glm.hpp>


namespace hmi {


struct Options
{
  bool quit = false;
  bool show_gui = true;
  bool wireframe = false;
  bool lighting = true;
  bool bounding_boxes = false;
  bool ground = true;
  bool ground_overlay = true;
  bool animate_overlay = true;
  bool road = true;
  bool road_markings = true;
  bool limit_fps = true;
  int window_width = 1280;
  int window_height = 720;
  glm::vec4 main_color = {1.0f, 1.0f, 1.0f, 1.0f};
  int msaa_samples = 4;
  int max_fps = 90;
  float camera_velocity = 10.0f;
  float camera_sensitivity = 0.02f;
  float vehicle_velocity = 0.0f;
  float position_deviation = 0.0f;
};


Options load_configuration(std::string_view filename);
void save_configuration(const Options& options, std::string_view filename);


}  // namespace hmi


#endif  // HMI_OPTIONS_H
