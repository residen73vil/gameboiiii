#include "menu_utils.h"
#include "text_output_utils.h"

sMenu* current_menu = 0;

enum MovePointer { UP = -1, DOWN = 1, NOMOVE = 0};
typedef enum MovePointer eMovePointer;
/// Moves the pointer in the menu. 
/// Ensures boundaries, clears old pointer position and draws it at the new one
void move_pointer(eMovePointer where){
	set_win_tile_xy(current_menu->x, current_menu->y +  current_menu->item_selected, current_menu->blank);
	int new_value = current_menu->item_selected + where;
	if ( new_value < 0 ) new_value = 0;
	if ( new_value >= current_menu->items_count - 1 ) new_value = current_menu->items_count - 1 ;
	set_win_tile_xy(current_menu->x, current_menu->y +  new_value, current_menu->pointer);
	current_menu->item_selected = new_value;
}

void clene_rect(int x, int y, int h, int w, Tile tile){
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			set_win_tile_xy(x+j, y+i, tile);
}

/// Draws decorations around menu, and its title if any.
/// @ param tiles Holds decoration tiles {top_left, middle, top_right, vertical, bottom_left, bottom_right}
void decorate(int x, int y, int h, int w, Tile tiles[]) {
	for (int i = -1; i <= h+1; i++) {
		if (i == -1) { // first lien, situated over the menu
			set_win_tile_xy( x-1, y-1, tiles[0] );
			for (int j = 0; j < w; j++)
			{
				set_win_tile_xy( x + j, y + i, tiles[1] );
			}
			set_win_tile_xy( x+w, y-1, tiles[2] );
			//print menu title at the top
			if ( current_menu->title_len > 0 && current_menu->title_len < current_menu->width)
			{
				int offset = ( current_menu->width - current_menu->title_len )/2;
				print_line_win( current_menu->x + offset, y-1, current_menu->title_len, current_menu->title );
			}

		} else if (i == h+1) { // bottom line of decoration
			set_win_tile_xy( x-1, y+h, tiles[4] );
			for (int j = 0; j < w; j++)
				set_win_tile_xy( x + j, y + h, tiles[1] );
			set_win_tile_xy( x+w, y+h, tiles[5] );
		} else {  // vertical borders at each side
			set_win_tile_xy( x-1, y+i, tiles[3] );
			set_win_tile_xy( x+w, y+i, tiles[3] );
		}
	}
}

void menu_show(){
		
	clene_rect( current_menu->x, current_menu->y, current_menu->items_count, 
					current_menu->width, current_menu->blank );
	if ( current_menu->borders[0] != 0 ){
		decorate( current_menu->x, current_menu->y, current_menu->items_count,
					 current_menu->width,  current_menu->borders );}
	//draw menu items
	for (int i = 0; i < current_menu->items_count; i++)
	{
		set_win_tile_xy( current_menu->x, current_menu->y+i, current_menu->blank);
		print_line_win(
						current_menu->x + 1, current_menu->y+i 
						, current_menu->items[i].len > current_menu->width ? 
								current_menu->width : current_menu->items[i].len
						, current_menu->items[i].name
					);
		
	}
	move_pointer(NOMOVE); // just draw the pointer
	SHOW_WIN;
	
}




void menu_action_up(){
	move_pointer( UP );
}  

void menu_action_down(){
	move_pointer( DOWN );
}

void menu_action_chouse(){
	current_menu->items[current_menu->item_selected].action();
	//print_int8hex_win(10, 6, 250);
}

void menu_init(sMenu* menu){
	
	menu->prev_menu = 0;
	if (current_menu != 0)
		menu->prev_menu = current_menu;
	current_menu =  menu;

}

void menu_close(){
	int x, y, h, w;
	x = current_menu->x;
	y = current_menu->y;
	h = current_menu->items_count;
	w = current_menu->width;
	if ( current_menu->borders[0] != 0 ) // if border is present 
	{
		x-=1;
		y-=1;
		h+=2;
		w+=2;
	}
		
	clene_rect( x, y, h, w, current_menu->blank );
	if (current_menu->prev_menu != 0 )
	{
		current_menu = current_menu->prev_menu;
		menu_show();
	}  else { // if last menu
		HIDE_WIN;
	}
}