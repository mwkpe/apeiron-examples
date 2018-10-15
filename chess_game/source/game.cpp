#include "game.h"


#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/model_flags.h"


namespace {


constexpr float tile_size = 1.0f;
constexpr float board_size = tile_size * 8.0f;
constexpr float board_height = 0.25f;
constexpr float tile_center = tile_size / 2.0f;
constexpr float board_center = board_size / 2.0f;


inline glm::vec3 as_world_position(std::size_t board_index)
{
  return {(board_index % 8) - board_center + tile_center, board_height,
      board_center - board_index / 8 - tile_center};
}


inline std::optional<std::size_t> as_board_index(float x, float y)
{
  if (x > -4.0f && x < 4.0f && y > -4.0f && y < 4.0f) {
    const auto col = static_cast<std::size_t>(std::floor(x + 4.0f));
    const auto row = static_cast<std::size_t>(std::floor(4.0f - y));
    return row * 8ul + col;
  }

  return std::nullopt;
}


}  // namespace


example::chess::Game::Game(const Options* options)
    : options_{options},
      roboto_mono_{16, 8, 32},
      camera_{-47.0f, -55.0f, {7.5f, 10.0f, 7.5f}},
      axes_{16, 0.01f, 25.0f},
      ground_{{32.0f, 32.0f}, 32, 32, {0.25f, 0.25f, 0.25f, 1.0f}, 1.0f},
      light_{&bulb_},
      board_{{board_size, board_height, board_size}},
      field_{}
{
}


void example::chess::Game::init()
{
  renderer_.init();
  auto aspect_ratio = static_cast<float>(options_->window_width) / options_->window_height;
  renderer_.preset_projection(glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 500.0f));

  roboto_mono_.load_texture("assets/roboto_mono.png");

  {
    namespace mf = apeiron::engine::model_flags;
    bulb_.load("assets/bulb.obj", mf::vertices);
    piece_models_[Piece::Type::Pawn].load("assets/pawn.obj", mf::vertices | mf::normals);
    piece_models_[Piece::Type::Rook].load("assets/rook.obj", mf::vertices | mf::normals);
    piece_models_[Piece::Type::Knight].load("assets/knight.obj", mf::vertices | mf::normals);
    piece_models_[Piece::Type::Bishop].load("assets/bishop.obj", mf::vertices | mf::normals);
    piece_models_[Piece::Type::Queen].load("assets/queen.obj", mf::vertices | mf::normals);
    piece_models_[Piece::Type::King].load("assets/king.obj", mf::vertices | mf::normals);
  }

  place_pieces();

  light_.set_position(0.0f, 8.0f, 0.0f);
  light_.set_color(1.0f, 1.0f, 1.0f);
  renderer_.set_light_color(light_.color());
  renderer_.set_light_position(light_.position());
}


void example::chess::Game::update([[maybe_unused]] float time, float delta_time,
    const std::vector<apeiron::engine::Event>& events, const apeiron::engine::Input* input)
{
  for (const auto& event : events)
    std::visit(*this, event);

  if (input) {
    if (!options_->show_menu) {
      update_camera(delta_time, input);
    }
  }
}


void example::chess::Game::render()
{
  frame_++;

  renderer_.preset_view(camera_.view());
  renderer_.set_view_projection();
  renderer_.set_wireframe(options_->wireframe); 
  renderer_.set_lighting(options_->lighting);

  renderer_.use_color_shading();
  for (const auto& piece : field_) {
    if (piece) {
      renderer_.render(*piece, piece->chess_color() == Piece::Chess_color::White ?
          options_->white_color : options_->black_color);
    }
  }

  renderer_.use_vertex_color_shading();
  board_.render(renderer_, options_);

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


void example::chess::Game::update_camera(float delta_time, const apeiron::engine::Input* input)
{
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


void example::chess::Game::place_pieces()
{
  using Pt = Piece::Type;
  const std::array<Piece::Type, 8> lineup { Pt::Rook, Pt::Knight, Pt::Bishop, Pt::Queen,
      Pt::King, Pt::Bishop, Pt::Knight, Pt::Rook };

  auto color = Piece::Chess_color::White;
  std::size_t index = 0;
  for (auto piece_type : lineup) {
    field_[index] = Piece{piece_type, color, &piece_models_[piece_type]};
    field_[index]->set_position(as_world_position(index));
    index++;
  }

  // Make knights face the opponent
  field_[1]->set_rotation(0.0f, glm::radians(-180.0f), 0.0f);
  field_[6]->set_rotation(0.0f, glm::radians(-180.0f), 0.0f);

  while (index < 16) {
    field_[index] = Piece{Pt::Pawn, color, &piece_models_[Pt::Pawn]};
    field_[index]->set_position(as_world_position(index));
    index++;
  }

  color = Piece::Chess_color::Black;
  index = 48;

  while (index < 56) {
    field_[index] = Piece{Pt::Pawn, color, &piece_models_[Pt::Pawn]};
    field_[index]->set_position(as_world_position(index));
    index++;
  }

  for (auto piece_type : lineup) {
    field_[index] = Piece{piece_type, color, &piece_models_[piece_type]};
    field_[index]->set_position(as_world_position(index));
    index++;
  }
}


std::vector<std::size_t> example::chess::Game::allowed_moves(std::size_t board_index,
    Piece::Type piece_type, Piece::Chess_color chess_color) const
{
  std::vector<std::size_t> allowed_moves;

  auto add_moves = [&](int steps, const int step_size) {
    int index = static_cast<int>(board_index) + step_size;
    while (steps-- > 0 && index >= 0 && index < 64) {
      if (!field_[index]) {
        allowed_moves.push_back(index);
      }
      else if (field_[index]->chess_color() != chess_color &&
          !(piece_type == Piece::Type::Pawn && std::abs(step_size) == 8)) {
        allowed_moves.push_back(index);
        return;
      }
      else return;
      index += step_size;
    }
  };

  const int up_steps = (field_.size() - board_index) / 8;
  const int down_steps = board_index / 8;
  const int left_steps = board_index % 8;
  const int right_steps = 8 - (board_index % 8) - 1;

  switch (piece_type) {
    case Piece::Type::Pawn: {
      auto add_kill_move = [this, &allowed_moves, chess_color](auto index, bool can_move) {
        if (can_move && field_[index] && field_[index]->chess_color() != chess_color)
          allowed_moves.push_back(index);
      };
      switch (chess_color) {
        case Piece::Chess_color::White:
          add_moves(board_index / 8 == 1 ? 2 : 1, 8);
          add_kill_move(board_index + 7, up_steps && left_steps);
          add_kill_move(board_index + 9, up_steps && right_steps);
          break;
        case Piece::Chess_color::Black:
          add_moves(board_index / 8 == 6 ? 2 : 1, -8);
          add_kill_move(board_index - 7, down_steps && right_steps);
          add_kill_move(board_index - 9, down_steps && left_steps);
          break;
      }
    } break;
    case Piece::Type::Rook: {
      add_moves(up_steps, 8);
      add_moves(down_steps, -8);
      add_moves(right_steps, 1);
      add_moves(left_steps, -1);
    } break;
    case Piece::Type::Knight: {
    } break;
    case Piece::Type::Bishop: {
      add_moves(left_steps, 7);
      add_moves(right_steps, 9);
      add_moves(right_steps, -7);
      add_moves(left_steps, -9);
    } break;
    case Piece::Type::Queen: {
      add_moves(up_steps, 8);
      add_moves(down_steps, -8);
      add_moves(right_steps, 1);
      add_moves(left_steps, -1);
      add_moves(left_steps, 7);
      add_moves(right_steps, 9);
      add_moves(right_steps, -7);
      add_moves(left_steps, -9);
    } break;
    case Piece::Type::King: {
    } break;
    default: return {};
  }

  return allowed_moves;
}


void example::chess::Game::operator()(const apeiron::engine::Mouse_motion_event& event)
{
  using namespace apeiron::engine::collision;
  float norm_x = static_cast<float>(event.x) / options_->window_width * 2.0f - 1.0f;
  float norm_y = -(static_cast<float>(event.y) / options_->window_height * 2.0f - 1.0f);
  Ray ray = screen_raycast(norm_x, norm_y, renderer_.inverse_view_projection());
  Plane plane{{0.0f, board_height, 0.0f}, {0.0f, 1.0f, 0.0f}};

  board_.clear_current();
  if (auto point = intersection_point(ray, plane)) {
    if (auto index = as_board_index(point->x, point->z))
      board_.set_current(*index);
  }
}


void example::chess::Game::operator()(const apeiron::engine::Mouse_button_down_event& event)
{
  using namespace apeiron::engine::collision;

  float norm_x = static_cast<float>(event.x) / options_->window_width * 2.0f - 1.0f;
  float norm_y = -(static_cast<float>(event.y) / options_->window_height * 2.0f - 1.0f);
  Ray ray = screen_raycast(norm_x, norm_y, renderer_.inverse_view_projection());
  Plane plane{{0.0f, board_height, 0.0f}, {0.0f, 1.0f, 0.0f}};

  if (auto point = intersection_point(ray, plane)) {
    if (auto index = as_board_index(point->x, point->z)) {
      if (auto piece = field_[*index]; !board_.selected_index() && piece) {
        board_.set_selected(*index);
        board_.clear_allowed();
        for (const auto i : allowed_moves(*index, piece->type(), piece->chess_color()))
          board_.set_allowed(i, true);
      }
      else if (auto selected_index = board_.selected_index(); selected_index &&
          board_.allowed(*index)) {
        field_[*index] = field_[*selected_index];
        field_[*index]->set_position(as_world_position(*index));
        field_[*selected_index] = std::nullopt;
        board_.clear_selected();
        board_.clear_allowed();
      }
    }
    else {
      board_.clear_selected();
      board_.clear_allowed();
    }
  }
  else {
    board_.clear_selected();
    board_.clear_allowed();
  }
}


void example::chess::Game::operator()([[maybe_unused]] const apeiron::engine::Mouse_button_up_event& event)
{
}


void example::chess::Game::operator()([[maybe_unused]] const apeiron::engine::Mouse_wheel_event& event)
{
}
