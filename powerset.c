#include <stdio.h>  // For printf function
#include <stdlib.h> // For atoi function to convert strings to integers
​
​
​
void check_sum(int *temp, int max_size, char **av, int target)
{
​
	int sum = 0;
​
	for (int i = 0; i < max_size; i++)
	{
		if (temp[i] == 1)
			sum += atoi(av[i]);
	}
​
	if (sum != target)
		return ;
​
​
	for (int i = 0; i < max_size; i++)
	{
		if (temp[i] == 1)
			printf("%d ", atoi(av[i]));
	}
	printf("\n");
}
​
​
​
int main(int ac, char **av)
{
	av++;
	int max_size = ac - 2;
	int target = atoi(av[0]);
	av++;
​
	int total_posi = 1 << max_size; // 2^7
​
​
	int temp[max_size];
	
	for (int i = 0; i < total_posi; i++)
	{
		for (int j = 0; j < max_size; j++)
		{
			if (i & (1 << j))
				temp[j] = 1;
			else
				temp[j] = 0;
		}
		check_sum(temp, max_size, av, target);
	}
}