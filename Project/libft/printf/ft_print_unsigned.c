/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:30:35 by aahaded           #+#    #+#             */
/*   Updated: 2024/11/07 12:44:39 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_unsigned(unsigned int nb)
{
	int	print_count;

	print_count = 0;
	if (nb > 9)
		print_count += ft_print_unsigned(nb / 10);
	print_count += ft_putchar(((nb % 10) + '0'));
	return (print_count);
}
