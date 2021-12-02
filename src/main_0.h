#ifndef MAIN_H
#define MAIN_H

#define PLAYER_SPRITES_START 2
#define PLAYER_SPRITES_NUMBER 5

#define PBULLET_SPRITES_START 7
#define PBULLET_P1MODE_SPRITES_NUMBER 3
#define PBULLET_P2MODE_SPRITES_NUMBER 5

#define INTRO_FRAME 320

void screen_fade_in(UINT8 delay, UINT16 * target, UINT8 number);
void screen_fade_out(UINT8 delay, UINT16 * start, UINT8 number);

#endif