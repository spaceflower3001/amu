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
		usleep(50000); // 50ms delay
	}

	usleep(100000); // 100ms delay to see finished anim
}

void draw_logo()
{
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
}

// Check next lvl
/*
bool next_lvl(short current_lvl[][arr_size_x]) 
{
    if (current_lvl[player.y][player.x] == i_exit)
    {
        level = level + 1;
        return true;
    }

    return false;
}
*/

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
    	current_state = MENU;

	// Draw window border hud
	attron(COLOR_PAIR(c_hud));
	box(stdscr, 0, 0);

	// MAIN LOOP
	while (current_state != FIN)
	{
		// Enable color support
		set_color();

		switch(current_state)
		{
			case MENU:
				draw_finger();
		}
	}

	getch();     			// Wait for user input

	endwin();    			// End ncurses

	return 0;
}
