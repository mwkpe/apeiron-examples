#ifndef EXAMPLE_WORLD_H
#define EXAMPLE_WORLD_H


#include "engine/input.h"
#include "engine/camera.h"
#include "opengl/renderer.h"
#include "point_cloud.h"


namespace example {


class World final
{
public:
  void init(int screen_width, int screen_height);
  void update(float time, float delta_time, const apeiron::engine::Input* input = nullptr);
  void render();

private:
  apeiron::opengl::Renderer renderer_;
  apeiron::engine::Camera camera_;
  Point_cloud point_cloud_;
  int frame_ = 0;
};


}  // namespace example


#endif  // EXAMPLE_WORLD_H
