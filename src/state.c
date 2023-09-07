#include "state.h"

uint8_t joy = 0;
uint8_t joy_presed = 0;


sTask* foreground_task = 0;

int number_of_bg_tasks = 0;
sTask* background_tasks[10];

sButtonsActions* buttons_actions = 0;

inline void set_buttons_actions(sButtonsActions*  actions){
	 buttons_actions = actions;
}

/// Check if a button is pressed and perform associated action.
/// @param NAMEUPPER is part of J_{NAMEUPPER} def 
/// @param NAMELOWER is lowercase name to be used in struct fields names 
#define CHECKBUTTON(NAMEUPPER,NAMELOWER)  if (joy & J_##NAMEUPPER \
				&& (buttons_actions->j_##NAMELOWER##_timeout_counter <= 0) \
			) \
	     if (buttons_actions->j_##NAMELOWER){ \
		   	 (*buttons_actions->j_##NAMELOWER)(); \
			 buttons_actions->j_##NAMELOWER##_timeout_counter = buttons_actions->j_##NAMELOWER##_timeout; \
		 }	
void poll_buttons()
{
    joy = joypad();
	CHECKBUTTON(START, start);
	CHECKBUTTON(LEFT, left); 
	CHECKBUTTON(RIGHT, right);
	CHECKBUTTON(UP, up);
	CHECKBUTTON(DOWN, down);
	CHECKBUTTON(A, a);
	CHECKBUTTON(B, b);
	CHECKBUTTON(SELECT, select);

	// check and update counters for buttons cooldowns 
	if (buttons_actions->j_start_timeout_counter >=0) buttons_actions->j_start_timeout_counter--;
	if (buttons_actions->j_left_timeout_counter >=0) buttons_actions->j_left_timeout_counter--;
	if (buttons_actions->j_right_timeout_counter >=0) buttons_actions->j_right_timeout_counter--;
	if (buttons_actions->j_up_timeout_counter >=0) buttons_actions->j_up_timeout_counter--;
	if (buttons_actions->j_down_timeout_counter >=0) buttons_actions->j_down_timeout_counter--;
	if (buttons_actions->j_a_timeout_counter >=0) buttons_actions->j_a_timeout_counter--;
	if (buttons_actions->j_b_timeout_counter >=0) buttons_actions->j_b_timeout_counter--;
	if (buttons_actions->j_select_timeout_counter >=0) buttons_actions->j_select_timeout_counter--;
	joy_presed = joy; //todo: add ignore mask joy & ignore mask
}

void run_foreground_task(){
	if (foreground_task == 0)
		return; // if there is no task just return (shouldn't happen!)
	foreground_task->counter--;
	print_int8hex_win(2, 11, foreground_task->counter);
	if (foreground_task->counter <= 0) {
		foreground_task->counter = foreground_task->counter_threshold;
		(*foreground_task->action)(foreground_task->object);
	}
}

void run_background_tasks(){
	if (number_of_bg_tasks <= 0)
		return;
	for (int i = 0; i < number_of_bg_tasks; i++) //run each action in the list
	{
		background_tasks[i]->counter--;
		print_int8hex_win(2, 13, background_tasks[i]->counter);
		if (background_tasks[i]->counter <= 0) {
			background_tasks[i]->counter = background_tasks[i]->counter_threshold;
			(*background_tasks[i]->action)(background_tasks[i]->object);
		}
	}
}

void set_foreground_task(sTask* task){
	foreground_task = task;
}


void add_background_task(sTask* task){
	//todo: make it so index of the task is returned, so that it could be deleted
	// also change the whole structure of the list to make it possible
	background_tasks[number_of_bg_tasks] = task;
	number_of_bg_tasks++;
}
