#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_test_font.h>
#include <string>
#include <vector>
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include "scripts/engine/language.h"
#include "scripts/engine/ui.h"
#include "scripts/classes/Character.h"
#include "scripts/classes/Attack.h"

#define NPC_OFFSET 216
#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4
uint8_t player_facing;


Uint64 last_time = SDL_GetTicksNS();

float delta_time = 0.0f;
uint8_t game_state = 0; // 0: none, 1: battle, >2: menus
uint8_t menu_option = 0;
bool can_move = true;

std::vector<Entity> npcs;
std::vector<Attack> atks;
uint8_t map[15][15] = {
    {23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23},
    {23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23},
    {23, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23},
    {23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23},
    {23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23},
    {23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23},
    {23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23},
    {23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23},
    {23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23},
    {23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23},
    {23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23},
    {23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23},
    {23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23},
    {23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23},
    {23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23}
};

uint8_t tile_walkable_tresh = 5;
void menu_choices(SDL_Event event);
void npc_movement();
void check_npc(Entity& entity);
void set_npc_in_map(Entity& npc);
void draw_ui(SDL_Renderer* renderer, SDL_FRect barraUI);
void draw_menu(SDL_Renderer* renderer);
void movement(Entity& entity);
void smooth_movement(int dir, float& x, float& y, float target_x, float target_y, float dt);
void draw_map(SDL_Renderer* renderer, SDL_Texture* tileset);
void draw_tile(SDL_Renderer* renderer, SDL_Texture* tileset, int tile_id, float screen_x, float screen_y);
bool check_collision(float x, float y, int dir);

Character chara("Pasquel", "Knight", 5, 20, 7, 10, 7, 9, 5, 3, 2, atks);


int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) return -1;

    SDL_Window* window = SDL_CreateWindow("Daring Engine", 480, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    SDL_SetRenderVSync(renderer, 1);

    Entity entity(0, 128, 128, 32, 32, "img/sprites/prova/prova.bmp", renderer);

    Entity npc = Entity(1, 160, 160, 32, 32, "img/sprites/prova/pg2.bmp", renderer);
    SDL_FRect barraUI = { 0.0f, 400.0f, 800.0f, 200.0f };

    npcs.push_back(npc);

    SDL_Surface* surface = SDL_LoadBMP("img/sprites/prova/tiles.bmp");
    SDL_Texture* tileset = SDL_CreateTextureFromSurface(renderer, surface);

    bool running = true;
    bool intro_fatta = true;
    SDL_Event event;

    set_npc_in_map(npcs[0]);

    player_facing = DOWN;

    while (running) {
        // delta calc
        Uint64 now = SDL_GetTicksNS();
        delta_time = (now - last_time) / 1000000000.0f;
        last_time = now;
        //

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.scancode == SDL_SCANCODE_ESCAPE && event.key.repeat == 0) {
                    if (game_state == 0) {
                        menu_option = 0;
                        game_state = 2;
                    }
                    else if (game_state == 2) {
                        game_state = 0;
                    }
                }
                if (game_state == 2) {
                    menu_choices(event);
                }
                if (event.key.scancode == SDL_SCANCODE_E && event.key.repeat == 0) {
                    if (script_is_active()) {
                        script_next();
                    }
                    else if (game_state == 0) {
                        check_npc(entity);
                    }
                }
            }
        }



        // movement
        if (can_move && game_state == 0) movement(entity);

        npc_movement();
        script_update();

        // DISEGNO
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);

        draw_map(renderer, tileset);

        entity.render(renderer);

        for (Entity& n : npcs) {
            n.render(renderer);
        }

        draw_ui(renderer, barraUI);
        draw_menu(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}

void smooth_movement(int dir, float& x, float& y, float target_x, float target_y, float dt) {
    float speed = 160.0f;
    float step = speed * dt;

    if (dir == RIGHT) {
        x += step;
        if (x >= target_x) x = target_x;
    } else if (dir == LEFT) {
        x -= step;
        if (x <= target_x) x = target_x;
    } else if (dir == UP) {
        y -= step;
        if (y <= target_y) y = target_y;
    } else if (dir == DOWN) {
        y += step;
        if (y >= target_y) y = target_y;
    }
}

bool check_collision(float x, float y, int dir) {
    int next_x = (int)x;
    int next_y = (int)y;

    if (dir == RIGHT) next_x += 32;
    if (dir == LEFT) next_x -= 32;
    if (dir == UP) next_y -= 32;
    if (dir == DOWN) next_y += 32;


    if (next_x < 0 || next_x >= 480 || next_y < 0 || next_y >= 480) return true;


    if (map[next_y / 32][next_x / 32] > tile_walkable_tresh) {
        return true;
    }
    return false;
}

void draw_tile(SDL_Renderer* renderer, SDL_Texture* tileset, int tile_id, float screen_x, float screen_y) {
    int tiles_per_row = 8;
    int size = 32;
    SDL_FRect src = {(float)((tile_id % tiles_per_row) * size), (float)((tile_id / tiles_per_row) * size), (float)size, (float)size};
    SDL_FRect dst = {screen_x, screen_y, (float)size, (float)size};
    SDL_RenderTexture(renderer, tileset, &src, &dst);
}

void draw_map(SDL_Renderer* renderer, SDL_Texture* tileset) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            draw_tile(renderer, tileset, map[i][j], j * 32, i * 32);
        }
    }
}

void movement(Entity &entity) {
    const bool* state = SDL_GetKeyboardState(NULL);
    static bool moving = false;
    static float target_x = 0;
    static float target_y = 0;
    static int current_dir = 0;
    if (!moving) {
        if (state[SDL_SCANCODE_RIGHT]) {
            player_facing = RIGHT;
            if (!check_collision(entity.get_pos_x(), entity.get_pos_y(), 1)) {
                target_x = entity.get_pos_x() + 32;
                target_y = entity.get_pos_y();
                current_dir = 1;
                moving = true;
            }
        } else if (state[SDL_SCANCODE_LEFT]) {
            player_facing = LEFT;
            if (!check_collision(entity.get_pos_x(), entity.get_pos_y(), 2)) {
                target_x = entity.get_pos_x() - 32;
                target_y = entity.get_pos_y();
                current_dir = 2;
                moving = true;
            }
        } else if (state[SDL_SCANCODE_UP]) {
            player_facing = UP;
            if (!check_collision(entity.get_pos_x(), entity.get_pos_y(), 3)) {
                target_x = entity.get_pos_x();
                target_y = entity.get_pos_y() - 32;
                current_dir = 3;
                moving = true;
            }
        } else if (state[SDL_SCANCODE_DOWN]) {
            player_facing = DOWN;
            if (!check_collision(entity.get_pos_x(), entity.get_pos_y(), 4)) {
                target_x = entity.get_pos_x();
                target_y = entity.get_pos_y() + 32;
                current_dir = 4;
                moving = true;
            }
        }
    }


    if (moving) {
        float x = entity.get_pos_x();
        float y = entity.get_pos_y();

        smooth_movement(current_dir, x, y, target_x, target_y, delta_time);

        entity.set_pos_x(x);
        entity.set_pos_y(y);


        if (x == target_x && y == target_y) {
            moving = false;
        }
    }
}

void draw_ui(SDL_Renderer* renderer, SDL_FRect barraUI) {
    if (!is_ui_visible) return;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &barraUI);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_SetRenderScale(renderer, 2.0f, 2.0f);

    float text_x = (barraUI.x + 20.0f) / 2.0f;
    float text_y = (barraUI.y + 20.0f) / 2.0f;

    SDL_RenderDebugText(renderer, text_x, text_y, current_ui_text.c_str());
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

void set_npc_in_map(Entity& npc) {
    uint8_t x_pos = (int)npc.get_pos_x()/32;
    uint8_t y_pos = (int)npc.get_pos_y()/32;
    map[y_pos][x_pos] = NPC_OFFSET + npc.get_id();
}

void check_npc(Entity& entity) {
    int x_pos = (int)entity.get_pos_x()/32;
    int y_pos = (int)entity.get_pos_y()/32;
    int target_x_pos;
    int target_y_pos;
    switch (player_facing) {
        case UP:
            target_x_pos = x_pos;
            target_y_pos = y_pos - 1;
            break;
        case RIGHT:
            target_x_pos = x_pos + 1;
            target_y_pos = y_pos;
            break;
        case DOWN:
            target_x_pos = x_pos;
            target_y_pos = y_pos + 1;
            break;
        case LEFT:
            target_x_pos = x_pos - 1;
            target_y_pos = y_pos;
    }
    if (map[target_y_pos][target_x_pos] >= NPC_OFFSET) {
        int target_id = map[target_y_pos][target_x_pos] - NPC_OFFSET;
        for (Entity& n : npcs) {
            if (n.get_id() == target_id) {
                script_load("game_scripts/script.txt", &n);
                break;
            }
        }

    }
    return;
}


void npc_movement() {
    for (Entity& n : npcs) {
        if (n.get_moving()) {
            float cur_x = n.get_pos_x();
            float cur_y = n.get_pos_y();

            smooth_movement(n.get_current_dir(), cur_x, cur_y, n.get_target_x(), n.get_target_y(), delta_time);

            n.set_pos_x(cur_x);
            n.set_pos_y(cur_y);
            if (SDL_fabsf(cur_x - n.get_target_x()) < 0.1f && SDL_fabsf(cur_y - n.get_target_y()) < 0.1f) {
                n.set_pos_x(n.get_target_x());
                n.set_pos_y(n.get_target_y());
                n.set_moving(false);
            }
        }
    }
}

void draw_menu(SDL_Renderer* renderer) {
    if (game_state == 2) {

        SDL_FRect lateral = { 32.0f, 64.0f, 160.0f, 240.0f };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &lateral);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_SetRenderScale(renderer, 2.0f, 2.0f);
        SDL_RenderDebugText(renderer, 28.0f, 40.0f, "STATUS");
        SDL_RenderDebugText(renderer, 28.0f, 56.0f, "ITEMS");
        SDL_RenderDebugText(renderer, 28.0f, 72.0f, "MAGIC");
        SDL_RenderDebugText(renderer, 28.0f, 88.0f, "QUESTS");
        SDL_RenderDebugText(renderer, 28.0f, 104.0f, "SAVE");
        SDL_RenderDebugText(renderer, 28.0f, 120.0f, "SETTINGS");
        SDL_RenderDebugText(renderer, 28.0f, 136.0f, "EXIT");
        SDL_SetRenderScale(renderer, 1.0f, 1.0f);

        SDL_Surface* arrow = SDL_LoadBMP("img/sprites/prova/arrow.bmp");
        SDL_Texture* arrow_text = SDL_CreateTextureFromSurface(renderer, arrow);
        SDL_FRect arr_rect = { 36.0f, 78.0f + (menu_option * 32), 16.0f, 16.0f};
        SDL_RenderTexture(renderer, arrow_text, NULL, &arr_rect);
    }
}

void menu_choices(SDL_Event event) {
    if (event.key.scancode == SDL_SCANCODE_UP && menu_option > 0) {
        menu_option--;
    }
    else if (event.key.scancode == SDL_SCANCODE_DOWN && menu_option < 6) {
        menu_option++;
    }
    else if (event.key.scancode == SDL_SCANCODE_E) {
        switch (menu_option) {
            case 6:
                menu_option = 0;
                game_state = 0;
                break;
            default:
                menu_option = 0;
                game_state = 0;
                break;
        }
    }
}
