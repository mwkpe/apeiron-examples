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
  void update(float time, float delta_time, const apeiron::engine::Input* input = nullptr);
  void render();

private:
  void update_camera(float delta_time, const apeiron::engine::Input* input);
  void handle_mouse_click(int x, int y);
  void place_pieces();
  std::vector<std::size_t> allowed_tiles(std::size_t board_index, Piece::Type piece_type,
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
  std::optional<std::size_t> selected_index_;
  bool mouse_left_pressed_ = false;
  int frame_ = 0;
};


}  // namespace example::chess


#endif  // EXAMPLE_CHESS_GAME_H
