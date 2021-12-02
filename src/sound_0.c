#include <gb/gb.h>
#include <stdio.h>
#include "sound_0.h"

//Volume range 0-7
UINT8 volume = 7;
//Whether sound is muted
BOOLEAN muted = FALSE;

UINT8 sound_fading = 0, fade_timer = 0, fade_speed = 12;
volatile UINT8 channel_timer[4] = {0, 0, 0, 0};
static UINT8 snd_i = 0;

void init_music()
{
    //Enable HUGE Player
    __critical {
        hUGE_init(INTRO_MUSIC_ADDR);
        add_VBL(hUGE_dosound);
    }
}

void play_music(const hUGESong_t * music_p) NONBANKED
{
    hUGE_init(music_p);
}

void mute(BOOLEAN mute) NONBANKED
{
    if(mute) {
        muted = TRUE;
        NR52_REG &= 0x7FU;
    }else {
        muted = FALSE;
        NR52_REG = 0x80;
        NR50_REG = volume | (volume << 4);
        NR51_REG = 0xFF;
    }
}

//Volume must be within 0-7
void set_volume(UINT8 new_volume) NONBANKED
{
    volume = new_volume;
    NR50_REG = volume | (volume << 4);
}

void volume_fade_out()
{
    if(volume != 0) {
        sound_fading = 1;
        fade_timer = fade_speed;
    }
}

void volume_fade_in()
{
    if(volume != 7) {
        sound_fading = 2;
        fade_timer = fade_speed;
    }
}

void play_sound(const Sound * s) NONBANKED
{
    hUGE_mute_channel(s->channel, HT_CH_MUTE);
    channel_timer[s->channel] = s->time;
    switch (s->channel)
    {
    case 0:
        NR10_REG = s->reg1;
        NR11_REG = s->reg2;
        NR12_REG = s->reg3;
        NR13_REG = s->reg4;
        NR14_REG = (NR11_REG & 0x3FU) == 0 ? 0x86 : 0xC6;
        break;
    case 1:
        NR21_REG = s->reg1;
        NR22_REG = s->reg2;
        NR23_REG = s->reg3;
        NR24_REG = s->reg4;
        break;
    case 2:
        NR30_REG = 0x80U;
        NR31_REG = s->reg1;
        NR32_REG = s->reg2;
        NR33_REG = s->reg3;
        NR34_REG = s->reg4;
        break;
    case 3:
        NR41_REG = s->reg1;
        NR42_REG = s->reg2;
        NR43_REG = s->reg3;
        NR44_REG = s->reg4;
        break;
    default:
        break;
    }
}

void play_sound_banked(const Sound * s, UINT8 current_bank) NONBANKED
{
    SWITCH_ROM_MBC1(SOUND_EFFECTS_BANK);
    play_sound(s);
    SWITCH_ROM_MBC1(current_bank);
}

//Note that fading to zero will call mute and sound power will be turned off
void update_volume()
{
    //Update SFX
    if(sound_fading) {
        fade_timer--;
        if(fade_timer == 0) {
            fade_timer = fade_speed;
            if(sound_fading == 2) {
                set_volume(++volume);
                if(volume == 7) {
                    sound_fading = 0;
                    return;
                }
            }else if(sound_fading == 1) {
                set_volume(--volume);
                if(volume == 0) {
                    sound_fading = 3;
                    return;
                }
            }else {
                sound_fading = 0;
                mute(TRUE);
                return;
            }
        }
    }

    //Update music channels
    for(snd_i = 0; snd_i != 4; snd_i++) {
        if(channel_timer[snd_i] != 0)
            channel_timer[snd_i] --;
        else
            hUGE_mute_channel(snd_i, HT_CH_PLAY);
    }
}