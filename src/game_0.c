#include <gb/gb.h>
#include <stdio.h>
#include "sprite_0.h"
#include "player_1.h"
#include "enemy_1.h"
#include "hud_1.h"
#include "collision_1.h"
#include "levels/level_1.h"

UINT8 key = 0;
//Camera-Horizontal-Speed should be always larger than or equal to 0
UINT8 cameraHSpeed = 0, cameraVSpeed = 0;
UINT16 mapWidth = 0, mapHeight = 0;
const UINT8 *level_tiles = NULL, *level_props = NULL;

UINT8 cameraTimer = 0;
UINT16 cameraX = 0, cameraY = 0;

UINT16 tileX = 0, counter = 0, temX = 0, temY = 0;
UINT8 camTileX = 0;

unsigned char mod8(unsigned char num, unsigned char denom);

/*.ts ignore:start */
void update_map(UINT8 bank) NONBANKED
/*.ts ignore:end */
{
    SWITCH_ROM_MBC1(bank);
    cameraX += cameraHSpeed;
    cameraY += cameraVSpeed;
    scroll_bkg(cameraHSpeed, cameraVSpeed);

    camTileX += cameraHSpeed;
    if(cameraHSpeed != 0) {
        load_blocks(cameraX, cameraY);

        if (camTileX == 8) {
            camTileX = 0;
            tileX++;
            counter = tileX + 21;
            temX = mod8(counter, 32);
            temY = counter * mapHeight;
            VBK_REG = 1;
            set_bkg_tiles(temX, 0, 1, mapHeight, (UINT8 *)(level_props + temY));
            VBK_REG = 0;
            set_bkg_tiles(temX, 0, 1, mapHeight, (UINT8 *)(level_tiles + temY));
        }
    }
    SWITCH_ROM_MBC1(0);
}

void game_update()
{
    cameraTimer++;
    if (cameraTimer == 3)
    {
        cameraHSpeed = 1;
        cameraTimer = 0;
    }
    SWITCH_ROM_MBC1(1);
    update_player();
    DEBUG_update_Michelle();
    update_score();
    update_HP();
    SWITCH_ROM_MBC1(0);
    update_map(3);
    cameraHSpeed = 0;
    drawAllSprites();
}

extern const unsigned char GAME_SPRITE_GRAPHICS[];
extern const unsigned char GAME_SPRITE_PALETTE[];
extern const unsigned char GAME_BKG_GRAPHICS[];
extern const unsigned int GAME_HUD_PALETTE[];
extern const unsigned char HUD_MAP_TILES[];
extern const unsigned char HUD_MAP_PROPS[];
extern const unsigned char SKY_MAP_TILES[];
extern const unsigned char SKY_MAP_PROPS[];

void init_game() NONBANKED
{
    SWITCH_ROM_MBC1(2);
    set_sprite_palette(0, 6, GAME_SPRITE_PALETTE);
    set_sprite_data(0, 64, GAME_SPRITE_GRAPHICS);
    SWITCH_ROM_MBC1(3);
    set_bkg_data(0, 64, GAME_BKG_GRAPHICS);
    set_bkg_palette(0, 4, GAME_HUD_PALETTE);
    VBK_REG = 1;
    set_bkg_tiles(0, 0, 32, 18, SKY_MAP_PROPS);
    VBK_REG = 0;
    set_bkg_tiles(0, 0, 32, 18, SKY_MAP_TILES);
    VBK_REG = 1;
    set_win_tiles(0, 0, 17, 1, HUD_MAP_PROPS);
    VBK_REG = 0;
    set_win_tiles(0, 0, 17, 1, HUD_MAP_TILES);
    move_win(31, 136);
    SWITCH_ROM_MBC1(0);
    SHOW_SPRITES;
    SHOW_BKG;
    SHOW_WIN;

    SWITCH_ROM_MBC1(1);
    init_player();
    //init_Michelle();
    init_level(1);
    SWITCH_ROM_MBC1(0);
    cameraX = 0;
    cameraY = 0;
    tileX = 0;
    counter = 21;
    camTileX = 0;
}

//shift n to t at the speed of v (all integers)
void shiftTo(INT16 *n, INT16 t, INT16 v)
{
    if (*n > t + v)
    {
        *n -= v;
    }
    else if (*n < t - v)
    {
        *n += v;
    }
    else
    {
        *n = t;
    }
}

extern const unsigned char DEBUG_TILES[];
extern const unsigned char DEBUG_PROPS[];
extern const unsigned char SKY_MAP_TILES[];
extern const unsigned char SKY_MAP_PROPS[];

unsigned char mod8(unsigned char num, unsigned char denom) NONBANKED {
    while(num >= denom) {
        num -= denom;
    }
    return num;
}