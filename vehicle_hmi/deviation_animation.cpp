#include "deviation_animation.h"


#include <cmath>


namespace {


constexpr float pi = 3.14159f;
constexpr float tau = 2.0f * pi;


std::vector<float> build_triangle_vertices(float base_length, float height)
{
  float l = base_length / 2.0f;
  float h = height / 2.0f;

  return {
    -l,    -h, 0.0f,
     l,    -h, 0.0f,
     0.0f,  h, 0.0f
  };
}


}  // namespace


hmi::Deviation_animation::Deviation_animation() : triangle_height_{0.5f * std::sqrt(3.0f)},
    triangle_{build_triangle_vertices(1.0f, triangle_height_)}
{
  set_rotation(glm::radians(-90.0f), 0.0f, 0.0f);
  set_position(0.0f, 0.05f, 0.0f);
}


void hmi::Deviation_animation::set_distance(float distance, float angle)
{
  if (distance > 0.0f)
    set_rotation(glm::radians(-90.0f), 0.0f, glm::radians(angle + 180.0f));
  else
    set_rotation(glm::radians(-90.0f), 0.0f, glm::radians(angle));

  distance_ = distance;

  // Reset animation phase
  if (std::abs(distance) < 1.0f)
    start_ = 0.0f;
}


void hmi::Deviation_animation::update(float delta_time)
{
  const float animation_velocity = velocity_;  // m/s
  start_ += animation_velocity * delta_time;
  if (start_ > gap_size_)
    start_ -= gap_size_;
}


void hmi::Deviation_animation::render() const
{
  triangle_.render();
}
