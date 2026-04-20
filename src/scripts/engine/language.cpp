#include "scripts/engine/language.h"
#include "scripts/engine/ui.h"
#include <fstream>

// SCRIPTING LANGUAGE
// COMMANDS:
// UP: go up
// DOWN: go down
// LEFT: go left
// RIGHT: go right
// BATTLE@BATTLE_ID: start a battle (boss?)
// BUFFSTAT@STAT_ID@amount: buff a stat
// GIVE@ITEM_ID@quantity: give item to player
// REMOVE@ITEM_ID@quantity: remove item from player
// ADDPARTY@ID: add to party
// SETON@FLAG_ID: set a flag on
// SETOFF@FLAG_ID: set a flag off
// IF@FLAG_ID: checks if a flag is on
// IFMULT@FLAG_ID1@FLAG_ID2@...: check multiple flags
// >COMMAND: indentation
// MSG@MESSAGE: message
// DISAPPEAR: scompare
// END: end script

#define NPC_OFFSET 216
#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

static Script ctx;

void script_load(std::string path, Entity* npc) {
    ctx.lines.clear();
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) ctx.lines.push_back(line);
    }
    ctx.targetNpc = npc;
    ctx.currentLine = 0;
    ctx.active = true;
    ctx.waitingForInput = false;
    ctx.waitingForMove = false;
}

void script_update() {
    if (!ctx.active || ctx.waitingForInput) return;

    if (ctx.waitingForMove) {
        if (!ctx.targetNpc->get_moving()) {
            ctx.waitingForMove = false;
            ctx.currentLine++;
        }
        return;
    }

    if (ctx.currentLine >= ctx.lines.size()) {
        return;
    }

    std::string cmd = ctx.lines[ctx.currentLine];
    can_move = false;
    // esecuzione comandi
    if (cmd == "UP") {
        move_npc_request(*ctx.targetNpc, UP);
        ctx.waitingForMove = true;
    }
    else if (cmd == "DOWN") {
        move_npc_request(*ctx.targetNpc, DOWN);
        ctx.waitingForMove = true;
    }
    else if (cmd == "LEFT") {
        move_npc_request(*ctx.targetNpc, LEFT);
        ctx.waitingForMove = true;
    }
    else if (cmd == "RIGHT") {
        move_npc_request(*ctx.targetNpc, RIGHT);
        ctx.waitingForMove = true;
    }
    else if (cmd.find("BATTLE@") == 0) { //
        int battle_id = std::stoi(cmd.substr(7));
        // start battle with id
    }
    // continue
    //
    else if (cmd.find("MSG@") == 0) {
        std::string msg = cmd.substr(4);
        ui_show_message(msg);
        ctx.waitingForInput = true;
    }
    else if (cmd.find("GIVE@") == 0) {
        std::string msg = cmd.substr(5);
        ui_show_item_get_message("item_name");
        ctx.waitingForInput = true;
        // add item to inventory
    }
    else if (cmd == "END") {
        ctx.active = false;
        can_move = true;
    }
    else {
        ctx.currentLine++;
    }
}

void script_next() {
    if (ctx.active && ctx.waitingForInput) {
        ctx.waitingForInput = false;
        ctx.currentLine++;
        ui_close_message();
    }
}


void move_up(Entity* npc)    { move_npc_request(*npc, UP); }
void move_down(Entity* npc)  { move_npc_request(*npc, DOWN); }
void move_left(Entity* npc)  { move_npc_request(*npc, LEFT); }
void move_right(Entity* npc) { move_npc_request(*npc, RIGHT); }


void move_npc_request(Entity& npc, int dir) {
    if (npc.get_moving()) {
        return;
    }

    int grid_x_pos = npc.get_pos_x() / 32;
    int grid_y_pos = npc.get_pos_y() / 32;

    int next_x = grid_x_pos;
    int next_y = grid_y_pos;

    if (dir == UP)      next_y--;
    if (dir == DOWN)    next_y++;
    if (dir == LEFT)    next_x--;
    if (dir == RIGHT)   next_x++;

    if (next_x >= 0 && next_x < 15 && next_y >= 0 && next_y < 15 && map[next_y][next_x] <= tile_walkable_tresh) {
        map[grid_y_pos][grid_x_pos] = 0;
        map[next_y][next_x] = npc.get_id() + NPC_OFFSET;

        npc.set_target_x(next_x*32.0f);
        npc.set_target_y(next_y*32.0f);
        npc.set_current_dir(dir);
        npc.set_moving(true);
    }

}

bool script_is_active() {
    return ctx.active;
}
