#include <gb/gb.h>
#include <stdio.h>
#include "../game_0.h"
#include "level1_3.h"
#include "block_struct_0.h"
#include "../collision_1.h"
#include "../sound_0.h"
#include "../sounds/music_all.h"

static const struct Block *level_blocks = 0;
static UINT16 block_num = 0, loaded_block = 0;
volatile UINT8 temp_block[4] = {0, 0, 0, 0};

void load_first_blocks(struct Block *blocks, UINT8 bank) NONBANKED
{
    SWITCH_ROM_MBC1(bank);
    for(UINT8 bn=0; blocks[bn].x <= 160U; bn++) {
        temp_block[0] = blocks[bn].x + 8;
        temp_block[1] = blocks[bn].y + 16;
        temp_block[2] = blocks[bn].w;
        temp_block[3] = blocks[bn].h;
        add_block_collider(temp_block);
        loaded_block ++;
    }
    SWITCH_ROM_MBC1(1);
}

void load_blocks(UINT16 cameraX, UINT16 cameraY) NONBANKED
{
    //SWITCH_ROM_MBC1(bank);
    if(loaded_block == block_num) return;

    while(level_blocks[loaded_block].x == cameraX + 160) {
        temp_block[0] = 168;
        temp_block[1] = level_blocks[loaded_block].y - cameraY + 16;
        temp_block[2] = level_blocks[loaded_block].w;
        temp_block[3] = level_blocks[loaded_block].h;
        add_block_collider(temp_block);
        loaded_block ++;
    }
    //SWITCH_ROM_MBC1(1);
}

void load_scene(UINT8 *tiles, UINT8 * props, UINT8 bank) NONBANKED
{
    SWITCH_ROM_MBC1(bank);
    VBK_REG = 1;
    set_bkg_tiles(0, 0, 22, 18, props);
    VBK_REG = 0;
    set_bkg_tiles(0, 0, 22, 18, tiles);
    SWITCH_ROM_MBC1(1);
}

void load_level(UINT8 level)
{
    loaded_block = 0;

    switch (level)
    {
    case 1:
        HIDE_SPRITES;
        HIDE_BKG;

        level_blocks = LEVEL1_BLOCKS;
        block_num = LEVEL1_BLOCK_NUM;

        load_scene(LEVEL1_FIRST_SCREEN_TILES, LEVEL1_FIRST_SCREEN_PROPS, 3);
        level_tiles = LEVEL1_TILES;
        level_props = LEVEL1_PROPS;
        mapWidth = LEVEL1_WIDTH;
        mapHeight = LEVEL1_HEIGHT;

        load_first_blocks(LEVEL1_BLOCKS, 3);
        
        play_music(&AHOU_MAJO);

        SHOW_SPRITES;
        SHOW_BKG;
        break;
    
    default:
        break;
    }
}

void init_level(UINT8 level)
{
    init_blocks();
    load_level(level);
}