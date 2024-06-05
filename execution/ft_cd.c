#include "../minishell.h"

void	get_old_pwd(char *cwd)
{
	t_envp	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, "OLDPWD"))
		{
			if (tmp_env && tmp_env->value)
				free (tmp_env->value);
			tmp_env->value = ft_strdup(cwd);
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
			if (tmp_env && tmp_env->value)
				free (tmp_env->value);
			tmp_env->value = ft_strdup(cwd);
			break ;
		}
		tmp_env = tmp_env->next; 
	}
}

void	cd_home(t_data *data, char *msg, char *cwd)
{
	char	*tmp;

	(void) data;
	tmp = my_get_env(env, "HOME");
	if (!tmp)
	    msg = my_strjoin(msg, "HOME not set\n");
	if (!tmp)
		ft_putstr_fd(msg, 2);
	else if (chdir(tmp) == -1)
	{
        perror(my_strjoin(msg, ": "));
		return ;
	}
	get_old_pwd(cwd);
	return ;
}

void	cd_old_pwd(t_data *data, char *msg, char *cwd)
{
	char (*tmp);
	if ((data->args[1][1] == '-' && !data->args[1][2]))
	{
		cd_home(data, msg, cwd);
		return ;
	}
	else if (!data->args[1][1])
	{
		tmp = my_get_env(env, "OLDPWD");
		if (!tmp)
		{
			msg = my_strjoin(msg, "OLDPWD not set\n");
			ft_putstr_fd(msg, 2);
		}   	
		else if (chdir(tmp) == -1)
		{
			perror(my_strjoin(msg, ": "));
			return ;
		}
	}
	else
	{
		ft_putstr_fd("bash: cd: --: invalid option\ncd: usage: cd [-L|-P] [dir]\n", 2);
		return ;
	}
	ft_putstr_fd(my_get_env(env, "OLDPWD"), 1);
	ft_putstr_fd("\n", 1);
	get_old_pwd(cwd);
}

void	ft_cd(t_data *data)
{
	char buff[PATH_MAX];

    char (*msg), (*cwd);
    cwd = getcwd(buff, PATH_MAX);
	if (!data || !data->args || !cwd)
	{
		if (!cwd)
			perror("getcwd : ");
		return ;
	}
    msg = my_strjoin("minishell: cd: ", data->args[1]);
    if (!data->args[1])
        cd_home(data, msg, cwd);
	else if (data->args[1] && !data->args[1][0])
        return ;
    else if (data->args[1][0] == '-')
		cd_old_pwd(data, msg, cwd);
    else
	{
		if (chdir(data->args[1]) == -1)
		{
        	perror(my_strjoin(msg, ": "));
			return ;
		}
		get_old_pwd(cwd);
	}
	set_pwd(getcwd(buff, PATH_MAX));
}