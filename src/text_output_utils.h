/**
 * @file text_output_utils.h
 * @brief Header file for text output utility functions
 * 
 * This header file provides declarations for utility functions that enable text output.
 * It provides functions to print out a specially prepared, with tools/text2tile_addreses.py 
 * string and to print out a 8bit hexadecimal number
 */

#ifndef TEXT_OUTPUT_UTILS_H
#define TEXT_OUTPUT_UTILS_H

#include <gb/gb.h>

#define ANSII_NUMBERIC_OFFSET 0xd1u
#define ANSII_ALPHABETIC_OFFSET 0xd8u
typedef unsigned char uchar_t;

/**
 * @brief Prints a line of characters of specified length from a buffer to the window
 * 
 * @param x The X-coordinate of the location to start printing the line, in pixels
 * @param y The Y-coordinate of the location to start printing the line, in pixels
 * @param len The length of the line to be printed, in characters
 * @param buf A pointer to the buffer containing the characters to be printed
 */
static inline void print_line_win(uint8_t x, uint8_t y, uint8_t len, const uchar_t* buf){
	set_win_tiles(x, y, len, 1, buf);
}

/**
 * @brief Prints a single byte value in hexadecimal format at the specified location within the window
 * 
 * @param x The X-coordinate of the location to print the value, in pixels
 * @param y The Y-coordinate of the location to print the value, in pixels
 * @param number The value to print, as an 8-bit unsigned integer
 */
void print_int8hex_win(uint8_t x,uint8_t y, uint8_t number);


#endif /* TEXT_OUTPUT_UTILS_H */


// For testing and as examples
//	set_bkg_data(194u, font_TILE_COUNT, font_tiles);
//  
//  set_win_tiles(1, 1, 6, 8, var4);
//	print_line_win(1, 0, LENGTH_VAR3, var3);
//	print_int8hex_win(10, 3, 10);
//	print_int8hex_win(10, 4, 0xFFu);
//	print_int8hex_win(10, 5, 0);
//	print_int8hex_win(10, 6, 255);
