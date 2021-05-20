#pragma once
#include <ncurses.h>
#include <cstdlib>

bool easyMode, normalMode, hardMode, wanderMode;

void sleepOnce(int count, int sleep = 100)
{
    if (count == 0)
        napms(sleep);
}

bool welcome()
{
    int ch;

    static int count = 0;
    static int i = -3;

    int columns, rows;
    getmaxyx(stdscr, rows, columns);

    sleepOnce(count);
    mvaddstr((rows / 2) - 11, (columns / 2) - 35, " __      __                    .___");
    refresh();

    sleepOnce(count);
    mvaddstr((rows / 2) - 10, (columns / 2) - 35, "/  \\    /  \\_____    ____    __| _/___________");
    refresh();

    sleepOnce(count);
    mvaddstr((rows / 2) - 9, (columns / 2) - 35, "\\   \\/\\/   /\\__  \\  /    \\  / __ |/ __ \\_  __ \\");
    refresh();

    sleepOnce(count);
    mvaddstr((rows / 2) - 8, (columns / 2) - 35, " \\        /  / __ \\|   |  \\/ /_/ \\  ___/|  | \\/");
    refresh();

    sleepOnce(count);        
    mvaddstr((rows / 2) - 7, (columns / 2) - 35, "  \\__/\\  /  (____  /___|  /\\____ |\\___  >__|");
    refresh();

    sleepOnce(count);        
    mvaddstr((rows / 2) - 6, (columns / 2) - 35, "       \\/        \\/     \\/      \\/    \\/  ");
    refresh();

    sleepOnce(count, 300); 
    mvaddstr((rows / 2) - 3, (columns / 2) - 20, "E A S Y  M O D E");
    mvaddstr((rows / 2) - 1, (columns / 2) - 20, "N O R M A L  M O D E");
    mvaddstr((rows / 2) + 1, (columns / 2) - 20, "H A R D  M O D E");
    mvaddstr((rows / 2) + 3, (columns / 2) - 20, "W A N D E R  M O D E");
    refresh();

    ch = wgetch(stdscr);
    switch (ch)
    {
    case 'w':
        mvaddstr((rows / 2) + i, (columns / 2) - 24, "  ");

        if (i != -3)
            i -= 2;
        
        refresh();
        break;
    case 's':
        mvaddstr((rows / 2) + i, (columns / 2) - 24, "  ");

        if (i != 3)
            i += 2;

        refresh();
        break;
    case 10:
        if (i == -3)
            easyMode = true;
        else if (i == -1)
            normalMode = true;
        else if (i == 1)
            hardMode = true;
        else
            wanderMode = true;
        
        return false;

    case 'q':
        exit(0);
        break;
    }

    sleepOnce(count, 300); 
    mvaddstr((rows / 2) + i, (columns / 2) - 24, ">>");

    mvaddstr((rows / 2) + 7, (columns / 2) - 35, "     S T A R T : [ENTER]      Q U I T : [Q]     ");

    ++count;

    refresh();

    return true;
}