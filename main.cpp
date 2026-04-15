#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_test_font.h>
#include <iostream>
#include <string>
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "scripts/classes/entity.h"

#define NPC_OFFSET 216
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
uint8_t player_facing;


Uint64 last_time = SDL_GetTicksNS();
float delta_time = 0.0f;

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

void check_npc(Entity& entity);
void set_npc_in_map(Entity npc);
void draw_ui(SDL_Renderer* renderer, SDL_FRect barraUI);
void movement(Entity& entity);
void smooth_movement(int dir, float& x, float& y, float target_x, float target_y, float dt);
void draw_map(SDL_Renderer* renderer, SDL_Texture* tileset);
void draw_tile(SDL_Renderer* renderer, SDL_Texture* tileset, int tile_id, float screen_x, float screen_y);
bool check_collision(float x, float y, int dir);

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) return -1;

    SDL_Window* window = SDL_CreateWindow("Daring Engine", 480, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    SDL_SetRenderVSync(renderer, 1);

    Entity entity(0, 128, 128, 32, 32, "img/sprites/prova/prova.bmp", renderer);
    Entity npc(0, 160, 160, 32, 32, "img/sprites/prova/pg2.bmp", renderer);
    SDL_FRect barraUI = { 0.0f, 400.0f, 800.0f, 200.0f };

    SDL_Surface* surface = SDL_LoadBMP("img/sprites/prova/tiles.bmp");
    SDL_Texture* tileset = SDL_CreateTextureFromSurface(renderer, surface);

    bool running = true;
    bool intro_fatta = true; // Impostato a true per saltare il debug text se vuoi testare subito
    SDL_Event event;

    set_npc_in_map(npc);

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
                    if (event.key.scancode == SDL_SCANCODE_E && event.key.repeat == 0) {
                        check_npc(entity);
                    }
            }
        }



        // movement
        movement(entity);


        // DISEGNO
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);

        draw_map(renderer, tileset);

        entity.render(renderer);
        npc.render(renderer);
        draw_ui(renderer, barraUI);

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}

void smooth_movement(int dir, float& x, float& y, float target_x, float target_y, float dt) {
    float speed = 160.0f; // 32 pixel in 0.1s
    float step = speed * dt;

    if (dir == 1) { // Destra
        x += step;
        if (x >= target_x) x = target_x;
    } else if (dir == 2) { // Sinistra
        x -= step;
        if (x <= target_x) x = target_x;
    } else if (dir == 3) { // Su
        y -= step;
        if (y <= target_y) y = target_y;
    } else if (dir == 4) { // Giù
        y += step;
        if (y >= target_y) y = target_y;
    }
}

bool check_collision(float x, float y, int dir) {
    int next_x = (int)x;
    int next_y = (int)y;

    if (dir == 1) next_x += 32;
    if (dir == 2) next_x -= 32;
    if (dir == 3) next_y -= 32;
    if (dir == 4) next_y += 32;

    // Controllo bordi mappa per sicurezza
    if (next_x < 0 || next_x >= 480 || next_y < 0 || next_y >= 480) return true;

    // Se il valore è > della soglia (22 o 23), è un muro
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

    // AGGIORNAMENTO POSIZIONE
    if (moving) {
        float x = entity.get_pos_x();
        float y = entity.get_pos_y();

        smooth_movement(current_dir, x, y, target_x, target_y, delta_time);

        entity.set_pos_x(x);
        entity.set_pos_y(y);

        // Snap finale per precisione griglia
        if (x == target_x && y == target_y) {
            moving = false;
        }
    }
}

void draw_ui(SDL_Renderer* renderer, SDL_FRect barraUI) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &barraUI);
}

void set_npc_in_map(Entity npc) {
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
        SDL_Log("Interacted!");
    }
    return;
}
