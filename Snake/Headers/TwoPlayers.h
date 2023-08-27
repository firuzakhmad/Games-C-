#pragma once

#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <vector>

#include "Snake.h"
#include "ISnakePlayer.h"

#define KEY_UP2                 ('w')
#define KEY_DOWN2               ('s')
#define KEY_RIGHT2              ('d')
#define KEY_LEFT2               ('a')



// static char Feed;
using namespace std;

// static bool Get;

class TwoPlayers : public ISnakePlayer {
    Snake c_Snake;
    WINDOW* window;

    int Delay;
    int Snake_1_Points, Snake_2_Points;

    char SnakeChar, Feed;
    char DirectionSnake1;
    char DirectionSnake2;

    bool GetSnake1, GetSnake2;

public:

    void InitScreen();
    void CloseScreen();
    void MoveSnake();       
    void Start();
    void ShowBoard();
    void InitBoard();
    bool Continue();
    bool DieSnake1();
    bool DieSnake2();
    bool CollisionSnake1();
    bool CollisionSnake2();
    void ShowSnake1();
    void ShowSnake2();
    void ShowPoint();
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
    void ShowFood();
   
    void GetFood();
    void DeletingDeadSnake(vector<SnakePart> Vv);
    int CuttingPoints(int* points);

    inline int8_t getBoard(int x, int y) { return (c_Snake.getBoard(x, y)); }
    inline int getTmpX()                 {   return c_Snake.tmpx;   }
    inline int getTmpY()                 {   return c_Snake.tmpy;   }

    TwoPlayers(/* args */);
    ~TwoPlayers();
};
