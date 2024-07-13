/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:40:06 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/11 16:35:10 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		cmd_number(t_cmd_limits *cmd)// number of commands
{
	int i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

char	**set_cmd_arr(t_cmd_limits *cmd)// command array aka command and its options
{
	char	**cmd_array;
	int		len;
	t_item	*tmp;
	int		i;

	i = 0;
	len = 0;
	tmp = cmd->start;
	while (tmp != cmd->end->next)// must check last limit aka end not end->next
	{
		if (tmp->type == WORD)
			len++;
		tmp = tmp->next;
	}
	cmd_array = malloc(sizeof(char *) * (len + 1));
	if (!cmd_array)
		return (NULL);
	tmp = cmd->start;
	while (tmp != cmd->end->next)// same as above
	{
		if (tmp->type == WORD)
			cmd_array[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	cmd_array[i] = NULL;
	return (cmd_array);
}

int		check_redir(t_cmd_limits *cmd,  int	type_1, int	type_2) // check redirections numbers of a type
{
	t_item	*tmp;
	int		i;

	i = 0;
	tmp = cmd->start;
	while(tmp != cmd->end->next) // must check last limit aka end not end->next
	{
		if (tmp->type == type_1 || tmp->type == type_2)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_redir	*set_redir(t_cmd_limits *cmd, int type1, int type2, int num)
{
	t_item	*tmp;
	t_redir *redir;
	int	i;

	i = 0;
	tmp = cmd->start;
	redir = malloc (sizeof(redir) * (num + 1));
	if (!redir)
		return (NULL);
	while (tmp != cmd->end->next)
	{
		if (tmp->type == type1)
		{
			redir[i].type = 1;
			redir[i].path_or_limiter = ft_strdup(tmp->content);
		}
		else if (tmp->type == type2)
		{
			redir[i].type = 2;
			redir[i].path_or_limiter = ft_strdup(tmp->content);
		}
		tmp = tmp->next;
		i++;
	}
	// redir[i] = NULL;
	return (redir);
}

void	set_pipe_flag(t_simple_cmd *head, int cmd_nbr)
{
	if (cmd_nbr == 1)
		return;
	while (head)
	{
		if (head->i == 0)
			head->pipe_flag = 2; // after
		else if (head->i == cmd_nbr - 1)
			head->pipe_flag = 1; // before
		else
			head->pipe_flag = 3; // before and after
		head = head->next;
	}
}
