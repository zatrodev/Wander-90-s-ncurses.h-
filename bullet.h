#pragma once
#include <ncurses.h>

struct Bullet
{
    int bulletSpeed = 2;
    int bulletX, bulletY;

    Bullet(int shipX, int shipY)
        : bulletX(shipX + 4)
        , bulletY(shipY)
    {
        draw();
    }

    void draw()
    {
        mvaddstr(bulletY, bulletX, "[|>");
    }

    void _delete()
    {
        mvaddstr(bulletY, bulletX, "   ");
    }

    void _move()
    {
        _delete();
        bulletX += bulletSpeed;
        draw();
    }

    static void print(int bulletCount)
    {
        mvprintw(2, 2, "[|> x%d", bulletCount);
    }
};