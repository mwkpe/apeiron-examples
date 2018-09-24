#include "point_cloud.h"


#include <vector>
#include <fstream>
#include "engine/vertex.h"
#include "string_utils.h"


void example::Point_cloud::load_data(std::string_view filename)
{
  using namespace nonstd::string_utils;
  using namespace apeiron::engine;

  if (std::ifstream file{std::string{filename}}; file.is_open()) {
    std::vector<Vertex_color> data;
    std::string line;
    while (getline(file, line)) {
      // Frame x y z r g b a
      auto values = split_copy(line, " ");
      if (values.size() == 8) {
        float x = std::stof(values[1]);
        float y = std::stof(values[2]);
        float z = std::stof(values[3]);
        float r = std::stof(values[4]);
        float g = std::stof(values[5]);
        float b = std::stof(values[6]);
        float a = std::stof(values[7]);
        data.push_back(Vertex_color{
            // Move cloud to center
            x + 30.0f,
            y + 625.0f,
            z - 128.0f,
            // Negative values indicate missing color information, use fuchsia
            r < 0 ? 1.0f : r,
            g < 0 ? 0.0f : g,
            b < 0 ? 1.0f : b,
            a < 0 ? 1.0f : a});
      }
    }

    points_.init(std::move(data));
  }
}


void example::Point_cloud::render() const
{
  points_.render();
}
