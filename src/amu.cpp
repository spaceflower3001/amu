// spaceflower3001

#include <ncurses.h>

const char *menu_logo[4] = 
{
 "	 __ _  _ __ ___   _   _",
 "	/ _` || '_ ` _ \ | | | |",
 "     | (_| || | | | | || |_| |",
 "	\__,_||_| |_| |_| \__,_|"
};

int main() 
{
    initscr(); // initialize ncurses
    noecho(); // don't echo user input
    cbreak(); // disable line buffering
    curs_set(0); // hide cursor

    clear();

    int height = LINES * 0.75; // calculate box height
    int width = height * 4 / 3; // calculate box width
    int y = (LINES - height) / 2; // calculate box y position
    int x = (COLS - width) / 2; // calculate box x position

    WINDOW *win = newwin(height, width, y, x); // create window
    box(win, 0, 0); // draw box around window
    wrefresh(win); // refresh window

    getch(); // wait for user input

    endwin(); // end ncurses
    return 0;
}



