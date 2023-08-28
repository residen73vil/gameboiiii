#ifndef MENU_UTILS_UTILS_H
#define MENU_UTILS_UTILS_H

#include <gb/gb.h>
#include <stdlib.h>
#include <string.h>

typedef char tile;
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
	tile pointer;
	tile blank;
	//tile borders[6];
	int items_count;
	int item_selected;
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