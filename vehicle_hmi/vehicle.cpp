#include "vehicle.h"


void hmi::Vehicle::load_model(std::string_view filename, int flags)
{
  model_.load(filename, flags);
}


void hmi::Vehicle::load_texture(std::string_view filename)
{
  texture_.load(filename);
}
