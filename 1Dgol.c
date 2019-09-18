#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#define KEEP_LOG 1
#if(KEEP_LOG)
#define ENDOFLINEPRNT printf("\n");
#else
#define ENDOFLINEPRNT printf("\r");
#endif

#define SLEEP_TIME 0
#define BASE 2

#define ADDMOD(a,b,M) ((a+b)%M)

uint8_t chartouint8(char c);
void step(uint8_t *state, const size_t STATE_SIZE);
void printstate(uint8_t *state, const size_t STATE_SIZE);

int main(int argc, char ** argv)
{
	if(argc < 2)
	{
		fprintf(stderr,"Usage:\n1Dgol INITIAL_STATE [STEPS]\n\n");
		return 1;
	}
	size_t initlen = strlen(argv[1]);
	uint8_t state[initlen];

	for(size_t i = 0; i < initlen; i++)
	{
		state[i] = chartouint8(argv[1][i]);
	}
	if(argc >= 3)
	{
		for(unsigned long i = 0; i < strtol(argv[2],NULL,10); i++)
		{
			printstate(state,initlen);
			step(state,initlen);
#if(SLEEP_TIME != 0)
			usleep(SLEEP_TIME);
#endif
		}
		
	}
	else
	{
		while(1)
		{
			printstate(state,initlen);
			step(state,initlen);
#if(SLEEP_TIME != 0)
			usleep(SLEEP_TIME);
#endif
		}
	}

}

void step(uint8_t *state, const size_t STATE_SIZE)
{
	uint8_t nextstate[STATE_SIZE];
	nextstate[0] = ADDMOD(state[STATE_SIZE-1],state[1%STATE_SIZE],BASE);
	if(STATE_SIZE >= 2)
	{
		nextstate[STATE_SIZE-1] = ADDMOD(state[STATE_SIZE-2],state[0],BASE);
	}
	for(size_t i = 1; i < STATE_SIZE-1; i++)
	{
		nextstate[i] = ADDMOD(state[i-1],state[i+1],BASE);
	}
	memcpy(state,nextstate,STATE_SIZE);
}

void printstate(uint8_t *state, const size_t STATE_SIZE)
{
	for(size_t i = 0; i < STATE_SIZE; i++)
	{
		printf("%u", state[i]);
	}
	ENDOFLINEPRNT
}

uint8_t chartouint8(char c)
{
	if(c >= '0' && c <= '9')
	{
		return c-'0';
	}
	return 0xFF;
}
