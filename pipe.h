#pragma once
#include <ncurses.h>
#include <vector>

#define PIPE_THRESHOLD 5
using namespace std;

struct Pipe
{
    vector<vector<float>> pipe_coords;

    float topHeight, botHeight, pipeSpeed = 1;
    float pipeX, pipeY;
    int color;

    Pipe(float topHeight, float botHeight, float pipeX, float pipeY, int color)
        : topHeight(topHeight)
        , botHeight(botHeight)
        , pipeX(pipeX)
        , pipeY(pipeY)
        , color(color)
    {
        draw();
    }

    void draw()
    {
        pipe_coords.clear();
        start_color();
        init_pair(color, COLOR_BLACK, color);
        attron(COLOR_PAIR(color));
        for (float i = 2; i < topHeight; ++i)
        {
            pipe_coords.push_back(vector<float>{pipeX, i});
            pipe_coords.push_back(vector<float>{pipeX + 2, i});
            if (i == topHeight - 1)
            {
                pipe_coords.push_back(vector<float>{pipeX + 1, i});
                mvaddstr(i, pipeX, "[_]");
            }
            else {
                mvaddch(i, pipeX, '[');
                mvaddch(i, pipeX + 2, ']');
            }
        }

        for (float i = 0; i < botHeight; ++i)
        {
            pipe_coords.push_back(vector<float>{pipeX, pipeY - i});
            pipe_coords.push_back(vector<float>{pipeX + 2, pipeY - i});

            if (i == botHeight - 1)
            {
                pipe_coords.push_back(vector<float>{pipeX + 1, pipeY - i});
                mvaddstr(pipeY - i, pipeX, "[^]");
            }
            else
            {
                mvaddch(pipeY - i, pipeX, '[');
                mvaddch(pipeY - i, pipeX + 2, ']');
            }
        }
        attroff(COLOR_PAIR(2));
    }

    void _delete(vector<Pipe> &pipes)
    {
        for (vector<float> coords : pipe_coords)
            mvaddstr(coords[1], coords[0], "  ");
        

        if (pipeX < PIPE_THRESHOLD) 
            pipes.erase(pipes.begin());
    }

    void _move(vector<Pipe> &pipes)
    {
        _delete(pipes);
        pipeX -= pipeSpeed;
        draw();
    }
};