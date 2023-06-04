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
		// Print the line of the hand gesture
		mvprintw(i, 0, "%s", finger[i]);
		refresh();

		// Delay
		usleep(50000); // 50ms delay
	}
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

	int y = (LINES - 4) / 2;
	int x = (COLS - 25) / 2;

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
    	current_state = MENU;

	// Draw window border hud
	attron(COLOR_PAIR(c_hud));
	box(stdscr, 0, 0);

	// Draw amu logo
	//draw_logo();
	
	draw_finger();

	getch();     			// Wait for user input

	endwin();    			// End ncurses

	return 0;
}
