#ifndef HMI_LINE_MARKINGS_H
#define HMI_LINE_MARKINGS_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/polygon.h"


namespace hmi {


class Line_markings final : public apeiron::engine::Entity
{
public:
  Line_markings();
  float line_spacing() const { return 18.0f; }
  glm::vec4 color() const { return {0.7f, 0.7f, 0.7f, 1.0f}; }
  void render() const override { lines_.render(); }


private:
  apeiron::opengl::Polygon lines_;
};


}  // namespace hmi


#endif  // HMI_LINE_MARKINGS_H