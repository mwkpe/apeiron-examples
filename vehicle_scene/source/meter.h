#ifndef EXAMPLE_METER_H
#define EXAMPLE_METER_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/rectangle.h"


namespace example {


class Meter final : public apeiron::engine::Entity
{
public:
  Meter() : meter_{1.0, 1.0} {}
  void set_value(float value) { value_ = value; };
  void set_color(glm::vec4 color) { color_ = color; }
  glm::vec4 color() const { return color_; }
  void render() const override { meter_.render(); }

private:
  float value_ = 0.0f;
  apeiron::opengl::Rectangle meter_;
  glm::vec4 color_ = glm::vec4{1.0f, 0.0f, 1.0f, 1.0f};
};


}  // namespace example


#endif  // EXAMPLE_METER_H
