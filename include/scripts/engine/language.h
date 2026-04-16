#include "../classes/entity.h"


void move_npc_request(Entity& npc, int dir);
void move_up(Entity* npc);
void move_down(Entity* npc);
void move_left(Entity* npc);
void move_right(Entity* npc);



extern uint8_t map[15][15];
extern uint8_t tile_walkable_tresh;
