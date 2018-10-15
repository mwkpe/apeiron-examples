#ifndef EXAMPLE_ROAD_H
#define EXAMPLE_ROAD_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/quad.h"


namespace example {


class Road final : public apeiron::engine::Entity
{
public:
  Road();
  void render() const override { quad_.render(); }

private:
  apeiron::opengl::Quad quad_;
};


}  // namespace example


#endif  // EXAMPLE_ROAD_H