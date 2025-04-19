#include "main.h"
#include <curses.h>
#include <locale.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define TICKS_PER_SECOND 15.0
#define SKIP_TICKS 1000000.0 / TICKS_PER_SECOND
#define MAX_FRAMESKIP 15

volatile sig_atomic_t stop;

void interruptHandler(int signum) { stop = 1; }

void loop() {}

void init(int *row, int *col) {
  signal(SIGINT, interruptHandler);
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);
  getmaxyx(stdscr, *row, *col);
}

int main(int argc, char *argv[]) {
  int loops, row, col;
  int totalTicks = 0;
  clock_t next_tick = clock();

  init(&row, &col);

  struct location ballLocation;
  ballLocation.row = row / 2;
  ballLocation.col = col / 2;

  mvprintw(0, 0, "Output: %f\n", (float)clock());
  mvprintw(1, 0, "Clocks per sec: %ld\n", CLOCKS_PER_SEC);
  mvprintw(ballLocation.row, ballLocation.col, "*");
  refresh();
  next_tick += SKIP_TICKS;
  while (!stop) {
    loops = 0;
    while (clock() > next_tick && loops < MAX_FRAMESKIP) {
      totalTicks++;
      next_tick += SKIP_TICKS;
      mvprintw(2, 0, "next_tick: %ld", next_tick);
      mvprintw(3, 0, "clock(): %ld", clock());
      loops++;
      mvprintw(4, 0, "loops: %d", loops);
      mvprintw(5, 0, "Game ticks: %d", totalTicks);
      if (totalTicks % 15 == 0) {
        mvprintw(ballLocation.row, ballLocation.col, " ");
        ballLocation.col++;
        mvprintw(ballLocation.row, ballLocation.col, "*");
        mvprintw(6, 0, "Total time(s): %d", totalTicks / 15);
      }

      refresh();
    }
  }
  printf("Game ended\n");
  endwin();
  return 0;
}
