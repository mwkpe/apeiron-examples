#ifndef EXAMPLE_LANE_MARKINGS_H
#define EXAMPLE_LANE_MARKINGS_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/triangles.h"


namespace example {


class Lane_markings final : public apeiron::engine::Entity
{
public:
  Lane_markings();
  float line_spacing() const { return 18.0f; }
  void render() const override { stripes_.render(); }


private:
  apeiron::opengl::Triangles stripes_;
};


}  // namespace example


#endif  // EXAMPLE_LANE_MARKINGS_H