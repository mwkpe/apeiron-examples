#ifndef EXAMPLE_ROAD_H
#define EXAMPLE_ROAD_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/rectangle.h"


namespace example {


class Road final : public apeiron::engine::Entity
{
public:
  Road();
  void render() const override { road_.render(); }

private:
  apeiron::opengl::Rectangle road_;
};


}  // namespace example


#endif  // EXAMPLE_ROAD_H