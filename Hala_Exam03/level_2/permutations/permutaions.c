/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutaions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeer <abeer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 01:31:11 by abeer             #+#    #+#             */
/*   Updated: 2025/05/04 02:16:21 by abeer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void	swap(char *a, char *b)
{
	char temp;

	temp = *a;
	*a = *b;
	*b = temp;	
}

void	permute(char *s, int start, int end)
{
	int	i;

	i = start;
	
	if (start == end)
	{
		printf("%s\n", s);
		return ;
	}
	while(i < end)
	{
		swap(&s[start], &s[i]);
		permute(s, start + 1, end);
		swap(&s[start], &s[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*s;
	
	if (argc != 2)
		return (1);
	s = strdup(argv[1]);
	permute(s, 0, strlen(s));
	return (0);
}