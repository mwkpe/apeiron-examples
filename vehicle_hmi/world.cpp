#include "world.h"


#include <glm/gtc/matrix_transform.hpp>
#include "engine/model_flags.h"


void hmi::World::init()
{
  namespace mf = apeiron::engine::model_flags;

  renderer_.init();

  bulb_.load("assets/bulb.obj", mf::vertices);

  ego_vehicle_.load_model("assets/bmw.obj", mf::vertices | mf::normals | mf::tex_coords);
  ego_vehicle_.load_texture("assets/bmw.png");
  ego_vehicle_.set_position(0.0f, 0.0f, 4.13102f / 2.0f);

  light_.set_position(0.0f, 7.5f, 5.5f);
  light_.set_color(1.0f, 1.0f, 1.0f);

  renderer_.set_light_position(light_.position());
  renderer_.set_light_color(light_.color());
}


void hmi::World::reset()
{
  camera_.reset();
}


void hmi::World::update([[maybe_unused]] float time, float delta_time, const apeiron::engine::Input* input)
{
  if (input) {
    using Direction = apeiron::engine::Camera::Direction;
    auto distance = options_->camera_velocity * delta_time;
    if (input->forward)
      camera_.move(Direction::Forward, distance);
    if (input->backward)
      camera_.move(Direction::Backward, distance);
    if (input->left)
      camera_.move(Direction::Left, distance);
    if (input->right)
      camera_.move(Direction::Right, distance);

    camera_.orient(input->mouse_x_rel, input->mouse_y_rel, options_->camera_sensitivity);
  }

  float ground_z = ground_.position().z;
  ground_z += delta_time * ego_vehicle_.velocity();
  if (ground_z > ground_.spacing().z)
    ground_z -= ground_.spacing().z;
  ground_.set_position(0.0f, 0.0f, ground_z);
}


void hmi::World::render()
{
  frame_++;
  auto aspect_ratio = static_cast<float>(options_->window_width) / options_->window_height;

  renderer_.set_projection(glm::perspective(glm::radians(45.0f), aspect_ratio, 1.5f, 500.0f));
  renderer_.set_view(camera_.view());
  renderer_.set_wireframe(options_->wireframe);

  renderer_.use_vertex_color_shading();
  renderer_.set_lighting(false);
  renderer_.render(ground_);

  renderer_.use_texture_shading();
  renderer_.set_lighting(true);
  renderer_.render(ego_vehicle_);
}
