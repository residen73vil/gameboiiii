#include <gb/gb.h>
#include <stdint.h>
#include "../res/dungeon_map.h"
#include "../res/dungeon_tiles.h"
#include "../res/window_map.h"
#include "../obj/res/font.h"
#include "../obj/res/strings.h"
#include "text_output_utils.h"


#define GAME_BKG_SCROLL_STEP 2
#define VRAM_MAP_WIDTH 0x20
#define VRAM_MAP_BKG 0x9800
#define VRAM_MAP_WIN 0x9C00

enum game_states { //to be changed
  TRANSITION_TO_TITLE,
  TITLE,
  TRANSITION_TO_TUTORIAL,
  TUTORIAL,
  MAIN,
  FAIL,
  TRANSITION_TO_RETRY,
  RETRY
};

void init_gfx() {
    // Load Background tiles and then map
DISPLAY_OFF;
    set_bkg_data(0, 84u, dungeon_tiles);
    set_bkg_data(194u, font_TILE_COUNT, font_tiles);
    set_bkg_tiles(0, 0, 32u, 32u, dungeon_mapPLN0);
    set_win_tiles(0, 0, 10u, 10u, window_mapPLN0);

	//tesing 
    set_win_tiles(1, 1, 6, 8, test_text);
	print_line_win(1, 0, LENGTH_TEST_LINE, test_line);

	print_int8hex_win(10, 3, 10);
	print_int8hex_win(10, 4, 0xFFu);
	print_int8hex_win(10, 5, 0);
	print_int8hex_win(10, 6, 255);
DISPLAY_ON;
	// Turn the background map on to make it visible
    SHOW_BKG;
    SHOW_WIN;
}



uint8_t joy = 0;

void main(void)
{
	init_gfx();


    // Loop forever
    while(1) {
        

		// Game main loop processing goes here
        joy = joypad();
        if (joy & J_START)
            scroll_bkg(1,0);
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
