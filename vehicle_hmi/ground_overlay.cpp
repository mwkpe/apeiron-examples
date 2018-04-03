#include "ground_overlay.h"


hmi::Ground_overlay::Ground_overlay() : line_array_{{
    -5.0f, 0.05f,  0.0f,
     5.0f, 0.05f,  0.0f,
     0.0f, 0.05f, -5.0f,
     0.0f, 0.05f,  5.0f
  }, false, 2.0f}
{
}
