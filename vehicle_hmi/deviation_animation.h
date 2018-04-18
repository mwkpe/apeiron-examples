#ifndef HMI_DEVIATION_ANIMATION_H
#define HMI_DEVIATION_ANIMATION_H


#include "engine/entity.h"
#include "opengl/polygon.h"


namespace hmi {


class Deviation_animation final : public apeiron::engine::Entity
{
public:
  Deviation_animation();
  void set_deviation(float distance);
  float distance() const { return distance_; }
  float triangle_gap() const { return triangle_gap_; };
  float triangle_start() const { return triangles_start_; }
  void update(float delta_time);
  void render() const override;

private:
  float triangle_height_;
  float triangles_start_ = 0.0f;
  float triangle_gap_ = 5.0f;
  float distance_ = 0.0f;
  apeiron::opengl::Polygon triangle_;
};


}  // namespace hmi


#endif  // HMI_DEVIATION_ANIMATION_H
