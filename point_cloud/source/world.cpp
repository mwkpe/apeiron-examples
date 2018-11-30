#include "world.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


example::World::World() : ground_{{200.0f, 200.0f}, 25, 25, {0.25f, 0.25f, 0.25f, 1.0f}}
{
}


void example::World::init(int screen_width, int screen_height)
{
  renderer_.init();  // Load default shader
  auto aspect_ratio = static_cast<float>(screen_width) / screen_height;
  // Set projection matrix in renderer
  renderer_.preset_projection(glm::perspective(glm::radians(45.0f), aspect_ratio, 1.0f, 1000.0f));
  // Set fragment shader to use color provided by the point vertices
  renderer_.use_vertex_color_shading();
  renderer_.set_lighting(false);

  // Setup camera's pitch, yaw and position
  camera_.setup(-30.0f, -100.0f, {55.0f, 25.0f, -15.0f});
  
  point_cloud_.load_data("MOUT_script3.xyzrgba");
  point_cloud_.set_point_size(1.0f);
  // Rotate point cloud z-up to opengl y-up
  point_cloud_.set_rotation(glm::vec3{glm::radians(-90.0f), 0.0f, 0.0f});
}


void example::World::update([[maybe_unused]] float time, float delta_time,
    const apeiron::engine::Input* input)
{
  // Move and orient camera based on user input
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
  // Set view matrix in renderer
  renderer_.preset_view(camera_.view());
  // Multiply view matrix with stored projection matrix and update shader
  renderer_.set_view_projection();
  renderer_.render(ground_);
  renderer_.render(point_cloud_);
}
