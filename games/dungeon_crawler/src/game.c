#include "game.h"

#include <stdio.h>

#include "caldera/ecs/ecs.h"
#include "caldera/ecs/components.h"
#include "caldera/ecs/systems/render_system.h"
#include "caldera/ecs/systems/animation_system.h"
#include "custom_components.h"
#include "caldera/graphics/frontend/font.h"
#include "caldera/graphics/frontend/renderer.h"
#include "systems/facing_system.h"
#include "systems/player_system.h"

static texture empty_texture;
static texture player_texture;
static texture items_texture;
static font main_font;

static world w;

u32 fps_counter;

static void register_custom_components(world *w) {
    ecs_register_component(w, FACING_DIRECTION, sizeof(facing_direction), nullptr);
    ecs_register_component(w, PLAYER_CONTROLLER, sizeof(player_controller), nullptr);
}

static void create_player() {
    u32 player = ecs_create_entity(&w);
    ec_transform *player_transform = ecs_add_component(&w, player, EC_TRANSFORM);
    *player_transform = (ec_transform){
        .position = {0.f, 0.f},
        .origin = {16.f, 5.f},
        .scale = {1.f, 1.f},
        .rotation = 0.f
    };

    ec_sprite *player_sprite = ecs_add_component(&w, player, EC_SPRITE);
    *player_sprite = (ec_sprite){
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

    ec_animator *player_animator = ecs_add_component(&w, player, EC_ANIMATOR);
    *player_animator = (ec_animator){
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
    ec_transform *npc_transform = ecs_add_component(&w, npc, EC_TRANSFORM);
    *npc_transform = (ec_transform){
        .position = position,
        .origin = {16.f, 5.f},
        .scale = {1.f, 1.f},
        .rotation = 0.f
    };

    ec_sprite *npc_sprite = ecs_add_component(&w, npc, EC_SPRITE);
    *npc_sprite = (ec_sprite){
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

    ec_animator *npc_animator = ecs_add_component(&w, npc, EC_ANIMATOR);
    *npc_animator = (ec_animator){
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
    ec_transform *t = ecs_add_component(&w, chest, EC_TRANSFORM);
    *t = (ec_transform){
        .position = position,
        .origin = {16.f, 2.f},
        .scale = {1.f, 1.f},
        .rotation = 0.f
    };

    ec_sprite *sprite = ecs_add_component(&w, chest, EC_SPRITE);
    *sprite = (ec_sprite){
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

    ec_animator *animator = ecs_add_component(&w, chest, EC_ANIMATOR);
    *animator = (ec_animator){
        .animation = {
            .offset = {0, 60},
            .frame_num = 6,
            .speed = 8.f
        },
        .current_frame = 0.f
    };
}

u32 create_fps_counter() {
    u32 entity = ecs_create_entity(&w);
    ec_transform *t = ecs_add_component(&w, entity, EC_TRANSFORM);
    *t = (ec_transform){
        .position = {0.f, 0.f},
        .origin = {0.f, 0.f},
        .scale = {1.f, 1.f},
        .rotation = 0.f
    };

    ec_text *text = ecs_add_component(&w, fps_counter, EC_TEXT);
    *text = (ec_text){
        .font = main_font,
        .str = nullptr,
        .color = {1.f, 1.f, 1.f, 1.f},
    };

    return entity;
}

void game_init() {
    ecs_init(&w);
    register_custom_components(&w);

    render_system_init();

    texture_init_empty(&empty_texture);
    texture_load_from_file(&player_texture, "../res/textures/character_idle.png");
    texture_load_from_file(&items_texture, "../res/textures/items.png");

    font_init(&main_font, "../res/fonts/uni05_53.ttf");
    fps_counter = create_fps_counter();

    create_player();
    create_npc((vec2){-40.f, 40.f}, DIR_DOWN);
    create_npc((vec2){40.f, 20.f}, DIR_LEFT);
    create_chest((vec2){10.f, -20.f});
}

void game_free() {
    texture_free(&player_texture);
    texture_free(&items_texture);
    font_free(&main_font);
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

    ec_text *fps_text = ecs_get_component(&w, fps_counter, EC_TEXT);
    ec_text_printf(fps_text, "%u FPS", info.fps);
}
