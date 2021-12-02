#include <gb/gb.h>
#include <stdio.h>
#include <gb/drawing.h>
#include "sprite_0.h"

//Screen x, screen y, iterator x, iterator y, iterator for pointer to graphics and palettes
static volatile UINT8 scX = 0, scY = 0, iX = 0, iY = 0, *iGr = NULL, *iPl = NULL;
static UINT8 flipX = 0;
static volatile UINT8 currentSprite = 0;
extern UINT8 i;

INT8 collide(struct Collider *c1, struct Collider *c2) {
    return (c1->x < c2->x + c2->w && c1->x + c1->w > c2->x && c1->y < c2->y + c2->h && c1->y + c1->h > c2->y);
}

typedef struct {
    UINT8 x, y;
    UINT8 width, height;
    INT8 alive;
    INT8 flipped;
    struct Collider *collider;
    UINT8 *tileNum, *palettes;
    UINT8 prop;
}Sprite;

Sprite sprites16[SPRITE16_NUM];
//Sprite sprites8[SPRITE8_NUM];

inline void setSprite16(UINT8 num, UINT8 _x, UINT8 _y, UINT8 _w, UINT8 _h, UINT8 *_tileNum, UINT8 *_palettes) NONBANKED {
    Sprite *sp = &sprites16[num];
    sp->x = _x;
    sp->y = _y;
    sp->width = _w;
    sp->height = _h;
    sp->alive = 0;
    sp->flipped = 0;
    sp->collider = NULL;
    sp->tileNum = _tileNum;
    sp->palettes = _palettes;
    sp->prop = 0;
}

void setSprite16Prop(UINT8 num, UINT8 _prop) {
    sprites16[num].prop = _prop;
}

void moveSprite16(UINT8 num, UINT8 _x, UINT8 _y) {
    Sprite *sp = &sprites16[num];
    sp->x = _x;
    sp->y = _y;
}

void activateSprite16(UINT8 num, UINT8 state) {
    sprites16[num].alive = state;
}

void flipSprite16(UINT8 num, INT8 state) {
    sprites16[num].flipped = state;
}

void setPaletteForSprite16(UINT8 num, unsigned char *_palettes) {
    sprites16[num].palettes = _palettes;
}

void setGraphicsForSprite16(UINT8 num, unsigned char *graphics) {
    sprites16[num].tileNum = graphics;
}

void attachCollider(UINT8 num, struct Collider *c) {
    sprites16[num].collider = c;
}

void moveCollider(UINT8 num, UINT8 _dx, UINT8 _dy) {
    Sprite *sp = &sprites16[num];
    if(sp->collider != NULL) {
        struct Collider *c = sp->collider;
        c->dx = _dx;
        c->dy = _dy;
        c->x = sp->x + c->dx;
        c->y = sp->y + c->dy;
    }
}

inline void updateCollider(UINT8 num) NONBANKED {
    Sprite *sp = &sprites16[num];
    if(sp->collider != NULL) {
        struct Collider *c = sp->collider;
        c->x = sp->x + c->dx;
        c->y = sp->y + c->dy;
        //DEBUG
        //box(c->x-8, c->y-16, c->w + c->x-8, c->y + c->h-16, M_NOFILL);
    }
}

inline struct Collider* getCollider(UINT8 num) NONBANKED {
    return sprites16[num].collider;
}

inline void setSprite16Tiles(UINT8 num, UINT8 *tiles) NONBANKED {
    sprites16[num].tileNum = tiles;
}

//Sprite8 has been abondoned because GBDK doesn't support
//displaying 8x8 and 8x16 sprite tiles simultaneously.

/*void setSprite8(UINT8 num, UINT8 _x, UINT8 _y, UINT8 _w, UINT8 _h, UINT8 *_tileNum) {
    Sprite *sp = &sprites8[num];
    sp->x = _x;
    sp->y = _y;
    sp->width = _w;
    sp->height = _h;
    sp->alive = 1;
    sp->flipped = 0;
    sp->collider = NULL;
    sp->tileNum = _tileNum;
}*/

inline void drawSpriteFlip(Sprite *sp, UINT8 size) NONBANKED {
    scX = flipX = sp->x + 8 * sp->width - 8;
    scY = sp->y;
    iGr = sp->tileNum;
    iPl = sp->palettes;
    for(iY = 0; iY != sp->height; ++iY) {
        for(iX = sp->width; iX != 0; --iX) {
            if(*iGr != NULL_SPRITE) {
                //set palette and flip by binary operation
                set_sprite_prop(currentSprite, *iPl | 0x20U | sp->prop);
                set_sprite_tile(currentSprite, *iGr);
                move_sprite(currentSprite, scX, scY);
                ++currentSprite;
            }
            ++iGr;
            ++iPl;
            if(currentSprite == 40) return;
            scX -= 8;
        }
        scX = flipX;
        scY += size;
    }
}

inline void drawSprite16(Sprite *sp) NONBANKED {
    if(!sp->alive) return;
    if(sp->flipped) {
        drawSpriteFlip(sp, 16);
        return;
    }

    scX = sp->x;
    scY = sp->y;
    iGr = sp->tileNum;
    iPl = sp->palettes;
    for(iY = 0; iY != sp->height; ++iY) {
        for(iX = 0; iX != sp->width; ++iX) {
            if(*iGr != NULL_SPRITE) {
                set_sprite_prop(currentSprite, *iPl | sp->prop);
                set_sprite_tile(currentSprite, *iGr);
                move_sprite(currentSprite, scX, scY);
                ++currentSprite;
            }
            ++iGr;
            ++iPl;
            if(currentSprite == 40) return;
            scX += 8;
        }
        scX = sp->x;
        scY += 16;
    }
}

/*void drawSprite8(Sprite *sp) {
    if(!sp->alive) return;
    if(sp->flipped) {
        drawSpriteFlip(sp, 8);
        return;
    }

    scX = sp->x;
    scY = sp->y;
    iGr = sp->tileNum;
    for(iY = 0; iY != sp->height; ++iY) {
        for(iX = 0; iX != sp->width; ++iX) {
            if(iGr != NULL) {
                set_sprite_tile(currentSprite, *iGr);
                move_sprite(currentSprite, scX, scY);
            }
            ++iGr;
            ++currentSprite;
            if(currentSprite == 40) return;
            scX += 8;
        }
        scX = sp->x;
        scY += 8;
    }
}*/

void drawAllSprites() {
    currentSprite = 0;

    for(i = 0; i < SPRITE16_NUM; ++i) {
        drawSprite16(&sprites16[i]);
        if(currentSprite == 40) return;
    }

    for(i = currentSprite; i != 40; ++i) {
        set_sprite_tile(i, NULL_SPRITE);
    }

    /*SPRITES_8x8;
    for(i = 0; i < SPRITE8_NUM; ++i) {
        drawSprite8(&sprites8[i]);
        if(currentSprite == 40) return;
    }*/
}

void disableAllSprites() {
    for(i = 0; i < SPRITE16_NUM; ++i) {
        sprites16[i].alive = INACTIVE;
    }
    gprintln(1, 20, SIGNED);
}

INT8 collideSprite(UINT8 n1, UINT8 n2) {
    struct Collider *c1 = sprites16[n1].collider;
    struct Collider *c2 = sprites16[n2].collider;
    if(c1 == NULL || c2 == NULL)
        return 0;
    else
        return collide(c1, c2);
}