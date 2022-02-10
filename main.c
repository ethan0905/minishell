#include "minishell.h"

int main()
{
	char *str;

	str = readline("\033[0;33m❖\033[0;m \033[0;35mℳιηι$ℎєᏝᏝ\033[0;m \033[0;33m❖ \033[0;m");
	printf("str = %s\n", str);
	return (0);
}