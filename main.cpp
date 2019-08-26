#include <curses.h>
#include <clocale>
#include <cstddef>
#include <array>
#include <string>
#include <sstream>
#include "Playground.h"
#include "Tetroid.h"
#include "NCurses.h"

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
    const position pg_pos = {5, 3 };

    Playground pg(pg_width, pg_height);

    for (size_t y_border = pg_pos.y; y_border <= pg_pos.y + pg_height; y_border++) {
        mvaddch(y_border, pg_pos.x - 1, '#');
        mvaddch(y_border, pg_pos.x + pg_width, '#');
    }
    mvaddstr(pg_pos.y + pg_height, pg_pos.x, std::string(pg_width, '#').c_str());
    refresh();

    bool gameOver = false;
    size_t it = 0;
    Tetroid tetroid(tetroid_strings[it].c_str());
    position currentPos = {pg_width / 2 - 2, 0 };

    while(!gameOver) {
        // Update display
        tetroid.print(pg_pos + currentPos);
        pg.print(pg_pos);
        refresh();

        // User input
        int cmd = getch();

        // Debug output char
        std::stringstream ss;
        ss << cmd;
        mvaddstr(20, 25, ss.str().c_str());
        tetroid.clear(pg_pos + currentPos);

        // Handle user input
        switch (cmd) {
            case 'A': // up
                tetroid.rotate();
                switch (pg.collision(currentPos, tetroid)) {
                    case Collision::BorderLeft:
                        currentPos.x++;
                        break;
                    case Collision::BorderRight:
                        currentPos.x--;
                        break;
                    case Collision::PieceOrGround:
                        tetroid.unrotate();
                        break;
                    case Collision::None:
                        break;
                }
                break;
            case 'B': // down
                if (pg.collision(currentPos + position(0, 1), tetroid) != Collision::None) {
                    pg.addTetroid(currentPos, tetroid);
                    it = (it + 1) % 7;
                    tetroid = Tetroid(tetroid_strings[it].c_str());
                    currentPos = { pg_width / 2 - 2, 0 };
                } else {
                    currentPos.y++;
                }
                break;
            case 'C': // right
                if (pg.collision(currentPos + position(1, 0), tetroid) == Collision::None) {
                    currentPos.x++;
                }
                break;
            case 'D': // left
                if (pg.collision(currentPos - position(1, 0), tetroid) == Collision::None) {
                    currentPos.x--;
                }
                break;
            case 'q':
                gameOver = true;
                break;
            default:
                break;
        }
        if (it > 6) {
            mvaddstr(LINES / 2, COLS / 2 - 5, "GAME OVER!");
            NCurses::drawBox({COLS / 2 - 7, LINES / 2 - 1},
                    {COLS / 2 + 6, LINES / 2 + 1},
                    '#');
            gameOver = true;
        }
    }
    endwin();
    return(0);
}
