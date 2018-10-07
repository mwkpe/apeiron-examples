#ifndef EXAMPLE_CHESS_MENU_H
#define EXAMPLE_CHESS_MENU_H


#include "opengl/gui.h"
#include "options.h"


namespace example::chess {


class Menu final : public apeiron::opengl::Gui
{
public:
  Menu(SDL_Window* window, SDL_GLContext context) : apeiron::opengl::Gui{window, context} {}
  void setup(Options* options);
  void build(Options* options, float time);
};


}  // namespace example::chess


#endif  // EXAMPLE_CHESS_MENU_H
