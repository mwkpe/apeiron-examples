#include "line_markings.h"


#include <cmath>


namespace {


std::vector<float> build_line_markings(int length = 200)
{
  float line_width = 0.2f;
  float line_length = 6.0f;
  float line_gap = 12.0f;
  float lane_width = 3.6f;
  auto vertices_count = static_cast<std::size_t>(std::round(length * 2.0f / (line_gap + line_length) + 0.5f)) * 36;
  std::vector<float> vertices(vertices_count);
  std::size_t index = 0;

  for (int i=length; i>-length; i-=static_cast<int>(line_gap + line_length)) {
    vertices[index++] = lane_width / 2.0f + line_width / 2.0f;
    vertices[index++] = static_cast<float>(i);
    vertices[index++] = 0.0f;
    vertices[index++] = lane_width / 2.0f - line_width / 2.0f;
    vertices[index++] = static_cast<float>(i);
    vertices[index++] = 0.0f;
    vertices[index++] = lane_width / 2.0f - line_width / 2.0f;
    vertices[index++] = static_cast<float>(i) - line_length;
    vertices[index++] = 0.0f;
    vertices[index++] = lane_width / 2.0f - line_width / 2.0f;
    vertices[index++] = static_cast<float>(i) - line_length;
    vertices[index++] = 0.0f;
    vertices[index++] = lane_width / 2.0f + line_width / 2.0f;
    vertices[index++] = static_cast<float>(i) - line_length;
    vertices[index++] = 0.0f;
    vertices[index++] = lane_width / 2.0f + line_width / 2.0f;
    vertices[index++] = static_cast<float>(i);
    vertices[index++] = 0.0f;

    vertices[index++] = -lane_width / 2.0f + line_width / 2.0f;
    vertices[index++] = static_cast<float>(i);
    vertices[index++] = 0.0f;
    vertices[index++] = -lane_width / 2.0f - line_width / 2.0f;
    vertices[index++] = static_cast<float>(i);
    vertices[index++] = 0.0f;
    vertices[index++] = -lane_width / 2.0f - line_width / 2.0f;
    vertices[index++] = static_cast<float>(i) - line_length;
    vertices[index++] = 0.0f;
    vertices[index++] = -lane_width / 2.0f - line_width / 2.0f;
    vertices[index++] = static_cast<float>(i) - line_length;
    vertices[index++] = 0.0f;
    vertices[index++] = -lane_width / 2.0f + line_width / 2.0f;
    vertices[index++] = static_cast<float>(i) - line_length;
    vertices[index++] = 0.0f;
    vertices[index++] = -lane_width / 2.0f + line_width / 2.0f;
    vertices[index++] = static_cast<float>(i);
    vertices[index++] = 0.0f;
  }

  return vertices;
}


}  // namespace


hmi::Line_markings::Line_markings() : lines_{build_line_markings()}
{
  set_rotation(glm::radians(-90.0f), 0.0f, 0.0f);
}
