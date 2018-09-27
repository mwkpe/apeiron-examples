#ifndef EXAMPLE_CHESS_TILE_H
#define EXAMPLE_CHESS_TILE_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/cuboid.h"


namespace example::chess {


class Tile final : public apeiron::engine::Entity
{
public:
  Tile(const apeiron::opengl::Cuboid* cuboid) : cuboid_{cuboid} {}
  void render() const override { cuboid_->render(); }

private:
  const apeiron::opengl::Cuboid* cuboid_ = nullptr;
};


}  // namespace example::chess


#endif  // EXAMPLE_CHESS_TILE_H
