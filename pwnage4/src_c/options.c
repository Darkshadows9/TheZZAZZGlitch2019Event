#include "options.h"

void parseTerminalOptions(int argc, char *argv[], struct options_s *options)
{
	for (int i = 1; i < argc && argv[i][0] == '-'; ++i)
	{
		switch (argv[i][1])
		{
		case 'h':
			options->help = true;
			break;
		}
	}
	return;
}

void printHelp(int argc, char *argv[])
{
	printf("Your command:\n");
	for (int i = 0; i < argc; ++i)
	{
		printf("%s ", argv[i]);
	}
	printf("\n\n");
	printf("Use the following format:\n");
	printf("[program_name] [flags] [file]\n\n");
	printf("Flags:\n");
	printf("[-h]elp: Display this help message. Also displayed when there's less than one argument, e.g. no file was specified.\n");
	printf("\n");
	printf("Example:\n");
	printf("%s \"fools.sav\"\n", argv[0]);
	printf("%s \"fools pwnage4 clean.sav\"\n", argv[0]);
	return;
}
