#ifndef CUSTOM_COMPONENTS_H
#define CUSTOM_COMPONENTS_H

typedef enum {
    //DIR_RIGHT = 0,
    DIR_UP_RIGHT = 0,
    DIR_UP,
    DIR_UP_LEFT,
    //DIR_LEFT,
    DIR_DOWN_LEFT,
    DIR_DOWN,
    DIR_DOWN_RIGHT,
} direction;

typedef struct facing_direction {
    direction direction;
} facing_direction;

typedef struct player_controller {
    float walk_speed;
} player_controller;

enum custom_component_type {
    FACING_DIRECTION = 10,
    PLAYER_CONTROLLER
};

#endif //CUSTOM_COMPONENTS_H
