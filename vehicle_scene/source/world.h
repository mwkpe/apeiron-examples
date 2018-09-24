#ifndef EXAMPLE_WORLD_H
#define EXAMPLE_WORLD_H


#include <cstdint>
#include <vector>
#include "engine/input.h"
#include "engine/camera.h"
#include "engine/text.h"
#include "opengl/model.h"
#include "opengl/renderer.h"
#include "prefab/light.h"
#include "prefab/ground.h"
#include "options.h"
#include "road.h"
#include "lane_markings.h"
#include "vehicle.h"


namespace example {


class World final
{
public:
  World(const Options* options);
  void init();
  void set_camera(int i);
  void update(float time, float delta_time, const apeiron::engine::Input* input = nullptr);
  void render();

private:
  const Options* options_;
  apeiron::opengl::Renderer renderer_;
  apeiron::opengl::Tileset roboto_mono_;
  apeiron::opengl::Model bulb_;
  apeiron::engine::Camera camera_;
  apeiron::prefab::Light light_;
  apeiron::prefab::Ground ground_;
  Road road_;
  Lane_markings lane_markings_;
  Vehicle ego_vehicle_;
  Vehicle target_vehicle_;
  int frame_ = 0;
};


}  // namespace example


#endif  // EXAMPLE_WORLD_H
