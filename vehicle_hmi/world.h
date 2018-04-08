#ifndef HMI_WORLD_H
#define HMI_WORLD_H


#include <cstdint>
#include <vector>
#include "engine/input.h"
#include "engine/camera.h"
#include "opengl/model.h"
#include "opengl/renderer.h"
#include "options.h"
#include "ground.h"
#include "road.h"
#include "line_markings.h"
#include "position_marker.h"
#include "deviation_meter.h"
#include "light.h"
#include "vehicle.h"


namespace hmi {


class World final
{
public:
  World(const Options* options) : options_{options},
      ground_{{30.0f, 0.0f, 400.0f}, {2.5f, 0.0f, 2.5f}, 0.01f, {0.05f, 0.05f, 0.05f}},
      light_{&bulb_},
      ego_vehicle_{{1.847f, 1.271f, 4.131f}},
      target_vehicle_{{1.916f, 1.266f, 4.396f}} {}
  void init();
  void reset();
  void update(float time, float delta_time, const apeiron::engine::Input* input = nullptr);
  void render();

private:
  const Options* options_;
  apeiron::opengl::Renderer renderer_;
  apeiron::opengl::Model bulb_;
  apeiron::engine::Camera camera_;
  Ground ground_;
  Road road_;
  Line_markings line_markings_;
  Position_marker target_position_;
  Deviation_meter deviation_meter_;
  Light light_;
  Vehicle ego_vehicle_;
  Vehicle target_vehicle_;
  int frame_ = 0;
};


}  // namespace hmi


#endif  // HMI_WORLD_H
