#include "lane_markings.h"


#include <cmath>
#include "engine/vertex.h"


namespace {


auto build_lane_markings()
{
  using namespace apeiron::engine;

  const float line_width = 0.2f;
  const float line_length = 6.0f;
  const float line_gap = 12.0f;
  const float lane_width = 3.6f;

  std::vector<Vertex_simple> vertices;
  const float lw = line_width;
  const float ll = line_length;
  const float w = lane_width / 2.0f;
  float h = 0.0f;
  const int sections = 12;
  int index = 0;

  while (index++ < sections) {
    // Left stripe
    vertices.push_back(Vertex_simple{-w - lw, h,      0.0f});
    vertices.push_back(Vertex_simple{-w,      h,      0.0f});
    vertices.push_back(Vertex_simple{-w - lw, h + ll, 0.0f});
    vertices.push_back(Vertex_simple{-w,      h,      0.0f});
    vertices.push_back(Vertex_simple{-w,      h + ll, 0.0f});
    vertices.push_back(Vertex_simple{-w - lw, h + ll, 0.0f});
    // Right stripe
    vertices.push_back(Vertex_simple{w,      h,      0.0f});
    vertices.push_back(Vertex_simple{w + lw, h,      0.0f});
    vertices.push_back(Vertex_simple{w,      h + ll, 0.0f});
    vertices.push_back(Vertex_simple{w + lw, h,      0.0f});
    vertices.push_back(Vertex_simple{w + lw, h + ll, 0.0f});
    vertices.push_back(Vertex_simple{w,      h + ll, 0.0f});

    h += line_length + line_gap;
  }

  return vertices;
}


}  // namespace


example::Lane_markings::Lane_markings() : stripes_{build_lane_markings()}
{
  set_position(0.0f, 0.05f, +100.0f);
  // Rotate to xz-plane
  set_rotation(glm::radians(-90.0f), 0.0f, 0.0f);
}
