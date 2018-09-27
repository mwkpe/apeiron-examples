#include "board.h"


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
    checkerboard.emplace_back(++flip % 2 ? black : white);
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
    white_{tile_size_, {0.9f, 0.9f, 0.9f, 1.0f}},
    black_{tile_size_, {0.1f, 0.1f, 0.1f, 1.0f}},
    checkerboard_{build_checkerboard(tile_size_, &white_, &black_)}
{
}


void example::chess::Board::render(apeiron::opengl::Renderer& renderer)
{
  renderer.use_vertex_color_shading();
  for (const auto& tile : checkerboard_) {
    renderer.render(tile);
  }
}
