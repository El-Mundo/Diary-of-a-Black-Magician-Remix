#include "hUGEDriver.h"
#include <stddef.h>
#include "huge_waves_0.h"

static const unsigned char order_cnt = 2;

static const unsigned char P0[] = {
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(E_6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(E_6,1,0x000),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(E_6,1,0x000),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(E_6,1,0x000),
    DN(___,0,0x000),
    DN(A_6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(A_6,1,0x000),
    DN(___,0,0x000),
    DN(G_6,1,0x000),
    DN(___,0,0x000),
    DN(A_6,1,0x000),
    DN(___,0,0x000),
    DN(G_6,1,0x000),
    DN(___,0,0x000),
    DN(E_6,1,0x000),
    DN(___,0,0x000),
    DN(E_6,1,0x000),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(E_6,1,0x000),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P1[] = {
    DN(G_5,2,0xC03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC02),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC01),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(E_6,2,0xC03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC02),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC01),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(D_6,2,0xC03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC02),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC01),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(A_6,2,0xC03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC02),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC01),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xC03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC02),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC01),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC00),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P2[] = {
    DN(C_5,1,0x000),
    DN(___,0,0xE00),
    DN(E_5,1,0x000),
    DN(___,0,0xE00),
    DN(C_5,1,0x000),
    DN(___,0,0xE00),
    DN(E_5,1,0x000),
    DN(___,0,0xE00),
    DN(C_5,1,0x000),
    DN(___,0,0xE00),
    DN(E_5,1,0x000),
    DN(___,0,0xE00),
    DN(C_5,1,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(D_5,1,0x000),
    DN(___,0,0xE00),
    DN(F_5,1,0x000),
    DN(___,0,0xE00),
    DN(D_5,1,0x000),
    DN(___,0,0xE00),
    DN(F_5,1,0x000),
    DN(___,0,0xE00),
    DN(D_5,1,0x000),
    DN(___,0,0xE00),
    DN(F_5,1,0x000),
    DN(___,0,0xE00),
    DN(D_5,1,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(A_4,1,0x000),
    DN(___,0,0xE00),
    DN(D_5,1,0x000),
    DN(___,0,0xE00),
    DN(A_4,1,0x000),
    DN(___,0,0xE00),
    DN(D_5,1,0x000),
    DN(___,0,0xE00),
    DN(A_4,1,0x000),
    DN(___,0,0xE00),
    DN(D_5,1,0x000),
    DN(___,0,0xE00),
    DN(A_4,1,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(C_5,1,0x000),
    DN(___,0,0xE00),
    DN(E_5,1,0x000),
    DN(___,0,0xE00),
    DN(C_5,1,0x000),
    DN(___,0,0xE00),
    DN(E_5,1,0x000),
    DN(___,0,0xE00),
    DN(C_5,1,0x000),
    DN(___,0,0xE00),
    DN(E_5,1,0x000),
    DN(___,0,0xE00),
    DN(C_5,1,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P3[] = {
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
};

static const unsigned char* const order1[] = {P0};
static const unsigned char* const order2[] = {P1};
static const unsigned char* const order3[] = {P2};
static const unsigned char* const order4[] = {P3};

static const unsigned char duty_instruments[] = {
8,0,210,128,
8,64,128,128,
8,128,240,128,
8,192,240,128,
8,0,241,128,
8,64,241,128,
8,128,241,128,
8,192,241,128,
8,128,240,128,
8,128,240,128,
8,128,240,128,
8,128,240,128,
8,128,240,128,
8,128,240,128,
8,128,240,128,
};
static const unsigned char wave_instruments[] = {
11,32,2,192,
0,32,1,128,
0,32,2,128,
0,32,3,128,
0,32,4,128,
0,32,5,128,
0,32,6,128,
0,32,7,128,
0,32,8,128,
0,32,9,128,
0,32,10,128,
0,32,11,128,
0,32,12,128,
0,32,13,128,
0,32,14,128,
};
static const unsigned char noise_instruments[] = {
243,108,19,24,20,0,0,0,
241,14,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
};

const hUGESong_t AHOU_MAJO = {8, &order_cnt, order1, order2, order3,order4, duty_instruments, wave_instruments, noise_instruments, NULL, waves};
