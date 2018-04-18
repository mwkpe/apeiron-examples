#include "road.h"


hmi::Road::Road() : road_{1.0f, 1.0f}
{
  set_position(0.0f, -0.05f, 0.0f);
  set_scale(11.2f, 1.0f, 400.0f);
  set_rotation(glm::radians(-90.0f), 0.0f, 0.0f);
}