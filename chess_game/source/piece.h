#ifndef EXAMPLE_CHESS_PIECE_H
#define EXAMPLE_CHESS_PIECE_H


#include "engine/entity.h"
#include "opengl/model.h"


namespace example::chess {


class Piece final : public apeiron::engine::Entity
{
public:
  enum class Type { Pawn, Knight, Bishop, Rook, Queen, King };
  enum class Chess_color { White, Black };
  explicit Piece(Type type, Chess_color color, const apeiron::opengl::Model* model = nullptr);
  void set_model(const apeiron::opengl::Model* model) { model_ = model; }
  void set_type(Type type) { type_ = type; }
  void set_chess_color(Chess_color color) { chess_color_ = color; }
  Type type() const { return type_; }
  Chess_color chess_color() const { return chess_color_; }
  void render() const override;

private:
  Type type_ = Type::Pawn;
  Chess_color chess_color_ = Chess_color::White;
  const apeiron::opengl::Model* model_ = nullptr;
};


}  // namespace example::chess


#endif  // EXAMPLE_CHESS_PIECE_H
