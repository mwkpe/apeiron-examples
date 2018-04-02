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
#include "light.h"
#include "vehicle.h"


namespace hmi {


class World final
{
public:
  World(const Options* options) : options_{options},
      ground_{{30.0f, 0.0f, 200.0f}, {2.5f, 0.0f, 2.5f}, 0.01f}, light_{&bulb_} {}
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
  Light light_;
  Vehicle ego_vehicle_;
  int frame_ = 0;
};


}  // namespace hmi


#endif  // HMI_WORLD_H
