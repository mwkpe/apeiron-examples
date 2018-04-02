#ifndef HMI_LIGHT_H
#define HMI_LIGHT_H


#include <glm/glm.hpp>
#include "opengl/model.h"


namespace hmi {


class Light final : public apeiron::engine::Entity
{
public:
  Light(const apeiron::opengl::Model* model) : model_{model}, color_{1.0f, 1.0f, 1.0f} {}
  void set_color(float r, float g, float b) { color_ = glm::vec3{r, g, b}; }
  void set_color(const glm::vec3 color) { color_ = color; }
  glm::vec3 color() const { return color_; }
  void render() const override { model_->render(); }

private:
  const apeiron::opengl::Model* model_;
  glm::vec3 color_;
};


}  // namespace hmi


#endif  // HMI_LIGHT_H
