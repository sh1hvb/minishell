#include "../../minishell.h"
 int	ft_lstsize_file(t_files *lst)
{
	int	count;

	if (!lst)
		return (0);
	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_files	*ft_lstlast_file(t_files *lst)
{
	int	last;

	last = ft_lstsize_file(lst);
	while (last-- > 1)
		lst = lst->next;
	return (lst);
}
char	*get_path(char *cmd)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
    t_envp *tmp = env;

	if (!cmd)
		return NULL;
	if (!access(cmd, X_OK) || cmd[0] == '/')
		return (ft_strdup(cmd));
	char *value = my_get_env(tmp, "PATH");
	allpath = ft_split(value, ':');
	if (!allpath)
		return (NULL);
	i = -1;
	while (allpath[++i] )
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);

		if (access(exec, X_OK) == 0)
        {
			ft_freed(allpath);
			free(value);
			return (exec);
        }
		free(exec);
	}
	if ((access(cmd , F_OK) == 0 && access(cmd , X_OK) != 0) && (cmd[0] == '/' || cmd[ft_strlen(cmd) - 1] == '/' ||(cmd[0] == '.' && cmd[1] == '/')))
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit (126);
	}
	free(value);
	ft_freed(allpath);
	return (NULL);
}