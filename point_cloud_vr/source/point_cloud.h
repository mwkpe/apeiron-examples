#ifndef EXAMPLE_POINT_CLOUD_H
#define EXAMPLE_POINT_CLOUD_H


#include "engine/entity.h"
#include "opengl/points.h"


namespace example {


class Point_cloud final : public apeiron::engine::Entity
{
public:
  void load_data(std::string_view filename);
  void set_point_size(float size) { points_.set_size(size); }
  void render() const override;

private:
  apeiron::opengl::Points points_;
};


}  // namespace example


#endif  // EXAMPLE_POINT_CLOUD_H
