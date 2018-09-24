#include "world.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


example::World::World() : ground_{{200.0f, 200.0f}, 25, 25, {0.25f, 0.25f, 0.25f, 1.0f}}
{
}


void example::World::init(int screen_width, int screen_height)
{
  renderer_.init();
  renderer_.use_vertex_color_shading();
  renderer_.set_lighting(false);
  auto aspect_ratio = static_cast<float>(screen_width) / screen_height;
  renderer_.set_projection(glm::perspective(glm::radians(45.0f), aspect_ratio, 1.0f, 1000.0f));
  camera_.setup(-30.0f, -190.0f, {55.0f, 25.0f, -15.0f});
  
  point_cloud_.load_data("MOUT_script3.xyzrgba");
  point_cloud_.set_point_size(2.0f);
  // Rotate point cloud z-up to opengl y-up
  point_cloud_.set_rotation(glm::vec3{glm::radians(-90.0f), 0.0f, 0.0f});
}


void example::World::update([[maybe_unused]] float time, float delta_time,
    const apeiron::engine::Input* input)
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
  renderer_.render(ground_);
  renderer_.render(point_cloud_);
}
