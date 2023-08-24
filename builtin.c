#include "shell.h"

/**
 * fctexit - Handle shell exit command.
 * @in: Pointer to the shell information struct.
 *
 * Return: Signal to terminate shell or error code.
 */
int fctexit(infocmd *in)
{
	int ext;

	if (in->argv[1])
	{
		ext = erconv(in->argv[1]);
		if (ext == -1)
		{
			in->status = 2;
			erprint(in, "Illegal number: ");
			erputs(in->argv[1]);
			eputchar('\n');
			return (1);
		}
		in->err_num = erconv(in->argv[1]);
		return (-2);
	}
	in->err_num = -1;
	return (-2);
}

/**
 * fctcurrent - Handle shell 'cd' command.
 * @in: Pointer to the shell information struct.
 *
 * Return: 0 on success, 1 on informational output, -1 on failure.
 */
int fctcurrent(infocmd *in)
{
	char *str, *d, buffer[1024];
	int ret;

	str = getcwd(buffer, 1024);
	if (!str)
		strputs("TODO: >>getcwd failure emsg here<<\n");
	if (!in->argv[1])
	{
		d = getVarEnv(in, "HOME=");
		if (!d)
			ret = chdir((d = getVarEnv(in, "PWD=")) ? d : "/");
		else
			ret = chdir(d);
	}
	else if (strcomparison(in->argv[1], "-") == 0)
	{
		if (!getVarEnv(in, "OLDPWD="))
		{
			strputs(str);
			_putchar('\n');
			return (1);
		}
		strputs(getVarEnv(in, "OLDPWD=")), _putchar('\n');
		ret = chdir((d = getVarEnv(in, "OLDPWD=")) ? d : "/");
	}
	else
		ret = chdir(in->argv[1]);
	if (ret == -1)
	{
		erprint(in, "can't cd to ");
		erputs(in->argv[1]), eputchar('\n');
	}
	else
	{
		setEnv(in, "OLDPWD", getVarEnv(in, "PWD="));
		setEnv(in, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * fcthelp - Handle shell 'help' command.
 * @in: Pointer to the shell information struct.
 *
 * Return: Always returns 0.
 */
int fcthelp(infocmd *in)
{
	char **ar;

	ar = in->argv;
	strputs("help call works. Function not yet implemented \n");
	if (0)
		strputs(*ar);
	return (0);
}
