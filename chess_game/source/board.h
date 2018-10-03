#ifndef EXAMPLE_CHESS_BOARD_H
#define EXAMPLE_CHESS_BOARD_H


#include <cstddef>
#include <array>
#include <vector>
#include <optional>
#include <functional>
#include "opengl/renderer.h"
#include "opengl/tileset.h"
#include "opengl/cuboid.h"
#include "engine/ray.h"
#include "engine/text.h"
#include "options.h"
#include "tile.h"
#include "tile_highlight.h"


namespace example::chess {


class Board final
{
public:
  Board(glm::vec3 size);
  void set_selected(std::size_t board_index, bool b);
  void set_allowed(std::size_t board_index, bool b);
  void render(apeiron::opengl::Renderer& renderer, const Options* options);
  glm::vec3 size() const { return board_size_; }
  std::optional<std::size_t> intersects(const apeiron::engine::Ray& ray) const;

private:
  glm::vec3 board_size_;
  glm::vec3 tile_size_;
  apeiron::opengl::Tileset charset_;
  apeiron::opengl::Cuboid white_;
  apeiron::opengl::Cuboid black_;
  std::vector<Tile> tiles_;
  Tile_highlight tile_highlight_;
  std::array<apeiron::engine::Text, 16> legend_;
};


}  // namespace example::chess


#endif  // EXAMPLE_CHESS_BOARD_H
