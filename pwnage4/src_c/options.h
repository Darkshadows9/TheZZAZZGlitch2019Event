#ifndef OPTIONS_INC
#define OPTIONS_INC

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct options_s
{
	bool help;
};

void parseTerminalOptions(int argc, char *argv[], struct options_s *options);
void printHelp();

#endif /*OPTIONS_INC*/
