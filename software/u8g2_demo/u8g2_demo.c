/*********************************************************************************
*
*       PROJECT:        WH32_DDR 
* 
*       FILENAME:       u8g2_demo.c 
* 
*       FUNCTION:       u8g2_demo driver 
* 
*       AUTHOR:         viking 
* 
*       DATE:           2020年 11月 06日 星期五 17:25:52 CST 
* 
*       ISFINISH:       YES 
* 
*       STATUS:  
*********************************************************************************/
#include "platform.h"

#include "csr.h"
#include "device/oledfont.h"
#include "csrc/u8g2.h"
#include "stdbool.h"
#include "csrc/u8g2_port.h"

u8g2_t u8g2;

#define u8g2_setFont(x) 						u8g2_SetFont(&u8g2,x)
#define u8g2_setFontRefHeightExtendedText()  	u8g2_SetFontRefHeightExtendedText(&u8g2)
#define u8g2_setDrawColor(x) 					u8g2_SetDrawColor(&u8g2,x)
#define u8g2_setFontPosTop()					u8g2_SetFontPosTop(&u8g2)
#define u8g2_setFontDirection(x)				u8g2_SetFontDirection(&u8g2,x)
#define u8g2_drawStr( x, y, z)					u8g2_DrawStr(&u8g2, x, y, z)
#define u8g2_drawBox(x,y,z,s)					u8g2_DrawBox(&u8g2,x,y,z,s)
#define u8g2_drawFrame(x,y,z,s)					u8g2_DrawFrame(&u8g2,x,y,z,s)
#define u8g2_drawDisc(x,y,z)					u8g2_DrawDisc(&u8g2,x,y,z,U8G2_DRAW_ALL)
#define	u8g2_drawCircle(x,y,z)					u8g2_DrawCircle(&u8g2,x,y,z,U8G2_DRAW_ALL)
#define	u8g2_drawRFrame(x, y,z,s, r)			u8g2_DrawRFrame(&u8g2,x, y,z,s, r)
#define	u8g2_drawRBox(x, y,z,s, r)				u8g2_DrawRBox(&u8g2,x, y,z,s, r)
#define	u8g2_drawLine(x, y, z, s)				u8g2_DrawLine(&u8g2,x, y, z, s)
#define	u8g2_drawTriangle(x,y, z,s, r,t)	    u8g2_DrawTriangle(&u8g2,x,y, z,s, r,t)
#define	u8g2_drawGlyph(x, y, z) 				u8g2_DrawGlyph(&u8g2,x, y, z);
#define	u8g2_setBitmapMode(x)					u8g2_SetBitmapMode(&u8g2,x)
#define	u8g2_drawXBMP(x,y, z, s,r)				u8g2_DrawXBMP(&u8g2,x,y, z, s,r)

void oled_sample_entry();

int main(void)
{
	/* write your code here */
//	oled_thread_trg();
	oled_sample_entry();
	
	return 0;
}
/*-----------------graphic test----------------*/
static void u8g2_prepare(void) {
  u8g2_setFont(u8g2_font_6x10_tf);
  u8g2_setFontRefHeightExtendedText();
  u8g2_setDrawColor(1);
  u8g2_setFontPosTop();
  u8g2_setFontDirection(0);
}

static void u8g2_box_frame(uint8_t a) {
  u8g2_drawStr( 0, 0, "drawBox");
  u8g2_drawBox(5,10,20,10);
  u8g2_drawBox(10+a,15,30,7);
  u8g2_drawStr( 0, 30, "drawFrame");
  u8g2_drawFrame(5,10+30,20,10);
  u8g2_drawFrame(10+a,15+30,30,7);
}

static void u8g2_disc_circle(uint8_t a) {
  u8g2_drawStr( 0, 0, "drawDisc");
  u8g2_drawDisc(10,18,9);
  u8g2_drawDisc(24+a,16,7);
  u8g2_drawStr( 0, 30, "drawCircle");
  u8g2_drawCircle(10,18+30,9);
  u8g2_drawCircle(24+a,16+30,7);
}

static void u8g2_r_frame(uint8_t a) {
  u8g2_drawStr( 0, 0, "drawRFrame/Box");
  u8g2_drawRFrame(5, 10,40,30, a+1);
  u8g2_drawRBox(50, 10,25,40, a+1);
}

static void u8g2_string(uint8_t a) {
  u8g2_setFontDirection(0);
  u8g2_drawStr(30+a,31, " 0");
  u8g2_setFontDirection(1);
  u8g2_drawStr(30,31+a, " 90");
  u8g2_setFontDirection(2);
  u8g2_drawStr(30-a,31, " 180");
  u8g2_setFontDirection(3);
  u8g2_drawStr(30,31-a, " 270");
}

static void u8g2_line(uint8_t a) {
  u8g2_drawStr( 0, 0, "drawLine");
  u8g2_drawLine(7+a, 10, 40, 55);
  u8g2_drawLine(7+a*2, 10, 60, 55);
  u8g2_drawLine(7+a*3, 10, 80, 55);
  u8g2_drawLine(7+a*4, 10, 100, 55);
}

static void u8g2_triangle(uint8_t a) {
  uint16_t offset = a;
  u8g2_drawStr( 0, 0, "drawTriangle");
  u8g2_drawTriangle(14,7, 45,30, 10,40);
  u8g2_drawTriangle(14+offset,7-offset, 45+offset,30-offset, 57+offset,10-offset);
  u8g2_drawTriangle(57+offset*2,10, 45+offset*2,30, 86+offset*2,53);
  u8g2_drawTriangle(10+offset,40+offset, 45+offset,30+offset, 86+offset,53+offset);
}

static void u8g2_ascii_1() {
  char s[2] = " ";
  uint8_t x, y;
  u8g2_drawStr( 0, 0, "ASCII page 1");
  for( y = 0; y < 6; y++ ) {
    for( x = 0; x < 16; x++ ) {
      s[0] = y*16 + x + 32;
      u8g2_drawStr(x*7, y*10+10, s);
    }
  }
}

static void u8g2_ascii_2() {
  char s[2] = " ";
  uint8_t x, y;
  u8g2_drawStr( 0, 0, "ASCII page 2");
  for( y = 0; y < 6; y++ ) {
    for( x = 0; x < 16; x++ ) {
      s[0] = y*16 + x + 160;
      u8g2_drawStr(x*7, y*10+10, s);
    }
  }
}

static void u8g2_extra_page(uint8_t a)
{
  u8g2_drawStr( 0, 0, "Unicode");
  u8g2_setFont(u8g2_font_unifont_t_symbols);
  u8g2_setFontPosTop();
  u8g2_drawGlyph(0, 24, 0x2600);
  u8g2_drawStr(5, 24, " ");
  u8g2_drawGlyph(8, 24, 0x2601);
  switch(a) {
    case 0:
    case 1:
    case 2:
    case 3:
      u8g2_drawGlyph(a*3, 36, 0x2602);
      break;
    case 4:
    case 5:
    case 6:
    case 7:
      u8g2_drawGlyph(a*3, 36, 0x2614);
      break;
  }
}

#define cross_width 24
#define cross_height 24
static const unsigned char cross_bits[] U8X8_PROGMEM  = {
  0x00, 0x18, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x42, 0x00,
  0x00, 0x42, 0x00, 0x00, 0x42, 0x00, 0x00, 0x81, 0x00, 0x00, 0x81, 0x00,
  0xC0, 0x00, 0x03, 0x38, 0x3C, 0x1C, 0x06, 0x42, 0x60, 0x01, 0x42, 0x80,
  0x01, 0x42, 0x80, 0x06, 0x42, 0x60, 0x38, 0x3C, 0x1C, 0xC0, 0x00, 0x03,
  0x00, 0x81, 0x00, 0x00, 0x81, 0x00, 0x00, 0x42, 0x00, 0x00, 0x42, 0x00,
  0x00, 0x42, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x18, 0x00, };

#define cross_fill_width 24
#define cross_fill_height 24
static const unsigned char cross_fill_bits[] U8X8_PROGMEM  = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x18, 0x64, 0x00, 0x26,
  0x84, 0x00, 0x21, 0x08, 0x81, 0x10, 0x08, 0x42, 0x10, 0x10, 0x3C, 0x08,
  0x20, 0x00, 0x04, 0x40, 0x00, 0x02, 0x80, 0x00, 0x01, 0x80, 0x18, 0x01,
  0x80, 0x18, 0x01, 0x80, 0x00, 0x01, 0x40, 0x00, 0x02, 0x20, 0x00, 0x04,
  0x10, 0x3C, 0x08, 0x08, 0x42, 0x10, 0x08, 0x81, 0x10, 0x84, 0x00, 0x21,
  0x64, 0x00, 0x26, 0x18, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

#define cross_block_width 14
#define cross_block_height 14
static const unsigned char cross_block_bits[] U8X8_PROGMEM  = {
  0xFF, 0x3F, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20,
  0xC1, 0x20, 0xC1, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20,
  0x01, 0x20, 0xFF, 0x3F, };

static void u8g2_bitmap_overlay(uint8_t a) {
  uint8_t frame_size = 28;

  u8g2_drawStr(0, 0, "Bitmap overlay");

  u8g2_drawStr(0, frame_size + 12, "Solid / transparent");
  u8g2_setBitmapMode(false /* solid */);
  u8g2_drawFrame(0, 10, frame_size, frame_size);
  u8g2_drawXBMP(2, 12, cross_width, cross_height, cross_bits);
  if(a & 4)
    u8g2_drawXBMP(7, 17, cross_block_width, cross_block_height, cross_block_bits);

  u8g2_setBitmapMode(true /* transparent*/);
  u8g2_drawFrame(frame_size + 5, 10, frame_size, frame_size);
  u8g2_drawXBMP(frame_size + 7, 12, cross_width, cross_height, cross_bits);
  if(a & 4)
    u8g2_drawXBMP(frame_size + 12, 17, cross_block_width, cross_block_height, cross_block_bits);
}

static void u8g2_bitmap_modes(uint8_t transparent) {
  const uint8_t frame_size = 24;

  u8g2_drawBox(0, frame_size * 0.5, frame_size * 5, frame_size);
  u8g2_drawStr(frame_size * 0.5, 50, "Black");
  u8g2_drawStr(frame_size * 2, 50, "White");
  u8g2_drawStr(frame_size * 3.5, 50, "XOR");

  if(!transparent) {
    u8g2_setBitmapMode(false /* solid */);
    u8g2_drawStr(0, 0, "Solid bitmap");
  } else {
    u8g2_setBitmapMode(true /* transparent*/);
    u8g2_drawStr(0, 0, "Transparent bitmap");
  }
  u8g2_setDrawColor(0);// Black
  u8g2_drawXBMP(frame_size * 0.5, 24, cross_width, cross_height, cross_bits);
  u8g2_setDrawColor(1); // White
  u8g2_drawXBMP(frame_size * 2, 24, cross_width, cross_height, cross_bits);
  u8g2_setDrawColor(2); // XOR
  u8g2_drawXBMP(frame_size * 3.5, 24, cross_width, cross_height, cross_bits);
}

static uint8_t draw_state = 0;

static void draw(void) {
  u8g2_prepare();
  switch(draw_state >> 3) {
    case 0: u8g2_box_frame(draw_state&7); break;
    case 1: u8g2_disc_circle(draw_state&7); break;
    case 2: u8g2_r_frame(draw_state&7); break;
    case 3: u8g2_string(draw_state&7); break;
    case 4: u8g2_line(draw_state&7); break;
    case 5: u8g2_triangle(draw_state&7); break;
    case 6: u8g2_ascii_1(); break;
    case 7: u8g2_ascii_2(); break;
    case 8: u8g2_extra_page(draw_state&7); break;
    case 9: u8g2_bitmap_modes(0); break;
    case 10: u8g2_bitmap_modes(1); break;
    case 11: u8g2_bitmap_overlay(draw_state&7); break;
  }
}

void u8g2_full_buffer_graphic_test(void)
{
  for(int i = 0; i < 12*8; i++)
  {
    // picture loop
    u8g2_ClearBuffer(&u8g2);
    draw();
    u8g2_SendBuffer(&u8g2);

    // increase the state
    draw_state++;

    // delay between each page
    oled_delay(5000);
  }
  draw_state = 0;
}

void oled_sample_entry()
{
	oled_delay(5000);

    u8g2_Setup_ssd1309_128x64_noname2_f(&u8g2, U8G2_R0, u8x8_byte_4wire_hw_spi,u8x8_gpio_and_delay_ls);

    u8g2_InitDisplay(&u8g2);

    u8g2_ClearDisplay(&u8g2);

    u8g2_SetPowerSave(&u8g2,0);

    while(1)
    {
    	u8g2_full_buffer_graphic_test();
    }

}
