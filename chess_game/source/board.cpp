#include "board.h"


#include <string>
#include "engine/vertex.h"


namespace {


auto build_checkerboard(glm::vec3 tile_size, const apeiron::opengl::Cuboid* white,
    const apeiron::opengl::Cuboid* black)
{
  std::vector<example::chess::Tile> checkerboard;

  float x = -tile_size.x * 4 + tile_size.x / 2;
  const float y = 0.0f + tile_size.y * 0.5f;  // Move to ground (constructed from center)
  float z = -tile_size.z * 4 + tile_size.z / 2;

  int flip = 0;
  for (int i=0; i<64; ++i) {
    checkerboard.emplace_back(++flip % 2 ? white : black);
    checkerboard.back().set_position(x, y, z);
    checkerboard.back().set_size(tile_size);
    x += tile_size.x;
    if ((i + 1) % 8 == 0) {
      flip--;
      z += tile_size.z;
      x -= tile_size.x * 8;
    }
  }

  return checkerboard;
}


}  // namespace


example::chess::Board::Board(glm::vec3 size) : board_size_{size},
    tile_size_{size.x / 8, size.y, size.z / 8},
    charset_{16, 8, 32, 0.5f, 1.0f},
    white_{tile_size_, {0.9f, 0.9f, 0.9f, 1.0f}},
    black_{tile_size_, {0.1f, 0.1f, 0.1f, 1.0f}},
    checkerboard_{build_checkerboard(tile_size_, &white_, &black_)}
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
    letter.set_size(0.75f);
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


void example::chess::Board::render(apeiron::opengl::Renderer& renderer)
{
  renderer.use_vertex_color_shading();
  for (const auto& tile : checkerboard_) {
    renderer.render(tile);
  }
  renderer.set_lighting(false);
  renderer.use_color_shading();
  for (const auto& letter : legend_) {
    renderer.render(letter, charset_, {1.0f, 1.0f, 1.0f, 1.0f});
  }
}
