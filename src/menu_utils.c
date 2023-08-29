#include "menu_utils.h"
#include "text_output_utils.h"

extern int menu_item_selected;
extern int menu_items_count;
extern sMenuButton menu_selected_items[];
sMenu* current_menu = 0;

enum MovePointer { UP = -1, DOWN = 1, NOMOVE = 0};
typedef enum MovePointer eMovePointer;
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

void decorate(int x, int y, int h, int w, Tile tiles[]) {
	for (int i = -1; i <= h+1; i++) {
		if (i == -1) {
			set_win_tile_xy( x-1, y-1, tiles[0] );
			for (int j = 0; j < w; j++)
				set_win_tile_xy( x + j, y + i, tiles[1] );
			set_win_tile_xy( x+w, y-1, tiles[2] );
		} else if (i == h+1) {
			set_win_tile_xy( x-1, y+h, tiles[4] );
			for (int j = 0; j < w; j++)
				set_win_tile_xy( x + j, y + h, tiles[1] );
			set_win_tile_xy( x+w, y+h, tiles[5] );
		} else {
			set_win_tile_xy( x-1, y+i, tiles[3] );
			set_win_tile_xy( x+w, y+i, tiles[3] );
		}
	}
}

void menu_show(){
		
	clene_rect( current_menu->x, current_menu->y, current_menu->items_count, current_menu->max_width, current_menu->blank );
	if ( current_menu->borders[0] != 0 )
		decorate( current_menu->x, current_menu->y, current_menu->items_count, current_menu->max_width,  current_menu->borders );
	for (int i = 0; i < current_menu->items_count; i++){
		set_win_tile_xy( current_menu->x, current_menu->y+i, current_menu->blank);
		print_line_win(current_menu->x + 1, current_menu->y+i, 
			current_menu->items[i].len > current_menu->max_width ? current_menu->max_width : current_menu->items[i].len
			, current_menu->items[i].name);
		
	}
	move_pointer(NOMOVE);
	SHOW_WIN;
	
}




inline void menu_action_up(){
	move_pointer( UP );
}  

inline void menu_action_down(){
	move_pointer( DOWN );
}

inline void menu_action_chouse(){
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
	w = current_menu->max_width;
	if ( current_menu->borders[0] != 0 )
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
	}  else {
		HIDE_WIN;
	}
}