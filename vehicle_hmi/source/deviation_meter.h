#ifndef HMI_DEVIATION_METER_H
#define HMI_DEVIATION_METER_H


#include <glm/glm.hpp>
#include "opengl/renderer.h"
#include "meter.h"
#include "deviation_animation.h"
#include "position_marker.h"


namespace hmi {


class Deviation_meter final
{
public:
  Deviation_meter();
  void set_deviation(float deviation);
  void update(float delta_time);
  void render(apeiron::opengl::Renderer& renderer, bool animated = true);

private:
  Meter meter_;
  Deviation_animation animation_;
  Position_marker target_position_;
};


}  // namespace hmi


#endif  // HMI_DEVIATION_METER_H
