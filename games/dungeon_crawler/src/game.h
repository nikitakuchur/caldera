#ifndef GAME_H
#define GAME_H

#include "caldera/defines.h"

void game_init();

void game_free();

void game_update(f32 delta_time);

void game_draw();

#endif //GAME_H
