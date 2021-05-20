#include <ncurses.h>
#include <string>
#include <time.h>

#include "pipe.h"
#include "ship.h"
#include "bullet.h"
#include "welcome.h"
#include "logic.h"

#define PIPE_GAP 4
#define PIPE_SPAWN 30
#define BULLET_ADD 100

void setup(int &columns, int &rows, float &shipX, float &shipY){
    clear();
    getmaxyx(stdscr, rows, columns);

    shipX = 3;
    shipY = (rows - 2) / 2;

    if (wanderMode)
        shipX = columns / 3;
}

void pipe_setup(int columns, int rows, float &topHeight, float &botHeight, float &pipeX, float &pipeY, int &color)
{
    srand(time(NULL));

    topHeight = rand() % (rows - 12) + 3;
    botHeight = (rows - 4) - topHeight - PIPE_GAP;
    pipeX = columns - 10;
    pipeY = rows - 3;
    ++color;

    if (color > 15)
        color = 1;

    if (wanderMode)
        botHeight = (rows - 1) - topHeight - PIPE_GAP - 5;
}

void layout(int columns, int rows){
    for (int i = 0; i < columns - 1; ++i){
        mvaddch(1, i, '#');
        mvaddch(rows - 2, i, '#');
    }

    for (int i = 1; i < rows - 1; ++i){
        mvaddch(i, 0, '|');
        mvaddch(i, columns - 1, '|');
    }
}

void score(int score, int rows, Logic &logic, vector<Pipe> &vec_pipes, Ship ship, int &bulletCount)
{
    move(rows - 1, 0);

    if (logic.distanceScore)
        printw("Score %d", ++score);
    else
    {
        static int point = 0;
        for (int i = 0; i < vec_pipes.size(); ++i)
        {
            if (ship.shipX == vec_pipes[i].pipeX || ship.shipY == vec_pipes[i].pipeY)
            {
                printw("Score %d", ++point);

                if (point % 2 == 0 && point != 0)
                    ++bulletCount;
            }
        }
    }
}

int main() {
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, FALSE);
    keypad(stdscr, TRUE);
    curs_set(0);

    resizeterm(22, 100);

    while(welcome()){}

    Logic logic;

    logic.set_mode();

    int columns;
    int rows;

    vector <Pipe> vec_pipes;
    vector <Bullet> bullets;

    int count = 0, bulletCount = 0, color = 0;

    float shipX, shipY;
    float topHeight, botHeight, pipeX, pipeY;

    setup(columns, rows, shipX, shipY);
    layout(columns, rows);

    Ship ship(shipX, shipY);
    while(!logic.gameOver){
        logic.controller(ship, bulletCount);
        ship.init();

        if (logic.shoot)
        {
            if (bullets.size() == 0)
                bullets.push_back(Bullet(ship.shipX, ship.shipY));

            bullets[0]._move();
            logic.check_bullet_collision(bullets, vec_pipes, columns);
        }

        if (count % PIPE_SPAWN == 0){
            pipe_setup(columns, rows, topHeight, botHeight, pipeX, pipeY, color);
            vec_pipes.push_back(Pipe(topHeight, botHeight, pipeX, pipeY, color));
        }

        if (count % BULLET_ADD == 0 && count != 0 && !wanderMode)
            ++bulletCount;

        if (vec_pipes.size() != 0)
        {
            for (int i = 0; i < vec_pipes.size(); ++i)
                vec_pipes[i]._move(vec_pipes);

            logic.check_collision(rows, ship, vec_pipes);
            score(count, rows, logic, vec_pipes, ship, bulletCount);
        }

        Bullet::print(bulletCount);

        if (logic.checkWin)
            logic.check_win(ship, columns, rows);

        refresh();
        napms(logic.mode);
        ++count;
    }
    
    clrtoeol();
    mvprintw(rows / 2, (columns / 2) - 10, "G A M E  O V E R");

    refresh();

    return 0;
}