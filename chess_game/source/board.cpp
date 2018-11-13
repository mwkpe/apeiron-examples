#include "board.h"


#include <string>
#include "engine/vertex.h"


namespace {


auto build_checkerboard(glm::vec3 tile_size, const apeiron::opengl::Cuboid* white,
    const apeiron::opengl::Cuboid* black)
{
  std::vector<example::chess::Tile> checkerboard;

  // Build board from bottom left
  float x = -tile_size.x * 4 + tile_size.x / 2;
  const float y = tile_size.y * 0.5f;  // Move to ground (constructed from center)
  float z = tile_size.z * 4 - tile_size.z / 2;

  int flip = 0;
  for (std::size_t i=0; i<64; ++i) {
    checkerboard.emplace_back(i, ++flip % 2 ? black : white);
    checkerboard.back().set_position(x, y, z);
    checkerboard.back().set_size(tile_size);
    checkerboard.back().set_intersection_radius(tile_size.y * 1.25f);
    x += tile_size.x;
    if ((i + 1) % 8 == 0) {
      flip--;
      z -= tile_size.z;
      x -= tile_size.x * 8;
    }
  }

  return checkerboard;
}


std::vector<apeiron::engine::Vertex_simple> build_highlight(glm::vec3 tile_size, float height)
{
  auto s = tile_size.x * 0.4f;
  auto thickness = tile_size.x * 0.04f;
  auto length = tile_size.x * 0.2f;

  return {
    // Top left
    {{-s,          height, -s + thickness}},
    {{-s + length, height, -s + thickness}},
    {{-s + length, height, -s}},
    {{-s + length, height, -s}},
    {{-s,          height, -s}},
    {{-s,          height, -s + thickness}},
    // Top right
    {{s - length, height, -s + thickness}},
    {{s,          height, -s + thickness}},
    {{s,          height, -s}},
    {{s,          height, -s}},
    {{s - length, height, -s}},
    {{s - length, height, -s + thickness}},
    // Bottom left
    {{-s,          height, s}},
    {{-s + length, height, s}},
    {{-s + length, height, s - thickness}},
    {{-s + length, height, s - thickness}},
    {{-s,          height, s - thickness}},
    {{-s,          height, s}},
    // Bottom right
    {{s - length, height, s}},
    {{s,          height, s}},
    {{s,          height, s - thickness}},
    {{s,          height, s - thickness}},
    {{s - length, height, s - thickness}},
    {{s - length, height, s}},
    // Left top
    {{-s + thickness, height, -s + thickness}},
    {{-s,             height, -s + thickness}},
    {{-s,             height, -s + length}},
    {{-s,             height, -s + length}},
    {{-s + thickness, height, -s + length}},
    {{-s + thickness, height, -s + thickness}},
    // Left bottom
    {{-s + thickness, height, s - length}},
    {{-s,             height, s - length}},
    {{-s,             height, s - thickness}},
    {{-s,             height, s - thickness}},
    {{-s + thickness, height, s - thickness}},
    {{-s + thickness, height, s - length}},
    // Right top
    {{s,             height, -s + thickness}},
    {{s - thickness, height, -s + thickness}},
    {{s - thickness, height, -s + length}},
    {{s - thickness, height, -s + length}},
    {{s,             height, -s + length}},
    {{s,             height, -s + thickness}},
    // Right bottom
    {{s,             height, s - length}},
    {{s - thickness, height, s - length}},
    {{s - thickness, height, s - thickness}},
    {{s - thickness, height, s - thickness}},
    {{s,             height, s - thickness}},
    {{s,             height, s - length}}
  };
}


std::vector<apeiron::engine::Vertex_simple> build_current_highlight(glm::vec3 tile_size, float height)
{
  auto s = tile_size.x * 0.4f;
  auto thickness = tile_size.x * 0.04f;
  auto length = tile_size.x * 0.2f;

  return {
    // Top
    {{-length / 2.0f,          height, -s + thickness}},
    {{-length / 2.0f + length, height, -s + thickness}},
    {{-length / 2.0f + length, height, -s}},
    {{-length / 2.0f + length, height, -s}},
    {{-length / 2.0f,          height, -s}},
    {{-length / 2.0f,          height, -s + thickness}},
    // Bottom
    {{-length / 2.0f,          height, s}},
    {{-length / 2.0f + length, height, s}},
    {{-length / 2.0f + length, height, s - thickness}},
    {{-length / 2.0f + length, height, s - thickness}},
    {{-length / 2.0f,          height, s - thickness}},
    {{-length / 2.0f,          height, s}},
    // Left
    {{-s + thickness, height, -length / 2.0f}},
    {{-s,             height, -length / 2.0f}},
    {{-s,             height, -length / 2.0f + length}},
    {{-s,             height, -length / 2.0f + length}},
    {{-s + thickness, height, -length / 2.0f + length}},
    {{-s + thickness, height, -length / 2.0f}},
    // Right
    {{s,             height, -length / 2.0f}},
    {{s - thickness, height, -length / 2.0f}},
    {{s - thickness, height, -length / 2.0f + length}},
    {{s - thickness, height, -length / 2.0f + length}},
    {{s,             height, -length / 2.0f + length}},
    {{s,             height, -length / 2.0f}}
  };
}


[[maybe_unused]] inline bool dark_tile(std::size_t index)
{
  return index % 2 == index / 8 % 2;
}


}  // namespace


example::chess::Board::Board(glm::vec3 size) : board_size_{size},
    tile_size_{size.x / 8, size.y, size.z / 8},
    charset_{16, 8, 32, 0.5f, 1.0f},
    white_{tile_size_, {0.2f, 0.2f, 0.2f, 1.0f}},
    black_{tile_size_, {0.1f, 0.1f, 0.1f, 1.0f}},
    tiles_{build_checkerboard(tile_size_, &white_, &black_)},
    tile_highlight_{build_highlight(tile_size_, size.y / 2.0f + 0.025f)},
    current_highlight_{build_current_highlight(tile_size_, size.y / 2.0f + 0.025f)}
{
  charset_.load_texture("assets/roboto_mono.png");

  const float center_offset_x = tile_size_.x / 2.0f;
  const float center_offset_z = tile_size_.z / 2.0f;
  float x = -board_size_.x / 2.0f + center_offset_x;
  float z = board_size_.z / 2.0f + center_offset_z;

  const std::array<std::string, 16> letters { "A", "B", "C", "D", "E", "F", "G", "H",
      "1", "2", "3", "4", "5", "6", "7", "8" };
  std::size_t index = 0;

  for (auto& letter : legend_) {
    letter.set_text(letters[index++]);
    letter.set_text_size(0.6f);
    letter.set_rotation(glm::radians(-90.0f), 0.0f, 0.0f);
    letter.set_position(x, 0.0f, z);
    
    if (index < 9) {
      x += tile_size_.x;
    }
    if (index > 7) {
      z -= tile_size_.z;
    }
  }
}


void example::chess::Board::set_allowed(std::size_t board_index, bool allowed)
{
  if (board_index < tiles_.size())
    tiles_[board_index].set_allowed(allowed);
}


void example::chess::Board::clear_allowed()
{
  for (auto& tile : tiles_)
    tile.set_allowed(false);
}


void example::chess::Board::render(apeiron::opengl::Renderer& renderer, const Options* options)
{
  renderer.set_lighting(options->lighting);
  renderer.use_vertex_color_shading();

  for (const auto& tile : tiles_) {
    renderer.render(tile);
  }

  renderer.set_lighting(false);
  renderer.use_color_shading();

  if (selected_index_) {
    tile_highlight_.set_position(tiles_[*selected_index_].position());
    renderer.render(tile_highlight_, selection_color_);
  }

  if (current_index_) {
    current_highlight_.set_position(tiles_[*current_index_].position());
    renderer.render(current_highlight_, current_color_);
  }

  for (const auto& tile : tiles_) {
    if (tile.allowed()) {
      tile_highlight_.set_position(tile.position());
      renderer.render(tile_highlight_, allowed_color_);
    }
  }

  for (const auto& letter : legend_) {
    renderer.render(letter, charset_, {0.7f, 0.7f, 0.7f, 1.0f});
  }
}
