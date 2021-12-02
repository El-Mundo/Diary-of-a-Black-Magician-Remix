#ifndef HUD_H
#define HUD_H

//Digit: 0-4, unit to ten thousand; s should be less than 10
void add_score(unsigned char digit, unsigned char s);
void clear_score(void);
void update_score(void);
void update_HP(void);

#endif