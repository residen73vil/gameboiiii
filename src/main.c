#include <gb/gb.h>
#include <stdint.h>
#include "../res/dungeon_map.h"
#include "../res/dungeon_tiles.h"
#include "../res/window_map.h"
#include "../obj/res/font.h"


#define GAME_BKG_SCROLL_STEP 2
#define VRAM_MAP_WIDTH 0x20
#define VRAM_MAP_BKG 0x9800
#define VRAM_MAP_WIN 0x9C00
typedef unsigned char uchar_t;

enum game_states {
  TRANSITION_TO_TITLE,
  TITLE,
  TRANSITION_TO_TUTORIAL,
  TUTORIAL,
  MAIN,
  FAIL,
  TRANSITION_TO_RETRY,
  RETRY
};

unsigned char  buf[37] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

void puttext(const uint8_t x, const uint8_t y, const uint8_t w, const uint8_t h, const uchar_t* str){
	uint8_t * addr =  (uint8_t*)(VRAM_MAP_WIN + x + y * VRAM_MAP_WIDTH);
	for (uint8_t i = 0; i < h; i++){
		addr =  (uint8_t*)(VRAM_MAP_WIN + x + (y+i)* VRAM_MAP_WIDTH);
		for (uint8_t j = 0; j < w; j++)
			*(addr++)=*(str++)+66;
	}
}

void init_gfx() {
    // Load Background tiles and then map
 DISPLAY_OFF;
    set_bkg_data(0, 84u, dungeon_tiles);
    set_bkg_data(84u, 77u, font_tiles);
    set_bkg_tiles(0, 0, 32u, 32u, dungeon_mapPLN0);
    set_win_tiles(0, 0, 10u, 10u, window_mapPLN0);

    puttext(1, 1, 6, 6, buf);
DISPLAY_ON;
	// Turn the background map on to make it visible
    SHOW_BKG;
    SHOW_WIN;
}



uint8_t joy = 0;
uint8_t x = 0;

void main(void)
{
	init_gfx();


    // Loop forever
    while(1) {
        

		// Game main loop processing goes here
        joy = joypad();
        if (joy & J_START)
            move_bkg(x++,0);
        if (joy & J_LEFT )
            scroll_win(1,0);
        if (joy & J_RIGHT)
            scroll_win(-1,0);
        if (joy & J_UP)
            scroll_win(0,1);
        if (joy & J_DOWN)
            scroll_win(0,-1);

		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
