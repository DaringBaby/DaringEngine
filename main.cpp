#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_test_font.h>
#include <string>
#include <vector>
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include "scripts/classes/PlayerVars.h"
#include "scripts/engine/language.h"
#include "scripts/engine/ui.h"
#include "scripts/classes/Character.h"
#include "scripts/classes/Attack.h"
#include "scripts/classes/Item.h"
#include <iostream>


#define NPC_OFFSET 216
#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4
uint8_t player_facing;


Uint64 last_time = SDL_GetTicksNS();

float delta_time = 0.0f;
uint8_t game_state = 0; // 0: none, 1: battle, 2: menu, 3: status, 4: item menu, 5: use item, 6: select party member to use item, 7: equip menu, 8: equip list
uint8_t menu_option = 0;
uint8_t status_option = 0;
uint8_t item_option = 0;
uint8_t use_option = 0;
uint8_t party_option = 0;
uint8_t equip_char_option = 0;

bool can_move = true;

int first_item = 0;


std::vector<Entity> npcs;
std::vector<Character> party;
std::vector<Attack> atks;
std::vector<Item> items;


PlayerVars player;

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
void status_choices(SDL_Event event);
void item_choices(SDL_Event event);
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
void draw_status(SDL_Renderer* renderer);
void draw_item_menu(SDL_Renderer* renderer);
void draw_use_item_menu(SDL_Renderer* renderer);
bool can_use_item(std::string type);
void use_item_choices(SDL_Event event);
void draw_line(SDL_Renderer* renderer, float pos_x, float pos_y, std::string text);
void draw_use_item_to_party(SDL_Renderer* renderer);
void party_menu_choices(SDL_Event event);
void use_item(const Item& item);
void use_healing_item(const Item& item);
void use_mana_item(const Item& item);
void use_revive_item(const Item& item);
void draw_equip_menu(SDL_Renderer* renderer);
void equip_menu_choices(SDL_Event event);


Character chara("Pasquel", "Knight", 5, 20, 7, 10, 7, 9, 5, 3, 2, atks, "None");
Character chara2("Babbo", "Hero", 5, 20, 7, 10, 7, 9, 5, 3, 2, atks, "None");
Character chara3("Pisnul", "Pippone", 5, 20, 7, 10, 7, 9, 5, 3, 2, atks, "None");
Character chara4("Sussy", "Baka", 5, 20, 7, 10, 7, 9, 5, 3, 2, atks, "None");

Equip none_wpn("NONE", "- - -", "WEAPON", 0, 0, 0, 0, 0, 0, 0);
Equip none_head("NONE", "- - -", "HEAD", 0, 0, 0, 0, 0, 0, 0);
Equip none_body("NONE", "- - -", "BODY", 0, 0, 0, 0, 0, 0, 0);
Equip none_greaves("NONE", "- - -", "GREAVES", 0, 0, 0, 0, 0, 0, 0);
Equip none_acc("NONE", "- - -", "HEAD", 0, 0, 0, 0, 0, 0, 0);



uint8_t party_size = 4;


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
    //
    party.push_back(chara);
    party.push_back(chara2);
    party.push_back(chara3);
    party.push_back(chara4);

    // DEBUG
    for (int i=0; i<std::size(party); i++) {
        party[i].set_current_hp(party[i].get_max_hp()/2);
        party[i].set_current_mp(party[i].get_max_mp()/2);
    }
    player.add_equip(none_wpn, 1);
    player.add_equip(none_head, 1);
    player.add_equip(none_body, 1);
    player.add_equip(none_greaves, 1);
    player.add_equip(none_acc, 1);

    //

    for (int i = 0; i<10; i++) {
        Item item("Oggect"+std::to_string(i), "This item sucks", 200, "DAMAGE", 3, "ALL");
        Item item2("OBgect"+std::to_string(i), "Cura", 20, "HEALING", 3, "ALL");
        items.push_back(item);
        items.push_back(item2);
        player.add_item(item, 3);
        player.add_item(item2, 3);
    }
    //
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
                switch (game_state) {
                    case 2:
                        menu_choices(event);
                        break;
                    case 3:
                        status_choices(event);
                        break;
                    case 4:
                        item_choices(event);
                        break;
                    case 5:
                        use_item_choices(event);
                        break;
                    case 6:
                        party_menu_choices(event);
                        break;
                    case 7:
                        equip_menu_choices(event);
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

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDebugText(renderer, 16.0f, 16.0f, (std::to_string(1.0f/delta_time)).c_str());

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
    if (game_state >= 2) {
        SDL_FRect lateral = { 32.0f, 64.0f, 160.0f, 272.0f };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &lateral);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_SetRenderScale(renderer, 2.0f, 2.0f);
        SDL_RenderDebugText(renderer, 28.0f, 40.0f, "STATUS");
        SDL_RenderDebugText(renderer, 28.0f, 56.0f, "ITEMS");
        SDL_RenderDebugText(renderer, 28.0f, 72.0f, "EQUIP");
        SDL_RenderDebugText(renderer, 28.0f, 88.0f, "MAGIC");
        SDL_RenderDebugText(renderer, 28.0f, 104.0f, "QUESTS");
        SDL_RenderDebugText(renderer, 28.0f, 120.0f, "SAVE");
        SDL_RenderDebugText(renderer, 28.0f, 136.0f, "SETTINGS");
        SDL_RenderDebugText(renderer, 28.0f, 152.0f, "EXIT");
        SDL_SetRenderScale(renderer, 1.0f, 1.0f);

        SDL_Surface* arrow = SDL_LoadBMP("img/sprites/prova/arrow.bmp");
        SDL_Texture* arrow_text = SDL_CreateTextureFromSurface(renderer, arrow);
        SDL_FRect arr_rect = { 36.0f, 78.0f + (menu_option * 32), 16.0f, 16.0f};
        SDL_RenderTexture(renderer, arrow_text, NULL, &arr_rect);
    }
    if (game_state == 3) {
        draw_status(renderer);
    }
    if (game_state == 4 ||game_state == 5 || game_state == 6) {
        draw_item_menu(renderer);
    }
    if (game_state == 5) {
        draw_use_item_menu(renderer);
    }
    if (game_state == 6) {
        draw_use_item_to_party(renderer);
    }
    if (game_state == 7) {
        draw_equip_menu(renderer);
    }
}

void menu_choices(SDL_Event event) {
    if (event.key.scancode == SDL_SCANCODE_UP && menu_option > 0) {
        menu_option--;
    }
    else if (event.key.scancode == SDL_SCANCODE_DOWN && menu_option < 7) {
        menu_option++;
    }
    else if (event.key.scancode == SDL_SCANCODE_E) {
        switch (menu_option) {
            case 0:
                status_option = 0;
                game_state = 3;
                break;
            case 1:
                first_item = 0;
                game_state = 4;
                break;
            case 2:
                game_state = 7;
                break;
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

void status_choices (SDL_Event event) {
    if (event.key.scancode == SDL_SCANCODE_A && status_option > 0) {
        status_option--;
    }
    else if (event.key.scancode == SDL_SCANCODE_S && status_option < std::size(party)-1) {
        status_option++;
    }
    if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
        status_option = 0;
        game_state = 2;
    }
}

void item_choices(SDL_Event event) {
    if (event.key.scancode == SDL_SCANCODE_UP && item_option > first_item) {
        item_option--;
    }
    else if (event.key.scancode == SDL_SCANCODE_DOWN && item_option < first_item + 7 && item_option < player.get_inventory().size()-1) {
        item_option++;
    }
    if (event.key.scancode == SDL_SCANCODE_S && std::size(player.get_inventory()) >= first_item + 7) {
        first_item += 8;
        item_option = first_item;
    }
    else if (event.key.scancode == SDL_SCANCODE_A && first_item != 0) {
        first_item -= 8;
        item_option = first_item;
    }
    if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
        item_option = 0;
        first_item = 0;
        game_state = 2;
    }
    if (event.key.scancode == SDL_SCANCODE_E) {
        if (can_use_item(player.get_inventory()[item_option].get_type())) {
            game_state = 5;
        }
    }
}

void draw_status(SDL_Renderer* renderer) {
    SDL_FRect status = { 224.0f, 64.0f, 160.0f, 368.0f };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &status);
    SDL_SetRenderScale(renderer, 2.0f, 2.0f);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDebugText(renderer, 136.0f, 40.0f, "Name ");
    SDL_RenderDebugText(renderer, 120.0f, 48.0f, party[status_option].get_name().c_str());
    SDL_RenderDebugText(renderer, 136.0f, 64.0f, "Class ");
    SDL_RenderDebugText(renderer, 120.0f, 72.0f, party[status_option].get_classe().c_str());
    //
    //
    SDL_RenderDebugText(renderer, 120.0f, 88.0f, ("Level " + std::to_string(party[status_option].get_level())).c_str());
    SDL_RenderDebugText(renderer, 120.0f, 96.0f, ("Nxt " + std::to_string(party[status_option].get_next_level_exp())).c_str());

    SDL_RenderDebugText(renderer, 120.0f, 112.0f, "HP: ");
    SDL_RenderDebugText(renderer, 136.0f, 120.0f, (std::to_string(party[status_option].get_current_hp()) + "/" + std::to_string(party[status_option].get_max_hp())).c_str());

    SDL_RenderDebugText(renderer, 120.0f, 136.0f, "MP: ");
    SDL_RenderDebugText(renderer, 136.0f, 144.0f, (std::to_string(party[status_option].get_current_mp()) + "/" + std::to_string(party[status_option].get_max_mp())).c_str());

    SDL_RenderDebugText(renderer, 120.0f, 160.0f, ("STR: " + std::to_string(party[status_option].get_current_strength())).c_str());
    SDL_RenderDebugText(renderer, 120.0f, 168.0f, ("DEF: " + std::to_string(party[status_option].get_current_defense())).c_str());
    SDL_RenderDebugText(renderer, 120.0f, 176.0f, ("INT: " + std::to_string(party[status_option].get_current_intelligence())).c_str());
    SDL_RenderDebugText(renderer, 120.0f, 184.0f, ("MDF: " + std::to_string(party[status_option].get_current_magic_defense())).c_str());
    SDL_RenderDebugText(renderer, 120.0f, 192.0f, ("SPD: " + std::to_string(party[status_option].get_current_speed())).c_str());
    SDL_RenderDebugText(renderer, 120.0f, 200.0f, ("LCK: " + std::to_string(party[status_option].get_current_luck())).c_str());

    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

void draw_item_menu(SDL_Renderer* renderer) {
    SDL_FRect item_menu = { 224.0f, 64.0f, 224.0f, 272.0f };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &item_menu);

    SDL_SetRenderScale(renderer, 2.0f, 2.0f);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (int i = 0; i+first_item < std::size(player.get_inventory()) && i < 8; i++) {
        SDL_RenderDebugText(renderer, 128.0f, 40.0f + 16.0f * i, (player.get_inventory()[first_item + i].get_name()).c_str());
        SDL_RenderDebugText(renderer, 200.0f, 40.0f + 16.0f * i, ("x"+std::to_string(player.get_items_quantity()[first_item + i])).c_str());
    }

    SDL_SetRenderScale(renderer, 1.0f, 1.0f);

    SDL_Surface* arrow = SDL_LoadBMP("img/sprites/prova/arrow.bmp");
    SDL_Texture* arrow_item = SDL_CreateTextureFromSurface(renderer, arrow);
    SDL_FRect arr_rect = { 230.0f, 78.0f + ((item_option - first_item) * 32.0f), 16.0f, 16.0f };
    SDL_RenderTexture(renderer, arrow_item, NULL, &arr_rect);

    SDL_FRect item_desc = { 32.0f, 368.0f, 416.0f, 80.0f };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &item_desc);


    SDL_SetRenderScale(renderer, 2.0f, 2.0f);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderDebugText(renderer, 24.0f, 192.0f, (player.get_inventory()[item_option].get_description().c_str()));

    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

void draw_use_item_menu(SDL_Renderer * renderer) {
    // riquadro
    SDL_FRect use_menu = { 332.0f, 368.0f, 116.0f, 80.0f };
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(renderer, &use_menu);
    // scritta
    draw_line(renderer, 332+32.0f, 384, "Use");
    draw_line(renderer, 332+32.0f, 416.0f, "Drop");

    // arrow
    SDL_Surface* arrow = SDL_LoadBMP("img/sprites/prova/arrow.bmp");
    SDL_Texture* arrow_item = SDL_CreateTextureFromSurface(renderer, arrow);
    SDL_FRect arr_rect;
    if (use_option == 0) {
        arr_rect = { 340.0f, 384.0f, 16.0f, 16.0f};
    }
    else {
        arr_rect = { 340.0f, 416.0f, 16.0f, 16.0f};
    }

    SDL_RenderTexture(renderer, arrow_item, NULL, &arr_rect);

}

bool can_use_item(std::string type) {
    return (type == "HEALING" || type == "MANA" || type == "REVIVE");
}

void draw_line(SDL_Renderer* renderer, float pos_x, float pos_y, std::string text) {
    SDL_SetRenderScale(renderer, 2.0f, 2.0f);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderDebugText(renderer, pos_x/2, pos_y/2, text.c_str());

    SDL_SetRenderScale(renderer, 1.0f, 1.0f);


}

void use_item_choices(SDL_Event event) {
    if (event.key.scancode == SDL_SCANCODE_UP && use_option == 1) {
        use_option = 0;
    }
    else if (event.key.scancode == SDL_SCANCODE_DOWN && use_option == 0) {
        use_option = 1;
    }
    else if (event.key.scancode == SDL_SCANCODE_E) {
        if (use_option == 1) {
            player.remove_item(player.get_inventory()[item_option], 1);
            item_option = 0;
            first_item = 0;
            use_option = 0;
            game_state = 4;
        }
        else {
            game_state = 6;
        }
    }
    else if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
        use_option = 0;
        game_state = 4;
    }
}

void draw_use_item_to_party(SDL_Renderer* renderer) {
    SDL_FRect party_members = { 32.0f, 368.0f, 416.0f, 80.0f };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &party_members);


    SDL_SetRenderScale(renderer, 2.0f, 2.0f);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (int i = 0; i < party.size(); i++) {
        float y = 376.0f + (i * 16.0f);

        // Nome
        draw_line(renderer, 56.0f, y, party[i].get_name().c_str());

        draw_line(renderer, 192.0f, y, "HP: ");
        draw_line(renderer, 240.0f, y, std::to_string(party[i].get_current_hp()).c_str());
        draw_line(renderer, 288.0f, y, "/");
        draw_line(renderer, 304.0f, y, std::to_string(party[i].get_max_hp()).c_str());

        draw_line(renderer, 352.0f, y, "MP: ");
        draw_line(renderer, 400.0f, y, std::to_string(party[i].get_current_mp()).c_str());
    }



    SDL_SetRenderScale(renderer, 1.0f, 1.0f);

    SDL_Surface* arrow = SDL_LoadBMP("img/sprites/prova/arrow.bmp");
    SDL_Texture* arrow_party = SDL_CreateTextureFromSurface(renderer, arrow);
    SDL_FRect arr_rect = {40.0f, 376.0f + 16*(party_option), 16.0f, 16.0f };

    SDL_RenderTexture(renderer, arrow_party, NULL, &arr_rect);
}

void party_menu_choices(SDL_Event event) {
    if (event.key.scancode == SDL_SCANCODE_UP && party_option > 0) {
        party_option--;
    }
    else if (event.key.scancode == SDL_SCANCODE_DOWN && party_option < party_size - 1) {
        party_option++;
    }
    else if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
        party_option = 0;
        item_option = 0;
        first_item = 0;
        use_option = 0;
        game_state = 4;
    }
    else if (event.key.scancode == SDL_SCANCODE_E) {
        use_item(player.get_inventory()[item_option]);
    }
}

void use_item(const Item& item) {
    if (item.get_type() == "HEALING") {
        use_healing_item(item);
    }
    else if (item.get_type() == "MANA") {
        use_mana_item(item);
    }
    else if (item.get_type() == "REVIVE") {
        use_revive_item(item);
    }
    return;
}

void use_healing_item(const Item& item) {
    if (item.get_target_type() == "Single") {
        Character* chara = &party[party_option];
        if (chara->get_current_hp() == 0) {
            return;
        }
        if (chara->get_current_hp() < chara->get_max_hp()) {
            chara->set_current_hp(chara->get_current_hp() + item.get_amount());
            if (chara->get_current_hp() > chara->get_max_hp()) {
                chara->set_current_hp(chara->get_max_hp());
            }
            player.remove_item(item, 1);
        }
    }
    else {
        bool used = false;
        for (int i = 0; i < party_size; i++) {
            Character* chara = &party[i];
            if (chara->get_current_hp() < chara->get_max_hp() && chara->get_current_hp() != 0) {
                chara->set_current_hp(chara->get_current_hp() + item.get_amount());
                if (chara->get_current_hp() > chara->get_max_hp()) {
                    chara->set_current_hp(chara->get_max_hp());
                }
                used = true;
            }
        }
        if (used) {
            player.remove_item(item, 1);
        }
    }
    return;
}

void use_mana_item(const Item& item) {
    if (item.get_target_type() == "Single") {
        Character* chara = &party[party_option];
        if (chara->get_current_mp() < chara->get_max_mp()) {
            chara->set_current_mp(chara->get_current_mp() + item.get_amount());
            if (chara->get_current_mp() > chara->get_max_mp()) {
                chara->set_current_mp(chara->get_max_mp());
            }
            player.remove_item(item, 1);
        }
    }
    else {
        bool used = false;
        for (int i = 0; i < party_size; i++) {
            Character* chara = &party[i];
            if (chara->get_current_mp() < chara->get_max_mp()) {
                chara->set_current_mp(chara->get_current_mp() + item.get_amount());
                if (chara->get_current_mp() > chara->get_max_mp()) {
                    chara->set_current_mp(chara->get_max_mp());
                }
                used = true;
            }
        }
        if (used) {
            player.remove_item(item, 1);
        }
    }
    return;
}

void use_revive_item(const Item& item) {
    if (item.get_target_type() == "Single") {
        Character* chara = &party[party_option];
        if (chara->get_current_hp() == 0) {
            chara->set_current_hp(1);
            player.remove_item(item, 1);
        }
    }
    else {
        bool used = false;
        for (int i=0; i<party_size; i++) {
            Character* chara = &party[i];
            if (chara->get_current_hp() == 0) {
                chara->set_current_hp(1);
                used = true;
            }
        }
        if (used) {
            player.remove_item(item, 1);
        }
    }
}

void draw_equip_menu(SDL_Renderer* renderer) {
    // menu bg
    SDL_FRect item_menu = { 224.0f, 64.0f, 224.0f, 272.0f };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &item_menu);

    // equip icon
    SDL_Surface* wpn_icon = SDL_LoadBMP("img/sprites/gui/sword.bmp");
    SDL_Texture* wpn = SDL_CreateTextureFromSurface(renderer, wpn_icon);
    SDL_FRect wpn_rect = {256.0f, 112.0f, 32.0f, 32.0f };

    SDL_Surface* head_icon = SDL_LoadBMP("img/sprites/gui/head.bmp");
    SDL_Texture* head = SDL_CreateTextureFromSurface(renderer, head_icon);
    SDL_FRect head_rect = {256.0f, 144.0f, 32.0f, 32.0f };

    SDL_Surface* body_icon = SDL_LoadBMP("img/sprites/gui/body.bmp");
    SDL_Texture* body = SDL_CreateTextureFromSurface(renderer, body_icon);
    SDL_FRect body_rect = {256.0f, 176.0f, 32.0f, 32.0f };

    SDL_Surface* greaves_icon = SDL_LoadBMP("img/sprites/gui/greaves.bmp");
    SDL_Texture* greaves = SDL_CreateTextureFromSurface(renderer, greaves_icon);
    SDL_FRect greaves_rect = {256.0f, 208.0f, 32.0f, 32.0f };

    SDL_Surface* acc_icon = SDL_LoadBMP("img/sprites/gui/accessory.bmp");
    SDL_Texture* acc = SDL_CreateTextureFromSurface(renderer, acc_icon);
    SDL_FRect acc_rect = {256.0f, 240.0f, 32.0f, 32.0f };

    SDL_RenderTexture(renderer, wpn, NULL, &wpn_rect);
    SDL_RenderTexture(renderer, head, NULL, &head_rect);
    SDL_RenderTexture(renderer, body, NULL, &body_rect);
    SDL_RenderTexture(renderer, greaves, NULL, &greaves_rect);
    SDL_RenderTexture(renderer, acc, NULL, &acc_rect);

    SDL_SetRenderScale(renderer, 2.0f, 2.0f);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    draw_line(renderer, 240.0f, 80.0f, party[equip_char_option].get_name());
    // stats
    draw_line(renderer, 320.0f, 112.0f, "ATK:");
    draw_line(renderer, 320.0f, 144.0f, "DEF:");
    draw_line(renderer, 320.0f, 176.0f, "MAG:");
    draw_line(renderer, 320.0f, 208.0f, "RES:");
    draw_line(renderer, 320.0f, 240.0f, "SPD:");
    draw_line(renderer, 320.0f, 272.0f, "LCK:");

    draw_line(renderer, 400.0f, 112.0f, std::to_string(party[equip_char_option].get_current_strength()).c_str());
    draw_line(renderer, 400.0f, 144.0f, std::to_string(party[equip_char_option].get_current_defense()).c_str());
    draw_line(renderer, 400.0f, 176.0f, std::to_string(party[equip_char_option].get_current_intelligence()).c_str());
    draw_line(renderer, 400.0f, 208.0f, std::to_string(party[equip_char_option].get_current_magic_defense()).c_str());
    draw_line(renderer, 400.0f, 240.0f, std::to_string(party[equip_char_option].get_current_speed()).c_str());
    draw_line(renderer, 400.0f, 272.0f, std::to_string(party[equip_char_option].get_current_luck()).c_str());

    SDL_FRect item_desc = { 32.0f, 368.0f, 416.0f, 80.0f };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &item_desc);


    SDL_SetRenderScale(renderer, 2.0f, 2.0f);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // SDL_RenderDebugText(renderer, 24.0f, 192.0f, (player.get_inventory()[item_option].get_description().c_str()));

    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
    return;
}

void equip_menu_choices(SDL_Event event) {
    if (event.key.scancode == SDL_SCANCODE_A && equip_char_option > 0) {
        equip_char_option--;
    }
    else if (event.key.scancode == SDL_SCANCODE_S && equip_char_option < std::size(party)-1) {
        equip_char_option++;
    }
}
