set lcc=F:\EclipseWorkSpaceforC++\GameBoyWorkSapce\gbdk-2020\bin\lcc
echo Compiler path: %lcc%

set huge=F:\EclipseWorkSpaceforC++\GameBoyWorkSapce\hUGEDriver\builder
echo Huge music driver path: %huge%

set card_type=3
set roms=4
set rams=4

%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o main.o src/main_0.c
%huge%\tools\rgb2sdas %huge%\hUGEDriver.obj

%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo0 -c -o sprite.o src/sprite_0.c
%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo2 -c -o graphics.o src/graphics_2.c
%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo1 -c -o graphics1.o src/graphics_1.c
%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo3 -c -o graphics2.o src/graphics_3.c
%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo1 -c -o graphics3.o src/graphics/intro_graphics_1.c

%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo0 -c -o game.o src/game_0.c
%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo1 -c -o hud.o src/hud_1.c
%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo1 -c -o player.o src/player_1.c
%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo1 -c -o collision.o src/collision_1.c
%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo1 -c -o enemy.o src/enemy_1.c

%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo0 -c -o sound.o src/sound_0.c
%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo1 -c -o music1.o src/sounds/Sokokuno_Kobanatachi_1.c
%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo0 -c -o music2.o src/sounds/Intro_Sound_0.c
%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo1 -c -o music3.o src/sounds/Ahou_Majo_1.c
%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo0 -c -o waves.o src/sounds/huge_waves_0.c
%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo2 -c -o sfx.o src/sounds/sfx_2.c

%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo1 -c -o level.o src/levels/level_1.c
%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo3 -c -o level1.o src/levels/level1_3.c

%lcc% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wm-yC ^
-Wl-yt%card_type% -Wl-yo%roms% -Wl-ya%rams% -o ^
Mahoutsukai_Nikki_REMIX.gbc main.o ^
%huge%\hUGEDriver.obj.o sprite.o graphics.o graphics1.o graphics2.o graphics3.o game.o player.o enemy.o hud.o collision.o sound.o ^
level.o level1.o sfx.o music1.o music2.o music3.o waves.o

del *.o *.lst *.sym *.map *.asm *.noi
pause