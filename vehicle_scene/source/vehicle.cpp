#include "vehicle.h"


example::Vehicle::Vehicle(const glm::vec3& size) : bounding_box_{size} 
{
  set_size(size);
}


void example::Vehicle::load_model(std::string_view filename)
{
  model_.load(filename);
  bounding_box_.set_line_width(2.0f);
}


void example::Vehicle::load_texture(std::string_view filename)
{
  texture_.load(filename);
}


void example::Vehicle::render() const
{
  texture_.bind();
  for (const auto& mesh : model_)
    mesh.render();
}
