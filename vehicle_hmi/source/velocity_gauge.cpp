#include "velocity_gauge.h"


#include <cmath>


hmi::Velocity_gauge::Velocity_gauge(apeiron::opengl::Charset* charset) : gauge_{400, 7.0f, 0.6f}, charset_{charset}
{
  auto pos = glm::vec3{16.0f, 0.05f, 12.0f};
  auto plane_rotation = glm::vec3{glm::radians(-90.0f), 0.0f, 0.0f};

  gauge_.set_position(pos);
  gauge_.set_rotation(plane_rotation);
  gauge_.set_start(200);
  gauge_.set_start(75);

  velocity_text_.set_text("0");
  velocity_text_.set_size(6.0f);
  velocity_text_.set_spacing(0.95f, 1.0f);
  auto text_x = pos.x - charset->character_width() * velocity_text_.size() *
      velocity_text_.spacing().x;  // Center of three characters
  auto text_z = pos.z - charset->character_height() * velocity_text_.size() * 0.3f;
  velocity_text_.set_position(text_x, pos.y+0.1f, text_z);
  velocity_text_.set_rotation(plane_rotation);

  unit_text_.set_text("km/h");
  unit_text_.set_position(pos.x+2.0f, pos.y+0.05f, pos.z+1.5f);
  unit_text_.set_rotation(plane_rotation);
  unit_text_.set_size(2.0f);
  unit_text_.set_spacing(0.95f, 1.0f);
}


void hmi::Velocity_gauge::update(float velocity)
{
  velocity_ = velocity;

  auto cur_vel = static_cast<int>(std::round(velocity_ * 3.6f));
  velocity_text_.set_text(std::to_string(cur_vel));

  gauge_.set_start(static_cast<std::uint32_t>(cur_vel < 0 ? cur_vel + 200 : 200));
  gauge_.set_count(static_cast<std::uint32_t>(std::abs(cur_vel)));
}


void hmi::Velocity_gauge::render(apeiron::opengl::Renderer& renderer) const
{
  renderer.set_lighting(false);
  renderer.use_color_shading();
  renderer.render(gauge_, color_);
  renderer.render(unit_text_, *charset_, glm::vec4{0.5f, 0.5f, 0.5f, 1.0f});
  renderer.render(velocity_text_, *charset_, color_);
}
