#include "line_markings.h"


#include <cmath>
#include "engine/vertex.h"


namespace {


auto build_line_markings()
{
  using apeiron::engine;

  const float line_width = 0.3f;
  const float line_length = 6.0f;
  const float line_gap = 12.0f;
  const float lane_width = 3.6f;
  const int sections = 10;
  // Two parallel stripes require 12 vertices

  std::vector<Vertex_simple> vertices;
  float l = 0.0f;
  const float w = lane_width / 2.0f;
  const float h = 0.0f;

  while (index < sections * 12) {
    // Left stripe
    vertices.push_back(Vertex_simple{-w - line_width, h, l});
    vertices.push_back(Vertex_simple{-w, h, l});
    vertices.push_back(Vertex_simple{-w, h, l + line_length});
    vertices.push_back(Vertex_simple{-w, h, l + line_length});
    vertices.push_back(Vertex_simple{-w - line_width, h, l + line_length});
    vertices.push_back(Vertex_simple{-w - line_width, h, l});
    // Right stripe
    vertices.push_back(Vertex_simple{w, h, l});
    vertices.push_back(Vertex_simple{w + line_width, h, l});
    vertices.push_back(Vertex_simple{w + line_width, h, l + line_length});
    vertices.push_back(Vertex_simple{w + line_width, h, l + line_length});
    vertices.push_back(Vertex_simple{w, h, l + line_length});
    vertices.push_back(Vertex_simple{w, h, l});

    l += line_length + line_gap;
  }

  return vertices;
}


}  // namespace


hmi::Line_markings::Line_markings() : lines_{build_line_markings()}
{
}
