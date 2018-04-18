#include "deviation_gauge.h"


#include <cmath>


hmi::Deviation_gauge::Deviation_gauge(apeiron::opengl::Charset* charset) : charset_{charset}
{
  deviation_header_text_.set_text("Position deviation");
  deviation_header_text_.set_position(-25.0f, 0.05f, 7.0f);
  deviation_header_text_.set_rotation(glm::radians(-90.0f), 0.0f, 0.0f);
  deviation_header_text_.set_size(2.0f);
  deviation_header_text_.set_spacing(0.95f, 1.0f);
  deviation_text_.set_text("0m");
  deviation_text_.set_position(-18.0f, 0.1f, 11.0f);
  deviation_text_.set_rotation(glm::radians(-90.0f), 0.0f, 0.0f);
  deviation_text_.set_size(5.0f);
  deviation_text_.set_spacing(0.95f, 1.0f);
  deviation_unit_text_.set_text("meter");
  deviation_unit_text_.set_position(-13.0f, 0.05f, 15.0f);
  deviation_unit_text_.set_rotation(glm::radians(-90.0f), 0.0f, 0.0f);
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
    deviation_text_.set_position(-18.0f - charset_->character_width() *
        deviation_text_.size() * deviation_text_.spacing().x, 0.1f, 11.0f);
  else
    deviation_text_.set_position(-18.0f, 0.1f, 11.0f);
}


void hmi::Deviation_gauge::render(apeiron::opengl::Renderer& renderer) const
{
  renderer.set_lighting(false);
  renderer.use_color_shading();
  renderer.render(deviation_header_text_, *charset_);
  renderer.render(deviation_unit_text_, *charset_);
  renderer.render(deviation_text_, *charset_);
}
