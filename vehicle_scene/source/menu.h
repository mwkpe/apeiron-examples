#ifndef EXAMPLE_MENU_H
#define EXAMPLE_MENU_H


#include "opengl/gui.h"
#include "options.h"


namespace example {


class Menu final : public apeiron::opengl::Gui
{
public:
  Menu(SDL_Window* window) : apeiron::opengl::Gui{window} {}
  void setup(Options* options);
  void build(Options* options, float time);
};


}  // namespace example


#endif  // EXAMPLE_MENU_H
