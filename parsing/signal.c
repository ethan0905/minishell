#include "../minishell.h"

void	control_c(int code)
{
	(void)code;
//	printf("^C");
//	printf("\n");
	printf("\033[0;31m➜ \033[0;33m❖\033[0;m \033[0;96mminishell\033[0;m \033[0;33m❖ \033[0;m");
}

void	control_d(int code)
{
	(void)code;
//	printf("^\n");
//	printf("code ctrl + C: %d\n", code);
}
