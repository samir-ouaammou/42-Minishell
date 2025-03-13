/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:31:17 by aahaded           #+#    #+#             */
/*   Updated: 2024/11/07 10:19:21 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_num(int nb)
{
	int	print_count;

	print_count = 0;
	if (nb == -2147483648)
		return (write(2, "-2147483648", 11));
	if (nb > 9)
		print_count += ft_print_num((nb / 10));
	if (nb < 0)
	{
		nb = -nb;
		print_count += ft_putchar('-');
		print_count += ft_print_num(nb);
	}
	else
		print_count += ft_putchar(nb % 10 + '0');
	return (print_count);
}
