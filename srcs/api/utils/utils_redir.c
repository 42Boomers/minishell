#include "minishell.h"

int	ft_pres_red(char **args)
{
	int	i;
	int ret;

	ret = 0;
	i = -1;
	while (args[++i])
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0)
			ret = ret | 2;
		if (ft_strcmp(args[i], "<<") == 0 || ft_strcmp(args[i], "<") == 0)
			ret = ret | 4;
		if (ft_strcmp(args[i], "|") == 0)
			return (ret);
	}
	return (ret);
}

int	ft_check_bad(int pos, char **args)
{
	char *ret;

	if ((pos > 0 && !args[pos]) || (pos < 0 && !args[-pos]))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		ft_putstr_fd("`newline\'\n", 2);
		return (-1);
	}
	if (pos > 0 && (ft_strcmp(args[pos], "<") == 0 || \
	ft_strcmp(args[pos], "<<") == 0 || ft_strcmp(args[pos], ">") == 0 \
	|| ft_strcmp(args[pos], ">>") == 0 || ft_strcmp(args[pos], "|") == 0))
	{
		ret = \
		ft_strjoin_plus("minishell: syntax error near unexpected token `", \
		args[pos], "\'\n");
		ft_putstr_fd(ret, 2);
		free(ret);
		return (-1);
	}
	if (pos < 0 && (ft_strcmp(args[-pos], "<") == 0 || \
	ft_strcmp(args[-pos], "<<") == 0 || ft_strcmp(args[-pos], ">") == 0 \
	|| ft_strcmp(args[-pos], ">>") == 0 || ft_strcmp(args[-pos], "|") == 0))
	{
		ret = \
		ft_strjoin_plus("minishell: syntax error near unexpected token `", \
		args[-pos], "\'\n");
		ft_putstr_fd(ret, 2);
		free(ret);
		return (-1);
	}
	return (0);
}

int	ft_redir_error(int ret, char **args)
{
	char *strer;

	if (ret > 0)
	{
		strer = ft_strjoin("minishell: ", args[ret]);
		perror(strer);
		free(strer);
	}
	else if (ret == -1)
		perror("minishell");
	return (-1);
}

int	ft_red_pip_cmd(char **command, char **args)
{
	int ret;
	int redir[2];
	char **new;
	char **temp;

	ret = 1;
	if (ft_isequals(*command, "|") || ft_isequals(*command, "<") || \
	ft_isequals(*command, "<<") || ft_isequals(*command, ">") || \
	ft_isequals(*command, ">>"))
	{
		if (ft_isequals(*command, "|"))
		{
			write(2, "minishell: syntax error near unexpected token `|'\n", 50);
			return (-1);
		}
		command[1] = NULL;
		new = ft_join_chars(command, args);
		ret = ms_red_in_out(new, redir);
		free(new);
	}
	return (ret);
}
