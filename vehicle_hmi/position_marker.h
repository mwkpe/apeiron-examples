#ifndef HMI_POSITION_MARKER_H
#define HMI_POSITION_MARKER_H


#include "engine/entity.h"
#include "opengl/rectangle.h"


namespace hmi {


class Position_marker final : public apeiron::engine::Entity
{
public:
  Position_marker();
  void render() const override;


private:
  apeiron::opengl::Rectangle horizontal_;
  apeiron::opengl::Rectangle vertical_;
};


}  // namespace hmi


#endif  // HMI_POSITION_MARKER_H