#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char *str;

	while (1)
	{
		str = readline("\033[0;31m➜ \033[0;33m❖\033[0;m \033[0;96mℳιηι$ℎєᏝᏝ\033[0;m \033[0;33m❖ \033[0;m");
		printf("str = %s\n", str);
		add_history(str);
		free(str);
	}
	return (0);
}