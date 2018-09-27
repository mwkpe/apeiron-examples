#include "piece.h"


example::chess::Piece::Piece(Type type, const apeiron::opengl::Model* model)
    : type_{type}, model_{model}
{
}
