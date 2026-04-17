#include "../classes/entity.h"
#include <vector>

struct Script{
    std::vector<std::string> lines;
    int currentLine = 0;
    bool active = false;
    bool waitingForInput = false;
    bool waitingForMove = false;
    Entity* targetNpc = nullptr;
};


void move_npc_request(Entity& npc, int dir);
void move_up(Entity* npc);
void move_down(Entity* npc);
void move_left(Entity* npc);
void move_right(Entity* npc);

void script_load(std::string path, Entity* npc);
void script_update();
void script_next();
bool script_is_active();



extern uint8_t map[15][15];
extern uint8_t tile_walkable_tresh;
