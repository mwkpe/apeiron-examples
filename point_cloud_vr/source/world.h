#ifndef EXAMPLE_WORLD_H
#define EXAMPLE_WORLD_H


#include <glm/glm.hpp>
#include "engine/input.h"
#include "opengl/renderer.h"
#include "opengl/frame_buffer.h"
#include "prefab/ground.h"
#include "hmd.h"
#include "point_cloud.h"


namespace example {


class World final
{
public:
  World();
  void init(int window_width, int window_height, Hmd* hmd);
  void update(float time, float delta_time, const apeiron::engine::Input* input = nullptr);
  void render();

private:
  void render_scene();
  apeiron::opengl::Renderer renderer_;
  apeiron::opengl::Frame_buffer left_eye_;
  apeiron::opengl::Frame_buffer right_eye_;
  apeiron::prefab::Ground ground_;
  int window_width_ = 1280;
  int window_height_ = 720;
  glm::mat4 window_projection_;
  Hmd* hmd_ = nullptr;
  Point_cloud point_cloud_;
  int frame_ = 0;
};


}  // namespace example


#endif  // EXAMPLE_WORLD_H
