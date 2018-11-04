#include "vehicle.h"


void example::Vehicle::load_model(std::string_view filename, int flags)
{
  model_.load(filename, flags);
  bounding_box_.set_line_width(2.0f);
}


void example::Vehicle::load_texture(std::string_view filename)
{
  texture_.load(filename);
}
