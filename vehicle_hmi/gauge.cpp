#include "gauge.h"


#include <vector>
#include <cmath>


namespace {


constexpr float pi = 3.14159f;
constexpr float tau = 2.0f * pi;


std::vector<float> build_circle_vertices(int points, float radius, float thickness)
{
  std::vector<float> vertices(static_cast<std::size_t>(points + 1) * 6 * 3);
  std::size_t index = 0;
  float last_angle = 0.0f;
  for (int i=1; i<=points; ++i) {
    const float angle = static_cast<float>(i) / points * tau;
    vertices[index++] = (radius - thickness) * std::cos(-last_angle);
    vertices[index++] = (radius - thickness) * std::sin(-last_angle);
    vertices[index++] = 0.0f;
    vertices[index++] = radius * std::cos(-last_angle);
    vertices[index++] = radius * std::sin(-last_angle);
    vertices[index++] = 0.0f;
    vertices[index++] = radius * std::cos(-angle);
    vertices[index++] = radius * std::sin(-angle);
    vertices[index++] = 0.0f;
    vertices[index++] = radius * std::cos(-angle);
    vertices[index++] = radius * std::sin(-angle);
    vertices[index++] = 0.0f;
    vertices[index++] = (radius - thickness) * std::cos(-angle);
    vertices[index++] = (radius - thickness) * std::sin(-angle);
    vertices[index++] = 0.0f;
    vertices[index++] = (radius - thickness) * std::cos(-last_angle);
    vertices[index++] = (radius - thickness) * std::sin(-last_angle);
    vertices[index++] = 0.0f;
    last_angle = angle;
  }
  return vertices;
}


}  // namespace


hmi::Gauge::Gauge(int points, float radius, float thickness)
    : vertices_per_value_{6}, circle_{build_circle_vertices(points, radius, thickness)}
{
}


void hmi::Gauge::render() const
{
  circle_.render(start_ * vertices_per_value_, count_ * vertices_per_value_);
}
