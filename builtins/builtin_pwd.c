/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:13:03 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/02 16:13:23 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_pwd(t_data *data)
{
	if (data->save_pwd)
	{
		printf("%s\n", data->save_pwd);
		data->exit_status = 0;
		return (0);
	}
	data->exit_status = 1;
	return (1);
}

