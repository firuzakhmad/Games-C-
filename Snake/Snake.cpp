#include <iostream>
#include <unistd.h>
#include <string.h>

#include "Headers/Snake.h"
#include "Headers/TwoPlayers.h"


SnakePart::SnakePart(int col, int row) {
    x = col;
    y = row;
}


SnakePart::SnakePart() {
    x = 0;
    y = 0;
}

Snake::Snake() {
    InitBoard();
}


// Putting Food in random posisionn and checking to not appear on the bodys' of snakes
void Snake::PuttingFood(vector<SnakePart>& S1, vector<SnakePart>& S2) {
    while (1) {
        tmpx = rand() % WALLWIDTH + 1;
        tmpy = rand() % WALLHEIGHT + 1;

        // To not appear on Snake One 
        for (int i = 0; i < S1.size(); i++) 
            if (S1[i].x == tmpx && S1[i].y == tmpy)
                continue;

        // To not appear on Snake Two 
        for (int i = 0; i < S2.size(); i++) 
            if (S2[i].x == tmpx && S2[i].y == tmpy)
                continue;

        if (tmpx >= WALLWIDTH - 2 || tmpy >= WALLHEIGHT - 3)
            continue;

        FOOD.x = tmpx;
        FOOD.y = tmpy;
        break;
    }
}

void Snake::PuttingFood_OneSnake(vector<SnakePart>& S1) {
    while (1) {
        tmpx = rand() % WALLWIDTH + 1;
        tmpy = rand() % WALLHEIGHT + 1;

        // To not appear on Snake One 
        for (int i = 0; i < S1.size(); i++) 
            if (S1[i].x == tmpx && S1[i].y == tmpy)
                continue;

        if (tmpx >= WALLWIDTH - 2 || tmpy >= WALLHEIGHT - 3)
            continue;

        FOOD.x = tmpx;
        FOOD.y = tmpy;
        break;
    }
}

void Snake::InitBoard() {
    memset(m_Board, 0, sizeof m_Board);

    for (int x = 0; x < WALLWIDTH; x++) {
        m_Board[x][0]                   = WALL;
        m_Board[x][WALLHEIGHT - 1]      = WALL;

        for (int y = 1; y < WALLHEIGHT; y++) {
            m_Board[0][y]               = WALL;
            m_Board[WALLWIDTH - 1][y]   = WALL;
        }
    }
}


// Creating Snake 1 in different position from the second one
void Snake::CreateSnake1(vector<SnakePart>& Vv) {
    for (int i = 0; i < 5; i++) {
        Vv.push_back(SnakePart(40 + i, 10));
    }
}

// Creating Snake 2 in different position from the first one
void Snake::CreateSnake2(vector<SnakePart>& Vv) {
    for (int i = 0; i < 5; i++) {
        Vv.push_back(SnakePart(50 + i, 10));
    }
}

// Erasing Vector as cutting points 
void Snake::EraseVector(vector<SnakePart>& Vv) {
    for (int i = 0; i < Vv.size() - 2; i++) {
        Vv.erase(Vv.begin(),Vv.begin() + i);
    }
}


// Movement of Snakes
void Snake::MoveDownSnake(vector<SnakePart>& Vv) {
    Vv.insert(Vv.begin(), SnakePart(Vv[0].x, Vv[0].y + 1));
}

void Snake::MoveLeftSnake(vector<SnakePart>& Vv) {
    Vv.insert(Vv.begin(), SnakePart(Vv[0].x - 1, Vv[0].y));
}

void Snake::MoveRightSnake(vector<SnakePart>& Vv) {
    Vv.insert(Vv.begin(), SnakePart(Vv[0].x + 1, Vv[0].y));
}

void Snake::MoveUpSnake(vector<SnakePart>& Vv) {
    Vv.insert(Vv.begin(), SnakePart(Vv[0].x, Vv[0].y - 1));
}



// Dying if Snakes touch the walls 
bool Snake::DieSnake(vector<SnakePart>& Vv) {
    if (Vv[0].x == 0 || Vv[0].x == WALLWIDTH - 1 ||
        Vv[0].y == 0 || Vv[0].y == WALLHEIGHT - 1)
        return true;

    return false;
}

bool Snake::Collision_OneSnake(vector<SnakePart>& S1) {
    for (int i = 2; i < S1.size(); i++)
        if ((S1[0].x == S1[i].x && S1[i].y == S1[0].y))
            return true;

    return false;
}

// Checking collision of Snake with their bodies and other bodies 
bool Snake::CollisionSnake1(vector<SnakePart>& S1, vector<SnakePart>& S2) {
    for (int i = 2; i < S1.size(); i++)
        if ((S1[0].x == S1[i].x && S1[i].y == S1[0].y) ||
            (S1[0].x == S2[i].x && S1[i].y == S2[0].y))
            return true;

    return false;
}

bool Snake::CollisionSnake2(vector<SnakePart>& S1, vector<SnakePart>& S2) {
    for (int i = 2; i < S2.size(); i++)
        if ((S2[0].x == S2[i].x && S2[i].y == S2[0].y) ||
            (S2[0].x == S1[i].x && S2[i].y == S1[0].y))
            return true;

    return false;
}

// bool Snake::CuttingPoints(int& points)
// {
//     if (points > 0 && points % 5 == 0) 
//     {
//         points -= 5;
//         return true;
//     }
        
//     return false;
// }
