#ifndef COLLISION_H
#define COLLISION_H

#define COLLIDABLE_TILES_MAXIMUM 10

void init_blocks(void);
UINT8 player_collide_all_tiles(struct Collider *p, UINT8 plx, UINT8 ply);
void add_block_collider(UINT8 *b);
void remove_block_collider(UINT8 num);

#endif