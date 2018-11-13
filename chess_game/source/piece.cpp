#include "piece.h"


example::chess::Piece::Piece(Type type, Chess_color color, const apeiron::opengl::Model* model)
    : type_{type}, chess_color_{color}, model_{model}
{
}


void example::chess::Piece::render() const
{
	for (const auto& mesh : *model_)
		mesh.render();
}
