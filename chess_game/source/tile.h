#ifndef EXAMPLE_CHESS_TILE_H
#define EXAMPLE_CHESS_TILE_H


#include <cstddef>
#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/cuboid.h"


namespace example::chess {


class Tile final : public apeiron::engine::Entity
{
public:
  Tile(std::size_t board_index, const apeiron::opengl::Cuboid* cuboid)
      : board_index_{board_index}, cuboid_{cuboid} {}
  std::size_t board_index() const { return board_index_; }
  void render() const override { cuboid_->render(); }

private:
  std::size_t board_index_ = 0;
  const apeiron::opengl::Cuboid* cuboid_ = nullptr;
};


}  // namespace example::chess


#endif  // EXAMPLE_CHESS_TILE_H
