#ifndef RENDERER_H
#define RENDERER_H

#include <math/types.h>

typedef struct sprite {
    vec2 position;
    vec2 origin;
    vec2 scale;
    vec4 color;
} sprite;

void renderer_init();

void renderer_begin();

void renderer_set_viewport(int width, int height);

void renderer_draw_sprite(sprite s);

void renderer_end();

void renderer_destroy();

#endif //RENDERER_H
