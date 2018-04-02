#ifndef HMI_VEHICLE_H
#define HMI_VEHICLE_H


#include "engine/entity.h"
#include "opengl/model.h"
#include "opengl/texture.h"


namespace hmi {


class Vehicle final : public apeiron::engine::Entity
{
public:
  void load_model(std::string_view filename, int flags);
  void load_texture(std::string_view filename);
  float velocity() const { return velocity_; }
  void render() const override { texture_.bind(); model_.render(); }

private:
  apeiron::opengl::Model model_;
  apeiron::opengl::Texture texture_;
  float velocity_ = 0.0f;
};


}  // namespace hmi


#endif  // HMI_VEHICLE_H
