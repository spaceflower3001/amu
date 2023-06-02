// spaceflower3001

#include <iostream>
#include <ncurses.h>
#include <string>
#include <locale>
#include <cwchar>

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

int main() 
{
	initscr(); // initialize ncurses
	noecho(); // don't echo user input
	cbreak(); // disable line buffering
	curs_set(0); // hide cursor

	refresh();

	draw_logo();

	getch(); // wait for user input

	endwin(); // end ncurses
	return 0;
}
