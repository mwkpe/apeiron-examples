#include "deviation_meter.h"


#include <cmath>


hmi::Deviation_meter::Deviation_meter() : meter_{1.0, 1.0}
{
  set_position(0.0f, 0.1f, 0.0f);
  set_rotation(glm::radians(-90.0), 0.0f, 0.0f);  // Parallel to ground (x, z)
}


void hmi::Deviation_meter::set_deviation(float deviation)
{
  set_scale(1.0, 1.0f, deviation);
  set_position(0.0f, 0.1f, deviation/2.0f);

  if (std::abs(deviation) < 5.0f)
    color_ = glm::vec4{0.0f, 0.784f, 0.325f, 1.0f};
  else if (std::abs(deviation) < 15.0f)
    color_ = glm::vec4{1.0f, 0.839f, 0.0f, 1.0f};
  else
    color_ = glm::vec4{0.956f, 0.317f, 0.117f, 1.0f};
}