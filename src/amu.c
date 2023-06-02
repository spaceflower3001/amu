/* 
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
	initscr();   // initialize ncurses
	noecho();    // don't echo user input
	cbreak();    // disable line buffering
	curs_set(0); // hide cursor


	draw_logo();

	getch();     // wait for user input

	endwin();    // end ncurses
	return 0;
}