/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:21:39 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 12:39:07 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_putchar(int c);
int	ft_putstr(char *s);
int	ft_print_num(int nb);
int	ft_printf(const char *str, ...);
int	ft_print_ptr(unsigned long ptr);
int	ft_print_unsigned(unsigned int nb);
int	ft_print_hex(char c, unsigned int args);

#endif
