#include "point_cloud.h"


#include <vector>
#include <fstream>
#include <regex>
#include <iostream>


void example::Point_cloud::load_data(std::string_view filename)
{
  std::vector<float> data;
  std::string s = std::string{filename};
  if (std::ifstream file{s}; file.is_open()) {
    std::string line;
    // Frame, x, y, z, r, g, b, a
    std::regex rx{R"(^\d+\s([^\s]+)\s([^\s]+)\s([^\s]+)\s([^\s]+)\s([^\s]+)\s([^\s]+).+)"};
    std::smatch m;
    while (getline(file, line)) {
      if (std::regex_match(line, m, rx)) {
        float x = std::stof(m[1]);
        float y = std::stof(m[2]);
        float z = std::stof(m[3]);
        float r = std::stof(m[4]);
        float g = std::stof(m[5]);
        float b = std::stof(m[6]);
        // Translation offset
        data.push_back(x + 50.0f);
        data.push_back(y + 650.0f);
        data.push_back(z - 400.0f);
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
