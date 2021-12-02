#include <gb/gb.h>
#include <stdio.h>
#include "player_1.h"
#include "enemy_1.h"
#include "sprite_0.h"

struct Michelle {
    UINT16 rx, ry;
    INT16 hSpeed, vSpeed;
    UINT8 frame, state;
    /*state:
    0: enter
    1: idle facing right
    2: idle facing middle
    3: idle facing left
    */
}michelle = {640, 640};

void update_Michelle(struct Michelle *m) {
    if(m->ry > playerRY){
        if(m->vSpeed > MICHELLE_VELOCITY_MIN)    
            m->vSpeed -= MICHELLE_ACCELERATION;
    }else {
        if(m->vSpeed < MICHELLE_VELOCITY_MAX)    
            m->vSpeed += MICHELLE_ACCELERATION;
    }
    if(m->rx < playerRX){
        if(m->hSpeed < MICHELLE_VELOCITY_MAX)
            m->hSpeed += MICHELLE_ACCELERATION;
    }else {
        if(m->hSpeed > MICHELLE_VELOCITY_MIN)
            m->hSpeed -= MICHELLE_ACCELERATION;
    }

    m->rx += m->hSpeed;
    m->ry += m->vSpeed;
    if(m->rx < BOSS_LEFT_BORDER) {
        m->rx = BOSS_LEFT_BORDER;
        m->hSpeed = 0;
    }else if(m->rx > BOSS_RIGHT_BORDER - 2) {
        m->rx = BOSS_RIGHT_BORDER - 2;
        m->hSpeed = 0;
    }
    if(m->ry < BOSS_UP_BORDER) {
        m->ry = BOSS_UP_BORDER;
        m->vSpeed = 0;
    }else if(m->ry > BOSS_DOWN_BORDER) {
        m->ry = BOSS_DOWN_BORDER;
        m->vSpeed = 0;
    }

    moveSprite16(MICHELLE_SPRITE_NUM, (UINT8)(m->rx / PLAYER_MOVE_DIV), (UINT8)(m->ry / PLAYER_MOVE_DIV));

    updateCollider(MICHELLE_SPRITE_NUM);
    if(playerState == 1 || playerState == 2) {
        if(collideSprite(PLAYER_SPRITE_NUM, MICHELLE_SPRITE_NUM))
            hurt_player();
    }
}

const unsigned char tileNums_m[] = {NULL_SPRITE, NULL_SPRITE, 12, 14, 16, 18, 20, 22};
const unsigned char sprc_m[] = {0x00U, 0x00U, 0x03U, 0x03U, 0x03U, 0x04U, 0x04U, 0x04U};
const unsigned char tileNums_m1[] = {NULL_SPRITE, 24, 26, NULL_SPRITE, NULL_SPRITE, 28, 30, NULL_SPRITE};
const unsigned char sprc_m1[] = {0x00U, 0x03U, 0x03U, 0x00U, 0x00U, 0x04U, 0x04U, 0x00U};
const UINT8 cDX[] = {17, 3, 11}, cDY = 8;//Collider diffrence X: face right, face left, face front
struct Collider mC = {17, 8, 15, 22};
extern const unsigned char MICHELLE_ANIMATION[];

void init_Michelle()
{
    setSprite16(MICHELLE_SPRITE_NUM, michelle.rx / PLAYER_MOVE_DIV, michelle.ry / PLAYER_MOVE_DIV, 4, 2, tileNums_m, sprc_m);
    activateSprite16(MICHELLE_SPRITE_NUM, ACTIVE);
    flipSprite16(MICHELLE_SPRITE_NUM, FLIPPED);
    attachCollider(MICHELLE_SPRITE_NUM, &mC);
    setSprite16Prop(MICHELLE_SPRITE_NUM, 0x80U);
}

void switch_Michelle_state(UINT8 _state)
{
    michelle.state = _state;
    michelle.frame = 0;
}

void animate_Michelle()
{
    michelle.frame ++;

    if(michelle.state == 0) {
        michelle.state = 1;
    }else if(michelle.state == 1) {
        if(michelle.hSpeed < 0)
            switch_Michelle_state(2);

        setGraphicsForSprite16(MICHELLE_SPRITE_NUM, tileNums_m);
        setPaletteForSprite16(MICHELLE_SPRITE_NUM, sprc_m);
        flipSprite16(MICHELLE_SPRITE_NUM, UNFLIPPED);
        moveCollider(MICHELLE_SPRITE_NUM, cDX[0], cDY);
    }else if(michelle.state == 3) {
        if(michelle.hSpeed > 0)
            switch_Michelle_state(2);

        setGraphicsForSprite16(MICHELLE_SPRITE_NUM, tileNums_m);
        setPaletteForSprite16(MICHELLE_SPRITE_NUM, sprc_m);
        flipSprite16(MICHELLE_SPRITE_NUM, FLIPPED);
        moveCollider(MICHELLE_SPRITE_NUM, cDX[1], cDY);
    }else {
        setGraphicsForSprite16(MICHELLE_SPRITE_NUM, tileNums_m1);
        setPaletteForSprite16(MICHELLE_SPRITE_NUM, sprc_m1);
        moveCollider(MICHELLE_SPRITE_NUM, cDX[2], cDY);
        if(michelle.frame == 7) {
            if(michelle.hSpeed > 0) {
                switch_Michelle_state(1);
            }else {
                switch_Michelle_state(3);
            }
        }
    }

    switch (michelle.frame)
    {
    case 7:
        set_sprite_data(14, 2, &MICHELLE_ANIMATION[32]);
        set_sprite_data(16, 2, &MICHELLE_ANIMATION[128]);
        break;
    case 14:
        set_sprite_data(14, 2, &MICHELLE_ANIMATION[0]);
        set_sprite_data(16, 2, &MICHELLE_ANIMATION[96]);
        break;
    case 21:
        set_sprite_data(14, 2, &MICHELLE_ANIMATION[64]);
        set_sprite_data(16, 2, &MICHELLE_ANIMATION[160]);
        michelle.frame = 0;
        break;
    default:
        break;
    }
}

void DEBUG_update_Michelle()
{
    update_Michelle(&michelle);
    animate_Michelle();
}