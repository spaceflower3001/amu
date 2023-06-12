#include <ncurses.h>

int main() {
    initscr();
    start_color();

    int num_color_pairs = COLOR_PAIRS;
    printw("Number of color pairs: %d\n", num_color_pairs);

    for (int i = 1; i < num_color_pairs; i++) {
        init_pair(i, i % 8, (i + 1) % 8);
        attron(COLOR_PAIR(i));
        printw("Color pair %d: Hello, world!\n", i);
        attroff(COLOR_PAIR(i));
    }

    refresh();
    getch();
    endwin();

    return 0;
}

