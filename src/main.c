#include <gb/gb.h>
#include <stdint.h>
#include "../res/dungeon_map.h"
#include "../res/dungeon_tiles.h"
#include "../res/window_map.h"
#include "../obj/res/font.h"
#include "../obj/res/strings.h"
#include "text_output_utils.h"
#include "menu_utils.h"


#define GAME_BKG_SCROLL_STEP 2
#define VRAM_MAP_WIDTH 0x20
#define VRAM_MAP_BKG 0x9800
#define VRAM_MAP_WIN 0x9C00

enum GameState { //to be changed
	MAINMENU = 1,
	OPTIONS = 1 << 1,
};
typedef enum GameState EGameState;

struct ButtonsActions {

	void (*j_start)();
	void (*j_select)(); 
	void (*j_a)();
	void (*j_b)(); 
	void (*j_up)(); 
	void (*j_down)(); 
	void (*j_left)(); 
	void (*j_right)();

} buttons_actions;
typedef struct ButtonsActions sButtonsActions;

sButtonsActions menu_actions = { menu_action_chouse, menu_action_chouse, menu_action_chouse, 0, menu_action_up, menu_action_down, 0, 0};




sMenu current_menu1 = { 5, 2, 10, 0, 0, 0x53, 0x01, { 0x2b, 0x2c, 0x2d, 0x3b, 0x31, 0x33 }, 3, 0, 0, { 
	{main_menu, LENGTH_MAIN_MENU, menu_action_main}, 
	{options, LENGTH_OPTIONS, menu_action_opt},
	{main_menu, LENGTH_MAIN_MENU, menu_action_main}

}};

//                      x  y  mw  name  point blank { tl    mid   tr    vert  bl    br     len select   prev_menu
sMenu current_menu2 = { 3, 6, 10, options, LENGTH_OPTIONS, 0x53, 0x01, { 0x22, 0x22, 0x2d, 0x33, 0x34, 0x35 }, 5, 0, 0, { 
	{main_menu, LENGTH_MAIN_MENU, menu_action_main}, 
	{options, LENGTH_OPTIONS, menu_action_opt},
	{main_menu, LENGTH_MAIN_MENU, menu_action_main},
	{main_menu, LENGTH_MAIN_MENU, menu_action_main},
	{main_menu, LENGTH_MAIN_MENU, menu_action_main}

}};


void menu_action_main(){
	print_line_win(1, 15, LENGTH_MAIN_MENU, main_menu);
	menu_close();
}  
void menu_action_opt(){	
	print_line_win(1, 15, LENGTH_OPTIONS, options);
	menu_init(&current_menu2);
	menu_show();
}  








void init_gfx() {
    // Load Background tiles and then map
DISPLAY_OFF;
    set_bkg_data(0, 84u, dungeon_tiles);
    set_bkg_data(194u, font_TILE_COUNT, font_tiles);
    set_bkg_tiles(0, 0, 32u, 32u, dungeon_mapPLN0);
    set_win_tiles(0, 0, 10u, 10u, window_mapPLN0);

	//tesing 
    //set_win_tiles(1, 1, 6, 8, test_text);
	//print_line_win(1, 0, LENGTH_TEST_LINE, test_line);

	print_int8hex_win(10, 4, 0xFFu);
	print_int8hex_win(10, 5, 0);
	print_int8hex_win(10, 6, 255);
DISPLAY_ON;
	// Turn the background map on to make it visible
    SHOW_BKG;
    SHOW_WIN;
}

EGameState current_game_state = MAINMENU;
EGameState previous_game_state = OPTIONS;


EGameState change_game_state(EGameState new_state)
{
	EGameState prev = current_game_state;
	current_game_state = new_state;
	return prev;
}

uint8_t joy = 0;
uint8_t joy_presed = 0;

void main(void)
{
	init_gfx();
	menu_init(&current_menu1);
	menu_show();
	buttons_actions = menu_actions;

    // Loop forever
    while(1) {
        

		// Game main loop processing goes here
		switch (current_game_state)
		{
			case MAINMENU:
				print_line_win(1, 0, LENGTH_MAIN_MENU, main_menu);
				break;
			case OPTIONS:
				print_line_win(1, 0, LENGTH_OPTIONS, options);
				break;

		}
        joy = joypad();
        if (joy & J_START && !(joy_presed &J_START) )
            if (buttons_actions.j_start)  (*buttons_actions.j_start)();
        if (joy & J_LEFT )
            if (buttons_actions.j_left)  (*buttons_actions.j_left)();
        if (joy & J_RIGHT)
            if (buttons_actions.j_right)  (*buttons_actions.j_right)();
        if (joy & J_UP && !(joy_presed &J_UP))
           if (buttons_actions.j_up)  (*buttons_actions.j_up)();
        if (joy & J_DOWN && !(joy_presed &J_DOWN))
            if (buttons_actions.j_down)  (*buttons_actions.j_down)();
		joy_presed = joy;

		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
