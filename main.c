#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define TICKS_PER_SECOND 15.0
#define SKIP_TICKS 1000000.0 / TICKS_PER_SECOND
#define MAX_FRAMESKIP 5

volatile sig_atomic_t stop;

void interruptHandler(int signum)
{
	stop = 1;
}


int main(int argc, char *argv[])
{
	signal(SIGINT, interruptHandler);
	clock_t next_tick = clock();

	int loops;
	

	printf("Output: %f\n",(float)clock());
	printf("Clocks per sec: %ld\n", CLOCKS_PER_SEC);
	next_tick += SKIP_TICKS;
	while(!stop)
	{
		loops = 0;
		while(clock() > next_tick && loops < MAX_FRAMESKIP)
		{
			next_tick += SKIP_TICKS;
			printf("next_tick: %ld\n", next_tick);
			printf("clock(): %ld\n", clock());
			loops++;
			printf("loops: %d\n", loops);
			printf("Game ticked\n");
		}
	}
	printf("Game ended\n");
	return 0;
}
