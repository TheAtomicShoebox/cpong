#ifndef MAIN_H
#define MAIN_H

//volatile sig_atomic_t stop;

void interruptHandler(int signum);

struct location 
{
	int row;
	int col;
};

#endif
