#ifndef EXAMPLE_CHESS_PIECE_H
#define EXAMPLE_CHESS_PIECE_H


#include "engine/entity.h"
#include "opengl/model.h"


namespace example::chess {


class Piece final : public apeiron::engine::Entity
{
public:
  enum class Type { Pawn, Knight, Bishop, Rook, Queen, King };
  explicit Piece(Type type, const apeiron::opengl::Model* model = nullptr);
  void set_model(const apeiron::opengl::Model* model) { model_ = model; }
  void render() const override { model_->render(); }

private:
  Type type_ = Type::Pawn;
  const apeiron::opengl::Model* model_ = nullptr;
};


}  // namespace example::chess


#endif  // EXAMPLE_CHESS_PIECE_H
