#ifndef HMI_DEVIATION_GAUGE_H
#define HMI_DEVIATION_GAUGE_H


#include <glm/glm.hpp>
#include "engine/text.h"
#include "opengl/charset.h"
#include "opengl/renderer.h"


namespace hmi {


class Deviation_gauge final
{
public:
  Deviation_gauge(apeiron::opengl::Charset* charset);
  void set_value(float deviation);
  void render(apeiron::opengl::Renderer& renderer) const;

private:
  float deviation_ = 0.0f;
  glm::vec4 deviation_color_ = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f};
  apeiron::opengl::Charset* charset_ = nullptr;
  apeiron::engine::Text deviation_header_text_;
  apeiron::engine::Text deviation_text_;
  apeiron::engine::Text deviation_unit_text_;
};


}  // namespace hmi


#endif  // HMI_DEVIATION_GAUGE_H