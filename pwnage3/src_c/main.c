#include <stdlib.h>
#include <stdio.h>

#include "decryption.h"
#include "save_file.h"
#include "options.h"

//TODO: Add option to get arbitrary values from a dump file of just the values required instead of from the original save file. Name it simple mode.
int main(int argc, char *argv[])
{
	struct options_s options;
	parseTerminalOptions(argc, argv, &options);
	if(options.help || argc < 2)
	{
		printHelp(argc, argv);
		return EXIT_FAILURE;
	}

	struct decryption_s *data = calloc(1, sizeof(struct decryption_s) + MAP_SIZE * sizeof(uint8_t));
	saveFileRead(argv[argc - 1], data);

	if(options.reverse)
	{
		printf("-[r]everse flag detected.\nRunning reverse decryption...\n");
		decryptionRunReverse(data);
	}
	else
	{
		printf("Running decryption...\n");
		decryptionRun(data);
	}

	saveFileWrite(argv[argc - 1], data);
	return EXIT_SUCCESS;
}
