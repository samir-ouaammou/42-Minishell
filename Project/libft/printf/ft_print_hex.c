/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:06:11 by aahaded           #+#    #+#             */
/*   Updated: 2024/11/10 13:40:40 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(char c, unsigned int va)
{
	char	*str_hex;
	int		print_count;

	str_hex = "0123456789abcdef";
	print_count = 0;
	if (c == 'X')
		str_hex = "0123456789ABCDEF";
	if (va >= 16)
		print_count += ft_print_hex(c, (va / 16));
	print_count += ft_putchar(str_hex[va % 16]);
	return (print_count);
}
