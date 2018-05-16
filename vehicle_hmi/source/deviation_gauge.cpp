#include "deviation_gauge.h"


#include <cmath>


hmi::Deviation_gauge::Deviation_gauge(apeiron::opengl::Charset* charset) : charset_{charset}
{
  auto pos = glm::vec3{-16.0f, 0.1f, 10.0f};
  auto plane_rotation = glm::vec3{glm::radians(-90.0f), 0.0f, 0.0f};

  deviation_header_text_.set_text("Position deviation");
  deviation_header_text_.set_position(pos.x-8.0f, pos.y-0.05f, pos.z-4.0f);
  deviation_header_text_.set_rotation(plane_rotation);
  deviation_header_text_.set_size(2.0f);
  deviation_header_text_.set_spacing(0.95f, 1.0f);
  deviation_text_.set_text("0m");
  deviation_text_.set_position(pos);
  deviation_text_.set_rotation(plane_rotation);
  deviation_text_.set_size(6.0f);
  deviation_text_.set_spacing(0.95f, 1.0f);
  deviation_unit_text_.set_text("meter");
  deviation_unit_text_.set_position(pos.x+3.0f, pos.y-0.05f, pos.z+3.5f);
  deviation_unit_text_.set_rotation(plane_rotation);
  deviation_unit_text_.set_size(2.0f);
  deviation_unit_text_.set_spacing(0.95f, 1.0f);
}


void hmi::Deviation_gauge::set_value(float deviation)
{
  deviation_ = deviation;
  auto dev = static_cast<int>(std::round(deviation_));
  deviation_text_.set_text(std::to_string(dev));

  if (dev <= 0)
    deviation_text_.set_text(std::to_string(dev));
  else
    deviation_text_.set_text(std::string{"+"} + std::to_string(dev));

  if (dev != 0)
    deviation_text_.set_position(-16.0f - charset_->character_width() *
        deviation_text_.size() * deviation_text_.spacing().x, 0.1f, 10.0f);
  else
    deviation_text_.set_position(-16.0f, 0.1f, 10.0f);

  if (std::abs(deviation) < 5)
    deviation_color_ = glm::vec4{0.0f, 0.717f, 0.215f, 1.0f};
  else if (std::abs(deviation) < 15)
    deviation_color_ = glm::vec4{1.0f, 0.839f, 0.0f, 1.0f};
  else
  deviation_color_ = glm::vec4{0.956f, 0.317f, 0.117f, 1.0f};
}


void hmi::Deviation_gauge::render(apeiron::opengl::Renderer& renderer) const
{
  renderer.set_lighting(false);
  renderer.use_color_shading();
  renderer.render(deviation_header_text_, *charset_, glm::vec4{0.5f, 0.5f, 0.5f, 1.0f});
  renderer.render(deviation_unit_text_, *charset_, glm::vec4{0.5f, 0.5f, 0.5f, 1.0f});
  renderer.render(deviation_text_, *charset_, deviation_color_);
}
