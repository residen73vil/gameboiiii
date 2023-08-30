/**
 * Menu routines.
 */


#ifndef MENU_UTILS_UTILS_H
#define MENU_UTILS_UTILS_H

#include <gb/gb.h>
#include <stdlib.h>
#include <string.h>

/// A type to hold tile number.
typedef char Tile;

/*
* Struct: sMenuButton
*
* Description: holds menu and its private fields
*/
struct MenuButton {

	char* name; 	///< Text on the button
	int len;		///< Text's length
	void (*action)(); ///< Action performed when button is pressed 


};
typedef struct MenuButton sMenuButton;



/*
* Struct: sMenu
*
* Description: holds menu and its private fields
*/
struct Menu {
	
	int x;
	int y;
	int width;		///< width of the menu
	char* title;			///< title shown at the top
	int title_len;		///< if 0 or > width: no title is shown
	Tile pointer;		///< tile to serve as a pointer
	Tile blank;			///< blank tile
	Tile borders[6];	///< borders {top_left, middle, top_right, vertical, bottom_left, bottom_right}
	int items_count;	///< elements in items[]
	int item_selected;	///< currently selected item
	struct Menu* prev_menu;  ///< pointer to the previous menu (if any)
	sMenuButton items[]; 

};
typedef struct Menu sMenu;

///  Shows the menu on the screen.
void menu_show();
/// Moves selection pointer up.
void menu_action_up();
/// Moves selection pointer down.
void menu_action_down();
/// Invoces function mentioned in menu item's action field. (if any)
void menu_action_chouse();
/// Prepairs menu to be displayed. Sets previous menu field to 0, or to the already opened one. 
void menu_init(sMenu* menu);
/// Closes menu and cleans its area to blank set in blank field
void menu_close();



#endif /* MENU_UTILS_H */



















/**
* @example
* Example usage:
* @code
* int result = square(5);
* 
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


	menu_init(&current_menu1);
	menu_show();
* @endcode
 */