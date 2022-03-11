#include "../minishell.h"

void	control_c(int code)
{
	(void)code;
//	write(1, "\n", 1);
//	rl_on_new_line();
//	rl_replace_line();
//	rl_redisplay();
//	printf("\n\033[0;31m➜ \033[0;33m❖\033[0;m \033[0;96 minishell \033[0;m \033[0;33m❖ \033[0;m");
}

void	control_d(int code)
{
	(void)code;
//	printf("^\n");
//	printf("code ctrl + C: %d\n", code);
}
