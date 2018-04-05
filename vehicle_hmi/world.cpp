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
  ego_vehicle_.set_center(0.0f, ego_vehicle_.size().y / 2.0f, 0.0f);
  ego_vehicle_.set_color({0.129f, 0.588f, 0.952f, 1.0f});

  target_vehicle_.load_model("assets/audi.obj", mf::vertices | mf::normals | mf::tex_coords);
  target_vehicle_.load_texture("assets/audi.png");
  target_vehicle_.set_position(5.0f, 0.0f, -15.0f);
  target_vehicle_.set_center(0.0f, target_vehicle_.size().y / 2.0f, 0.0f);
  target_vehicle_.set_color({0.956f, 0.262f, 0.211f, 1.0f});

  light_.set_position(0.0f, 5.0f, 1.0f);
  light_.set_color(1.0f, 1.0f, 1.0f);

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

  if (options_->vehicle_velocity != ego_vehicle_.velocity())
    ego_vehicle_.set_velocity(options_->vehicle_velocity);

  float ground_z = ground_.position().z;
  ground_z += delta_time * (ego_vehicle_.velocity());
  if (ground_z > ground_.spacing().z)
    ground_z -= ground_.spacing().z;
  if (ground_z < -ground_.spacing().z)
    ground_z += ground_.spacing().z;
  ground_.set_position(0.0f, 0.0f, ground_z);

  deviation_meter_.set_deviation(options_->distance_deviation);
  ground_overlay_.set_position(0.0f, ground_overlay_.position().y, options_->distance_deviation);
}


void hmi::World::render()
{
  frame_++;
  auto aspect_ratio = static_cast<float>(options_->window_width) / options_->window_height;

  renderer_.set_projection(glm::perspective(glm::radians(45.0f), aspect_ratio, 2.5f, 500.0f));
  renderer_.set_view(camera_.view());
  renderer_.set_wireframe(options_->wireframe);
  renderer_.set_light_color({1.0f, 1.0f, 1.0f});

  renderer_.use_vertex_color_shading();
  renderer_.set_lighting(false);
  renderer_.render(ground_);
  if (options_->ground_overlay) {
    renderer_.use_color_shading();
    renderer_.render(deviation_meter_, deviation_meter_.color());
    auto c = deviation_meter_.color();
    c.a = 1.0f;
    renderer_.render(ground_overlay_, c);
  }

  renderer_.use_texture_shading();
  renderer_.set_light_position(ego_vehicle_.position() + light_.position());
  renderer_.set_lighting(options_->lighting);
  renderer_.render(ego_vehicle_);
  renderer_.set_light_position(target_vehicle_.position() + light_.position());
  renderer_.render(target_vehicle_);

  if (options_->bounding_boxes) {
    renderer_.set_lighting(false);
    renderer_.use_color_shading();
    renderer_.render_bounds(ego_vehicle_, ego_vehicle_.color());
    renderer_.render_bounds(target_vehicle_, target_vehicle_.color());
  }
}
