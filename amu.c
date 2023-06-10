/* 	
 	~ 2023
	~ spaceflower3001
	~ GNU GPLv3
	~ spaceflower3001@gmail.com
*/

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <ncurses.h>
#include <locale.h>
#include <stddef.h>

// Draw colored instance
#define td_indent 2 // Top & down ident
#define symbol_count 3

#define s_moon "o"

// Window width & Height
int w, h;

// Const color
const short c_hud  = 3;
const short c_moon = 7;

// Level size
int current_lvl_x;
int current_lvl_y;

// Const state
bool EXIT = false;

// Game state
typedef enum 
{
	TEST,
	STATE_MENU_FINGER_ANIM,
	STATE_MENU_TITLE,
	STATE_CONTROLS,
	STATE_GAME,
	STATE_DIE,
	STATE_END
} game_state;

// Init current state
game_state current_state;

// Set color
void set_color() 
{
	start_color();
    	init_pair(c_hud,  COLOR_BLUE, COLOR_BLACK);
	init_pair(c_moon,  COLOR_YELLOW, COLOR_BLACK);
}

void draw_instance(int y, int x, int color, char name[]) 
{
    attron(COLOR_PAIR(color));

    mvprintw(y, x, name);

    attroff(COLOR_PAIR(color));
}

void draw_finger()
{
	const char *finger[21] =
	{
		"				     .",                                                                   
		"				    :==-",                                                                  
		"				  :=++==-.",                                                                
		"			       .::-::::::::",                                                              
		"			  ....:::::.    ..::.",                                                             
		"		     .:==-::::::-:::..  .:::-.",                                                           
		"		   :=**++++=------::::..::::",                                                          
		"		 -**#*+++*++=-==---:::--::.",                                                            
		"	       -###**+++**++==========---.",
		"	     :*###*+++++++=--+===---===-.",                                                                
		"	   -*##**##**++=-...-.   :--=-.",                                                               
		"	 .*##****+***+=: .:::    .--.",                                                                 
		"	-##+++=:  +**+-:-=-:.:-:.::",                                                                   
		"       +*+++:    +#*+=-+++=-=++==+:",                                                                      
		"     .**==-      :**++***++***++=.:",                                                                    
		"     .+=-.         :--. -+=-.::.",                                                                      
		" ........",                                                                             
		" .------:",                                                                                                    
		" .-ENTER:",                                                                                                      
		" :------:",                                                                                                     
		" ::::::::"
	};

	// Set up timer
	timeout(100);

	// Loop through each line of the hand gesture
	for (int i = 0; i < 21; i++) 
	{
		// Center Finger ASCII
		int y = (LINES - 21) / 2;
		int x = (COLS - 53) / 2;

		// Print the line of the hand gesture
		mvprintw(y + i, x, "%s", finger[i]);
		refresh();

		// Delay
		usleep(20000); // 50ms delay
	}

	usleep(100000); // 100ms delay to see finished anim

	erase();

	refresh();

	current_state = STATE_MENU_TITLE;
}

void draw_title()
{
	// ASCII logo
	const char *logo[4] = 
	{
		"  __ _  _ __ ___   _   _ ",
		" / _` || '_ ` _ | | | | |",
		"| (_| || | | | | || |_| |",
		" \\__,_||_| |_| |_| \\__,_|"
	};

	// Center Title ASCII
	int y = (LINES - 4) / 2;
	int x = (COLS - 25) / 2;

	// Print title
	for (int i = 0; i < 4; i++) 
	{
		mvprintw(y + i, x, logo[i]);
	}

	// Update screen to display title
	refresh();
}

// Game Over
void game_over() 
{
    EXIT = true;
    endwin();
    printf("Game Over!\n");
}

void test()
{
	// Get the screen size
	int x, y;
	getmaxyx(stdscr, x, y);

	// Define the string to be printed
	wchar_t* message = L" ⁂  ";
	int messageLength = wcslen(message);

	// Calculate the coordinates for centering the string
	int row = x / 2;
	int col = (y - messageLength) / 2;

	// Print the string at the center of the screen
	mvprintw(row, col, "%ls", message);
	refresh();
}

int main(void) 
{
	setlocale(LC_ALL, "");  	// Locale to support wide characters
	initscr();             		// Initialize ncurses library
	noecho();    	       		// Don't echo user input
	cbreak();    	       		// Disable line buffering
	curs_set(0); 	       		// Hide cursor
    	keypad(stdscr, TRUE);  		// Enable keypad mode
	leaveok(stdscr, TRUE);		// Control cursor behavior between windows

	// If terminal does not support color
	if (!has_colors()) 
	{
		endwin();		// End ncurses 
		printf("Your terminal does not support colors. Please enable colors to play this game.\n");
	}

	// Init current state
	current_state = TEST;

	// Enable color support
	set_color();

	// Draw window border hud
	attron(COLOR_PAIR(c_hud));
	box(stdscr, 0, 0);
	attron(COLOR_PAIR(c_hud));


	// MAIN LOOP
	while (current_state != STATE_END || current_state != STATE_DIE)
	{
		// Enable color support
		set_color();

		// Draw window border hud
		attron(COLOR_PAIR(c_hud));
		box(stdscr, 0, 0);
		attron(COLOR_PAIR(c_hud));

		switch(current_state)
		{
			case TEST:
				//test();	
				draw_instance(50, 50, c_moon, s_moon);
				break;
			case STATE_MENU_FINGER_ANIM:
				draw_finger();
				break;
			case STATE_MENU_TITLE:
				draw_title();
				break;
			case STATE_CONTROLS:
				break;
			case STATE_GAME:
				break;
			case STATE_END:
				break;
		}

		//Clear
		erase();
	}

	getch();     			// Wait for user input

	endwin();    			// End ncurses

	return 0;
}
