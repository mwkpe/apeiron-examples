#ifndef HMI_GROUND_OVERLAY_H
#define HMI_GROUND_OVERLAY_H


#include "engine/entity.h"
#include "opengl/line_array.h"


namespace hmi {


class Ground_overlay final : public apeiron::engine::Entity
{
public:
  Ground_overlay();
  void render() const override { line_array_.render(); }


private:
  apeiron::opengl::Line_array line_array_;
};


}  // namespace hmi


#endif  // HMI_GROUND_OVERLAY_H