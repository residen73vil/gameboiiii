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

void menu_show(){
	print_int8hex_win(2, 2, (int) &menu_selected_items);
	print_int8hex_win(0, 2, (int) current_menu->items);
	
	for (int i = 0; i < current_menu->items_count; i++){
		set_win_tile_xy( current_menu->x, current_menu->y+i, current_menu->blank);
		print_line_win(current_menu->x + 1, current_menu->y+i, 
			current_menu->items[i].len > current_menu->max_width ? current_menu->max_width : current_menu->items[i].len
			, current_menu->items[i].name);
		
	}
	move_pointer(NOMOVE);
}


inline void menu_action_up(){
	move_pointer( UP );
}  

inline void menu_action_down(){
	move_pointer( DOWN );
}

void menu_action_chouse(){
	current_menu->items[current_menu->item_selected].action();
	//print_int8hex_win(10, 6, 250);
}

void menu_init(sMenu* menu){
	
	current_menu =  menu;

}

void menu_close(){
}