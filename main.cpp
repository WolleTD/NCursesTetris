#include <curses.h>
#include <clocale>
#include <cstddef>
#include <array>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <random>
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


int main() {
    // Playground configuration
    const size_t pg_width = 10;
    const size_t pg_height = 20;
    const position pg_pos = {5, 3 };

    // Initialize curses
    setlocale(LC_ALL, "");

    WINDOW* curswin = initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(curswin, true);

    // Debug output
    mvprintw(2, 5, "LINES: %d", LINES);
    mvprintw(2, 15, "COLS:  %d", COLS);

    // Draw playground border (TODO: Replace with drawBox)
    for (size_t y_border = pg_pos.y; y_border <= pg_pos.y + pg_height; y_border++) {
        mvaddch(y_border, pg_pos.x - 1, '#');
        mvaddch(y_border, pg_pos.x + pg_width, '#');
    }
    mvaddstr(pg_pos.y + pg_height, pg_pos.x, std::string(pg_width, '#').c_str());

    // RNG setup
    std::random_device r;
    std::mt19937 rng(r());
    std::uniform_int_distribution<size_t> randTet(0, 6);

    // Setup game variables
    bool gameOver = false;
    size_t score = 0;
    size_t clearedRows = 0;
    size_t frameCounter = 0;
    size_t speed = 20;
    size_t nextTetroidId = randTet(rng);

    Playground pg(pg_width, pg_height);
    Tetroid tetroid(tetroid_strings[nextTetroidId].c_str());
    position currentPos = {pg_width / 2 - 2, 0 };

    // Initial print
    pg.print(pg_pos);
    tetroid.print(pg_pos + currentPos);
    refresh();

    // Main loop
    while(!gameOver) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        position backupPos = currentPos;
        bool rotated = false;
        bool updatedMarks = false;
        bool needsNewTetroid = false;
        if (frameCounter % 4 == 0) {
            updatedMarks = pg.updateMarkedLines();
        }

        // Read and handle user input
        int cmd = getch();

        switch (cmd) {
            case 'A': // up
                rotated = true;
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
                    needsNewTetroid = true;
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

        if (frameCounter % speed == 0) {
            if (pg.collision(currentPos + position(0, 1), tetroid) != Collision::None) {
                needsNewTetroid = true;
            } else {
                currentPos.y++;
            }
        }

        if (needsNewTetroid) {
            size_t rows = pg.addTetroid(currentPos, tetroid);
            score += 50 * rows * (1u << rows);
            clearedRows += rows;
            if ((clearedRows >= 5) && (speed > 1)) {
                clearedRows = 0;
                speed--;
            }

            nextTetroidId = randTet(rng);
            tetroid = Tetroid(tetroid_strings[nextTetroidId].c_str());
            currentPos = { pg_width / 2 - 2, 0 };
            if (pg.collision(currentPos, tetroid) == Collision::PieceOrGround) {
                gameOver = true;
            }
        }

        // Update display
        if ((backupPos != currentPos) || rotated || updatedMarks) {
            pg.print(pg_pos);
            tetroid.print(pg_pos + currentPos);
            std::stringstream ss;
            ss << "Score: " << score;
            mvaddstr(pg_pos.y + 2, pg_pos.x + pg_width + 2, ss.str().c_str());
        }
        if (gameOver) {
            mvaddstr(LINES / 2, COLS / 2 - 5, "GAME OVER!");
            NCurses::drawBox({COLS / 2 - 7, LINES / 2 - 1},
                             {COLS / 2 + 6, LINES / 2 + 1},
                             '#');
        }
        refresh();
        frameCounter++;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    endwin();
    std::cout << "Final score: " << score << std::endl;
    return(0);
}
