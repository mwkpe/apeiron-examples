#ifndef HMI_DEVIATION_METER_H
#define HMI_DEVIATION_METER_H


#include <glm/glm.hpp>
#include "opengl/renderer.h"
#include "deviation_animation.h"
#include "meter.h"


namespace hmi {


class Deviation_meter final
{
public:
  Deviation_meter();
  void set_longitudinal_deviation(float deviation);
  glm::vec4 longitudinal_color() const;
  void update(float delta_time);
  void render(apeiron::opengl::Renderer& renderer, bool animated = true);

private:
  Meter longitudinal_meter_;
  Deviation_animation longitudinal_animation_;
};


}  // namespace hmi


#endif  // HMI_DEVIATION_METER_H
