#ifndef EXAMPLE_CHESS_BOARD_H
#define EXAMPLE_CHESS_BOARD_H


#include <vector>
#include "opengl/renderer.h"
#include "opengl/cuboid.h"
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
	apeiron::opengl::Cuboid white_;
	apeiron::opengl::Cuboid black_;
  std::vector<Tile> checkerboard_;
};


}  // namespace example::chess


#endif  // EXAMPLE_CHESS_BOARD_H
