#include <curses.h>
#include <clocale>
#include <vector>
#include <array>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include "Tetroid.h"
#include "math_utils.h"
#include "curses_utils.h"

static const std::array<std::string,7> tetroid_strings = {
        {{" A  "
         " AA "
         "  A "
         "    "},
        {"  B "
         " BB "
         " B  "
         "    "},
        {"  C "
         "  C "
         " CC "
         "    "},
        {" D  "
         " D  "
         " DD "
         "    "},
        {"    "
         " EE "
         " EE "
         "    "},
        {"  F "
         " FF "
         "  F "
         "    "},
        {"  G "
         "  G "
         "  G "
         "  G "}}};




int main()
{
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    curs_set(0);

    mvprintw(2, 5, "LINES: %d", LINES);
    mvprintw(2, 15, "COLS:  %d", COLS);

    const size_t pg_width = 10;
    const size_t pg_height = 20;
    const pos pg_pos = {5, 3 };

    playground pg(pg_width, pg_height);

    for (size_t y_border = pg_pos.y; y_border <= pg_pos.y + pg_height + 1; y_border++) {
        mvaddch(y_border, pg_pos.x - 1, '#');
        mvaddch(y_border, pg_pos.x + pg_width + 1, '#');
    }
    mvaddstr(pg_pos.y + pg_height + 1, pg_pos.x, std::string(pg_width + 1, '#').c_str());
    refresh();

    bool gameOver = false;
    size_t it = 0;
    Tetroid tetroid(tetroid_strings[it].c_str());
    pos currentPos = { pg_width / 2 - 2, 0 };
    while(!gameOver) {
        if (collision(currentPos, tetroid, pg)) {
            it = (it + 1) % 7;
            tetroid = Tetroid(tetroid_strings[it].c_str());
            currentPos = { pg_width / 2 - 2, 0 };
            if (it > 6) {
                mvaddstr(LINES / 2, COLS / 2 - 5, "GAME OVER!");
                drawBox({COLS / 2 - 7, LINES / 2 - 1},
                        {COLS / 2 + 6, LINES / 2 + 1},
                        '#');
                gameOver = true;
            }
        }
        printTetroid(pg_pos + currentPos, tetroid);
        refresh();
        int cmd = getch();
        std::stringstream ss;
        ss << cmd;
        mvaddstr(20, 25, ss.str().c_str());
        clearTetroid(pg_pos + currentPos, tetroid);
        switch (cmd) {
            case 'A': // up
                tetroid.rotate();
                break;
            case 'B': // down
                currentPos.y++;
                break;
            case 'C': // right
                currentPos.x++;
                break;
            case 'D': // left
                currentPos.x--;
                break;
            case 'q':
                gameOver = true;
                break;
            default:
                break;
        }
    }
    endwin();
    return(0);
}
