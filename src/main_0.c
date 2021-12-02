#include <gb/gb.h>
#include <stdio.h>
#include "main_0.h"
#include "game_0.h"
#include "sprite_0.h"
#include "sound_0.h"
#include "sounds/sfx_2.h"
#include "sounds/music_all.h"

void menu_update(void);
void init_intro(void);
void update_intro(void);
void init(void);
void init_menu(void);
extern void update_volume(void);
extern void init_music(void);

static UINT8 game_state = 0;
UINT16 main_frame = 0;
UINT8 i = 0;

extern const unsigned int INTRO_PALETTE[], LOGO_PALETTE[];
extern const unsigned char LOGO_MAP[], LOGO_DATA[];

int main() NONBANKED
{
    disable_interrupts();
    cpu_fast();
    init();
    enable_interrupts();

    update_intro();

    while(1) {
        switch (game_state)
        {
        case 0:
            menu_update();
            break;
        
        case 1:
            init_game();
            game_state = 2;
            break;

        case 2:
            game_update();
            break;
        
        default:
            break;
        }
        update_volume();
        wait_vbl_done();
    }
}

extern const unsigned char PUSH_START_TILES_1[];
extern const unsigned char PUSH_START_TILES_2[];
extern const unsigned int GAME_SPRITE_PALETTE[];

void menu_update() NONBANKED
{
    main_frame++;
    if(main_frame == 53) main_frame = 2;
    else if(main_frame == 1) init_menu();
    switch(main_frame) {
        case 32:
            set_bkg_tiles(9, 11, 10, 1, PUSH_START_TILES_2);
            break;
        case 52:
            set_bkg_tiles(9, 11, 10, 1, PUSH_START_TILES_1);
            break;
        default:
            break;
    }
    if(joypad() & J_START) {
        waitpadup();
        game_state = 1;
    }
}

extern const unsigned char PUSH_START_GRAPHICS[];
extern unsigned char pixel_art_splashscreen_data[];
extern const unsigned char pixel_art_splashscreen_map[];
extern const unsigned char TITLE_DATA[];
extern const unsigned char TITLE_MAP[];

void init_menu() NONBANKED
{
    screen_fade_out(1, INTRO_PALETTE, 1);
    HIDE_BKG;
    SWITCH_ROM_MBC1(1);
    /*VBK_REG = 1;
    set_bkg_tiles(0, 0, 32, 18, SKY_MAP_PROPS);*/
    //VBK_REG = 0;
    set_bkg_tiles(9, 11, 10, 1, PUSH_START_TILES_1);
    SWITCH_ROM_MBC1(0);
    SHOW_BKG;
    play_music(&SOKOKUNO_KOBANATACHI);
    mute(FALSE);
    screen_fade_in(1, INTRO_PALETTE, 1);
}

void init_intro() NONBANKED
{
    screen_fade_out(2, LOGO_PALETTE, 1);
    HIDE_BKG;
    SWITCH_ROM_MBC1(1);
    set_bkg_data(0, 156, pixel_art_splashscreen_data);
    set_bkg_data(156, 8, PUSH_START_GRAPHICS);
    set_bkg_data(166, 41, TITLE_DATA);
    /*VBK_REG = 1;
    set_bkg_tiles(0, 0, 32, 18, SKY_MAP_PROPS);*/
    //VBK_REG = 0;
    set_bkg_tiles(0, 0, 20, 18, pixel_art_splashscreen_map);
    //set_bkg_tiles(9, 11, 10, 1, PUSH_START_TILES_1);
    set_bkg_tiles(11, 2, 9, 5, TITLE_MAP);
    SWITCH_ROM_MBC1(0);
    SHOW_BKG;
    screen_fade_in(2, INTRO_PALETTE, 1);
}

void init_intro_and_menu(unsigned int * palette) NONBANKED
{
    screen_fade_out(1, palette, 1);
    HIDE_BKG;
    SWITCH_ROM_MBC1(1);
    set_bkg_data(0, 156, pixel_art_splashscreen_data);
    set_bkg_data(156, 8, PUSH_START_GRAPHICS);
    set_bkg_data(166, 41, TITLE_DATA);
    set_bkg_tiles(0, 0, 20, 18, pixel_art_splashscreen_map);
    set_bkg_tiles(9, 11, 10, 1, PUSH_START_TILES_1);
    set_bkg_tiles(11, 2, 9, 5, TITLE_MAP);
    SWITCH_ROM_MBC1(0);
    SHOW_BKG;
    play_music(&SOKOKUNO_KOBANATACHI);
    mute(FALSE);
    screen_fade_in(1, INTRO_PALETTE, 1);
}

void update_intro()
{
    for(main_frame=0; main_frame!=INTRO_FRAME; ++main_frame) {
        wait_vbl_done();
        if(main_frame == 150) {
            init_intro();
        }else if(main_frame == 260) {
            mute(TRUE);
        }
        if(joypad() & J_A || joypad() & J_START) {
            mute(TRUE);
            waitpadup();
            if(main_frame<=150)
                init_intro_and_menu(LOGO_PALETTE);
            else
                init_intro_and_menu(INTRO_PALETTE);
            main_frame = 2;
            return;
        }
    }
    main_frame = 0;
}

void init()
{
    //Register sound
    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;
    OBP1_REG = 0xD2;

    set_bkg_palette(0, 1, LOGO_PALETTE);
    set_bkg_data(0, 109, LOGO_DATA);
    set_bkg_tiles(0, 0, 20, 18, LOGO_MAP);
    SPRITES_8x16;
    SHOW_SPRITES;
    SHOW_BKG;

    init_music();
}

//Credits to Simon Larson's code on Github
//------------------------CODE BELOW FROM GITHUB-----------------------
#define GET_RED(c) (c & 0x1FU)
#define GET_GREEN(c) ((c >> 5) & 0x1FU)
#define GET_BLUE(c) ((c >> 10) & 0x1FU)
#define RGB(r, g, b) \
  ((((UINT16)(b) & 0x1f) << 10) | (((UINT16)(g) & 0x1f) << 5) | (((UINT16)(r) & 0x1f) << 0))

UINT16 palette_buffer[32];
UINT16 *palette_ram = (UINT16 *)0xFF69;
UINT8 *palette_index = (UINT8 *)0xFF68;

void screen_fade_in(UINT8 delay, UINT16 * target, UINT8 number) {
    UINT8 i, c;
    UINT8 r, g, b;
    UINT16 v;
    UINT8 size = number * 4U;

    for(c = 0U; c != 32U; ++c) {
        palette_buffer[c] = 32767;
    }

    for(i = 31U; i != 1U; i -= 2U) {
        for(c = 0U; c != size; ++c) {
            v = target[c];
            r = GET_RED(v);
            g = GET_GREEN(v);
            b = GET_BLUE(v);

            if(r <= 31U-i) r += i; else r = 31U;
            if(g <= 31U-i) g += i; else g = 31U;
            if(b <= 31U-i) b += i; else b = 31U;
            palette_buffer[c] = RGB(r, g, b);
        }

        while((STAT_REG & 3U) == 1U) {}
        set_bkg_palette(0, number, palette_buffer);

        for(c = 0U; c != delay; ++c) {
            wait_vbl_done();
        }
    }

    set_bkg_palette(0, number, target);
}

void screen_fade_out(UINT8 delay, UINT16 * start, UINT8 number) {
    UINT8 i, c;
    UINT8 r, g, b;
    UINT16 v;
    UINT8 size = number * 4U;

    for(i = 0U; i != size; ++i) {
        palette_buffer[i] = start[i];
    }

    for(i = 0U; i != 15U; ++i) {
        for(c = 0U; c != size; ++c) {
            v = palette_buffer[c];
            r = GET_RED(v);
            g = GET_GREEN(v);
            b = GET_BLUE(v);

            if(r <= 29U) r += 2U; else r = 31U;
            if(g <= 29U) g += 2U; else g = 31U;
            if(b <= 29U) b += 2U; else b = 31U;
            palette_buffer[c] = RGB(r, g, b);
        }

        while((STAT_REG & 3U) == 1U) {}
        set_bkg_palette(0, number, palette_buffer);

        for(c = 0U; c != delay; ++c) {
            wait_vbl_done();
        }
    }
}
//------------------------END OF GITHUB CODE-----------------------