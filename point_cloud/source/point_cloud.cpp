#include "point_cloud.h"


#include <vector>
#include <fstream>
#include "string_utils.h"


void example::Point_cloud::load_data(std::string_view filename)
{
  using namespace nonstd::string_utils;
  std::vector<float> data;

  if (std::ifstream file{std::string{filename}}; file.is_open()) {
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
        // Translation offset
        data.push_back(x);
        data.push_back(y + 650.0f);
        data.push_back(z - 100.0f);
        // Negative values indicate missing color information
        data.push_back(r < 0 ? 1.0f : r);
        data.push_back(g < 0 ? 0.0f : g);
        data.push_back(b < 0 ? 1.0f : b);
      }
    }

    points_.init(std::move(data), apeiron::opengl::Points::Format::Xyzrgb);
  }
}


void example::Point_cloud::render() const
{
  points_.render();
}
