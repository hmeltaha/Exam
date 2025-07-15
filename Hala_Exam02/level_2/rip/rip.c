#include <unistd.h>
#include <stdio.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return i;
}

int is_valid(char *str, int len)
{
	int i = 0;
	int balance = 0;

	while (i < len)
	{
		if (str[i] == '(')
			balance++;
		if (str[i] == ')')
			balance--;
		if (balance < 0)
			return 0;
		i++;
	}
	return (balance == 0);
}
//What’s the smallest number of parentheses we must remove to make the string valid
void find_min(char *str, int len, int *min, int i, int removed)
{
	char tmp;

	if (is_valid(str, len))
	{
		if (*min == -1 || removed < *min)
			*min = removed;
	}
	while (i < len)
	{
		tmp = str[i];
		str[i] = ' ';
		find_min(str, len, min, i + 1, removed + 1);
		str[i] = tmp;
		i++;
	}
}

void print_valid(char *str, int len, int min, int i, int removed)
{
	char tmp;

	if (removed > min)
		return ;
	if (is_valid(str, len) && removed == min)
	{
		puts(str);
		return ;
	}
	while (i < len)
	{
		tmp = str[i];
		str[i] = ' ';
		print_valid(str, len, min, i + 1, removed + 1);
		str[i] = tmp;
		i++;
	}
}


int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);

	int min = -1;
	int len = ft_strlen(argv[1]);

	find_min(argv[1], len, &min, 0, 0);
	print_valid(argv[1], len, min, 0, 0);

	return (0);
}
