/* 	
 	~ 2023
	~ spaceflower3001
	~ GNU GPLv3
	~ spaceflower3001@gmail.com
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ncurses.h>

// Window width * height
int w, h;

// Const color
const short c_hud = 1;

// Set color
void set_color() 
{
	start_color();
    	init_pair(c_hud,  COLOR_BLUE, COLOR_BLACK);
}

const char *menu_logo[4] = 
{
	"  __ _  _ __ ___   _   _ ",
	" / _` || '_ ` _ | | | | |",
	"| (_| || | | | | || |_| |",
	" \\__,_||_| |_| |_| \\__,_|"
};

void draw_logo()
{
	int y = (LINES - 4) / 2;
	int x = (COLS - 25) / 2;

	for (int i = 0; i < 4; i++) 
	{
		mvprintw(y + i, x, menu_logo[i]);
	}
}

int main(void) 
{
	initscr();             		// Initialize ncurses library
	noecho();    	       		// Don't echo user input
	cbreak();    	       		// Disable line buffering
	curs_set(0); 	       		// Hide cursor
    	keypad(stdscr, TRUE);  		// Enable keypad mode
	leaveok(stdscr, TRUE);		// Control cursor behavior between windows

	// If terminal does not support color
	if (!has_colors()) 
	{
		endwin();
		printf("Your terminal does not support colors. Please enable colors to play this game.\n");
	}

	// Enable color support
	set_color();

	// Game state
	typedef enum 
	{
        	MENU,
        	CONTROLS,
	        GAME,
        	FIN,
	} game_state;
	
	// Init current state
	game_state current_state;
    	current_state = STATE_MENU;

	// Draw window border hud
	attron(COLOR_PAIR(c_hud));
	box(stdscr, 0, 0);

	// Draw amu logo
	draw_logo();

	getch();     			// Wait for user input

	endwin();    			// End ncurses

	return 0;
}
