#include "./exec_files.h"

int main(int argc, char **argv, char **env)
{
	// int pid;
	// int fd[2];
	// char **test;

	// test = ft_split(argv[1], ' ');
	// pid = fork();
	// if (pid == 0)
	// {
	// 	fd[0] = open("MANOMANO", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// 	fd[1] = open("test@", O_CREAT | O_WRONLY | O_APPEND, 0644);
	// 	dup2(fd[0], 1);
	// 	dup2(fd[1], fd[0]);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	execve(test[0], test, env);
	// 	puts("PASSER");
	// }
	char str[2];

	str[0] = 'p';
	str[1] = 0;
	if (str[1])
		return (1);
	return (0);
}

//multiple redirection dans bash 
//il prend en compte le dernier fichier pour infile et outfile
