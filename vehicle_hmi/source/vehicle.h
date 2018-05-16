#ifndef HMI_VEHICLE_H
#define HMI_VEHICLE_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/model.h"
#include "opengl/cuboid.h"
#include "opengl/texture.h"


namespace hmi {


class Vehicle final : public apeiron::engine::Entity
{
public:
  explicit Vehicle(const glm::vec3& size) : Entity{size}, bounding_box_{size, true, 2.0f} {}
  void load_model(std::string_view filename, int flags);
  void load_texture(std::string_view filename);
  void set_velocity(float velocity) { velocity_ = velocity; }
  void set_color(const glm::vec4& color) { color_ = color; }
  float velocity() const { return velocity_; }
  glm::vec4 color() const { return color_; }
  void render() const override { texture_.bind(); model_.render(); }
  void render_bounds() const override { bounding_box_.render(); };

private:
  apeiron::opengl::Model model_;
  apeiron::opengl::Texture texture_;
  apeiron::opengl::Cuboid bounding_box_;
  glm::vec4 color_ = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f};
  float velocity_ = 0.0f;
};


}  // namespace hmi


#endif  // HMI_VEHICLE_H
