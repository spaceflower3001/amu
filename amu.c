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

// Define symbol
#define s_player "ꆛ ꐕ ꆜ"

// Const color
const short c_floor    = 0;
const short c_industry = 0;
const short c_space    = 0;
const short c_hud      = 1;
const short c_title    = 2;
const short c_player   = 3;
const short c_moon     = 3;
const short c_islands  = 4;

// Const state
bool EXIT = false;

// Game state
typedef enum 
{
	STATE_TEST,
	STATE_MENU_FINGER_ANIM,
	STATE_MENU_TITLE,
	STATE_CONTROLS,
	STATE_GAME,
	STATE_DIE,
	STATE_END
} game_state;

// Lvl state
typedef enum
{
	LVL_TEST,
	LVL_MOON,
	LVL_SPACE,
	LVL_ISLANDS,
	LVL_INDUSTRY
} lvl_state;

// Init states
game_state current_game_state;
lvl_state current_level_state;

// Player position
int playerX = 0;
int playerY = 0;

// Game world dimensions
const int worldWidth = 100;
const int worldHeight = 100;

void draw_instance(int y, int x, int color, char name[]) 
{
    attron(COLOR_PAIR(color));

    mvprintw(y, x, name);

	refresh();

    attroff(COLOR_PAIR(color));
}

// Function to handle player movement
void move_player(int dx, int dy) 
{
    int newX = playerX + dx;
    int newY = playerY + dy;

    // Check y or x
    if (newX >= 0)
        playerX = newX;
    if (newY >= 0)
        playerY = newY;	
}

void player_input()
{
	int ch;
	// Handle player movement based on Vim bindings
	while ((ch = getch()) != 'q')
	{
		refresh();
		switch (ch) 
		{
			case 'h':
				move_player(-1, 0);
				break;
			case 'j':
				move_player(0, 1);
				break;
			case 'k':
				move_player(0, -1);
				break;
			case 'l':
				move_player(1, 0);
				break;
		}
		draw_instance(playerY, playerX, c_player, s_player);
	}
}

// Set color
void set_color() 
{
	start_color();
    init_pair(c_hud,  COLOR_BLUE, COLOR_BLACK);
	init_pair(c_title, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(c_moon,  COLOR_YELLOW, COLOR_BLACK);
	init_pair(c_space, COLOR_WHITE, COLOR_BLACK);
	init_pair(c_islands, COLOR_GREEN, COLOR_BLACK);
	init_pair(c_industry, COLOR_WHITE, COLOR_BLACK);
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

	attron(COLOR_PAIR(c_hud));

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

	attroff(COLOR_PAIR(c_hud));

	current_game_state = STATE_MENU_TITLE;

	// Remove ASCII
	erase();

	// Update screen
	refresh();

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

	attron(COLOR_PAIR(c_title));

	// Center Title ASCII
	int y = (LINES - 4) / 2;
	int x = (COLS - 25) / 2;

	// Print title
	for (int i = 0; i < 4; i++) 
	{
		mvprintw(y + i, x, logo[i]);
	}

	attroff(COLOR_PAIR(c_title));

	// Update screen to display title
	refresh();
}

void game_over() 
{
    EXIT = true;
    endwin();
}

int main(void) 
{
	setlocale(LC_ALL, "");  	// Locale to support wide characters
	initscr();             		// Initialize ncurses library
	noecho();    	       		// Don't echo user input
	cbreak();    	       		// Disable line buffering
	curs_set(FALSE); 	       	// Hide cursor
    keypad(stdscr, TRUE);  		// Enable keypad mode
	leaveok(stdscr, TRUE);		// Control cursor behavior between windows

	// If terminal does not support color
	if (!has_colors()) 
	{
		endwin();		// End ncurses 
		printf("Your terminal does not support colors. Please enable colors to play this game.\n");
	}

	// Init current state
	current_game_state = STATE_TEST;

	// MAIN LOOP
	while (current_game_state != STATE_END || current_game_state != STATE_DIE)
	{
		// Enable color support
		set_color();

		// Draw window border hud
		attron(COLOR_PAIR(c_hud));
		box(stdscr, 0, 0);
		attron(COLOR_PAIR(c_hud));

		switch(current_game_state)
		{
			case STATE_TEST:
				player_input();
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
