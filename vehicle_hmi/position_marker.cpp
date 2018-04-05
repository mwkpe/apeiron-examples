#include "position_marker.h"


hmi::Position_marker::Position_marker() : horizontal_{6.0f, 0.3f}, vertical_{0.3f, 6.0f}
{
  set_position(0.0f, 0.1f, 0.0f);
  set_rotation(glm::radians(-90.0f), 0.0f, 0.0f);
}


void hmi::Position_marker::render() const
{
  horizontal_.render();
  vertical_.render();
}
