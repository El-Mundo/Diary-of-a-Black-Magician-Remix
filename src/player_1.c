#include <gb/gb.h>
#include <stdio.h>
#include <gb/drawing.h>
#include "game_0.h"
#include "player_1.h"
#include "sprite_0.h"
#include "collision_1.h"
#include "sound_0.h"
#include "sounds/sfx_2.h"

UINT16 playerRX = 0, playerRY = 0;
UINT8 playerState = 0, playerHP = 0;

struct Korriel {
    UINT16 rx, ry;
    INT16 hSpeed, vSpeed;
    UINT8 frame, state;
    /*Player state:
    0: Enter
    1: Idle
    2: Attack
    3: Hurt
    4: Retire
    */
    UINT8 hp;
}player = {8, 1280};

void switch_player_state(UINT8 num)
{
    player.state = num;
    player.frame = 0;
}

static volatile UINT8 lSprite_px, lSprite_py;
//Volatile Colliders for rigidbody collision detection and movement
volatile struct Collider pCollider;
void rigid_collision(struct Korriel *p);

void update_Korriel(struct Korriel *p) {
    key = joypad();

    if(key & J_UP){
        if(p->vSpeed > PLAYER_VELOCITY_MIN)    
            p->vSpeed -= PLAYER_ACCELERATION;
    }else if (key & J_DOWN){
        if(p->vSpeed < PLAYER_VELOCITY_MAX)    
            p->vSpeed += PLAYER_ACCELERATION;
    }else {
        shiftTo(&p->vSpeed, 0, PLAYER_BRAKE);
    }
    if(key & J_RIGHT){
        if(p->hSpeed < PLAYER_VELOCITY_MAX)
            p->hSpeed += PLAYER_ACCELERATION;
    }else if (key & J_LEFT){
        if(p->hSpeed > PLAYER_VELOCITY_MIN)
            p->hSpeed -= PLAYER_ACCELERATION;
    }else {
        shiftTo(&p->hSpeed, 0, PLAYER_BRAKE);
    }

    rigid_collision(p);
}

extern const unsigned char KORRIEL_ANIMATION[];
extern const unsigned char GAME_SPRITE_GRAPHICS[];

const unsigned char tileNums[] = {NULL_SPRITE, NULL_SPRITE, 0, 2, 4, 6, 8, 10};
const unsigned char sprc[] = {0x00U, 0x00U, 0x01U, 0x01U, 0x02U, 0x02U, 0x02U, 0x02U};
const unsigned char icc[] = {0x01U, 0x01U};
const unsigned char ICON_NORMAL[] = {32, 34};
const unsigned char ICON_HURT[] = {36, 38};
const unsigned char ICON_WIN[] = {40, 42};

void animate_Korriel(struct Korriel *p)
{
    p->frame ++;
    if(p->state == 1) {
        switch (p->frame)
        {
        case 7:
        case 21:
            set_sprite_data(0, 2, &KORRIEL_ANIMATION[0]);
            set_sprite_data(4, 2, &KORRIEL_ANIMATION[64]);
            set_sprite_data(6, 2, &KORRIEL_ANIMATION[256]);
            break;
        case 14:
            set_sprite_data(0, 2, &KORRIEL_ANIMATION[32]);
            set_sprite_data(4, 2, &KORRIEL_ANIMATION[96]);
            set_sprite_data(6, 2, &KORRIEL_ANIMATION[160]);
            break;
        case 28:
            set_sprite_data(0, 2, &KORRIEL_ANIMATION[192]);
            set_sprite_data(4, 2, &KORRIEL_ANIMATION[224]);
            set_sprite_data(6, 2, &KORRIEL_ANIMATION[128]);
            p->frame = 0;
            break;
        default:
            break;
        }
    }else if(p->state == 3) {
        switch (p->frame)
        {
        case 12:
            activateSprite16(PLAYER_SPRITE_NUM, INACTIVE);
            set_sprite_data(2, 2, &KORRIEL_ANIMATION[288]);
            set_sprite_data(0, 2, &KORRIEL_ANIMATION[32]);
            set_sprite_data(4, 2, &KORRIEL_ANIMATION[96]);
            set_sprite_data(6, 2, &KORRIEL_ANIMATION[160]);
            break;
        case 24:
        case 48:
        case 72:
        case 96:
            activateSprite16(PLAYER_SPRITE_NUM, ACTIVE);
            break;
        case 36:
        case 60:
        case 84:
            activateSprite16(PLAYER_SPRITE_NUM, INACTIVE);
            break;
        case 120:
            set_sprite_data(2, 2, &KORRIEL_ANIMATION[320]);
            setSprite16Tiles(PLAYER_ICON_NUM, ICON_NORMAL);
            switch_player_state(1);
            break;
        default:
            break;
        }
    }
}

struct Collider kC = {17, 8, 10, 20};

void init_player()
{
    setSprite16(PLAYER_SPRITE_NUM, player.rx / PLAYER_MOVE_DIV, player.ry / PLAYER_MOVE_DIV, 4, 2, tileNums, sprc);
    activateSprite16(PLAYER_SPRITE_NUM, ACTIVE);
    attachCollider(PLAYER_SPRITE_NUM, &kC);
    setSprite16Prop(PLAYER_SPRITE_NUM, 0x80U);
    player.rx = 8;
    player.ry = 1280;
    pCollider.x = (UINT8)(player.rx / PLAYER_MOVE_DIV) + kC.dx;
    pCollider.y = (UINT8)(player.ry / PLAYER_MOVE_DIV) + kC.dy;
    pCollider.w = kC.w - 2;
    pCollider.h = kC.h - 2;
    switch_player_state(1);
    player.hp = 3;

    setSprite16(PLAYER_ICON_NUM, 12, 144, 2, 1, ICON_NORMAL, icc);
    activateSprite16(PLAYER_ICON_NUM, ACTIVE);
}

void update_player()
{
    update_Korriel(&player);
    animate_Korriel(&player);

    playerState = player.state;
    playerHP = player.hp;

    updateCollider(PLAYER_SPRITE_NUM);
}

void hurt_player()
{
    if(player.hp == 0) {
        play_sound_banked(&SHOOT_SFX, 1);
        return;
    }
    player.hp --;
    player.hSpeed = -50;
    player.vSpeed = -30;
    switch_player_state(3);
    setSprite16Tiles(PLAYER_ICON_NUM, ICON_HURT);
    play_sound_banked(&HURT_SFX, 1);
}

extern UINT8 i;
/*UINT8 tile_collided;
const UINT8 DEBUG_RED = 0x03U;
UINT8 scx, scy;
UINT8 tyMin, tyMax, txMin, txMax, xMin, yMin, xMax, yMax;
UINT8 tx, ty;
INT8 hasCollided;*/

/*
1. Check colliding tiles
2. Check whether there is collidable tiles
3. Get a rectagnle based on collidable tiles
4. Change player's position based on this rectangle
*/
/*----------------------------ABONDONED FOR PERFORMANCE---------------------------------------------
void rigid_collision(struct Korriel *p)
{
    rigid_state = 0x00U;

    p->rx += p->hSpeed;
    p->ry += p->vSpeed;
    lSprite_px = pCollider.x;
    lSprite_py = pCollider.y;
    pCollider.x = (UINT8)(player.rx / PLAYER_MOVE_DIV) + kC.dx;
    pCollider.y = (UINT8)(player.ry / PLAYER_MOVE_DIV) + kC.dy;

    scx = SCX_REG;
    scy = SCY_REG;
    tyMin = (UINT8)((pCollider.y + scy - 16) / 8);
    tyMax = (UINT8)((pCollider.y + pCollider.h + scy - 16) / 8);
    txMin = (UINT8)((pCollider.x + scx - 8) / 8);
    txMax = (UINT8)((pCollider.x + pCollider.w + scx - 8) / 8);
    xMin = 255U;
    yMin = 255U;
    xMax = 0U;
    yMax = 0U;
    tx = 0;
    ty = 0;
    hasCollided = 0;

    //Read digit 3 of tile's property
    if(txMin > 31) txMin -= 31;
    if(tyMin > 31) tyMin -= 31;
    if(txMax > 31) txMax -= 31;
    if(tyMax > 31) tyMax -= 31;
    printf("%u,%u\n",txMin,tyMin);
    VBK_REG = 1;
    for(tx = txMin; tx != txMax; ++tx) {
        for(ty = tyMin; ty != tyMax; ++ty) {
            get_bkg_tiles(tx, ty, 1, 1, &tile_collided);
            if(tile_collided & 0b1000U) {
                //set_bkg_tiles(tx, ty, 1, 1, &DEBUG_RED);
                if(tx < xMin) xMin = tx;
                if(tx + 1 > xMax) xMax = tx + 1;
                if(ty < yMin) yMin = ty;
                if(ty + 1 > yMax) yMax = ty + 1;
                hasCollided = 1;
            }
        }
    }
    VBK_REG = 0;

    if(hasCollided) {
        xMin = xMin * 8 - scx + 16;
        xMax = xMax * 8 - scx + 8;
        yMin = yMin * 8 - scy + 24;
        yMax = yMax * 8 - scy + 16;
        
        //DEBUG
        //printf("Y:%u+%u<%u\n",lSprite_py,pCollider.h,yMin);
        //printf("X:%u+%u<%u\n",lSprite_px,pCollider.w,xMin);

        if(lSprite_py + pCollider.h <= yMin && pCollider.y+ pCollider.h >= yMin - cameraVSpeed) {
            p->vSpeed = 0;
            pCollider.y = yMin - pCollider.h - 1;
            rigid_state |= 0b0001U;
        }else if(lSprite_py >= yMax && pCollider.y <= yMax - cameraVSpeed) {
            p->vSpeed = 0;
            pCollider.y = yMax + 1;
            rigid_state |= 0b0010U;
        }
        if(lSprite_px + pCollider.w <= xMin && pCollider.x + pCollider.w >= xMin - cameraHSpeed) {
            p->hSpeed = 0;
            pCollider.x = xMin - pCollider.w - 1;
            rigid_state |= 0b0100U;
        }else if(lSprite_px >= xMax && pCollider.x <= xMax - cameraHSpeed) {
            p->hSpeed = 0;
            pCollider.x = xMax + 1;
            rigid_state |= 0b1000U;
        }
    }

    if(pCollider.x < PLAYER_LEFT_BORDER) {
        pCollider.x = PLAYER_LEFT_BORDER;
        p->hSpeed = 0;
        if(rigid_state & 0b0100U != 0) p->hp = 0;
        rigid_state |= 0b1000U;
    }else if(pCollider.x > PLAYER_RIGHT_BORDER) {
        pCollider.x = PLAYER_RIGHT_BORDER;
        p->hSpeed = 0;
        if(rigid_state & 0b1000U != 0) p->hp = 0;
        rigid_state |= 0b0100U;
    }
    if(pCollider.y < PLAYER_UP_BORDER) {
        pCollider.y = PLAYER_UP_BORDER;
        p->vSpeed = 0;
        if(rigid_state & 0b0001U != 0) p->hp = 0;
        rigid_state |= 0b0010U;
    }else if(pCollider.y > PLAYER_DOWN_BORDER) {
        pCollider.y = PLAYER_DOWN_BORDER;
        p->vSpeed = 0;
        if(rigid_state & 0b0010U != 0) p->hp = 0;
        rigid_state |= 0b0001U;
    }

    if(rigid_state == 0) {
        playerRX = p->rx;
        playerRY = p->ry;
        moveSprite16(PLAYER_SPRITE_NUM, (UINT8)(p->rx / PLAYER_MOVE_DIV), (UINT8)(p->ry / PLAYER_MOVE_DIV));
    }else {
        moveSprite16(PLAYER_SPRITE_NUM, pCollider.x - kC.dx, pCollider.y - kC.dy);
        playerRX = p->rx = (UINT16)(pCollider.x - kC.dx) * PLAYER_MOVE_DIV;
        playerRY = p->ry = (UINT16)(pCollider.y - kC.dy) * PLAYER_MOVE_DIV;
    }
    
    playerState = p->state;
    playerHP = p->hp;

    updateCollider(PLAYER_SPRITE_NUM);
}
*/

void rigid_collision(struct Korriel *p)
{
    p->rx += p->hSpeed;
    p->ry += p->vSpeed;
    lSprite_px = pCollider.x;
    lSprite_py = pCollider.y;
    pCollider.x = (UINT8)(player.rx / PLAYER_MOVE_DIV) + kC.dx;
    pCollider.y = (UINT8)(player.ry / PLAYER_MOVE_DIV) + kC.dy;
    
    if(p->hp != 0) {
        UINT8 rigid = player_collide_all_tiles(&pCollider, lSprite_px, lSprite_py);

        if(rigid == 0) {
            playerRX = p->rx;
            playerRY = p->ry;
            moveSprite16(PLAYER_SPRITE_NUM, (UINT8)(p->rx / PLAYER_MOVE_DIV), (UINT8)(p->ry / PLAYER_MOVE_DIV));
        }else {
            UINT8 lrup = rigid & 0b1100U;
            if(lrup != 0) {
                p->hSpeed = 0;
                if(lrup == 0b1100U) p->hp = 0;
            }
            lrup = rigid & 0b0011U;
            if(lrup != 0) {
                p->vSpeed = 0;
                if(lrup == 0b1100U) p->hp = 0;
            }
            moveSprite16(PLAYER_SPRITE_NUM, pCollider.x - kC.dx, pCollider.y - kC.dy);
            playerRX = p->rx = (UINT16)(pCollider.x - kC.dx) * PLAYER_MOVE_DIV;
            playerRY = p->ry = (UINT16)(pCollider.y - kC.dy) * PLAYER_MOVE_DIV;
        }
    }else {
        playerRX = p->rx;
        playerRY = p->ry;
        moveSprite16(PLAYER_SPRITE_NUM, (UINT8)(p->rx / PLAYER_MOVE_DIV), (UINT8)(p->ry / PLAYER_MOVE_DIV));
    }
}