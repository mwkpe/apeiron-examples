#include "world.h"


#include <glm/gtc/matrix_transform.hpp>


example::World::World() : ground_{{200.0f, 200.0f}, 25, 25, {0.25f, 0.25f, 0.25f, 1.0f}}
{
}


void example::World::init(int window_width, int window_height, Hmd* hmd)
{
  hmd_ = hmd;

  window_width_ = window_width;
  window_height_ = window_height;
  auto aspect_ratio = static_cast<float>(window_width) / window_height;
  window_projection_ = glm::perspective(glm::radians(45.0f), aspect_ratio, 1.0f, 1000.0f);

  const auto& s = hmd_->settings();
  left_eye_.init(s.render_width, s.render_height, s.msaa_samples);
  right_eye_.init(s.render_width, s.render_height, s.msaa_samples);
  
  renderer_.init();
  renderer_.use_vertex_color_shading();
  renderer_.set_lighting(false);
  
  // Setup scene
  point_cloud_.load_data("MOUT_script3.xyzrgba");
  point_cloud_.set_point_size(1.0f);
  // Rotate point cloud z-up to opengl y-up
  point_cloud_.set_rotation(glm::vec3{glm::radians(-90.0f), 0.0f, 0.0f});
}


void example::World::update([[maybe_unused]] float time, [[maybe_unused]] float delta_time,
   [[maybe_unused]] const apeiron::engine::Input* input)
{
  hmd_->update_poses();
}


void example::World::render()
{
  frame_++;

  // Render companion window (in not the most efficient way)
  renderer_.set_viewport(0, 0, window_width_, window_height_);
  renderer_.preset_view(hmd_->pose());
  renderer_.preset_projection(window_projection_);
  renderer_.set_view_projection();
  render_scene();

  // Render VR
  const auto& s = hmd_->settings();
  renderer_.set_viewport(0, 0, s.render_width, s.render_height);

  // Render left eye
  renderer_.preset_view(hmd_->pose());
  renderer_.preset_projection(hmd_->eye_projection_left() * hmd_->eye_pose_left());
  renderer_.set_view_projection();
  left_eye_.bind();
  render_scene();
  left_eye_.blit();
  left_eye_.unbind();
  hmd_->submit_frame(vr::Eye_Left, left_eye_.texture_id());

  // Render right eye
  renderer_.preset_view(hmd_->pose());
  renderer_.preset_projection(hmd_->eye_projection_right() * hmd_->eye_pose_right());
  renderer_.set_view_projection();
  right_eye_.bind();
  render_scene();
  right_eye_.blit();
  right_eye_.unbind();
  hmd_->submit_frame(vr::Eye_Right, right_eye_.texture_id());
}


void example::World::render_scene()
{
  renderer_.clear(0.1f, 0.1f, 0.1f);
  renderer_.render(ground_);
  renderer_.render(point_cloud_);
}
