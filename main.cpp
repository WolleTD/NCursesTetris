#include <curses.h>
#include <clocale>
#include <cstddef>
#include <array>
#include <string>
#include <sstream>
#include "Playground.h"
#include "Tetroid.h"
#include "curses_utils.h"

static const std::array<std::string,7> tetroid_strings = {
        {{" A   AA   A     "},
        {"  B  BB  B      "},
        {"  C   C  CC     "},
        {" D   D   DD     "},
        {"     EE  EE     "},
        {"  F  FF   F     "},
        {"  G   G   G   G "}}};

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

    Playground pg(pg_width, pg_height);

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
        // Update display
        printTetroid(pg_pos + currentPos, tetroid);
        refresh();

        // User input
        int cmd = getch();

        // Debug output char
        std::stringstream ss;
        ss << cmd;
        mvaddstr(20, 25, ss.str().c_str());
        clearTetroid(pg_pos + currentPos, tetroid);

        // Handle user input
        pos newPos = currentPos;
        switch (cmd) {
            case 'A': // up
                tetroid.rotate();
                if (pg.collision(newPos, tetroid)) {
                    tetroid.unrotate();
                }
                break;
            case 'B': // down
                newPos.y++;
                break;
            case 'C': // right
                newPos.x++;
                break;
            case 'D': // left
                newPos.x--;
                break;
            case 'q':
                gameOver = true;
                break;
            default:
                break;
        }
        if (!pg.collision(newPos, tetroid)) {
            currentPos = newPos;
        } else {
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
    }
    endwin();
    return(0);
}
