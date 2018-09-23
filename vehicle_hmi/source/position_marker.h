#ifndef HMI_POSITION_MARKER_H
#define HMI_POSITION_MARKER_H


#include "engine/entity.h"
#include "opengl/triangles.h"


namespace hmi {


class Position_marker final : public apeiron::engine::Entity
{
public:
  enum class Style { Cross, Target };

  Position_marker();
  void set_style(Style style);
  void set_position(float x, float y);
  void render() const override;

private:
  Style style_ = Style::Target;
  apeiron::opengl::Triangles cross_;
  apeiron::opengl::Triangles circle_;
  apeiron::opengl::Triangles triangle_;
};


}  // namespace hmi


#endif  // HMI_POSITION_MARKER_H