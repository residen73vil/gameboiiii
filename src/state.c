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


void poll_buttons()
{
    joy = joypad();
    if (joy & J_START && !(joy_presed &J_START) )
        if (buttons_actions->j_start)  (*buttons_actions->j_start)();
    if (joy & J_LEFT )
        if (buttons_actions->j_left)  (*buttons_actions->j_left)();
    if (joy & J_RIGHT)
        if (buttons_actions->j_right)  (*buttons_actions->j_right)();
    if (joy & J_UP && !(joy_presed &J_UP))
       if (buttons_actions->j_up)  (*buttons_actions->j_up)();
    if (joy & J_DOWN && !(joy_presed &J_DOWN))
        if (buttons_actions->j_down)  (*buttons_actions->j_down)();
	joy_presed = joy; //todo: add ignore mask joy & ignore mask
}

void run_foreground_task(){
	if (foreground_task == 0)
		return;
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
	for (int i = 0; i < number_of_bg_tasks; i++)
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
	background_tasks[number_of_bg_tasks] = task;
	number_of_bg_tasks++;
}