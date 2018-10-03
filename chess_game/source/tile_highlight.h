#ifndef EXAMPLE_CHESS_TILE_HIGHLIGHT_H
#define EXAMPLE_CHESS_TILE_HIGHLIGHT_H


#include "engine/entity.h"
#include "engine/vertex.h"
#include "opengl/triangles.h"


namespace example::chess {


class Tile_highlight final : public apeiron::engine::Entity
{
public:
  Tile_highlight(std::vector<apeiron::engine::Vertex_simple>&& vertices)
  		: vertices_{std::move(vertices)} {}
  void render() const override { vertices_.render(); }

private:
  apeiron::opengl::Triangles vertices_;
};


}  // namespace example::chess


#endif  // EXAMPLE_CHESS_TILE_HIGHLIGHT_H
