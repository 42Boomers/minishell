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

static int	ms_builtin(t_master *master, char *comd, char **args)
{
	t_ms_command	*cmd;
	t_ms_input		*input;
	char **temp;
	char *tmp;
	int i;

	tmp = NULL;
	temp = ft_join_chars(args, &tmp);
	ft_pipe_check(temp);
	i = 0;
	while (temp[i])
		i++;
	cmd = ft_lstget(master->cmds, comd, ms_cmd_get_key);
	input = ms_cmd_input(cmd, temp, i);
	// ms_set_status didnt work cause it is override by fork result
	// We won't need to use fork at this case.
	ms_set_status(master, ms_cmd_execute(input));
	ms_garbage_free(&input->garbage);
	free(temp);
	free(input);
	return (0);
}

int	ft_red_pip_cmd(char **command, char **args, t_master *master)
{
	int ret;
	int redir[2];
	char **new;

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
	else if (ft_isequals(*command, "cd") || ft_isequals(*command, "export") || \
	ft_isequals(*command, "unset"))
		return (ms_builtin(master, *command, args));
	return (ret);
}
