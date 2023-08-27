#include <cstdlib>
#include <unistd.h>

#include "Headers/Snake.h"
#include "Headers/TwoPlayers.h"

TwoPlayers::TwoPlayers() {
    InitScreen();
    window = newwin(HEIGHT, WIDTH, 5, 30);
    SnakeChar = 'o'; Feed = '+';
    
    srand(time(0));

    ShowBoard();

    Snake_1_Points = 0;
    Snake_2_Points = 0;

    Delay = 110000;
    GetSnake1 = false;

    DirectionSnake1 = 'l';
    DirectionSnake2 = 's';

    srand(time(0));

    ShowFood();

    ShowPoint();

    ShowSnake1();
    ShowSnake2();
    
    wrefresh(window);
}

TwoPlayers::~TwoPlayers() {
    CloseScreen();
}

void TwoPlayers::InitScreen() {
    initscr();
    nodelay(stdscr, true);          // To start the program without pressing any key
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    if (has_colors()) {
        start_color();

        // init_color(COLOR_RED, 1000, 0, 0);
        init_color(COLOR_RED, 1000, 0, 0);
        init_color(COLOR_GREEN, 0, 1000, 0);
        init_color(COLOR_BLUE, 0, 0, 1000);
        init_color(COLOR_CYAN, 0, 1000, 1000);
        init_color(COLOR_MAGENTA, 1000, 0, 1000);
        // init_color(COLOR_YELLOW, 1000, 1000, 0);
        init_color(COLOR_WHITE, 1000, 1000, 1000);

        init_pair(COLOR_BLOCK(1), COLOR_GREEN, COLOR_GREEN);
        init_pair(COLOR_BLOCK(2), COLOR_RED, COLOR_RED);
        init_pair(COLOR_BLOCK(3), COLOR_BLUE, COLOR_BLUE);
        init_pair(COLOR_BLOCK(4), COLOR_BLUE, COLOR_YELLOW);
        init_pair(COLOR_BLOCK(5), COLOR_CYAN, COLOR_CYAN);
    }
    
    refresh();
}

void TwoPlayers::CloseScreen() {

    nodelay(stdscr, false);
    wgetch(window);
    timeout(-1);
    curs_set(1);
    echo();
    delwin(window);
    endwin();
}

void TwoPlayers::ShowBoard() {
    for (int x = 0; x < WALLWIDTH; ++x) {
        for (int y = 0; y < WALLHEIGHT; ++y) {
            mvwaddch(window, y, x, (chtype) ((getBoard(x, y) == WALL) ? WALLBLOCK : ' '));
        }
    }
    wrefresh(window);
}

void TwoPlayers::ShowSnake1() {
    c_Snake.CreateSnake1(SnakeVector1);

    for (int i = 0; i < SnakeVector1.size(); i++) {
        wmove(window, SnakeVector1[i].y, SnakeVector1[i].x );
        waddch(window, SnakeChar);
    }
}

void TwoPlayers::ShowSnake2() {
    c_Snake.CreateSnake2(SnakeVector2);

    for (int i = 0; i < SnakeVector2.size(); i++) {
        wmove(window, SnakeVector2[i].y, SnakeVector2[i].x );
    }
}

void TwoPlayers::ShowPoint() {
    wmove(window, HEIGHT / 5, WIDTH - 25);
    wprintw(window, "WELCOME TO THE SNAKE GAME");
    wmove(window, HEIGHT / 3, WIDTH - 25);
    wprintw(window, "First Snake Points: %d", Snake_1_Points);

    wmove(window, HEIGHT / 2, WIDTH - 25);
    wprintw(window, "Second Snake Points: %d", Snake_2_Points);
}

void TwoPlayers::ShowFood() {
    c_Snake.PuttingFood(SnakeVector1, SnakeVector2);
    FOOD.y = getTmpY();
    FOOD.x = getTmpX();
    wmove(window, FOOD.y, FOOD.x);
    waddch(window, (chtype) (FOODCOLOR));
}

void TwoPlayers::GetFood() {
    if (SnakeVector2[0].x == FOOD.x && SnakeVector2[0].y == FOOD.y) {
        GetSnake2 = true;
        ShowFood();
        
        Snake_2_Points += 10;
        ShowPoint();
    } 

    else if (SnakeVector1[0].x == FOOD.x && SnakeVector1[0].y == FOOD.y) {
        GetSnake1 = true;
        ShowFood();
        
        Snake_1_Points += 10;
        ShowPoint();
    } else 
        (GetSnake1 = false, GetSnake2 = false);
}


void TwoPlayers::MoveSnake() {
    int tmp = getch();

    switch (tmp) {
        case KEY_LEFT:  
            if (DirectionSnake1 != 'r')
                DirectionSnake1 = 'l';
            break;
        case KEY_UP:
            if (DirectionSnake1 != 'd')
                DirectionSnake1 = 'u';
            break;
        case KEY_DOWN:
            if (DirectionSnake1 != 'u')
                DirectionSnake1 = 'd';
            break;
        case KEY_RIGHT:
            if (DirectionSnake1 != 'l')
                DirectionSnake1 = 'r';
            break;

        case KEY_UP2:
            if (DirectionSnake2 != 's')
                DirectionSnake2 = 'w';
            break;
        case KEY_DOWN2:
            if (DirectionSnake2 != 'w')
                DirectionSnake2 = 's';
            break;
        case KEY_RIGHT2:
            if (DirectionSnake2 != 'a')
                DirectionSnake2 = 'd';
            break;
        case KEY_LEFT2:
            if (DirectionSnake2 != 'd')
                DirectionSnake2 = 'a';
            break;
        case KEY_BACKSPACE:
            DirectionSnake1 = 'q';
            break;
    }

    if(!GetSnake1) {
        // Snake 1
        wmove(window, SnakeVector1[SnakeVector1.size() - 1].y, SnakeVector1[SnakeVector1.size() - 1].x);
        waddch(window, ' ');
        wrefresh(window);
        SnakeVector1.pop_back();
    }

    if(!GetSnake2) {
        // Snake 2
            wmove(window, SnakeVector2[SnakeVector2.size() - 1].y, SnakeVector2[SnakeVector2.size() - 1].x);
            waddch(window, ' ');
            wrefresh(window);
            SnakeVector2.pop_back();
    }
    
    // First Snake Movement
    if (DirectionSnake1 == 'l')                       c_Snake.MoveLeftSnake(SnakeVector1);
    else if (DirectionSnake1 == 'r')                  c_Snake.MoveRightSnake(SnakeVector1);
    else if (DirectionSnake1 == 'u')                  c_Snake.MoveUpSnake(SnakeVector1);
    else if (DirectionSnake1 == 'd')                  c_Snake.MoveDownSnake(SnakeVector1);
    wmove(window, SnakeVector1[0].y, SnakeVector1[0].x);


    // Second Snake Movement
    if (DirectionSnake2 == 'a')                       c_Snake.MoveLeftSnake(SnakeVector2);
    else if (DirectionSnake2 == 'd')                  c_Snake.MoveRightSnake(SnakeVector2);
    else if (DirectionSnake2 == 'w')                  c_Snake.MoveUpSnake(SnakeVector2);
    else if (DirectionSnake2 == 's')                  c_Snake.MoveDownSnake(SnakeVector2);
    wmove(window, SnakeVector2[0].y, SnakeVector2[0].x);

    // Snake 1 Color
    for (int i = 0; i < SnakeVector1.size(); i++) {
        mvwaddch(window, SnakeVector1[0].y, SnakeVector1[0].x, (chtype) (SNAKEHEADCOLOR1));
        mvwaddch(window, SnakeVector1[i].y, SnakeVector1[i].x, (chtype) (SNAKBODYCOLOR1));
    }

    // Snake 2 Color
    for (int i = 0; i < SnakeVector2.size(); i++) {
        mvwaddch(window, SnakeVector2[0].y, SnakeVector2[0].x, (chtype) (SNAKEHEADCOLOR2));
        mvwaddch(window, SnakeVector2[i].y, SnakeVector2[i].x, (chtype) (SNAKBODYCOLOR2));
    }

    wrefresh(window);
}

// int TwoPlayers::CuttingPoints(int points)
// {
//     if (points > 0 && points % 5 == 0) 
//         points -= 5;
//     return points;
// }

void TwoPlayers::DeletingDeadSnake(vector<SnakePart> Vv) {
    for (int i = 0; i < Vv.size() - 2; i++) {
        mvwaddch(window, Vv[i].y, Vv[i].x, (chtype) (' '));
    }
}


void TwoPlayers::Start() {
    while(1) {
        if(c_Snake.GetDieSnake(SnakeVector1)) {
            wmove(window, WALLHEIGHT  / 2, WALLWIDTH / 2);
            wprintw(window, "Player Two Won");
            break;
        }

        if(c_Snake.GetDieSnake(SnakeVector2)) {
            wmove(window, WALLHEIGHT  / 2, WALLWIDTH / 2);
            wprintw(window, "Player One Won");
            break;
        }

        if(c_Snake.GetCollisionSnake1(SnakeVector1, SnakeVector2)) {
            DeletingDeadSnake(SnakeVector1);
            c_Snake.EraseVector(SnakeVector1);
            c_Snake.GetCuttingPoints(Snake_1_Points);
            ShowPoint();
        }

        if(c_Snake.GetCollisionSnake2(SnakeVector1, SnakeVector2)) {
            DeletingDeadSnake(SnakeVector2);
            c_Snake.EraseVector(SnakeVector2);
            c_Snake.GetCuttingPoints(Snake_2_Points);
            ShowPoint();
        }  

        GetFood();
        MoveSnake();

        if (DirectionSnake1 == 'q')   break;

        usleep(Delay); 
    }
}