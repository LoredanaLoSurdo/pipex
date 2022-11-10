/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llo-surd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:56:32 by llo-surd          #+#    #+#             */
/*   Updated: 2022/11/10 14:44:25 by llo-surd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(void)
{
	perror("\033[32mError");
	exit(EXIT_FAILURE);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*part;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part, cmd);
		free(part);
		if (access(path, X_OK) == 0)
			return (path);
		free (path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;

	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
		{
			free(cmd[i]);
		}
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_putstr_fd("\033[31mError: command not found: \e[0m", 2);
		ft_putstr_fd(cmd[0], 2);
		exit(127);
	}
	free(cmd);
}
