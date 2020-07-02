#define RENDER_DISTANCE 1000

//Vector light = {.x = -150, .y = 300, .z = -50};
Vector light = {.x = 0, .y = 0, .z = 0};

Primitive sphere1 = {.center = {.x = 30, .y = 15, .z = 130}, .radius = 50, .color = COLOR_RED};
Primitive sphere2 = {.center = {.x = -15, .y = -10, .z = 67.5}, .radius = 25, .color = COLOR_GREEN};
Primitive sphere3 = {.center = {.x = -50, .y = -5, .z = 110}, .radius = 30, .color = COLOR_BLUE};
Primitive* primitives [] = {&sphere1, &sphere2, &sphere3};