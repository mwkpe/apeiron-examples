#ifndef EXAMPLE_CHESS_GAME_H
#define EXAMPLE_CHESS_GAME_H


#include <cstdint>
#include <vector>
#include <map>
#include "engine/input.h"
#include "engine/camera.h"
#include "engine/text.h"
#include "opengl/model.h"
#include "opengl/renderer.h"
#include "prefab/axes.h"
#include "prefab/light.h"
#include "prefab/ground.h"
#include "prefab/teapot.h"
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
  const Options* options_;
  apeiron::opengl::Renderer renderer_;
  apeiron::opengl::Tileset roboto_mono_;
  apeiron::opengl::Model bulb_;
  std::map<Piece::Type, apeiron::opengl::Model> piece_models_;
  apeiron::engine::Camera camera_;
  apeiron::prefab::Axes axes_;
  apeiron::prefab::Ground ground_;
  apeiron::prefab::Light light_;
  apeiron::prefab::Teapot teapot_;
  Board board_;
  Piece pawn_;
  Piece queen_;
  Piece king_;
  int frame_ = 0;
};


}  // namespace example::chess


#endif  // EXAMPLE_CHESS_GAME_H