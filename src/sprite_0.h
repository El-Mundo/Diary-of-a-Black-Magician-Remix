#ifndef SPRITE_H
#define SPRITE_H
#include <gb/gb.h>

#define SPRITE16_NUM 12
#define SPRITE8_NUM 6

#define ACTIVE 1
#define INACTIVE 0

#define FLIPPED 1
#define UNFLIPPED 0

#define NULL_SPRITE 126

struct Collider {
    unsigned char dx, dy, w, h, x, y;
};

void setSprite16(UINT8 num, UINT8 _x, UINT8 _y, UINT8 _w, UINT8 _h, UINT8 *_tileNum, UINT8 *palettes);
//void setSprite8(UINT8 num, UINT8 _x, UINT8 _y, UINT8 _w, UINT8 _h, UINT8 *_tileNum);
void drawAllSprites(void);
void activateSprite16(UINT8 num, UINT8 state);
void moveSprite16(UINT8 num, UINT8 _x, UINT8 _y);
void flipSprite16(UINT8 num, INT8 state);
INT8 collide(struct Collider *c1, struct Collider *c2);
INT8 collideSprite(UINT8 n1, UINT8 n2);
void attachCollider(UINT8 num, struct Collider *c);
void updateCollider(UINT8 num);
void disableAllSprites(void);
void setPaletteForSprite16(UINT8 num, unsigned char *_palettes);
void setGraphicsForSprite16(UINT8 num, unsigned char *graphics);
void moveCollider(UINT8 num, UINT8 _dx, UINT8 _dy);
void setSprite16Prop(UINT8 num, UINT8 _prop);
inline void setSprite16Tiles(UINT8 num, UINT8 *tiles);
inline struct Collider* getCollider(UINT8 num);

#endif