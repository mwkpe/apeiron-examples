#include "position_marker.h"


#include <tuple>
#include <vector>
#include <cmath>


namespace {


constexpr float pi = 3.14159f;
constexpr float tau = 2.0f * pi;


std::vector<float> build_cross_vertices(float width_ratio)
{
  // Constructing from center
  float l = 0.5f;
  float w = width_ratio / 2.0f;

  return {
    // Horizontal bar
    -l, -w, 0.0f,
     l, -w, 0.0f,
     l,  w, 0.0f,
     l,  w, 0.0f,
    -l,  w, 0.0f,
    -l, -w, 0.0f,
    // Lower vertical bar
    -w, -w, 0.0f,
    -w, -l, 0.0f,
     w, -l, 0.0f,
     w, -l, 0.0f,
     w, -w, 0.0f,
    -w, -w, 0.0f,
    // Upper vertical bar
     w, w, 0.0f,
     w, l, 0.0f,
    -w, l, 0.0f,
    -w, l, 0.0f,
    -w, w, 0.0f,
     w, w, 0.0f
  };
}


std::vector<float> build_circle_vertices(int points, float radius, float thickness)
{
  std::vector<float> vertices(static_cast<std::size_t>(points + 1) * 6 * 3);
  std::size_t index = 0;
  float last_angle = 0.0f;
  for (int i=1; i<=points; ++i) {
    float angle = static_cast<float>(i) / points * tau;
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


std::vector<float> build_triangle_vertices(float base_length, float height)
{

  float l = base_length / 2.0f;
  float h = height / 2.0f;

  return {
      -l, -h, 0.0f,
       l, -h, 0.0f,
    0.0f,  h, 0.0f
  };
}


}  // namespace


hmi::Position_marker::Position_marker() : cross_{build_cross_vertices(0.05f)},
    circle_{build_circle_vertices(64, 0.25f, 0.05f)},
    triangle_{build_triangle_vertices(1.0f, 0.5f * std::sqrt(3.0f))}
{
  set_rotation(glm::radians(-90.0f), 0.0f, 0.0f);
  apeiron::engine::Entity::set_position(0.0f, 0.05f, 0.0f);
  set_style(style_);
}


void hmi::Position_marker::set_style(Style style)
{
  style_ = style;
  switch (style_) {
    case Style::Cross:
      [[fallthrough]];
    case Style::Target:
      set_scale(5.5f, 1.0f, 5.5f);
      break;
  }
}


void hmi::Position_marker::set_position(float x, float y)
{
  switch (style_) {
    case Style::Cross:
      [[fallthrough]];
    case Style::Target:
      apeiron::engine::Entity::set_position(x, 0.075f, y);
      break;
  }
}


void hmi::Position_marker::render() const
{
    switch (style_) {
    case Style::Cross:
      cross_.render();
      break;
    case Style::Target:
      cross_.render();
      circle_.render();
      break;
  }
}
