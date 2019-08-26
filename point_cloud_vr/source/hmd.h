#ifndef EXAMPLE_HMD_H
#define EXAMPLE_HMD_H


#include <stdexcept>
#include <glm/glm.hpp>
#include <openvr_mingw.h>


namespace example {


class Hmd_error : public std::runtime_error
{
public:
  explicit Hmd_error(const std::string& s) : std::runtime_error{s} {}
  explicit Hmd_error(const char* s) : std::runtime_error{s} {}
};


struct Hmd_settings
{
  int render_width;
  int render_height;
  int msaa_samples;
};


class Hmd final
{
public:
  Hmd() = delete;
  Hmd(const Hmd_settings& settings) : settings_{settings} {}
  void init();
  void update_poses();
  void submit_frame(vr::EVREye eye, std::uint32_t texture_id);
  Hmd_settings settings() const { return settings_; }
  glm::mat4 pose() const { return pose_; }
  glm::mat4 eye_pose_left() const { return eye_pose_left_; }
  glm::mat4 eye_pose_right() const { return eye_pose_right_; }
  glm::mat4 eye_projection_left() const { return eye_projection_left_; }
  glm::mat4 eye_projection_right() const { return eye_projection_right_; }

private:
  Hmd_settings settings_;
  vr::IVRSystem* vr_system_ = nullptr;
  vr::IVRCompositor* vr_compositor_ = nullptr;
  vr::TrackedDevicePose_t device_poses_[vr::k_unMaxTrackedDeviceCount];
  glm::mat4 device_pose_matrices_[vr::k_unMaxTrackedDeviceCount];
  glm::mat4 pose_;
  glm::mat4 eye_pose_left_;
  glm::mat4 eye_pose_right_;
  glm::mat4 eye_projection_left_;
  glm::mat4 eye_projection_right_;
};


}  // namespace example


#endif  // EXAMPLE_HMD_H
