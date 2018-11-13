#include "point_cloud.h"


#include <vector>
#include <fstream>
#include "engine/vertex.h"
#include "string_utils.h"
#include "utility/timer.h"


void example::Point_cloud::load_data(std::string_view filename)
{
  using namespace nonstd::string_utils;
  using namespace apeiron::engine;

  apeiron::utility::Scope_timer timer{"Load time"};

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

        // Negative values indicate missing color information, use fuchsia
        if (float r = std::stof(values[4]); r < 0.0f) {
          data.push_back({{x + 30.0f, y + 625.0f, z - 128.0f}, {1.0f, 0.0f, 1.0f, 1.0f}});
        }
        else {
          float g = std::stof(values[5]);
          float b = std::stof(values[6]);
          float a = std::stof(values[7]);
          data.push_back({{x + 30.0f, y + 625.0f, z - 128.0f}, {r, g, b, a}});
        }
      }
    }

    points_.set(std::move(data));
  }
}


void example::Point_cloud::render() const
{
  points_.render();
}
