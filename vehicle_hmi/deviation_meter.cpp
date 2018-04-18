#include "deviation_meter.h"


#include <cmath>


hmi::Deviation_meter::Deviation_meter()
{
  longitudinal_meter_.set_position(0.0f, 0.05f, 0.0f);
  longitudinal_meter_.set_rotation(glm::radians(-90.0f), 0.0f, 0.0f);  // Parallel to ground (x, z)
}


void hmi::Deviation_meter::set_longitudinal_deviation(float deviation)
{
  longitudinal_meter_.set_scale(1.0f, 1.0f, deviation);
  longitudinal_meter_.set_position(0.0f, 0.05f, deviation/2.0f);

  if (std::abs(deviation) < 5.0f)
    longitudinal_meter_.set_color(glm::vec4{0.0f, 0.717f, 0.215f, 0.33f});
  else if (std::abs(deviation) < 15.0f)
    longitudinal_meter_.set_color(glm::vec4{1.0f, 0.839f, 0.0f, 0.33f});
  else
    longitudinal_meter_.set_color(glm::vec4{0.956f, 0.317f, 0.117f, 0.33f});

  longitudinal_animation_.set_deviation(deviation);
}


glm::vec4 hmi::Deviation_meter::longitudinal_color() const
{
  auto color = longitudinal_meter_.color();
  color.a = 1.0f;
  return color;
}


void hmi::Deviation_meter::update(float delta_time)
{
  longitudinal_animation_.update(delta_time);
}


void hmi::Deviation_meter::render(apeiron::opengl::Renderer& renderer, bool animated)
{
  renderer.use_color_shading();
  renderer.set_lighting(false);
  renderer.render(longitudinal_meter_, longitudinal_meter_.color());

  auto color = longitudinal_meter_.color();
  auto triangle_gap = longitudinal_animation_.triangle_gap();
  auto triangle_start = animated ? longitudinal_animation_.triangle_start() : 1.2f;
  auto distance = longitudinal_animation_.distance();
  for (auto i = triangle_start; i < std::abs(distance); i += triangle_gap) {
    if (distance < 0.0f)
      longitudinal_animation_.set_position(0.0f, 0.1f, -i);
    else
      longitudinal_animation_.set_position(0.0f, 0.1f, i);
    if (float rem = std::abs(distance) - i - 4.0f; rem < 4.0f)
      color.a = rem / 4.0f;
    else
      color.a = 1.0f;
    renderer.render(longitudinal_animation_, color);
  }
}
