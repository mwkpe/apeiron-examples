#ifndef HMI_VELOCITY_GAUGE_H
#define HMI_VELOCITY_GAUGE_H


#include <glm/glm.hpp>
#include "gauge.h"
#include "engine/text.h"
#include "opengl/charset.h"
#include "opengl/renderer.h"


namespace hmi {


class Velocity_gauge final
{
public:
  Velocity_gauge(apeiron::opengl::Charset* charset);
  void update(float velocity);
  void render(apeiron::opengl::Renderer& renderer) const;

private:
  float velocity_ = 0.0f;
  glm::vec4 color_ = glm::vec4{0.129f, 0.588f, 0.952f, 1.0f};
  Gauge gauge_;
  apeiron::opengl::Charset* charset_ = nullptr;
  apeiron::engine::Text velocity_text_;
  apeiron::engine::Text unit_text_;
};


}  // namespace hmi


#endif  // HMI_VELOCITY_GAUGE_H
