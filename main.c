#include "shell.h"
#include "_printf.h"

/**
 * main - shell
 * Return: Always 0.
 */
int main()
{
	int status;
	size_t len = 0;
	char *buffer = 0, *delim = " \t\n", **args;
	ssize_t getline_status = 1;
	int i = 0;

	while (1)
	{
		_printf("#cisfun$ ");
		getline_status = getline(&buffer, &len, stdin);
		if (getline_status == -1)
			break;
		buffer = strtok(buffer, "\n");
		if (!buffer)
			continue;
		printf("%s\n", buffer);
		/* delimit buffer by delimiters */
		args = split(buffer, delim);

		while (args && args[i])
			printf("%s\n", args[i++]);

		/* create a child process */
		if (args && fork() == 0)
		{
			/* exec shell command, return error message if it fails */
			if (execve(args[0], args, NULL) == -1)
				perror("Error:");
			break;
		}
		else
		{
			/* wait until child process ends to continue */
			wait(&status);
			free(buffer);
		}
		free_string_list(args);
	}

	/* WE SHOULD HANDLE end-of-file (Ctrl+d, etc.) AND FREE ALLOCATED MEMORY
	 * BEFORE ENDING THE PROGRAM.
	 * - **arg
	 * - *buffer
	 */
	free_string_list(args);
	free(buffer);
	return (0);
}
