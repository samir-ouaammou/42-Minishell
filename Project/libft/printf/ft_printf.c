/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:36:35 by aahaded           #+#    #+#             */
/*   Updated: 2024/11/10 13:52:25 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(const char c, va_list args)
{
	int	print_count;

	print_count = 0;
	if (c == 'c')
		print_count += ft_putchar(va_arg(args, int));
	else if (c == 's')
		print_count += ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		print_count += ft_print_ptr(va_arg(args, unsigned long));
	else if (c == 'd' || c == 'i')
		print_count += ft_print_num(va_arg(args, int));
	else if (c == 'u')
		print_count += ft_print_unsigned(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		print_count += ft_print_hex(c, va_arg(args, unsigned int));
	else if (c == '%')
		print_count += ft_putchar('%');
	return (print_count);
}

int	ft_lkmala_2(const char *str, va_list args, int i, int print_count)
{
	int	ret;

	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			ret = ft_format(str[i], args);
			if (ret == -1)
				return (-1);
			print_count += ret;
		}
		else
		{
			ret = write(2, &str[i], 1);
			if (ret == -1)
				return (-1);
			print_count++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (print_count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		print_count;
	va_list	args;

	i = 0;
	print_count = 0;
	va_start(args, str);
	if (!str)
		return (-1);
	print_count += ft_lkmala_2(str, args, i, print_count);
	va_end(args);
	return (print_count);
}
