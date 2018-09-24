#include "road.h"


example::Road::Road() : road_{11.2f, 200.0f, {0.126f, 0.138f, 0.134f, 1.0f}}
{
  set_position(0.0f, -0.05f, 0.0f);
  // Rotate to xz-plane
  set_rotation(glm::radians(-90.0f), 0.0f, 0.0f);
}