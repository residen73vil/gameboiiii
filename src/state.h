/**
 * State routines.
 */


#ifndef STATE_H
#define STATE_H

#include <gb/gb.h>
#include <stdlib.h>
#include <string.h>
#include "text_output_utils.h"


enum GameState { //to be changed
	INMENU = 1,
	GAMELOOP = 1 << 1,
	INTRO = 1 << 2,
};


struct ButtonsActions {

	void (*j_start)();
	void (*j_select)(); 
	void (*j_a)();
	void (*j_b)(); 
	void (*j_up)(); 
	void (*j_down)(); 
	void (*j_left)(); 
	void (*j_right)();
	int ignore_mask;
	//todo: refresh timers

};
typedef struct ButtonsActions sButtonsActions;

struct Task{
	int counter;
	int counter_threshold;
	void (*action)(void* object);
	void* object;
};
typedef struct Task sTask;

void run_background_tasks();

void run_foreground_task();

void poll_buttons();


inline void set_buttons_actions(sButtonsActions*  actions);

void set_foreground_task(sTask* task);

void run_background_tasks();

void add_background_task(sTask* task);

#endif /* STATE */