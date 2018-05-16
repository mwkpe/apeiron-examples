#ifndef HMI_POSITION_MARKER_H
#define HMI_POSITION_MARKER_H


#include "engine/entity.h"
#include "opengl/polygon.h"


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
  apeiron::opengl::Polygon cross_;
  apeiron::opengl::Polygon circle_;
  apeiron::opengl::Polygon triangle_;
};


}  // namespace hmi


#endif  // HMI_POSITION_MARKER_H