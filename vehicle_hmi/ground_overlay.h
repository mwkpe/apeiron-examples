#ifndef HMI_GROUND_OVERLAY_H
#define HMI_GROUND_OVERLAY_H


#include "engine/entity.h"
#include "opengl/rectangle.h"


namespace hmi {


class Ground_overlay final : public apeiron::engine::Entity
{
public:
  Ground_overlay();
  void render() const override;


private:
  apeiron::opengl::Rectangle horizontal_;
  apeiron::opengl::Rectangle vertical_;
};


}  // namespace hmi


#endif  // HMI_GROUND_OVERLAY_H