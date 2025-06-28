#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct texture {
    int id;
    int width;
    int height;
    void *platform_texture;
} texture;

void texture_init_empty(texture *texture);

void texture_init(texture *texture, const char *filename);

void texture_free(texture *texture);

#endif //TEXTURE_H
