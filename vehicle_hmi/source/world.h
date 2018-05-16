#ifndef HMI_WORLD_H
#define HMI_WORLD_H


#include <cstdint>
#include <vector>
#include "engine/input.h"
#include "engine/camera.h"
#include "engine/text.h"
#include "opengl/model.h"
#include "opengl/renderer.h"
#include "options.h"
#include "ground.h"
#include "road.h"
#include "line_markings.h"
#include "deviation_meter.h"
#include "deviation_animation.h"
#include "gauge.h"
#include "light.h"
#include "vehicle.h"
#include "deviation_gauge.h"
#include "velocity_gauge.h"


namespace hmi {


class World final
{
public:
  World(const Options* options) : options_{options},
      roboto_mono_{16, 8, 32},
      ground_{{40.0f, 0.0f, 400.0f}, {2.5f, 0.0f, 5.0f}, 0.01f, {0.3f, 0.3f, 0.3f}},
      deviation_gauge_{&roboto_mono_},
      velocity_gauge_{&roboto_mono_},
      light_{&bulb_},
      ego_vehicle_{{1.847f, 1.271f, 4.131f}},
      target_vehicle_{{1.916f, 1.266f, 4.396f}}
      {}
  void init();
  void set_camera(int i);
  void update(float time, float delta_time, const apeiron::engine::Input* input = nullptr);
  void render();

private:
  const Options* options_;
  apeiron::opengl::Renderer renderer_;
  apeiron::opengl::Charset roboto_mono_;
  apeiron::opengl::Model bulb_;
  apeiron::engine::Camera camera_;
  Ground ground_;
  Road road_;
  Line_markings line_markings_;
  Deviation_meter deviation_meter_;
  Deviation_gauge deviation_gauge_;
  Velocity_gauge velocity_gauge_;
  Light light_;
  Vehicle ego_vehicle_;
  Vehicle target_vehicle_;
  int frame_ = 0;
};


}  // namespace hmi


#endif  // HMI_WORLD_H
