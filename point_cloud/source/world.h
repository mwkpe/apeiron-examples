#ifndef EXAMPLE_WORLD_H
#define EXAMPLE_WORLD_H


#include "engine/input.h"
#include "engine/camera.h"
#include "opengl/renderer.h"
#include "prefab/ground.h"
#include "point_cloud.h"


namespace example {


class World final
{
public:
  World();
  void init(int window_width, int window_height);
  void update(float time, float delta_time, const apeiron::engine::Input* input = nullptr);
  void render();

private:
  apeiron::opengl::Renderer renderer_;
  apeiron::engine::Camera camera_;
  apeiron::prefab::Ground ground_;
  Point_cloud point_cloud_;
  int frame_ = 0;
};


}  // namespace example


#endif  // EXAMPLE_WORLD_H
