/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:19:39 by aahaded           #+#    #+#             */
/*   Updated: 2024/11/07 09:41:11 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_lkmala_ta3ptr(unsigned long va)
{
	int		print_count;
	char	*str_hex;

	print_count = 0;
	str_hex = "0123456789abcdef";
	if (va >= 16)
		print_count += ft_lkmala_ta3ptr(va / 16);
	print_count += ft_putchar(str_hex[va % 16]);
	return (print_count);
}

int	ft_print_ptr(unsigned long ptr)
{
	int	print_count;

	print_count = 0;
	if (!ptr)
		return (write(2, "0x0", 3));
	print_count += write(2, "0x", 2);
	print_count += ft_lkmala_ta3ptr(ptr);
	return (print_count);
}
