/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:34:38 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 13:53:40 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int check_for_wildcards(char *pattern)
{
	int(i), (count);
	i = 0;
	count = 0;
	if (!pattern)
		return (0);
	while (pattern[i])
	{
		if (pattern[i] == '*')
			count++;
		i++;
	}
	if (count == 0)
		return (1);
	return (0);
}

static int count_wildcards(char *str)
{
	DIR *dir;
	struct dirent *entry;
	int count;
	int check_count;

	count = 0;
	check_count = 0;
	dir = opendir(".");
	if (!dir)
		return (1);
	while ((entry = readdir(dir)) != NULL)
	{
		if (is_wildcard_match(str, entry->d_name))
		{
			check_count += 1;
			count++;
		}
	}
	if (check_count == 0)
		count += 1;
	closedir(dir);
	return (count);
}

static int expand_wildcards(char *pattern, t_exaction *data, int *index)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir(".");
	if (!dir)
		return (1);
	while ((entry = readdir(dir)) != NULL)
	{
		if (is_wildcard_match(pattern, entry->d_name))
		{
			data->count_ok++;
			data->matches[*index] = ft_strdup(entry->d_name);
			(*index)++;
		}
	}
	closedir(dir);
	return (0);
}

static int count_total_matches(char **args)
{
	int(i), (count);
	i = 0;
	count = 0;
	while (args[i])
	{
		if (check_for_wildcards(args[i]) == 0)
			count += count_wildcards(args[i]);
		else
			count += 1;
		i++;
	}
	return (count);
}

int handle_wildcards(char **args, t_exaction *data)
{
	int(i), (count), (match_index);
	i = 0;
	match_index = 0;

	count = count_total_matches(args);
	data->matches = malloc(sizeof(char *) * (count + 1));
	if (!data->matches)
		return (-1);
	while (args[i])
	{
		data->count_ok = 0;
		if (check_for_wildcards(args[i]) == 0)
			expand_wildcards(args[i], data, &match_index);
		if (data->count_ok <= 0)
		{
			data->matches[match_index] = ft_strdup(args[i]);
			match_index++;
		}
		i++;
	}
	data->matches[match_index] = NULL;
	return (0);
}
