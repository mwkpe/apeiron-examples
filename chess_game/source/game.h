#ifndef EXAMPLE_CHESS_GAME_H
#define EXAMPLE_CHESS_GAME_H


#include <cstddef>
#include <cstdint>
#include <array>
#include <vector>
#include <map>
#include "opengl/model.h"
#include "opengl/renderer.h"
#include "engine/input.h"
#include "engine/event.h"
#include "engine/camera.h"
#include "engine/text.h"
#include "prefab/axes.h"
#include "prefab/light.h"
#include "prefab/ground.h"
#include "options.h"
#include "board.h"
#include "piece.h"


namespace example::chess {


class Game final
{
public:
  Game(const Options* options);
  void init();
  void update(float time, float delta_time, const std::vector<apeiron::engine::Event>& events,
      const apeiron::engine::Input* input = nullptr);
  void render();

  // Event handling
  void operator()(const apeiron::engine::Mouse_motion_event& event);
  void operator()(const apeiron::engine::Mouse_button_down_event& event);
  void operator()(const apeiron::engine::Mouse_button_up_event& event);
  void operator()(const apeiron::engine::Mouse_wheel_event& event);

private:
  void update_camera(float delta_time, const apeiron::engine::Input* input);
  void place_pieces();
  std::vector<std::size_t> allowed_moves(std::size_t board_index, Piece::Type piece_type,
      Piece::Chess_color chess_color) const;

  const Options* options_;
  apeiron::opengl::Renderer renderer_;
  apeiron::opengl::Tileset roboto_mono_;
  apeiron::opengl::Model bulb_;
  std::map<Piece::Type, apeiron::opengl::Model> piece_models_;
  apeiron::engine::Camera camera_;
  apeiron::prefab::Axes axes_;
  apeiron::prefab::Ground ground_;
  apeiron::prefab::Light light_;
  Board board_;
  std::array<std::optional<Piece>, 64> field_;
  int frame_ = 0;
};


}  // namespace example::chess


#endif  // EXAMPLE_CHESS_GAME_H
