#ifndef HMI_DEVIATION_ANIMATION_H
#define HMI_DEVIATION_ANIMATION_H


#include "engine/entity.h"
#include "opengl/triangles.h"


namespace hmi {


class Deviation_animation final : public apeiron::engine::Entity
{
public:
  Deviation_animation();
  void set_distance(float distance, float angle);
  void set_velocity(float velocity) { velocity_ = velocity; };
  void set_gap_size(float gap_size) { gap_size_ = gap_size; }
  float distance() const { return distance_; }
  float gap_size() const { return gap_size_; };
  float start() const { return start_; }
  void update(float delta_time);
  void render() const override;

private:
  float triangle_height_;
  float start_ = 0.0f;
  float gap_size_ = 5.0f;
  float distance_ = 0.0f;
  float velocity_ = 1.0f;
  apeiron::opengl::Triangles triangle_;
};


}  // namespace hmi


#endif  // HMI_DEVIATION_ANIMATION_H
