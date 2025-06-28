#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "caldera/ecs/ecs.h"

void render_system_init();

void render_system_free();

void render_system_draw(const world *r);

#endif //RENDER_SYSTEM_H
