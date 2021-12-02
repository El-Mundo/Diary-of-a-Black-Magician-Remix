#define HUD_COLOR 32767

const unsigned int GAME_HUD_PALETTE[] =
{
  32767, HUD_COLOR, 31822, 0,//Crystal ball
  32767, HUD_COLOR, 2495, 0,//HP bar
  32320, 31710, 32320, 32552,//Sky dark
  282, 282, 282, 282//DEBUG RED
};

const unsigned char GAME_BKG_GRAPHICS[] =
{
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xFF,0x3C,0xFF,0x66,0xFF,0x6E,0xFF,0x76,
  0xFF,0x66,0xFF,0x66,0xFF,0x3C,0xFF,0x00,
  0xFF,0x18,0xFF,0x38,0xFF,0x18,0xFF,0x18,
  0xFF,0x18,0xFF,0x18,0xFF,0x18,0xFF,0x00,
  0xFF,0x3C,0xFF,0x66,0xFF,0x0E,0xFF,0x1C,
  0xFF,0x38,0xFF,0x70,0xFF,0x7E,0xFF,0x00,
  0xFF,0x7E,0xFF,0x0C,0xFF,0x18,0xFF,0x3C,
  0xFF,0x06,0xFF,0x46,0xFF,0x3C,0xFF,0x00,
  0xFF,0x0C,0xFF,0x1C,0xFF,0x2C,0xFF,0x4C,
  0xFF,0x7E,0xFF,0x0C,0xFF,0x0C,0xFF,0x00,
  0xFF,0x7E,0xFF,0x60,0xFF,0x7C,0xFF,0x06,
  0xFF,0x06,0xFF,0x46,0xFF,0x3C,0xFF,0x00,
  0xFF,0x1C,0xFF,0x20,0xFF,0x60,0xFF,0x7C,
  0xFF,0x66,0xFF,0x66,0xFF,0x3C,0xFF,0x00,
  0xFF,0x7E,0xFF,0x06,0xFF,0x0E,0xFF,0x1C,
  0xFF,0x18,0xFF,0x18,0xFF,0x18,0xFF,0x00,
  0xFF,0x3C,0xFF,0x66,0xFF,0x66,0xFF,0x3C,
  0xFF,0x66,0xFF,0x66,0xFF,0x3C,0xFF,0x00,
  0xFF,0x3C,0xFF,0x66,0xFF,0x66,0xFF,0x3E,
  0xFF,0x06,0xFF,0x0C,0xFF,0x38,0xFF,0x00,
  0xFF,0x3C,0xFF,0x62,0xFF,0x70,0xFF,0x3C,
  0xFF,0x0E,0xFF,0x46,0xFF,0x3C,0xFF,0x00,
  0xFF,0x3C,0xFF,0x62,0xFF,0x60,0xFF,0x60,
  0xFF,0x60,0xFF,0x62,0xFF,0x3C,0xFF,0x00,
  0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
  0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
  0xFF,0x66,0xFF,0x66,0xFF,0x66,0xFF,0x7E,
  0xFF,0x66,0xFF,0x66,0xFF,0x66,0xFF,0x00,
  0xFF,0x7C,0xFF,0x66,0xFF,0x66,0xFF,0x7C,
  0xFF,0x60,0xFF,0x60,0xFF,0x60,0xFF,0x00,
  0xFF,0x3F,0xC0,0x7F,0x80,0xFF,0x80,0xFF,
  0x80,0xFF,0x80,0xFF,0xFF,0x7F,0xFF,0x3F,
  0xFF,0xFF,0x81,0xFF,0x81,0xFF,0x81,0xFF,
  0x81,0xFF,0x81,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFC,0x03,0xFE,0x01,0xFF,0x01,0xFF,
  0x01,0xFF,0x01,0xFF,0xFF,0xFE,0xFF,0xFC,
  0xFF,0x3F,0xFF,0x40,0xFF,0x80,0xFF,0x80,
  0xFF,0x80,0xBF,0xC0,0xC0,0x7F,0xFF,0x3F,
  0xFF,0xFF,0xFF,0x81,0xFF,0x81,0xFF,0x81,
  0xFF,0x81,0xFF,0x81,0x81,0xFF,0xFF,0xFF,
  0xFF,0xFC,0xFF,0x02,0xFF,0x01,0xFF,0x01,
  0xFF,0x01,0xFD,0x03,0x03,0xFE,0xFF,0xFC,
  0xFF,0x3C,0xCB,0x76,0x9D,0xE3,0x89,0xF7,
  0xC1,0xBF,0xE1,0x9F,0xFB,0x46,0xFF,0x3C,
  0xFF,0x00,0xFF,0x66,0xFF,0x66,0xFF,0x3C,
  0xFF,0x66,0xFF,0x66,0xFF,0x66,0xFF,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xC0,0x40,0xF0,0x10,0xF8,0x08,0xFC,0x04,
  0xFE,0x02,0xFE,0x00,0xFF,0x01,0xFF,0x00,
  0xFF,0x00,0xFF,0x01,0xFE,0x01,0xFE,0x03,
  0xFC,0x07,0xF8,0x0F,0xF0,0x1F,0xC0,0x7F,
  0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
  0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
  0x03,0xFE,0x0F,0xF8,0x1F,0xF0,0x3F,0xE0,
  0x7F,0xC0,0x7F,0x80,0xFF,0x80,0xFF,0x00,
  0xFF,0x00,0xFF,0x80,0x7F,0x80,0x7F,0xC0,
  0x3F,0xE0,0x1F,0xF0,0x0F,0xF8,0x03,0xFE,
  0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
  0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
  0xAA,0xFF,0x55,0xFF,0xAA,0xFF,0x55,0xFF,
  0xAA,0xFF,0x55,0xFF,0xAA,0xFF,0x55,0xFF
};

//Set VBK_REG to 0
const unsigned char HUD_MAP_TILES[] =
{
  0x0E,0x0F,0x10,0x11,0x12,0x0D,0x0B,0x0C,0x01,0x01,
  0x01,0x01,0x01,0x0D,0x16,0x17,0x01
};

//Set VBK_REG to 1
const unsigned char HUD_MAP_PROPS[] =
{
  0x81,0x81,0x81,0x81,0x81,0x81,0x80,0x80,0x80,0x80,
  0x80,0x80,0x80,0x81,0x80,0x80,0x80
};

const unsigned char SKY_MAP_TILES[] =
{
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x1A,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x1A,0x1C,0x1A,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x1A,0x1C,0x1C,0x1C,
  0x1A,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x1A,0x1C,0x1A,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x1A,0x1C,0x1C,
  0x1C,0x1C,0x1C,0x1A,0x19,0x19,0x19,0x19,0x19,0x19,
  0x1A,0x1A,0x19,0x19,0x19,0x19,0x19,0x1A,0x1C,0x1C,
  0x1C,0x1A,0x19,0x19,0x1A,0x1A,0x19,0x19,0x1A,0x1C,
  0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1A,0x19,0x19,0x19,
  0x19,0x1A,0x1C,0x1C,0x1A,0x19,0x19,0x19,0x1A,0x1C,
  0x1C,0x1C,0x1C,0x1C,0x1A,0x1A,0x1C,0x1C,0x1A,0x1A,
  0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1A,
  0x19,0x19,0x1A,0x1C,0x1C,0x1C,0x1C,0x1A,0x19,0x1A,
  0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,
  0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,
  0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,
  0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,
  0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,
  0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,
  0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,
  0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,
  0x1B,0x1C,0x1C,0x1C,0x1C,0x1C,0x1B,0x1B,0x1C,0x1C,
  0x1C,0x1C,0x1C,0x1C,0x1C,0x1E,0x1E,0x1C,0x1C,0x1C,
  0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,
  0x1B,0x19,0x19,0x1B,0x1C,0x1C,0x1C,0x1B,0x19,0x19,
  0x1B,0x1C,0x1C,0x1C,0x1B,0x19,0x19,0x19,0x19,0x19,
  0x1B,0x1C,0x1C,0x1C,0x1C,0x1C,0x1B,0x19,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19,0x1B,0x1B,0x19,0x19,
  0x19,0x19,0x19,0x1B,0x1C,0x1B,0x19,0x19,0x19,0x19,
  0x19,0x19,0x19,0x1B,0x1C,0x1C,0x1C,0x1B,0x19,0x19,
  0x19,0x19,0x19,0x19,0x19,0x19
};

const unsigned char SKY_MAP_PROPS[] =
{
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0xA2,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0xA2,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0xA2,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0xA2,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0xA2,0x82,0x82,0x82,0x82,0x82,0x82,0xA2,0x82,0x82,
  0x82,0x82,0x82,0x82,0xA2,0x82,0x82,0x82,0xA2,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0xA2,0x82,0x82,0x82,0x82,0x82,0x82,0xA2,0x82,
  0x82,0x82,0x82,0x82,0x82,0xA2,0x82,0x82,0x82,0xA2,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0xA2,0x82,0x82,0x82,0x82,0x82,0x82,0xA2,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0xA2,0x82,0x82,0x82,0x82,0x82,0x82,0xA2,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0xA2,0x82,0x82,0x82,0x82,
  0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,
  0x82,0x82,0x02,0x22,0x02,0x02,0x02,0x02,0x02,0x02,
  0x22,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
  0x22,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
  0x02,0x02,0x02,0x02,0x02,0x02,0x22,0x02,0x02,0x02,
  0x02,0x02,0x02,0x22,0x02,0x02,0x02,0x02,0x02,0x02,
  0x02,0x02,0x02,0x22,0x02,0x02,0x02,0x02,0x02,0x02,
  0x02,0x02,0x02,0x02,0x02,0x02
};