#include "../minishell.h"

void	get_old_pwd(void)
{
	t_envp	*tmp_env;
	char	*tmp;

	tmp_env = env;
	tmp = my_get_env(env, "PWD");
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, "OLDPWD"))
		{
			if (tmp_env && tmp_env->value)
				free(tmp_env->value);
			tmp_env->value = tmp;
			break ;
		}
		tmp_env = tmp_env->next;
	}
}

void	set_pwd(char *cwd)
{
	t_envp	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, "PWD"))
		{
			if (tmp_env && tmp_env->value && cwd)
			{
				free(tmp_env->value);
				tmp_env->value = ft_strdup(cwd);
			}
			break ;
		}
		tmp_env = tmp_env->next;
	}
}

void	cd_home(t_data *data, char *msg)
{
	char	*tmp;

	(void) data;
	tmp = my_get_env(env, "HOME");
	if (!tmp)
	{
		msg = my_strjoin(msg, "HOME not set\n");
		ft_putstr_fd(msg, 2);
	}
	else if (chdir(tmp) == -1)
	{
		perror(my_strjoin(msg, ": "));
		env->exit_status = 1;
		free(tmp);
		return ;
	}
	get_old_pwd();
	env->exit_status = 0;
	free(tmp);
	return ;
}

void	cd_old_pwd(t_data *data, char *msg)
{
	char	*tmp;

	if (!data->args[1][1])
	{
		tmp = my_get_env(env, "OLDPWD");
		if (!tmp)
		{
			msg = my_strjoin(msg, "OLDPWD not set\n");
			ft_putstr_fd(msg, 2);
			env->exit_status = 1;
			return ;
		}
		else if (chdir(tmp) == -1)
		{
			perror(my_strjoin(msg, ": "));
			env->exit_status = 1;
			free(tmp);
			return ;
		}
		free(tmp);
	}
	else
	{
		ft_putstr_fd("bash: cd: --: invalid option\ncd: usage: \
		cd [-L|-P] [dir]\n", 2);
		env->exit_status = 1;
		return ;
	}
	tmp = my_get_env(env, "OLDPWD");
	ft_putstr_fd(tmp, 1);
	ft_putstr_fd("\n", 1);
	get_old_pwd();
	free(tmp);
}

void	ft_cd(t_data *data)
{
	char	buff[PATH_MAX];
	char	*msg;
	char	*cwd;

	cwd = getcwd(buff, PATH_MAX);
	msg = my_strjoin("minishell: cd: ", data->args[1]);
	if ((!data || !data->args || !cwd) && ft_strcmp(data->args[1], ".."))
	{
		if (!cwd)
			perror("getcwd : ");
		return ;
	}
	if (data->args[1])
	{
		if (data->args[2])
			(ft_putendl_fd("minishell: cd: too many arguments", 2), env->exit_status = 1);
		
		return ;
	}
	else if (data->args[1] && !data->args[1][0])
	{
		env->exit_status = 0;
		return ;
	}
	if (!data->args[1] || !ft_strcmp(data->args[1], "--"))
		cd_home(data, msg);
	else if (data->args[1][0] == '-')
		cd_old_pwd(data, msg);
	else
	{
		if (chdir(data->args[1]) == -1)
		{
			if (!ft_strcmp(data->args[1], ".."))
				ft_putendl_fd("minishell : cd: No such file or directory", 2);
			else
				perror(msg);
			env->exit_status = 1;
			return ;
		}
		get_old_pwd();
	}
	set_pwd(getcwd(buff, PATH_MAX));
	env->exit_status = 0;
}
