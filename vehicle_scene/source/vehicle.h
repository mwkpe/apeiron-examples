#ifndef EXAMPLE_VEHICLE_H
#define EXAMPLE_VEHICLE_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/model.h"
#include "opengl/wire_cuboid.h"
#include "opengl/texture.h"


namespace example {


class Vehicle final : public apeiron::engine::Entity
{
public:
  explicit Vehicle(const glm::vec3& size);
  void load_model(std::string_view filename);
  void load_texture(std::string_view filename);
  void set_color(float r, float g, float b, float a = 1.0f) { color_ = glm::vec4{r, g, b, a}; };
  void set_velocity(float velocity) { velocity_ = velocity; }
  glm::vec4 color() const { return color_; }
  float velocity() const { return velocity_; }
  void render() const override;
  void render_bounds() const override { bounding_box_.render(); };

private:
  apeiron::opengl::Model model_;
  apeiron::opengl::Texture texture_;
  apeiron::opengl::Wire_cuboid bounding_box_;
  glm::vec4 color_;
  float velocity_ = 0.0f;
};


}  // namespace example


#endif  // EXAMPLE_VEHICLE_H
