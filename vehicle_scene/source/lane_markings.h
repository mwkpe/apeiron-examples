#ifndef EXAMPLE_LANE_MARKINGS_H
#define EXAMPLE_LANE_MARKINGS_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/triangles.h"


namespace example {


class Lane_markings final : public apeiron::engine::Entity
{
public:
  Lane_markings();
  void set_color(float r, float g, float b, float a = 1.0f) { color_ = glm::vec4{r, g, b, a}; };
  float line_spacing() const { return 18.0f; }
  glm::vec4 color() const { return color_; }
  void render() const override { stripes_.render(); }

private:
  apeiron::opengl::Triangles stripes_;
  glm::vec4 color_;
};


}  // namespace example


#endif  // EXAMPLE_LANE_MARKINGS_H