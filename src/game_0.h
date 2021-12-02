#ifndef GAME_H
#define GAME_H

extern UINT8 key;
//Camera-Horizontal-Speed should be always larger than or equal to 0
extern UINT8 cameraHSpeed, cameraVSpeed;
extern UINT16 mapWidth, mapHeight;
extern const UINT8 *level_tiles, *level_props;
extern UINT16 cameraX, cameraY;

void game_update(void);
void init_game(void);
void shiftTo(INT16 *n, INT16 t, INT16 v);
void update_map(UINT8 bank);

#endif