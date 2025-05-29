#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct texture {
    int id;
    int width;
    int height;
    void *platform_texture;
} texture;

texture texture_create_empty();

texture texture_create(const char *filename);

void texture_destroy(texture texture);

#endif //TEXTURE_H
