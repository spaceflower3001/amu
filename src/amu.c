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

// Const Color
const short c_hud = 1;

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
	initscr();             // Initialize ncurses library
	noecho();    	       // Don't echo user input
	cbreak();    	       // Disable line buffering
	curs_set(0); 	       // Hide cursor
    	keypad(stdscr, TRUE);  // Enable keypad mode
	leaveok(stdscr, TRUE); // Control cursor behavior between windows

	// If terminal does not support color
	if (!has_colors()) 
	{
		endwin();
		printf("Your terminal does not support color\n");
	}

	typedef enum 
	{
        	STATE_MENU,
        	STATE_INFO,
	        STATE_GAME,
        	STATE_EXIT,
	} game_state;
	
	// Init current state
	game_state current_state;
    	current_state = STATE_MENU;

	// Draw box
	attron(COLOR_PAIR(c_hud));
	box(stdscr, 0, 0);
	attron(COLOR_PAIR(c_hud));

	draw_logo();

	getch();     // Wait for user input

	endwin();    // End ncurses

	return 0;
}
