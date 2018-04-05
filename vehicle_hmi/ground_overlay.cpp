#include "ground_overlay.h"


hmi::Ground_overlay::Ground_overlay() : horizontal_{6.0f, 0.4f}, vertical_{0.4f, 6.0f}
{
  set_position(0.0f, 0.1f, 0.0f);
  set_rotation(glm::radians(-90.0f), 0.0f, 0.0f);
}


void hmi::Ground_overlay::render() const
{
  horizontal_.render();
  vertical_.render();
}
