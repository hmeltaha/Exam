/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf_fixed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:03:11 by abeer             #+#    #+#             */
/*   Updated: 2025/06/29 18:45:27 by hmeltaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

// Skip over whitespace in the file (spaces, tabs, newlines)
int match_space(FILE *f)
{
	int c;

	c = fgetc(f); // read one character from the file
	while (isspace(c) && c != EOF) // keep reading while it's whitespace
		c = fgetc(f);
	if (c == EOF) // if end of file, return EOF
		return (EOF);
	ungetc(c, f); // put back the non-whitespace character
	return (1);   // success
}

// Try to match a specific character `c` from file
int match_char(FILE *f, char c)
{
	int ch;

	ch = fgetc(f); // read one character
	if (ch == EOF) // if end of file, return EOF
		return (EOF);
	if (ch == c)   // if it matches the expected char
		return (1); // success
	ungetc(ch, f); // otherwise, put it back
	return (0);    // not matched
}

// This function reads one character from input and stores it in a variable provided by the user
int scan_char(FILE *f, va_list ap)
{
	int c;        // This will temporarily hold the character we read
	char *ch;     // This will point to the variable where we need to store the character

	c = fgetc(f); // Read one character from the input (like stdin)
	if (c == EOF) // If there's nothing to read (end of input), return an error
		return (EOF);

	// Get the next argument from the variable argument list.
	// It should be a pointer to a char (like &x if user called ft_scanf("%c", &x))
	ch = va_arg(ap, char *);

	// Store the character we just read into the user's variable
	*ch = c;
	return (1);
}


// Read and parse an integer from the file, and store it in the given pointer
int scan_int(FILE *f, va_list ap)
{
	int c;
	int sign;
	int *i;
	int num;

	num = 0; // initial value of number
	i = va_arg(ap, int *); // get pointer to int from argument list
	c = fgetc(f); // read first character
	sign = 1;     // assume positive

	// Handle optional '+' or '-' sign
	if (c == '+' || c == '-')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f); // move to next character
	}

	if (!isdigit(c)) // if not a digit after sign, invalid input
		return (0);

	// Read digits and build the number
	while (isdigit(c) && c != EOF)
	{
		num = num * 10 + c - '0'; // build number from digits
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f); // put back non-digit character
	*i = sign * num; // store the final signed number
	return (1); // success
}

// Read a string (non-whitespace characters) and store it in buffer
int scan_string(FILE *f, va_list ap)
{
	char *str;
	int s;

	str = va_arg(ap, char *); // get char* to store the result
	s = fgetc(f); // read first character

	while (!isspace(s) && s != EOF) // keep reading until whitespace or EOF
	{
		*str = s; // store character in string
		s = fgetc(f); // get next character
		str++; // move pointer forward
	}
	if (s != EOF)
		ungetc(s, f); // put back the whitespace
	*str = '\0'; // null-terminate the string
	return (1); // success
}



// Handle format specifiers like %d, %c, %s
int match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format) // check current format character
	{
		case 'c': // char
			return scan_char(f, ap);
		case 'd': // integer
			match_space(f); // skip whitespace before reading
			return scan_int(f, ap);
		case 's': // string
			match_space(f); // skip whitespace before reading
			return scan_string(f, ap);
		case EOF: // end of format string
			return -1;
		default: // unknown specifier
			return -1;
	}
}

// Main parsing logic, processes the format string and reads from file
int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0; // number of successful conversions

	int c = fgetc(f); // check if there's anything in the input
	if (c == EOF)
		return EOF;
	ungetc(c, f); // put it back to process normally

	while (*format) // loop through format string
	{
		if (*format == '%') // if conversion specifier
		{
			format++; // move past '%'
			if (match_conv(f, &format, ap) != 1) // handle conversion
				break; // stop on failure
			else
				nconv++; // count successful conversion
		}
		else if (isspace(*format)) // if format has space
		{
			if (match_space(f) == -1) // skip matching input whitespace
				break;
		}
		else if (match_char(f, *format) != 1) // match literal characters
			break;
		format++; // move to next character
	}
	if (ferror(f)) // check for file errors
		return EOF;
	return nconv; // return number of successful conversions
}

// Wrapper around ft_vfscanf that handles variable arguments
int ft_scanf(const char *format, ...)
{
	va_list ap; // argument list
	int ret;

	va_start(ap, format); // start reading arguments after format
	ret = ft_vfscanf(stdin, format, ap); // parse from standard input
	va_end(ap); // clean up
	return (ret); // return number of successful conversions
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
