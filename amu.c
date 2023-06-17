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

// Level size
int current_lvl_x = 27;
int current_lvl_y = 20;

// Window width & Height
int w, h;

// Const color
const short c_floor = 0;
const short c_industry = 0;
const short c_space = 0;
const short c_hud = 1;
const short c_title = 2;
const short c_player = 3;
const short c_moon = 3;
const short c_islands = 4;

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
	STATE_DEATH,
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

// Draw colored instance
#define td_indent 2 // Top & down ident
#define symbol_count 3

void draw_instance(int y, int x, int color, char name[])
{
	attron(COLOR_PAIR(color));

	//mvprintw(y, x, name);

	// Win offset
    int win_xoffset = w/2;
    int win_yoffset = h/2;
    
    // Level offset
    int lvl_xoffset = (current_lvl_x/2)*symbol_count+(current_lvl_x%2);
    int lvl_yoffset = (current_lvl_y+(td_indent*2))/2-(1 /* +1 indent hud */+(current_lvl_y%2));

    mvprintw(
        /* Y pos */ ceil(win_yoffset - lvl_yoffset) + (y+td_indent), 
        /* X pos */ ceil(win_xoffset - lvl_xoffset) + (x*symbol_count), 
        /* S pos */ name
    );

	refresh();

	attroff(COLOR_PAIR(color));
}

void player()
{
	// Player position
	int playerX = 0;
	int playerY = 0;

	int isJumping = 0;
    int jumpHeight = 2;
    int jumpCount = 0;

	int ch;
	// Handle player movement based on Vim bindings
	while ((ch = getch()) != 'q')
	{
		clear();
		refresh();

		if (!isJumping && playerY < current_lvl_y - 1)
        {
            playerY++;
        }

		switch (ch)
		{
			case 'h':
				if (playerX > 0)
					playerX--;	
				break;
			case 'k':
				if (!isJumping)
            	{
                	isJumping = 1;
                	jumpCount = 0;
            	}
				break;
			case 'l':
				if (playerX < current_lvl_x - 1)
					playerX++;
				break;
		}

        if (isJumping)
        {
            jumpCount++;
            if (jumpCount <= jumpHeight)
            {
                playerY--;
            }
            else if (jumpCount <= 2 * jumpHeight)
            {
            	playerY++;
            }
            else
            {
                isJumping = 0;
            }
        }

		draw_instance(playerY, playerX, c_player, s_player);

        if (playerY >= current_lvl_y)
        {
            break;
        }
	}
}

// Set color
void set_color()
{
	start_color();
	init_pair(c_hud, COLOR_BLUE, COLOR_BLACK);
	init_pair(c_title, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(c_moon, COLOR_YELLOW, COLOR_BLACK);
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
			" ::::::::"};

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
			" \\__,_||_| |_| |_| \\__,_|"};

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
	setlocale(LC_ALL, ""); // Locale to support wide characters
	initscr();			   // Initialize ncurses library
	noecho();			   // Don't echo user input
	cbreak();			   // Disable line buffering
	curs_set(FALSE);	   // Hide cursor
	keypad(stdscr, TRUE);  // Enable keypad mode
	leaveok(stdscr, TRUE); // Control cursor behavior between windows

	// If terminal does not support color
	if (!has_colors())
	{
		endwin(); // End ncurses
		printf("Your terminal does not support colors. Please enable colors to play this game.\n");
	}

	// Init current state
	current_game_state = STATE_TEST;

    getmaxyx(stdscr, h, w);

	// MAIN LOOP
	while (current_game_state != STATE_END || current_game_state != STATE_DEATH)
	{
		// Enable color support
		set_color();

		// Draw window border hud
		attron(COLOR_PAIR(c_hud));
		box(stdscr, 0, 0);
		attron(COLOR_PAIR(c_hud));

		switch (current_game_state)
		{
			case STATE_TEST:
				player();
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

		// Clear
		erase();
	}

	getch(); // Wait for user input

	endwin(); // End ncurses

	return 0;
}
