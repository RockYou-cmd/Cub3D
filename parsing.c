#include "cub3d.h"

void	end_game(char *error_message)
{
	printf("\033[1;31m");
	if (error_message)
		exit(printf("Error\n%s\n", error_message));
	if (!error_message)
	{
		printf("\033[0;36m");
		printf("\n░▒▓█►─═  ＧＡＭＥ ＣＬＯＳＥＤ ＳＵＣＣＥＳＦＵＬＬＹ ═─◄█▓▒░\n");
		exit(0);
	}
}

void parsing()
{
	
}