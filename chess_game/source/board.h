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
#include "engine/collision.h"
#include "engine/text.h"
#include "options.h"
#include "tile.h"
#include "tile_highlight.h"


namespace example::chess {


class Board final
{
public:
  Board(glm::vec3 size);

  void set_allowed(std::size_t board_index, bool allowed);
  void set_selected(std::size_t board_index) { board_index < tiles_.size() ?
      selected_index_ = board_index : selected_index_ = std::nullopt; }
  void set_current(std::size_t board_index) { board_index < tiles_.size() ?
      current_index_ = board_index : current_index_ = std::nullopt; }

  void clear_allowed();
  void clear_selected() { selected_index_ = std::nullopt; }
  void clear_current() { current_index_ = std::nullopt; }

  std::optional<std::size_t> selected_index() const { return selected_index_; }

  void render(apeiron::opengl::Renderer& renderer, const Options* options);
  glm::vec3 size() const { return board_size_; }
  bool allowed(std::size_t board_index) { return tiles_[board_index].allowed(); }

private:
  glm::vec3 board_size_;
  glm::vec3 tile_size_;
  glm::vec4 selection_color_ = {0.7f, 0.7f, 0.7f, 1.0f};
  glm::vec4 allowed_color_ = {0.203f, 0.698f, 0.419f, 1.0f};
  glm::vec4 current_color_ = {0.007f, 0.533f, 0.819f, 1.0f};
  apeiron::opengl::Tileset charset_;
  apeiron::opengl::Cuboid white_;
  apeiron::opengl::Cuboid black_;
  std::vector<Tile> tiles_;
  Tile_highlight tile_highlight_;
  Tile_highlight current_highlight_;
  std::array<apeiron::engine::Text, 16> legend_;
  std::optional<std::size_t> selected_index_ = std::nullopt;
  std::optional<std::size_t> current_index_ = std::nullopt;
};


}  // namespace example::chess


#endif  // EXAMPLE_CHESS_BOARD_H
