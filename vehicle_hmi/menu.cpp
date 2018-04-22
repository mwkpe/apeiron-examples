#include "menu.h"


#include <array>
#include "GL/glew.h"
#include <glm/glm.hpp>
#include "imgui/imgui.h"


namespace {


void set_style(ImGuiStyle& style)
{
  style.WindowPadding = ImVec2{8, 8};
  style.WindowRounding = 0.0f;
  style.WindowBorderSize = 0.0f;
  style.FramePadding = ImVec2{3, 3};
  style.FrameRounding = 0.0f;
  style.FrameBorderSize = 0.0f;
  style.ItemSpacing = ImVec2{12, 8};
  style.ItemInnerSpacing = ImVec2{8, 6};
  style.IndentSpacing = 25.0f;
  style.ScrollbarSize = 15.0f;
  style.ScrollbarRounding = 9.0f;
  style.GrabMinSize = 5.0f;
  style.GrabRounding = 5.0f;

  ImVec4 almostblack{0.03f, 0.03f, 0.03f, 1.0f};
  ImVec4 blackglass{0.05f, 0.05f, 0.05f, 0.9f};
  ImVec4 darkgrey{0.15f, 0.15f, 0.15f, 0.9f};
  ImVec4 grey{0.2f, 0.2f, 0.2f, 0.9f};
  ImVec4 lightgrey{0.4f, 0.4f, 0.4f, 0.9f};

  style.Colors[ImGuiCol_WindowBg] = blackglass;
  style.Colors[ImGuiCol_FrameBg] = darkgrey;
  style.Colors[ImGuiCol_FrameBgHovered] = grey;
  style.Colors[ImGuiCol_FrameBgActive] = grey;
  style.Colors[ImGuiCol_TextDisabled] = grey;
  style.Colors[ImGuiCol_TitleBg] = darkgrey;
  style.Colors[ImGuiCol_TitleBgCollapsed] = darkgrey;
  style.Colors[ImGuiCol_TitleBgActive] = grey;
  style.Colors[ImGuiCol_ResizeGrip] = darkgrey;
  style.Colors[ImGuiCol_ResizeGripHovered] = lightgrey;
  style.Colors[ImGuiCol_SliderGrab] = almostblack;
  style.Colors[ImGuiCol_SliderGrabActive] = lightgrey;
  style.Colors[ImGuiCol_Button] = darkgrey;
  style.Colors[ImGuiCol_ButtonHovered] = grey;
  style.Colors[ImGuiCol_ButtonActive] = lightgrey;
}


void set_main_color(ImGuiStyle& style, ImVec4 color)
{
  style.Colors[ImGuiCol_Border] = color;
  style.Colors[ImGuiCol_Text] = color;
  style.Colors[ImGuiCol_CheckMark] = color;
  style.Colors[ImGuiCol_ResizeGripActive] = color;
}


}  // namespace


void hmi::Menu::setup(Options* options)
{
  ImGui::StyleColorsDark();
  set_style(ImGui::GetStyle());
  const auto& color = options->main_color;
  set_main_color(ImGui::GetStyle(), ImVec4{color.r, color.g, color.b, color.a});
}


void hmi::Menu::build(Options* options, float time)
{
  auto& io = ImGui::GetIO();

  create_frame();
  {
    ImGui::Begin("Debug view");
    ImGui::Text("Runtime: %.0f s", time);
    ImGui::Text("Framerate: %.0f fps", io.Framerate);
    ImGui::Text("Frametime: %.1f ms", 1000.0f / io.Framerate);
    ImGui::Text("Rendering");
    ImGui::Checkbox("Framerate limit", &options->limit_fps);
    ImGui::SliderInt("FPS", &options->max_fps, 30, 240);
    ImGui::Checkbox("Wireframe", &options->wireframe);
    ImGui::SameLine();
    ImGui::Checkbox("Lighting", &options->lighting);
    ImGui::SameLine();
    ImGui::Checkbox("Bounding boxes", &options->bounding_boxes);
    ImGui::Checkbox("Ground", &options->ground);
    ImGui::SameLine();
    ImGui::Checkbox("Road", &options->road);
    ImGui::Checkbox("Ground overlay", &options->ground_overlay);
    ImGui::SameLine();
    ImGui::Checkbox("Animate overlay", &options->animate_overlay);
    ImGui::Text("Velocity");
    ImGui::SliderFloat("Vehicle (m/s)", &options->vehicle_velocity, -10.0f, 55.5f);
    ImGui::SliderFloat("Target (m/s)", &options->target_velocity, -10.0f, 55.5f);
    ImGui::Text("Deviation");
    ImGui::SliderFloat("Position (m)", &options->position_deviation, -150.0f, 50.0f);
    ImGui::SliderFloat("Lane (m)", &options->lane_deviation, -10.0f, 10.0f);
    ImGui::Text("Camera");
    ImGui::SliderFloat("Velocity (m/s)", &options->camera_velocity, 0.0f, 20.0f);
    ImGui::SliderFloat("Sensitivity", &options->camera_sensitivity, 0.0f, 0.1f);
    if (ImGui::Button("Quit"))
      options->quit = true;
    ImGui::End();

    ImGui::Begin("Networking");
    static std::array<char, 32> ip{"192.168.1.100"};
    int port = options->port;
    ImGui::InputText("IP", ip.data(), sizeof(ip));
    options->ip = ip.data();
    ImGui::InputInt("Port", &port);
    options->port = static_cast<std::uint16_t>(port);
    if (ImGui::Button("Connect")) {
    }
    ImGui::End();
  }
}
