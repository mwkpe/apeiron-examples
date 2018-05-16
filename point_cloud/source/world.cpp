#include "world.h"


#include <glm/gtc/matrix_transform.hpp>


void example::World::init()
{
  renderer_.init();
  renderer_.use_vertex_color_shading();
  renderer_.set_lighting(false);
  auto aspect_ratio = static_cast<float>(1280) / 720;
  renderer_.set_projection(glm::perspective(glm::radians(45.0f), aspect_ratio, 1.0f, 1000.0f));

  camera_.set({0.0f, -200.0f, 00.0f}, -50.0f, -45.0f);

  point_cloud_.load_data("MOUT_script3.xyzrgba");
  point_cloud_.set_point_size(2.0f);
  auto plane_rotation = glm::vec3{glm::radians(-90.0f), 0.0f, 0.0f};
  point_cloud_.set_rotation(plane_rotation);
}


void example::World::update([[maybe_unused]] float time, float delta_time, const apeiron::engine::Input* input)
{
  if (input) {
    using Direction = apeiron::engine::Camera::Direction;
    auto distance = 25.0f * delta_time;
    if (input->forward)
      camera_.move(Direction::Forward, distance);
    if (input->backward)
      camera_.move(Direction::Backward, distance);
    if (input->left)
      camera_.move(Direction::Left, distance);
    if (input->right)
      camera_.move(Direction::Right, distance);

    camera_.orient(input->mouse_x_rel, input->mouse_y_rel, 0.02f);
  }
}


void example::World::render()
{
  frame_++;
  renderer_.set_view(camera_.view());
  renderer_.render(point_cloud_);
}
