#ifndef HMI_GAUGE_H
#define HMI_GAUGE_H


#include "engine/entity.h"
#include "opengl/polygon.h"


namespace hmi {


class Gauge final : public apeiron::engine::Entity
{
public:
  Gauge(int points, float radius, float thickness);
  void set_start(std::uint32_t start) { start_ = start; }
  void set_count(std::uint32_t count) { count_ = count; }
  void render() const override;

private:
  std::uint32_t start_ = 0;
  std::uint32_t count_ = 0;
  std::uint32_t vertices_per_value_ = 0;
  apeiron::opengl::Polygon circle_;
};


}  // namespace hmi


#endif  // HMI_GAUGE_H
