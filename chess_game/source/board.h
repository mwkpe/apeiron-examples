#ifndef EXAMPLE_CHESS_BOARD_H
#define EXAMPLE_CHESS_BOARD_H


#include <array>
#include <vector>
#include "opengl/renderer.h"
#include "opengl/tileset.h"
#include "opengl/cuboid.h"
#include "engine/text.h"
#include "tile.h"


namespace example::chess {


class Board final
{
public:
  Board(glm::vec3 size);
  void render(apeiron::opengl::Renderer& renderer);
  glm::vec3 size() const { return board_size_; }

private:
  glm::vec3 board_size_;
  glm::vec3 tile_size_;
  apeiron::opengl::Tileset charset_;
  apeiron::opengl::Cuboid white_;
  apeiron::opengl::Cuboid black_;
  std::vector<Tile> checkerboard_;
  std::array<apeiron::engine::Text, 16> legend_;
};


}  // namespace example::chess


#endif  // EXAMPLE_CHESS_BOARD_H
