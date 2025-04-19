#ifndef MAIN_H
#define MAIN_H

#define FALSE 0
#define TRUE 1

// volatile sig_atomic_t stop;

void interruptHandler(int signum);

struct location {
  int row;
  int col;
};

#endif
