#ifndef HMI_GROUND_H
#define HMI_GROUND_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/grid.h"


namespace hmi {


class Ground final : public apeiron::engine::Entity
{
public:
  Ground(const glm::vec3& size, const glm::vec3& spacing, float precision)
      : grid_{size, spacing, precision} {}
  glm::vec3 size() const { return grid_.size(); }
  glm::vec3 spacing() const { return grid_.spacing(); }
  void render() const override { grid_.render(); }


private:
  apeiron::opengl::Grid grid_;
};


}  // namespace hmi


#endif  // HMI_GROUND_H
