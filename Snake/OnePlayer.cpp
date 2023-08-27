#include <cstdlib>
#include <unistd.h>

#include "Headers/OnePlayer.h"
#include "Headers/Snake.h"

OnePlayer::OnePlayer() {
    InitScreen();
    window = newwin(HEIGHT, WIDTH, 5, 30);
    SnakeChar = 'o'; Feed = '+';
    
    srand(time(0));

    ShowBoard();

    Points = 0;
    Delay = 110000;
    Get = false;

    Direction = 'l';
    srand(time(0));

    ShowFood();

    ShowPoint();

    ShowSnake();
    
    wrefresh(window);
}

OnePlayer::~OnePlayer() {
    CloseScreen();
}


void OnePlayer::InitScreen() {
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
    }
    
    refresh();
}

void OnePlayer::CloseScreen() {

    nodelay(stdscr, false);
    wgetch(window);
    timeout(-1);
    curs_set(1);
    echo();
    delwin(window);
    endwin();
}


void OnePlayer::ShowBoard() {
    for (int x = 0; x < WALLWIDTH; ++x) {
        for (int y = 0; y < WALLHEIGHT; ++y) {
            mvwaddch(window, y, x, (chtype) ((getBoard(x, y) == WALL) ? WALLBLOCK : ' '));
        }
    }

    wrefresh(window);
}

void OnePlayer::ShowSnake() {
    c_Snake.CreateSnake1(SnakeVector1);

    for (int i = 0; i < SnakeVector1.size(); i++) {
        wmove(window, SnakeVector1[i].y, SnakeVector1[i].x );
    }
}

void OnePlayer::ShowPoint() {
    wmove(window, HEIGHT / 5, WIDTH - 25);
    wprintw(window, "WELCOME TO THE SNAKE GAME");
    wmove(window, HEIGHT / 3, WIDTH - 18);
    wprintw(window, "Points: %d", Points);
}

void OnePlayer::ShowFood() {
    c_Snake.PuttingFood_OneSnake(SnakeVector1);
    FOOD.y = getTmpY();
    FOOD.x = getTmpX();
    wmove(window, FOOD.y, FOOD.x);
    waddch(window, (chtype) (FOODCOLOR));
}


void OnePlayer::GetFood() {
   if (SnakeVector1[0].x == FOOD.x && SnakeVector1[0].y == FOOD.y) {
        Get = true;
        ShowFood();
        
        Points += 10;
        ShowPoint();
    } else 
        Get = false;
}


void OnePlayer::MoveSnake() {
    int tmp = getch();

    switch (tmp) {
        case KEY_LEFT:  
            if (Direction != 'r')
                Direction = 'l';
            break;
        case KEY_UP:
            if (Direction != 'd')
                Direction = 'u';
            break;
        case KEY_DOWN:
            if (Direction != 'u')
                Direction = 'd';
            break;
        case KEY_RIGHT:
            if (Direction != 'l')
                Direction = 'r';
            break;
        case KEY_BACKSPACE:
            Direction = 'q';
            break;
    }

    if (!Get) {
        wmove(window, SnakeVector1[SnakeVector1.size() - 1].y, 
                SnakeVector1[SnakeVector1.size() - 1].x);
        waddch(window, ' ');
        wrefresh(window);
        SnakeVector1.pop_back();
    }

    if (Direction == 'l')               c_Snake.MoveLeftSnake(SnakeVector1);
    else if (Direction == 'r')          c_Snake.MoveRightSnake(SnakeVector1);
    else if (Direction == 'u')          c_Snake.MoveUpSnake(SnakeVector1);
    else if (Direction == 'd')          c_Snake.MoveDownSnake(SnakeVector1);

    wmove(window, SnakeVector1[0].y, SnakeVector1[0].x);

    // Snake Color
    for (int i = 0; i < SnakeVector1.size(); i++) {
        mvwaddch(window, SnakeVector1[0].y, SnakeVector1[0].x, (chtype) (SNAKEHEADCOLOR1));
        mvwaddch(window, SnakeVector1[i].y, SnakeVector1[i].x, (chtype) (SNAKBODYCOLOR1));
    }

    wrefresh(window);
}


void OnePlayer::Start() {
    while(1) {
        if (c_Snake.GetDieSnake(SnakeVector1) || 
            c_Snake.Collision_OneSnake(SnakeVector1)) {

            wmove(window, WALLHEIGHT  / 2, WALLWIDTH / 2);
            wprintw(window, "Game Over");
            break;
        } 

        GetFood();
        MoveSnake();

        if (Direction == 'q')   break;

        usleep(Delay); 
    }
}