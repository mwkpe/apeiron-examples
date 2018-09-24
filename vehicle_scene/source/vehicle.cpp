#include "vehicle.h"


void example::Vehicle::load_model(std::string_view filename, int flags)
{
  model_.load(filename, flags);
}


void example::Vehicle::load_texture(std::string_view filename)
{
  texture_.load(filename);
}
