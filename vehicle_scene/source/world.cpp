#include "world.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


example::World::World(const Options* options)
    : options_{options},
      roboto_mono_{16, 8, 32},
      light_{&bulb_},
      ground_{{40.0f, 200.0f}, 17, 41, {0.25f, 0.25f, 0.25f, 1.0f}, 1.0f},
      ego_vehicle_{{1.847f, 1.271f, 4.131f}},
      target_vehicle_{{1.916f, 1.266f, 4.396f}}
{
}


void example::World::init()
{
  renderer_.init();
  auto aspect_ratio = static_cast<float>(options_->window_width) / options_->window_height;
  renderer_.preset_projection(glm::perspective(glm::radians(45.0f), aspect_ratio, 2.5f, 500.0f));
  renderer_.set_light_color({1.0f, 1.0f, 1.0f, 1.0f});

  roboto_mono_.load_texture("assets/roboto_mono_modified.png");

  bulb_.load("assets/bulb.obj");
  light_.set_position(0.0f, 5.0f, 1.0f);
  light_.set_color(1.0f, 1.0f, 1.0f);
  renderer_.set_light_color(light_.color());

  ego_vehicle_.load_model("assets/bmw.obj");
  ego_vehicle_.load_texture("assets/bmw.png");
  ego_vehicle_.set_position(0.0f, 0.1f, 15.0f);
  ego_vehicle_.set_center(0.0f, ego_vehicle_.size().y / 2.0f, 0.0f);
  ego_vehicle_.set_color(0.129f, 0.588f, 0.952f);

  target_vehicle_.load_model("assets/audi.obj");
  target_vehicle_.load_texture("assets/audi.png");
  target_vehicle_.set_position(3.6f, 0.1f, 0.0f);
  target_vehicle_.set_center(0.0f, target_vehicle_.size().y / 2.0f, 0.0f);
  target_vehicle_.set_color(0.956f, 0.262f, 0.211f);

  lane_markings_.set_color(0.85f, 0.85f, 0.85f);

  set_camera(0);
}


void example::World::set_camera(int i)
{
  switch (i) {
    case 0:
      camera_.setup(-40.0f, 0.0f, {0.0f, 25.0f, 35.0f});
      break;
    case 1:
      camera_.setup(-45.0f, -45.0f, {25.0f, 40.0f, 40.0f});
      break;
    default:;
  }
}


void example::World::update([[maybe_unused]] float time, float delta_time,
    const apeiron::engine::Input* input)
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
}


void example::World::render()
{
  frame_++;

  renderer_.preset_view(camera_.view());
  renderer_.set_view_projection();
  renderer_.set_wireframe(options_->wireframe); 
  renderer_.set_lighting(false);

  renderer_.use_vertex_color_shading();
  if (options_->ground) {
    renderer_.render(ground_);
  }
  if (options_->road) {
    renderer_.render(road_);
  }

  renderer_.use_color_shading();
  if (options_->lane_markings) {
    renderer_.render(lane_markings_, lane_markings_.color());
  }
  if (options_->bounding_boxes) {
    renderer_.render_bounds(ego_vehicle_, ego_vehicle_.color());
    renderer_.render_bounds(target_vehicle_, target_vehicle_.color());
  }

  renderer_.use_texture_shading();
  renderer_.set_light_position(ego_vehicle_.position() + light_.position());
  renderer_.set_lighting(options_->lighting);
  renderer_.render(ego_vehicle_);
  renderer_.set_light_position(target_vehicle_.position() + light_.position());
  renderer_.render(target_vehicle_);
}
