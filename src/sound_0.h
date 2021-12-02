#ifndef SOUND_H
#define SOUND_H

#include <hUGEDriver.h>

#define SOUND_EFFECTS_BANK 2

//Channel 1: 1-NR10 2-NR11 3-NR12 4-NR13
#define SFX_CH1 0
//Channel 2: 1-NR21 2-NR22 3-NR23 4-NR24
#define SFX_CH2 1
//Channel 3: 1-NR31 2-NR32 3-NR33 4-NR34
#define SFX_CH3 2
//Channel 4: 1-NR41 2-NR42 3-NR43 4-NR44
#define SFX_CH4 3

typedef struct {
    const UINT8 channel;
    const UINT8 reg1, reg2, reg3, reg4;
    const UINT8 time;
}Sound;

extern const hUGESong_t INTRO_SOUND;
#define INTRO_MUSIC_ADDR &INTRO_SOUND

//Volume range 0-7
extern UINT8 volume;
//Whether sound is muted
extern BOOLEAN muted;
extern UINT8 fade_speed;

void mute(BOOLEAN mute);
void set_volume(UINT8 new_volume);
void volume_fade_out(void);
void volume_fade_in(void);
void play_sound(const Sound * s);
void play_sound_banked(const Sound * s, UINT8 current_bank);
void play_music(const hUGESong_t * music_p);

#endif