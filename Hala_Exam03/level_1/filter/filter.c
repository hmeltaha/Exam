#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif


void ft_filter (char *str, char *word)
{
	int i = 0;
	int k = 0;
	int word_len = strlen(word);

	while (str[i])
	{
		if (str[i] == word[0])
		{
			k = 0;
			while (str[i + k] == word[k])
				k++;
			if (k == word_len)
			{
				while (k)
				{
					write(1,"*",1);
					k--;
				}
				i += word_len;
				continue ;
			}
		}
		write(1,&str[i],1);
		i++;
	}
}

int main(int argc, char **argv)
{
	char *str = NULL;
	char buf[BUFFER_SIZE];
	char *temp = NULL;
	int b_read = 0;
	int total = 0;
	if (argc != 2)
		return (1);

	while ((b_read = read(0,buf,BUFFER_SIZE)) > 0)
	{
		temp = realloc(str,total + b_read + 1);
		if (!temp)
		{
			perror("malloc");
			return (1);
		}
		str = temp;
		memmove(str + total, buf, b_read);
		total += b_read;
		str[total] = 0;
	}
	if (b_read == -1)
	{
		perror("read");
		return (1);
	}
	ft_filter(str,argv[1]);
	return (0);
}