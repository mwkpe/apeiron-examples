#ifndef HMI_MENU_H
#define HMI_MENU_H


#include "opengl/gui.h"
#include "options.h"


namespace hmi {


class Menu final : public apeiron::opengl::Gui
{
public:
  Menu(SDL_Window* window) : apeiron::opengl::Gui{window} {}
  void setup(Options* options);
  void build(Options* options, float time);
};


}  // hmi


#endif  // HMI_MENU_H
