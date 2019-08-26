#include "hmd.h"


namespace {


glm::mat4 convert_matrix(const vr::HmdMatrix44_t& mat)
{
  return {
    mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
    mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
    mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
    mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]
  };
}


glm::mat4 convert_matrix(const vr::HmdMatrix34_t& mat)
{
  return {
    mat.m[0][0], mat.m[1][0], mat.m[2][0], 0.0f,
    mat.m[0][1], mat.m[1][1], mat.m[2][1], 0.0f,
    mat.m[0][2], mat.m[1][2], mat.m[2][2], 0.0f,
    mat.m[0][3], mat.m[1][3], mat.m[2][3], 1.0f
  };
}


glm::mat4 get_projection(vr::IVRSystem* vr_system, vr::Hmd_Eye eye)
{
  return convert_matrix(vr_system->GetProjectionMatrix(eye, 0.1f, 1000.0f));
}


glm::mat4 get_pose(vr::IVRSystem* vr_system, vr::Hmd_Eye eye)
{
  return glm::inverse(convert_matrix(vr_system->GetEyeToHeadTransform(eye)));
}


}  // namespace


void example::Hmd::init()
{
  vr::EVRInitError vr_error = vr::VRInitError_None;
  vr_system_ = vr::VR_Init(&vr_error, vr::VRApplication_Scene);

  if (vr_error != vr::VRInitError_None) {
    throw Hmd_error{"Error initializing VR runtime"};
  }

  if (vr_compositor_ = vr::VRCompositor(); !vr_compositor_) {
    throw Hmd_error{"Error initializing VR compositor"};
  }

  eye_pose_left_ = get_pose(vr_system_, vr::Eye_Left);
  eye_pose_right_ = get_pose(vr_system_, vr::Eye_Right);
  eye_projection_left_ = get_projection(vr_system_, vr::Eye_Left);
  eye_projection_right_ = get_projection(vr_system_, vr::Eye_Right);
}


void example::Hmd::update_poses()
{
  vr_compositor_->WaitGetPoses(device_poses_, vr::k_unMaxTrackedDeviceCount, nullptr, 0);

  for (std::uint32_t device=0; device<vr::k_unMaxTrackedDeviceCount; ++device) {
    if (device_poses_[device].bPoseIsValid) {
      device_pose_matrices_[device] = convert_matrix(device_poses_[device].mDeviceToAbsoluteTracking);
    }
  }

  if (device_poses_[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid) {
    pose_ = glm::inverse(device_pose_matrices_[vr::k_unTrackedDeviceIndex_Hmd]);
  }
}


void example::Hmd::submit_frame(vr::EVREye eye, std::uint32_t texture_id)
{
  vr::Texture_t texture = {(void*)(std::uintptr_t)texture_id,
      vr::TextureType_OpenGL, vr::ColorSpace_Gamma};
  vr_compositor_->Submit(eye, &texture);
}
