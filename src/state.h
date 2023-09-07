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

/// Struct: sButtonsActions 
/// Description: Struct to hold buttons actions and into on buttons cooldowns
struct ButtonsActions {

	void (*j_start)(); ///< action to be performed on button press
	int j_start_timeout; ///< sets cooldown time
	int j_start_timeout_counter; ///< counts cooldown frames, initialy should be 0 
	void (*j_select)(); 
	int j_select_timeout;
	int j_select_timeout_counter;
	void (*j_a)();
	int j_a_timeout;
	int j_a_timeout_counter;
	void (*j_b)(); 
	int j_b_timeout;
	int j_b_timeout_counter;
	void (*j_up)(); 
	int j_up_timeout;
	int j_up_timeout_counter;
	void (*j_down)(); 
	int j_down_timeout;
	int j_down_timeout_counter;
	void (*j_left)(); 
	int j_left_timeout;
	int j_left_timeout_counter;
	void (*j_right)();
	int j_right_timeout;
	int j_right_timeout_counter;
	//todo: refresh timers

};
typedef struct ButtonsActions sButtonsActions;

/*
* Struct: sTask
*
* Description: holds description of a task
*/
struct Task{
	int counter; ///< is decremented every frame
	int counter_threshold; ///< after counter reaches 0, it gets reset to this value
	void (*action)(void* object); ///< action performed when counter reaches 0
	void* object; ///< Object passed to action
};

typedef struct Task sTask;
/// Run tasks from background tasks list.
void run_background_tasks();
/// Run main task for current state.
void run_foreground_task();
/// Polls buttons and performs assigned actions if any and if button pressed.
void poll_buttons();

/// Sets structure with a set of current button actions.
inline void set_buttons_actions(sButtonsActions*  actions);

/// Sets mail task for current game state
void set_foreground_task(sTask* task);


/// Adds a task into background tasks list
void add_background_task(sTask* task);

#endif /* STATE */
