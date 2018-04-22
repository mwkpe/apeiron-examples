#include "deviation_meter.h"


#include <cmath>


hmi::Deviation_meter::Deviation_meter()
{
  auto plane_rotation = glm::vec3{glm::radians(-90.0f), 0.0f, 0.0f};
  longitudinal_meter_.set_position(0.0f, 0.025f, 0.0f);
  longitudinal_meter_.set_rotation(plane_rotation);
  longitudinal_animation_.set_scale(1.4f, 1.0f, 1.4f);
  longitudinal_animation_.set_velocity(5.0f);
  longitudinal_animation_.set_gap_size(5.0f);
  lateral_meter_.set_position(0.0f, 0.025f, 0.0f);
  lateral_meter_.set_rotation(plane_rotation);
  lateral_animation_.set_scale(1.8f, 1.0f, 1.8f);
  lateral_animation_.set_velocity(2.5f);
  lateral_animation_.set_gap_size(2.5f);

  lateral_meter_.set_color(glm::vec4{0.956f, 0.317f, 0.117f, 0.43f});
  set_lateral_deviation(3.6f);
}


void hmi::Deviation_meter::set_longitudinal_deviation(float deviation)
{
  longitudinal_meter_.set_scale(1.0f, 1.0f, deviation);
  longitudinal_meter_.set_position(0.0f, 0.025f, deviation/2.0f);
  longitudinal_animation_.set_distance(deviation, 0.0f);
  target_position_.set_position(0.0f, deviation);

  if (std::abs(deviation) < 5.0f)
    longitudinal_meter_.set_color(glm::vec4{0.0f, 0.717f, 0.215f, 0.43f});
  else if (std::abs(deviation) < 15.0f)
    longitudinal_meter_.set_color(glm::vec4{1.0f, 0.839f, 0.0f, 0.43f});
  else
    longitudinal_meter_.set_color(glm::vec4{0.956f, 0.317f, 0.117f, 0.43f});
}


void hmi::Deviation_meter::set_lateral_deviation(float deviation)
{
  lateral_meter_.set_scale(deviation, 1.0f, 2.5f);
  lateral_meter_.set_position(deviation/2.0f, 0.025f, 0.0f);
  lateral_animation_.set_distance(deviation, 90.0f);
}


void hmi::Deviation_meter::update(float delta_time)
{
  longitudinal_animation_.update(delta_time);
  lateral_animation_.update(delta_time);
}


void hmi::Deviation_meter::render(apeiron::opengl::Renderer& renderer, bool animated)
{
  renderer.use_color_shading();
  renderer.set_lighting(false);
  renderer.render(longitudinal_meter_, longitudinal_meter_.color());
  renderer.render(lateral_meter_, lateral_meter_.color());

  auto color = longitudinal_meter_.color();
  auto triangle_gap = longitudinal_animation_.gap_size();
  auto triangle_start = animated ? longitudinal_animation_.start() : 1.2f;
  auto distance = longitudinal_animation_.distance();
  for (auto i=triangle_start; i<std::abs(distance); i+=triangle_gap) {
    if (distance < 0.0f)
      longitudinal_animation_.set_position(0.0f, 0.05f, -i);
    else
      longitudinal_animation_.set_position(0.0f, 0.05f, i);
    if (float rem = std::abs(distance) - i - 4.0f; rem < 4.0f)
      color.a = rem / 4.0f;
    else
      color.a = 1.0f;
    renderer.render(longitudinal_animation_, color);
  }

  color.a = 1.0f;
  renderer.render(target_position_, color);

  color = lateral_meter_.color();
  triangle_start = 2.0f;
  distance = lateral_animation_.distance();
  if (std::abs(distance) > triangle_start) {
    if (distance < 0.0f)
      lateral_animation_.set_position(-triangle_start, 0.2f, 0.0f);
    else
      lateral_animation_.set_position(triangle_start, 0.2f, 0.0f);
    if (float rem = std::abs(distance) - triangle_start; rem < 1.0f)
      color.a = rem;
    else
      color.a = 1.0f;
    renderer.render(lateral_animation_, color);
  }
}
