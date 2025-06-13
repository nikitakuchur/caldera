#include "game.h"

#include <stdio.h>

#include "caldera/ecs/ecs.h"
#include "caldera/ecs/components.h"
#include "caldera/ecs/systems/render_system.h"
#include "caldera/ecs/systems/animation_system.h"
#include "custom_components.h"
#include "systems/facing_system.h"
#include "systems/player_system.h"

static texture player_texture;
static registry r;

static void register_custom_components(registry *r) {
    ecs_register_component(r, FACING_DIRECTION, sizeof(facing_direction));
    ecs_register_component(r, PLAYER_CONTROLLER, sizeof(player_controller));
}

void game_init() {
    ecs_init(&r);
    register_custom_components(&r);

    render_system_init();

    player_texture = texture_create("../res/textures/character_v3.png");

    const size_t entity_1 = ecs_create_entity(&r);
    transform *t1 = ecs_add_component(&r, entity_1, TRANSFORM);
    *t1 = (transform){
        .position = {0, 0},
        .origin = {16, 2},
        .scale = {1, 1},
        .rotation = 0
    };

    sprite_renderer *sr1 = ecs_add_component(&r, entity_1, SPRITE_RENDERER);
    *sr1 = (sprite_renderer){
        .texture = player_texture,
        .size = {32, 32},
        .texture_rect = (irect){
            0, 96,
            32, 96,
            32, 96 + 32,
            0, 96 + 32
        },
        .color = {1, 1, 1, 1}
    };

    sprite_animator *sa = ecs_add_component(&r, entity_1, SPRITE_ANIMATOR);
    *sa = (sprite_animator){
        .animation = (animation){
            .x_offset = 0,
            .y_offset = 0,
            .frame_num = 3,
            .speed = 3.5f
        },
        .frame = 0
    };

    facing_direction *dir = ecs_add_component(&r, entity_1, FACING_DIRECTION);
    dir->direction = DIR_DOWN_LEFT;

    player_controller *controller = ecs_add_component(&r, entity_1, PLAYER_CONTROLLER);
    controller->walk_speed = 40.f;
    controller->forward_speed_multiplier = 1.2f;
    controller->backwards_speed_multiplier = 0.8f;

    const size_t entity_2 = ecs_create_entity(&r);
    transform *t2 = ecs_add_component(&r, entity_2, TRANSFORM);
    *t2 = (transform){
        .position = {-40, 0},
        .origin = {0, 0},
        .scale = {1, 1},
        .rotation = 0
    };

    sprite_renderer *sr2 = ecs_add_component(&r, entity_2, SPRITE_RENDERER);
    *sr2 = (sprite_renderer){
        .texture = player_texture,
        .size = {32, 32},
        .texture_rect = (irect){
            0, 0,
            32, 0,
            32, 32,
            0, 32
        },
        .color = {1, 1, 1, 1}
    };

    sprite_animator *sa2 = ecs_add_component(&r, entity_2, SPRITE_ANIMATOR);
    *sa2 = (sprite_animator){
        .animation = (animation){
            .x_offset = 0,
            .y_offset = 0,
            .frame_num = 3,
            .speed = 3.5f
        },
        .frame = 0
    };

    facing_direction *dir2 = ecs_add_component(&r, entity_2, FACING_DIRECTION);
    dir2->direction = DIR_DOWN_RIGHT;
}

void game_update(const float delta_time) {
    player_system_update(&r, delta_time);
    animation_system_update(&r, delta_time);
    facing_system_update(&r);
}

void game_draw() {
    render_system_draw(&r);
}

void game_destroy() {
    texture_destroy(player_texture);
    render_system_destroy();
    ecs_free(&r);
}
