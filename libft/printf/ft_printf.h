/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:21:39 by aahaded           #+#    #+#             */
/*   Updated: 2024/11/10 13:35:33 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_print_ptr(unsigned long ptr);
int	ft_print_num(int nb);
int	ft_print_hex(char c, unsigned int args);
int	ft_print_unsigned(unsigned int nb);
int	ft_putchar(int c);
int	ft_putstr(char *s);

#endif
