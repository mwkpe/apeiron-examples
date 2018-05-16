#ifndef HMI_ROAD_H
#define HMI_ROAD_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/rectangle.h"


namespace hmi {


class Road final : public apeiron::engine::Entity
{
public:
  Road();
  glm::vec4 color() const { return {0.156f, 0.168f, 0.164f, 1.0f}; }
  void render() const override { road_.render(); }

private:
  apeiron::opengl::Rectangle road_;
};


}  // namespace hmi


#endif  // HMI_ROAD_H