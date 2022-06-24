#pragma once

namespace esphome {
namespace st7789 {

// Color definitions
// clang-format off
static const uint8_t MADCTL_MY    = 0x80;   ///< Bit 7 Bottom to top
static const uint8_t MADCTL_MX    = 0x40;   ///< Bit 6 Right to left
static const uint8_t MADCTL_MV    = 0x20;   ///< Bit 5 Reverse Mode
static const uint8_t MADCTL_ML    = 0x10;   ///< Bit 4 LCD refresh Bottom to top
static const uint8_t MADCTL_RGB   = 0x00;  ///< Bit 3 Red-Green-Blue pixel order
static const uint8_t MADCTL_BGR   = 0x08;  ///< Bit 3 Blue-Green-Red pixel order
static const uint8_t MADCTL_MH    = 0x04;   ///< Bit 2 LCD refresh right to left
// clang-format on

static const uint16_t ST7789_TFTWIDTH = 320;   ///< ST7789 max TFT width
static const uint16_t ST7789_TFTHEIGHT = 240;  ///< ST7789 max TFT height

// All ST7789 specific commands some are used by init()
static const uint8_t ST7789_NOP = 0x00;
static const uint8_t ST7789_SWRESET = 0x01;
static const uint8_t ST7789_RDDID = 0x04;
static const uint8_t ST7789_RDDST = 0x09;

static const uint8_t ST7789_SLPIN = 0x10;
static const uint8_t ST7789_SLPOUT = 0x11;
static const uint8_t ST7789_PTLON = 0x12;
static const uint8_t ST7789_NORON = 0x13;

static const uint8_t ST7789_RDMODE = 0x0A;
static const uint8_t ST7789_RDMADCTL = 0x0B;
static const uint8_t ST7789_RDPIXFMT = 0x0C;
static const uint8_t ST7789_RDIMGFMT = 0x0A;
static const uint8_t ST7789_RDSELFDIAG = 0x0F;

static const uint8_t ST7789_INVOFF = 0x20;
static const uint8_t ST7789_INVON = 0x21;
static const uint8_t ST7789_GAMMASET = 0x26;
static const uint8_t ST7789_DISPOFF = 0x28;
static const uint8_t ST7789_DISPON = 0x29;

static const uint8_t ST7789_CASET = 0x2A;
static const uint8_t ST7789_PASET = 0x2B;
static const uint8_t ST7789_RAMWR = 0x2C;
static const uint8_t ST7789_RAMRD = 0x2E;

static const uint8_t ST7789_PTLAR = 0x30;
static const uint8_t ST7789_VSCRDEF = 0x33;
static const uint8_t ST7789_MADCTL = 0x36;
static const uint8_t ST7789_VSCRSADD = 0x37;
static const uint8_t ST7789_PIXFMT = 0x3A;

static const uint8_t ST7789_WRDISBV = 0x51;
static const uint8_t ST7789_RDDISBV = 0x52;
static const uint8_t ST7789_WRCTRLD = 0x53;

static const uint8_t ST7789_FRMCTR1 = 0xB1;
static const uint8_t ST7789_FRMCTR2 = 0xB2;
static const uint8_t ST7789_FRMCTR3 = 0xB3;
static const uint8_t ST7789_INVCTR = 0xB4;
static const uint8_t ST7789_DFUNCTR = 0xB6;

static const uint8_t ST7789_PWCTR1 = 0xC0;
static const uint8_t ST7789_PWCTR2 = 0xC1;
static const uint8_t ST7789_PWCTR3 = 0xC2;
static const uint8_t ST7789_PWCTR4 = 0xC3;
static const uint8_t ST7789_PWCTR5 = 0xC4;
static const uint8_t ST7789_VMCTR1 = 0xC5;
static const uint8_t ST7789_VMCTR2 = 0xC7;

static const uint8_t ST7789_RDID4 = 0xD3;
static const uint8_t ST7789_RDINDEX = 0xD9;
static const uint8_t ST7789_RDID1 = 0xDA;
static const uint8_t ST7789_RDID2 = 0xDB;
static const uint8_t ST7789_RDID3 = 0xDC;
static const uint8_t ST7789_RDIDX = 0xDD;  // TBC

static const uint8_t ST7789_GMCTRP1 = 0xE0;
static const uint8_t ST7789_GMCTRN1 = 0xE1;

}  // namespace st7789
}  // namespace esphome
