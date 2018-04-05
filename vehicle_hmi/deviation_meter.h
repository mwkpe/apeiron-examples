#ifndef HMI_DEVIATION_METER_H
#define HMI_DEVIATION_METER_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/rectangle.h"


namespace hmi {


class Deviation_meter final : public apeiron::engine::Entity
{
public:
  Deviation_meter();
  void set_deviation(float deviation);
  glm::vec4 color() const { return color_; }
  void render() const override { meter_.render(); }


private:
  apeiron::opengl::Rectangle meter_;
  glm::vec4 color_ = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f};
};


}  // namespace hmi


#endif  // HMI_DEVIATION_METER_H
