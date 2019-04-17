#include <stdlib.h>
#include <stdio.h>

#include "encoder.h"
#include "save_file.h"
#include "options.h"

int main(int argc, char *argv[])
{
	struct options_s options;
	parseTerminalOptions(argc, argv, &options);
	if(options.help || argc < 2)
	{
		printHelp(argc, argv);
		return EXIT_FAILURE;
	}
	struct encoder_s data;
    saveFileRead(argv[argc - 1], &data);

    printf("Running encoder...\n");
	encoderRun(&data);

	saveFileWrite(argv[argc - 1], &data);
	return EXIT_SUCCESS;
}
