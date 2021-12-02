#include <gb/gb.h>
#include "hud_1.h"

//Score digits, one to ten thousand
UINT8 s_dig[5] = {0, 0, 0, 0, 0};
UINT8 s_tiles[5] = {0, 0, 0, 0, 0};
extern UINT8 i;

void max_score()
{
    s_dig[0] = s_dig[1] = s_dig[2] = s_dig[3] = s_dig[4] = 9;
}

void clear_score()
{
    s_dig[0] = s_dig[1] = s_dig[2] = s_dig[3] = s_dig[4] = 0;
}

void add_score(UINT8 digit, UINT8 s)
{
    s_dig[digit] += s;
    if(s_dig[digit] > 9) {
        if(digit != 4) {
            s_dig[digit] -= 10;
            add_score(digit + 1, 1);
        }else {
            max_score();
        }
    }
}

void update_score()
{
    for(i = 0; i != 5; i++) {
        s_tiles[4-i] = s_dig[i] + 1;
    }
    set_win_tiles(8, 0, 5, 1, s_tiles);
}

extern UINT8 playerHP;
const unsigned char HP_BAR[4][3] = {{19, 20, 21}, {16, 20, 21}, {16, 17, 21}, {16, 17, 18}};

void update_HP()
{
    set_win_tiles(2, 0, 3, 1, HP_BAR[playerHP]);
}