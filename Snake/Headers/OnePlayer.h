#pragma once

#include <ncurses.h>
#include <string.h>
#include <vector>
#include <iostream>
#include "Snake.h"

#include "ISnakePlayer.h"

// static char Feed;
using namespace std;

static bool Get;

class OnePlayer : public ISnakePlayer {
    Snake c_Snake;
    WINDOW* window;
    char SnakeChar, Feed;
    int Points, Delay;
    char Direction;
    // bool Get;


public:

    void InitScreen();
    void CloseScreen();
    void MoveSnake();       
    void Start();
    void ShowBoard();
    void InitBoard();
    bool Continue();
    bool Collision();
    void ShowSnake();
    void ShowPoint();
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
    void ShowFood();
    void GetFood();

    inline int8_t getBoard(int x, int y) { return (c_Snake.getBoard(x, y)); }
    inline int getTmpX()                 {   return c_Snake.tmpx;   }
    inline int getTmpY()                 {   return c_Snake.tmpy;   }

    OnePlayer(/* args */);
    ~OnePlayer();
};
