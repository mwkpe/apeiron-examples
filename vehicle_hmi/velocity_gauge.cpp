#include "velocity_gauge.h"


#include <cmath>


hmi::Velocity_gauge::Velocity_gauge(apeiron::opengl::Charset* charset) : current_velocity_gauge_{400, 7.0f, 0.6f},
    target_velocity_gauge_{400, 7.6f, 0.6f}, target_velocity_notch_{400, 8.2f, 1.2f}, charset_{charset}
{
  auto pos = glm::vec3{16.0f, 0.05f, 12.0f};
  auto plane_rotation = glm::vec3{glm::radians(-90.0f), 0.0f, 0.0f};

  current_velocity_gauge_.set_position(pos);
  target_velocity_gauge_.set_position(pos);
  target_velocity_notch_.set_position(pos);

  current_velocity_gauge_.set_rotation(plane_rotation);
  target_velocity_gauge_.set_rotation(plane_rotation);
  target_velocity_notch_.set_rotation(plane_rotation);

  current_velocity_gauge_.set_start(200);
  current_velocity_gauge_.set_start(75);
  target_velocity_gauge_.set_start(200);
  target_velocity_gauge_.set_count(90);
  target_velocity_notch_.set_start(200);
  target_velocity_notch_.set_count(90);

  current_velocity_text_.set_text("0");
  current_velocity_text_.set_size(6.0f);
  current_velocity_text_.set_spacing(0.95f, 1.0f);
  auto text_x = pos.x - charset->character_width() * current_velocity_text_.size() *
      current_velocity_text_.spacing().x;  // Center of three characters
  auto text_z = pos.z - charset->character_height() * current_velocity_text_.size() * 0.3f;
  current_velocity_text_.set_position(text_x, pos.y+0.1f, text_z);
  current_velocity_text_.set_rotation(plane_rotation);

  target_velocity_text_.set_text("90");
  target_velocity_text_.set_size(4.0f);
  target_velocity_text_.set_spacing(0.95f, 1.0f);
  text_x = pos.x - charset->character_width() * target_velocity_text_.size() *
      target_velocity_text_.spacing().x;
  text_z = pos.z - charset->character_height() * target_velocity_text_.size() * 2.5f;
  target_velocity_text_.set_position(text_x, pos.y+0.1f, text_z);
  target_velocity_text_.set_rotation(plane_rotation);

  current_velocity_unit_text_.set_text("km/h");
  current_velocity_unit_text_.set_position(pos.x+2.0f, pos.y+0.05f, pos.z+1.5f);
  current_velocity_unit_text_.set_rotation(plane_rotation);
  current_velocity_unit_text_.set_size(2.0f);
  current_velocity_unit_text_.set_spacing(0.95f, 1.0f);
}


void hmi::Velocity_gauge::update(float current_velocity, float target_velocity)
{
  current_velocity_ = current_velocity;
  target_velocity_ = target_velocity;

  auto cur_vel = static_cast<int>(std::round(current_velocity_ * 3.6f));
  current_velocity_text_.set_text(std::to_string(cur_vel));

  current_velocity_gauge_.set_start(static_cast<std::uint32_t>(cur_vel < 0 ? cur_vel + 200 : 200));
  current_velocity_gauge_.set_count(static_cast<std::uint32_t>(std::abs(cur_vel)));

  auto tar_vel = std::max(0, static_cast<int>(std::round(target_velocity_ * 3.6f)));
  target_velocity_text_.set_text(std::to_string(tar_vel));

  tar_vel = std::max(0, tar_vel);
  tar_vel = std::min(200, tar_vel);
  target_velocity_gauge_.set_start(static_cast<std::uint32_t>(tar_vel < 0 ? tar_vel + 200 : 200));
  target_velocity_gauge_.set_count(static_cast<std::uint32_t>(std::abs(tar_vel)));
  target_velocity_notch_.set_start(static_cast<std::uint32_t>(tar_vel < 0 ? tar_vel + 195 + std::abs(tar_vel) : 195 + std::abs(tar_vel)));
  target_velocity_notch_.set_count(static_cast<std::uint32_t>(5));

  if (cur_vel < tar_vel) {
    current_velocity_color_ = glm::vec4{0.129f, 0.588f, 0.952f, 1.0f};
  }
  else {
    current_velocity_color_ = glm::vec4{0.956f, 0.317f, 0.117f, 1.0f};
  }
}


void hmi::Velocity_gauge::render(apeiron::opengl::Renderer& renderer) const
{
  renderer.set_lighting(false);
  renderer.use_color_shading();
  renderer.render(current_velocity_gauge_, current_velocity_color_);
  renderer.render(target_velocity_gauge_, glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
  renderer.render(target_velocity_notch_, glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
  renderer.render(target_velocity_text_, *charset_, glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
  renderer.render(current_velocity_unit_text_, *charset_, glm::vec4{0.5f, 0.5f, 0.5f, 1.0f});
  renderer.render(current_velocity_text_, *charset_, current_velocity_color_);
}
