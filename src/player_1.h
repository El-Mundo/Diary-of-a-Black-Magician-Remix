#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_MOVE_DIV 20

#define BLOCK_MIXIMUM 5

#define PLAYER_SPRITE_NUM 1
#define PLAYER_ICON_NUM 0

#define PLAYER_VELOCITY_MAX 50
#define PLAYER_VELOCITY_MIN -50
#define PLAYER_ACCELERATION 1
#define PLAYER_BRAKE 2

#define PLAYER_UP_BORDER 16
#define PLAYER_DOWN_BORDER 140
#define PLAYER_LEFT_BORDER 21
#define PLAYER_RIGHT_BORDER 156

#define BOSS_UP_BORDER (PLAYER_MOVE_DIV * 8)
#define BOSS_DOWN_BORDER (PLAYER_MOVE_DIV * 132)
#define BOSS_LEFT_BORDER (PLAYER_MOVE_DIV * 5)
#define BOSS_RIGHT_BORDER (PLAYER_MOVE_DIV * 140)

extern unsigned int playerRX, playerRY;
extern unsigned char playerState;

void update_player(void);
void init_player(void);
void hurt_player(void);

#endif