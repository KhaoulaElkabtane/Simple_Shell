#include "shell.h"

/**
 * shellLoop - Execute the main shell loop.
 * @in: Pointer to the infocmd struct containing shell information.
 * @str: Array of strings containing command line arguments.
 *
 * Return: the status code to indicate the exit condition of the shell.
 */
int shellLoop(infocmd *in, char **str)
{
	ssize_t i = 0;
	int ret = 0;

	while (i != -1 && ret != -2)
	{
		unsetInfo(in);
		if (fctActive(in))
			strputs("$ ");
		eputchar(BUF_FLUSH);
		i = extractInput(in);
		if (i != -1)
		{
			setInfo(in, str);
			ret = findBuil(in);
			if (ret == -1)
				pathCmd(in);
		}
		else if (fctActive(in))
			_putchar('\n');
		libInfo(in, 0);
	}
	creathistory(in);
	libInfo(in, 1);
	if (!fctActive(in) && in->status)
		exit(in->status);
	if (ret == -2)
	{
		if (in->err_num == -1)
			exit(in->status);
		exit(in->err_num);
	}
	return (ret);
}

/**
 * findBuil - Find and execute a built-in command.
 * @in: Pointer to the infocmd struct containing shell information.
 *
 * Return: the result of executing the built-in command or -1 if the command
 * is not found.
 */
int findBuil(infocmd *in)
{
	int i, ret = -1;
	builtin_table table[] = {
		{"exit", fctexit},
		{"env", curEnv},
		{"help", fcthelp},
		{"history", printHistory},
		{"setenv", setEnvVal},
		{"unsetenv", unsetEnvVal},
		{"cd", fctcurrent},
		{"alias", manAlias},
		{NULL, NULL}
	};

	for (i = 0; table[i].type; i++)
		if (strcomparison(in->argv[0], table[i].type) == 0)
		{
			in->line_count++;
			ret = table[i].func(in);
			break;
		}
	return (ret);
}

/**
 * pathCmd - Handle non-built-in commands by searching in the PATH.
 * @in: Pointer to the infocmd struct containing shell information.
 *
 * Return: none
 */
void pathCmd(infocmd *in)
{
	char *th = NULL;
	int i, j;

	in->path = in->argv[0];
	if (in->linecount_flag == 1)
	{
		in->line_count++;
		in->linecount_flag = 0;
	}
	for (i = 0, j = 0; in->arg[i]; i++)
		if (!fctDelim(in->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	th = fctpath(in, getVarEnv(in, "PATH="), in->argv[0]);
	if (th)
	{
		in->path = th;
		forkCmd(in);
	}
	else
	{
		if ((fctActive(in) || getVarEnv(in, "PATH=")
			|| in->argv[0][0] == '/') && fctCmd(in, in->argv[0]))
			forkCmd(in);
		else if (*(in->arg) != '\n')
		{
			in->status = 127;
			erprint(in, "not found\n");
		}
	}
}

/**
 * forkCmd - Fork and execute a command in a child process.
 * @in: Pointer to the infocmd struct containing shell information.
 *
 * Return: none
 */
void forkCmd(infocmd *in)
{
	pid_t id;

	id = fork();
	if (id == -1)
	{
		perror("Error:");
		return;
	}
	if (id == 0)
	{
		if (execve(in->path, in->argv, getEnv(in)) == -1)
		{
			libInfo(in, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(in->status));
		if (WIFEXITED(in->status))
		{
			in->status = WEXITSTATUS(in->status);
			if (in->status == 126)
				erprint(in, "Permission denied\n");
		}
	}
}
