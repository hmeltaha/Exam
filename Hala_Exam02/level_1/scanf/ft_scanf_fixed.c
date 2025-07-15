/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeer <abeer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:03:11 by abeer             #+#    #+#             */
/*   Updated: 2025/05/25 23:47:55 by abeer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int	c;
	
	c = fgetc(f);
	while (isspace(c) && c != EOF)
		c = fgetc(f);
	if (c == EOF)
		return (EOF);
	ungetc(c, f);
    return (1);
}

int match_char(FILE *f, char c)
{
    int	ch;

	ch = fgetc(f);
	if (ch == EOF)
		return (EOF);
	if (ch == c)
		return (1);
	ungetc(ch, f);
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
	int		c;
	char	*ch;
	
	c = fgetc(f);
	if (c == EOF)
		return (EOF);
	ch = va_arg(ap, char *);
	*ch = c;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
   	int	c;
	int	sign;
	int	*i;
	int	num;

	num = 0;
	i = va_arg(ap, int *);
	c = fgetc(f);
	sign = 1;
	if ( c == '+' || c == '-')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f);
	}
	if (!isdigit(c))
		return (0);
	while (isdigit(c) && c != EOF)
	{
		num = num * 10 + c - 48;
		c = fgetc(f);
	}
	if (c != EOF)
        ungetc(c, f);
	*i = sign * num;
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
	char	*str;
	int		s;

	str = va_arg(ap, char *);
	s = fgetc(f);
	while (!isspace(s) && s != EOF) 
	{
		*str = s;
		s = fgetc(f);
		str++;
	}
	if (s != EOF)
		ungetc(s, f);
	*str = '\0';
    return (1);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list	ap;
	int 	ret;
	
	va_start(ap, format);
	ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (ret);
}

int	main(void)
{
	// char	i[200];
	int	i;
	
	// scanf("%d", &i);
	ft_scanf("%d", &i);
	printf("%d\n", i);
	return (0);
}
