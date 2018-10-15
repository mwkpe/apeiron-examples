#ifndef EXAMPLE_CHESS_TILE_H
#define EXAMPLE_CHESS_TILE_H


#include <cstddef>
#include <glm/glm.hpp>
#include "engine/entity.h"
#include "engine/collision.h"
#include "opengl/cuboid.h"


namespace example::chess {


class Tile final : public apeiron::engine::Entity
{
public:
  Tile(std::size_t board_index, const apeiron::opengl::Cuboid* cuboid)
      : board_index_{board_index}, cuboid_{cuboid} {}
  std::size_t board_index() const { return board_index_; }
  void set_allowed(bool allowed) { allowed_ = allowed; }
  bool allowed() const { return allowed_; }
  void render() const override { cuboid_->render(); }

private:
  std::size_t board_index_ = 0;
  bool selected_ = false;
  bool allowed_ = false;
  const apeiron::opengl::Cuboid* cuboid_ = nullptr;
};


}  // namespace example::chess


#endif  // EXAMPLE_CHESS_TILE_H
