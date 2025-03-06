/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:13:03 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 12:19:54 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_pwd(t_exaction *data)
{
	(void)data;
	if (data_struc()->save_pwd)
	{
		printf("%s\n", data_struc()->save_pwd);
		data_struc()->exit_status = 0;
		return (0);
	}
	data_struc()->exit_status = 1;
	return (1);
}

