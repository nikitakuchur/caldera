#include "game.h"

#include <stdio.h>

#include "caldera/ecs/ecs.h"
#include "caldera/ecs/components.h"
#include "caldera/ecs/systems/render_system.h"
#include "caldera/ecs/systems/animation_system.h"
#include "custom_components.h"
#include "caldera/graphics/frontend/renderer.h"
#include "systems/facing_system.h"
#include "systems/player_system.h"

static texture player_texture;
static texture items_texture;

static world w;

static void register_custom_components(world *w) {
    ecs_register_component(w, FACING_DIRECTION, sizeof(facing_direction));
    ecs_register_component(w, PLAYER_CONTROLLER, sizeof(player_controller));
}

static void create_player() {
    u32 player = ecs_create_entity(&w);
    transform *player_transform = ecs_add_component(&w, player, TRANSFORM);
    *player_transform = (transform){
        .position = {0.f, 0.f},
        .origin = {16.f, 2.f},
        .scale = {1.f, 1.f},
        .rotation = 0.f
    };

    sprite_renderer *player_renderer = ecs_add_component(&w, player, SPRITE_RENDERER);
    *player_renderer = (sprite_renderer){
        .texture = player_texture,
        .size = {32, 32},
        .texture_rect = {
            0, 96,
            32, 96,
            32, 96 + 32,
            0, 96 + 32
        },
        .color = {1.f, 1.f, 1.f, 1.f}
    };

    sprite_animator *player_animator = ecs_add_component(&w, player, SPRITE_ANIMATOR);
    *player_animator = (sprite_animator){
        .animation = {
            .offset = {0, 0},
            .frame_num = 3,
            .speed = 3.5f
        },
        .current_frame = 0.f
    };

    facing_direction *player_direction = ecs_add_component(&w, player, FACING_DIRECTION);
    player_direction->direction = DIR_LEFT;

    player_controller *controller = ecs_add_component(&w, player, PLAYER_CONTROLLER);
    controller->walk_speed = 40.f;
}

static void create_npc(vec2 position, direction dir) {
    u32 npc = ecs_create_entity(&w);
    transform *npc_transform = ecs_add_component(&w, npc, TRANSFORM);
    *npc_transform = (transform){
        .position = position,
        .origin = {0.f, 0.f},
        .scale = {1.f, 1.f},
        .rotation = 0.f
    };

    sprite_renderer *npc_renderer = ecs_add_component(&w, npc, SPRITE_RENDERER);
    *npc_renderer = (sprite_renderer){
        .texture = player_texture,
        .size = {32, 32},
        .texture_rect = {
            0, 0,
            32, 0,
            32, 32,
            0, 32
        },
        .color = {1.f, 1.f, 1.f, 1.f}
    };

    sprite_animator *npc_animator = ecs_add_component(&w, npc, SPRITE_ANIMATOR);
    *npc_animator = (sprite_animator){
        .animation = {
            .offset = {0, 0},
            .frame_num = 3,
            .speed = 3.5f
        },
        .current_frame = 0.f
    };

    facing_direction *npc_direction = ecs_add_component(&w, npc, FACING_DIRECTION);
    npc_direction->direction = dir;
}

static void create_chest(vec2 position) {
    u32 chest = ecs_create_entity(&w);
    transform *t = ecs_add_component(&w, chest, TRANSFORM);
    *t = (transform){
        .position = position,
        .origin = {16.f, 2.f},
        .scale = {1.f, 1.f},
        .rotation = 0.f
    };

    sprite_renderer *sr = ecs_add_component(&w, chest, SPRITE_RENDERER);
    *sr = (sprite_renderer){
        .texture = items_texture,
        .size = {20, 20},
        .texture_rect = {
            0, 60,
            20, 60,
            20, 60 + 20,
            0, 60 + 20
        },
        .color = {1.f, 1.f, 1.f, 1.f}
    };

    sprite_animator *sa = ecs_add_component(&w, chest, SPRITE_ANIMATOR);
    *sa = (sprite_animator){
        .animation = {
            .offset = {0, 60},
            .frame_num = 6,
            .speed = 8.f
        },
        .current_frame = 0.f
    };
}

void game_init() {
    ecs_init(&w);
    register_custom_components(&w);

    render_system_init();

    texture_init(&player_texture, "../res/textures/character_idle.png");
    texture_init(&items_texture, "../res/textures/items.png");

    create_player();
    create_npc((vec2){-40.f, 40.f}, DIR_DOWN);
    create_npc((vec2){40.f, 20.f}, DIR_LEFT);
    create_chest((vec2){10.f, -20.f});
}

void game_free() {
    texture_free(&player_texture);
    texture_free(&items_texture);
    render_system_free();
    ecs_free(&w);
}

void game_draw() {
    static f32 delta_time = 0;

    player_system_update(&w, delta_time);
    animation_system_update(&w, delta_time);
    facing_system_update(&w);

    renderer_frame_begin();
    renderer_set_clear_color((vec4){0.11f, 0.1f, 0.15f, 1.0f});

    render_system_draw(&w);

    frame_info info = renderer_frame_end();
    delta_time = info.delta_time;
    printf("FPS: %d\n", info.fps);
}
