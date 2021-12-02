#include <gb/drawing.h>
#include <stdio.h>

#include "sprite_0.h"
#include "player_1.h"
#include "game_0.h"
#include "collision_1.h"

//A 8-bit binary variable, format: 0000 lrud (left/right/up/down collided)
static volatile UINT8 rigid_state = 0;
static UINT8 col_i = 0, col_num = 0;
static UINT8 *current_block = NULL;
static volatile UINT8 colNum_temp = 0;

//2D array of UINT8, block format: x, y, w, h, isActive
UINT8 blocks[COLLIDABLE_TILES_MAXIMUM][5];

INT8 collideWithInteger(struct Collider *c1, UINT8 *b) {
    return (c1->x < b[0] + b[2] && c1->x + c1->w > b[0] && c1->y < b[1] + b[3] && c1->y + c1->h > b[1]);
}

void player_collide_tile(struct Collider *p, UINT8 *b, UINT8 plx, UINT8 ply)
{
    if(!collideWithInteger(p, b)) return;

    if(ply + p->h <= b[1] + cameraVSpeed) {
        rigid_state |= 0b0001U;
        p->y = b[1] - p->h - 1;
    }else if(ply >= b[1] + b[3] + cameraVSpeed) {
        rigid_state |= 0b0010U;
        p->y = b[1] + b[3] + 1;
    }
    if(plx + p->w <= b[0] + cameraHSpeed) {
        rigid_state |= 0b0100U;
        p->x = b[0] - p->w - 1;
    }else if(plx >= b[0] + b[2] + cameraHSpeed) {
        rigid_state |= 0b1000U;
        p->x = b[0] + b[2] + 1;
    }
}

void move_block(UINT8 *b)
{
    INT16 dif = (INT16)b[0] - (INT16)cameraHSpeed;
    if(dif < -b[2]) {
        remove_block_collider(col_i);
    }else if(dif < 0) {
        b[0] = 0;
        b[2] += dif;
    }else {
        b[0] = (UINT8)dif;
    }

    dif = (INT16)b[1] - (INT16)cameraVSpeed;
    if(dif < 0) {
        b[1] = 0;
        b[3] += dif;
    }else if(dif > 160) {
        b[1] = 160;
        b[3] += 160 - dif;
    }else {
        b[1] = (UINT8)dif;
    }
}

UINT8 player_collide_all_tiles(struct Collider *p, UINT8 plx, UINT8 ply)
{
    rigid_state = 0U;

    if(p->x < PLAYER_LEFT_BORDER) {
        p->x = PLAYER_LEFT_BORDER;
        rigid_state |= 0b1000U;
    }else if(p->x > PLAYER_RIGHT_BORDER) {
        p->x = PLAYER_RIGHT_BORDER;
        rigid_state |= 0b0100U;
    }
    if(p->y < PLAYER_UP_BORDER) {
        p->y = PLAYER_UP_BORDER;
        rigid_state |= 0b0010U;
    }else if(p->y > PLAYER_DOWN_BORDER) {
        p->y = PLAYER_DOWN_BORDER;
        rigid_state |= 0b0001U;
    }

    for(col_i = 0; col_i != COLLIDABLE_TILES_MAXIMUM; ++col_i) {
        current_block = blocks[col_i];
        if(current_block[4] != 0) {
            move_block(current_block);
            player_collide_tile(p, current_block, plx, ply);
        }
    }
    //printf("%d\n",col_num);
    return rigid_state;
}

void init_blocks()
{
    col_num = 0;
}

void add_block_collider(UINT8 *b) NONBANKED
{
    //Iterate to get an empty adress to add a block
    colNum_temp = col_num - 1;

    while(blocks[col_num][4] == 1) {
        col_num ++;
        if(col_num == COLLIDABLE_TILES_MAXIMUM) 
            col_num = 0;
        else if(col_num == colNum_temp)
            return;
    }

    blocks[col_num][4] = 1;
    blocks[col_num][0] = b[0];
    blocks[col_num][1] = b[1];
    blocks[col_num][2] = b[2];
    blocks[col_num][3] = b[3];
    col_num ++;
}

void remove_block_collider(UINT8 num)
{
    blocks[num][4] = 0;
    col_num = num;
}