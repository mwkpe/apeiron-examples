#include "deviation_meter.h"


#include <cmath>


hmi::Deviation_meter::Deviation_meter()
{
  auto plane_rotation = glm::vec3{glm::radians(-90.0f), 0.0f, 0.0f};
  meter_.set_position(0.0f, 0.025f, 0.0f);
  meter_.set_rotation(plane_rotation);
  animation_.set_scale(1.4f, 1.0f, 1.4f);
  animation_.set_velocity(5.0f);
  animation_.set_gap_size(5.0f);
}


void hmi::Deviation_meter::set_deviation(float deviation)
{
  meter_.set_scale(1.0f, 1.0f, deviation);
  meter_.set_position(0.0f, 0.025f, deviation/2.0f);
  animation_.set_distance(deviation, 0.0f);
  target_position_.set_position(0.0f, deviation);

  if (std::abs(deviation) < 5.0f)
    meter_.set_color(glm::vec4{0.0f, 0.717f, 0.215f, 0.43f});
  else if (std::abs(deviation) < 15.0f)
    meter_.set_color(glm::vec4{1.0f, 0.839f, 0.0f, 0.43f});
  else
    meter_.set_color(glm::vec4{0.956f, 0.317f, 0.117f, 0.43f});
}


void hmi::Deviation_meter::update(float delta_time)
{
  animation_.update(delta_time);
}


void hmi::Deviation_meter::render(apeiron::opengl::Renderer& renderer, bool animated)
{
  renderer.use_color_shading();
  renderer.set_lighting(false);
  renderer.render(meter_, meter_.color());

  auto color = meter_.color();
  auto triangle_gap = animation_.gap_size();
  auto triangle_start = animated ? animation_.start() : 1.2f;
  auto distance = animation_.distance();
  for (auto i=triangle_start; i<std::abs(distance); i+=triangle_gap) {
    if (distance < 0.0f)
      animation_.set_position(0.0f, 0.05f, -i);
    else
      animation_.set_position(0.0f, 0.05f, i);
    if (float rem = std::abs(distance) - i - 4.0f; rem < 4.0f)
      color.a = rem / 4.0f;
    else
      color.a = 1.0f;
    renderer.render(animation_, color);
  }

  color.a = 1.0f;
  renderer.render(target_position_, color);
}
