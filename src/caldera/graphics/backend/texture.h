#ifndef TEXTURE_H
#define TEXTURE_H

#include "caldera/math/ivec2.h"

typedef struct texture {
    i32 id;
    ivec2 size;
    void *platform_texture;
} texture;

void texture_init_empty(texture *texture);

void texture_init(texture *texture, const char *filename);

void texture_free(texture *texture);

#endif //TEXTURE_H
