#include "game.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/model_flags.h"


example::chess::Game::Game(const Options* options)
    : options_{options},
      roboto_mono_{16, 8, 32},
      camera_{-45.0f, -145.0f, {7.5f, 10.0f, 7.5f}},
      axes_{16, 0.01f, 25.0f},
      ground_{{32.0f, 32.0f}, 33, 33, {0.33f, 0.33f, 0.33f, 1.0f}, 1.0f},
      light_{&bulb_},
      board_{{8.0f, 0.25f, 8.0f}},
      pawn_{Piece::Type::Pawn},
      queen_{Piece::Type::Queen},
      king_{Piece::Type::King}
{
}


void example::chess::Game::init()
{
  renderer_.init();
  auto aspect_ratio = static_cast<float>(options_->window_width) / options_->window_height;
  renderer_.set_projection(glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 500.0f));

  roboto_mono_.load_texture("assets/roboto_mono.png");

  {
    namespace mf = apeiron::engine::model_flags;
    bulb_.load("assets/bulb.obj", mf::vertices);
    piece_models_[Piece::Type::Pawn].load("assets/pawn.obj", mf::vertices | mf::normals);
    piece_models_[Piece::Type::Queen].load("assets/queen.obj", mf::vertices | mf::normals);
    piece_models_[Piece::Type::King].load("assets/king.obj", mf::vertices | mf::normals);
  }

  pawn_.set_model(&piece_models_[Piece::Type::Pawn]);
  pawn_.set_position(1.5f, board_.size().y, 1.5f);
  queen_.set_model(&piece_models_[Piece::Type::Queen]);
  queen_.set_position(0.5f, board_.size().y, -3.5f);
  king_.set_model(&piece_models_[Piece::Type::King]);
  king_.set_position(-1.5f, board_.size().y, 2.5f);

  teapot_.load_model();
  teapot_.set_position(-3.0f, 1.0f, 5.0f);
  teapot_.set_rotation(0.0f, glm::radians(-45.0f), 0.0f);

  light_.set_position(3.0f, 4.5f, 3.0f);
  light_.set_color(1.0f, 1.0f, 1.0f);
  renderer_.set_light_color(light_.color());
  renderer_.set_light_position(light_.position());
}


void example::chess::Game::update([[maybe_unused]] float time, float delta_time,
    const apeiron::engine::Input* input)
{
  if (input) {
    using Direction = apeiron::engine::Camera::Direction;
    auto distance = options_->camera_velocity * delta_time;
    if (input->forward)
      camera_.move(Direction::Forward, distance);
    if (input->backward)
      camera_.move(Direction::Backward, distance);
    if (input->left)
      camera_.move(Direction::Left, distance);
    if (input->right)
      camera_.move(Direction::Right, distance);

    camera_.orient(input->mouse_x_rel, input->mouse_y_rel, options_->camera_sensitivity);
  }

  teapot_.set_rotation(time * glm::radians(120.0f) * glm::vec3{0.0f, 0.2f, 0.2f});
}


void example::chess::Game::render()
{
  frame_++;

  renderer_.use_world_space();
  renderer_.set_view(camera_.view());
  renderer_.set_wireframe(options_->wireframe); 
  renderer_.set_lighting(options_->lighting);

  //renderer_.use_color_shading();
  //renderer_.render(teapot_, {1.0f, 1.0f, 1.0f, 1.0f});

  renderer_.use_color_shading();
  renderer_.render(pawn_, {0.882f, 0.156f, 0.521f, 1.0f});
  renderer_.render(queen_, {0.882f, 0.156f, 0.521f, 1.0f});
  renderer_.render(king_, {0.047f, 0.760f, 1.0f, 1.0f});

  renderer_.use_vertex_color_shading();
  board_.render(renderer_);

  renderer_.set_lighting(false);

  if (options_->show_axes) {
    axes_.render(renderer_);
  }

  if (options_->show_ground) {
    renderer_.use_vertex_color_shading();
    renderer_.render(ground_);
  }

  if (options_->show_light) {
    renderer_.set_wireframe(true);
    renderer_.use_color_shading();
    if (options_->lighting)
      renderer_.render(light_, light_.color());
    else
      renderer_.render(light_, {0.3f, 0.3f, 0.3f, 1.0f});
  }
}
