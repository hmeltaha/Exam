#include <stdlib.h>
int ft_strlen(char *s)
{
	int		i = 0;
	while(s[i])
		i++;
	return(i);
}
char *strchr(const char *s, int c)
{
	int		i = 0;
	while(s[i] && s[i] != c)
	{
		if(s[i] == c)
			return(&s[i]);
		i++;
	}
	return(0);
}

void sort(char *s, int len)
{
	int i = 0;
	while(i < len -1)
	{
		int j = i + 1;
		while(j < len)
		{
			if(s[i] > s[j])
			{
				char temp = s[i];
				s[i] = s[j];
				s[j] = temp;
			}
			j++;
		}
		i++;
	}
}
void perm(char *argv, char *result, int pos, int len)
{
	int i = 0;
	if(pos == len)
	{
			puts(result);
			return ;
	}
	while(len > i)
	{
		if(!strchr(result, argv[i]))
		{
			result[pos] = argv[i];
			perm(argv, result, pos + 1, len);
			result[pos] = '\0';
		}
		i++;
	}

}
int main(int argc, char **argv)
{
	if(argc != 2)
		return(1);
	int len = ft_strlen(argv[1]);
	char *result = calloc(len + 1, 1);
	sort(argv[1], len);
	perm(argv[1], result, 0, len);
	return(0);
}