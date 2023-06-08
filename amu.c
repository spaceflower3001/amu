/* 	
 	~ 2023
	~ spaceflower3001
	~ GNU GPLv3
	~ spaceflower3001@gmail.com
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <ncurses.h>

// Const color
const short c_hud = 1;

// Game state
typedef enum 
{
	STATE_MENU_FINGER_ANIM,
	STATE_MENU_TITLE,
	STATE_CONTROLS,
	STATE_GAME,
	STATE_FIN
} game_state;

// Init current state
game_state current_state;

// Set color
void set_color() 
{
	start_color();
    	init_pair(c_hud,  COLOR_BLUE, COLOR_BLACK);
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
		endwin();		// End ncurses 
		printf("Your terminal does not support colors. Please enable colors to play this game.\n");
	}

	// Init current state
	current_state = STATE_MENU_FINGER_ANIM;

	// MAIN LOOP
	while (current_state != STATE_FIN)
	{
		// Enable color support
		set_color();

		// Draw window border hud
		attron(COLOR_PAIR(c_hud));
		box(stdscr, 0, 0);

		switch(current_state)
		{
			case STATE_MENU_FINGER_ANIM:
				draw_finger();
				break;
			case STATE_MENU_TITLE:
				draw_title();
				break;
		}

		//Clear
		erase();
	}

	getch();     			// Wait for user input

	endwin();    			// End ncurses

	return 0;
}
