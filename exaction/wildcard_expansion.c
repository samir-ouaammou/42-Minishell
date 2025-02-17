/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:34:38 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/17 08:34:40 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_for_wildcards(char *pattern)
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

static int	count_wildcards(char *str)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (1);
	while ((entry = readdir(dir)) != NULL)
	{
		if (is_wildcard_match(str, entry->d_name))
			count++;
	}
	closedir(dir);
	return (count);
}

static int	expand_wildcards(char *pattern, t_data *data, int *index)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		return (1);
	while ((entry = readdir(dir)) != NULL)
	{
		if (is_wildcard_match(pattern, entry->d_name))
		{
			data->matches[*index] = ft_strdup(entry->d_name);
			(*index)++;
		}
	}
	closedir(dir);
	return (0);
}

static int	count_total_matches(char **args)
{
	int(i), (count);

	i = 0;
	count = 0;
	while (args[i])
	{
		if (check_for_wildcards(args[i]) == 0)
			count += count_wildcards(args[i]);
		i++;
	}
	return (count);
}

void free_matches(char **matches)
{
    if (matches)
    {
        for (int i = 0; matches[i]; i++)
            free(matches[i]);
        free(matches);
    }
}
// int	handle_wildcards(char **args, t_data *data)
// {
// 	int(i), (count), (match_index);
// 	i = 0;
// 	match_index = 0;
// 	count = count_total_matches(args);
// 	data->matches = malloc(sizeof(char *) * (count + 1));
// 	if (!data->matches)
// 		return (-1);
// 	while (args[i])
// 	{
// 		if (check_for_wildcards(args[i]) == 0)
// 			expand_wildcards(args[i], data, &match_index);
// 		else
// 		{
// 			data->matches[match_index] = ft_strdup(args[i]);
// 			match_index++;
// 		}
// 		i++;
// 	}
// 	data->matches[match_index] = NULL;
// 	return (0);
// }

int handle_wildcards(char **args, t_data *data)
{
    int i, count, match_index;

    i = 0;
    match_index = 0;
    count = count_total_matches(args);

    // Allocate memory for matches
    data->matches = malloc(sizeof(char *) * (count + 1));
    if (!data->matches)
        return (-1); // Return error if malloc fails

    // Initialize all pointers to NULL
    for (i = 0; i <= count; i++)
        data->matches[i] = NULL;

    i = 0;
    while (args[i])
    {
        if (check_for_wildcards(args[i]) == 0)
        {
            if (expand_wildcards(args[i], data, &match_index) != 0)
            {
                // Handle error in expand_wildcards
                free_matches(data->matches); // Free previously allocated memory
                return (-1);
            }
        }
        else
        {
            data->matches[match_index] = ft_strdup(args[i]);
            if (!data->matches[match_index])
            {
                // Handle error in ft_strdup
                free_matches(data->matches); // Free previously allocated memory
                return (-1);
            }
            match_index++;
        }
        i++;
    }

    // Ensure the array is null-terminated
    data->matches[match_index] = NULL;

    return (0);
}

// Helper function to free all allocated matches