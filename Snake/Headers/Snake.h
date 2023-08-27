#pragma once

#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <vector>
#include <cstdlib>


#define HEIGHT                      (40)
#define WIDTH                       (100)
#define WALLHEIGHT                  (35)
#define WALLWIDTH                   (70)
#define WALLBLOCK                   (ACS_PLUS | COLOR_PAIR(COLOR_BLOCK(4)))
#define COLOR_BLOCK(n)              (n)

#define SNAKEHEADCOLOR1             (ACS_PLUS | COLOR_PAIR(COLOR_BLOCK(2)))
#define SNAKBODYCOLOR1              (ACS_PLUS | COLOR_PAIR(COLOR_BLOCK(3)))
#define SNAKEHEADCOLOR2             (ACS_PLUS | COLOR_PAIR(COLOR_BLOCK(2)))
#define SNAKBODYCOLOR2              (ACS_PLUS | COLOR_PAIR(COLOR_BLOCK(5)))
#define FOODCOLOR                   (ACS_PLUS | COLOR_PAIR(COLOR_BLOCK(1)))
#define WALL	                    (-1)


using namespace std;

struct SnakePart {
    int x, y;
    SnakePart(int col, int row);
    SnakePart();
};


static vector<SnakePart> SnakeVector1;
static vector<SnakePart> SnakeVector2;

static SnakePart FOOD;

    
class Snake {
    
    int8_t m_Board[WIDTH][HEIGHT];        

public:

    int tmpx, tmpy;

    Snake(/* args */);

    void InitScreen();
    void CloseScreen();
    void Start();
    void InitBoard();
    void ShowBoard();
    void PuttingFood(vector<SnakePart>& S1, vector<SnakePart>& S2); 
    bool Collision();
    void MoveLeft();
    void CreateSnake1(vector<SnakePart>& Vv);
    void CreateSnake2(vector<SnakePart>& Vv);
    void EraseVector(vector<SnakePart>& Vv);
    void MoveDownSnake(vector<SnakePart>& Vv);
    void MoveUpSnake(vector<SnakePart>& Vv);
    void MoveRightSnake(vector<SnakePart>& Vv);
    void MoveLeftSnake(vector<SnakePart>& Vv);
    bool MoveDownDirection();
    bool MoveUpDirection();
    bool MoveRightDirection();
    void MoveLeftDirection();
    void PuttingFood_OneSnake(vector<SnakePart>& S1);
    bool Collision_OneSnake(vector<SnakePart>& S1);

    bool DieSnake(vector<SnakePart>& Vv);
    bool CollisionSnake1(vector<SnakePart>& S1, vector<SnakePart>& S2);
    bool CollisionSnake2(vector<SnakePart>& S1, vector<SnakePart>& S2);

    bool CuttingPoints(int& points);
    inline bool GetCuttingPoints(int& points) {   return  points;}

    inline int8_t getBoard(int x, int y)    {  return m_Board[x][y]; }
    inline int getTmpX()                    {   return tmpx;   }
    inline int getTmpY()                    {   return tmpy;   }
    inline bool GetDieSnake(vector<SnakePart>& V)  {   return DieSnake(V);   }
    inline bool GetCollisionSnake1(vector<SnakePart>& S1, vector<SnakePart>& S2) {   return  CollisionSnake1(S1, S2); }
    inline bool GetCollisionSnake2(vector<SnakePart>& S1, vector<SnakePart>& S2) {   return  CollisionSnake2(S1, S2); }
};


