#ifndef MENU_UTILS_UTILS_H
#define MENU_UTILS_UTILS_H

#include <gb/gb.h>
#include <stdlib.h>
#include <string.h>

typedef char Tile;
struct MenuButton {

	char* name;
	int len;
	void (*action)();


};
typedef struct MenuButton sMenuButton;


struct Menu {
	
	int x;
	int y;
	int max_width;
	char* name;
	int name_len;
	Tile pointer;
	Tile blank;
	Tile borders[6];
	int items_count;
	int item_selected;
	struct Menu* prev_menu;
	sMenuButton items[];

};

typedef struct Menu sMenu;

void menu_show();
void menu_action_up();
void menu_action_down();
void menu_action_chouse();
void menu_init(sMenu* menu);
void menu_close();



#endif /* MENU_UTILS_H */