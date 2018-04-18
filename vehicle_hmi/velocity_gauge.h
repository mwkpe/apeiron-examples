#ifndef HMI_VELOCITY_GAUGE_H
#define HMI_VELOCITY_GAUGE_H


#include "gauge.h"
#include "engine/text.h"
#include "opengl/charset.h"
#include "opengl/renderer.h"


namespace hmi {


class Velocity_gauge final
{
public:
  Velocity_gauge(apeiron::opengl::Charset* charset);
  void update(float current_velocity, float target_velocity);
  void render(apeiron::opengl::Renderer& renderer) const;

private:
  float current_velocity_ = 0.0f;
  float target_velocity_ = 0.0f;
  Gauge current_velocity_gauge_;
  Gauge target_velocity_gauge_;
  Gauge target_velocity_notch_;
  apeiron::opengl::Charset* charset_ = nullptr;
  apeiron::engine::Text current_velocity_text_;
  apeiron::engine::Text current_velocity_unit_text_;
  apeiron::engine::Text target_velocity_text_;
};


}  // namespace hmi


#endif  // HMI_VELOCITY_GAUGE_H
