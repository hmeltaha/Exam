#include <stdio.h>
#include <stdlib.h>

void	find_subsets(int *nums, int size, int index, int *subset, int subset_size, int target)
{
	int	sum;
	int	k;

	// Base case: when we have checked all numbers
	if (index == size)
	{
		// Calculate sum of current subset
		sum = 0;
		k = 0;
		while (k < subset_size)
		{
			sum += subset[k];
			k++;
		}
		// If sum matches target, print it
		if (sum == target)
		{
			k = 0;
			while (k < subset_size)
			{
				if ((k + 1) == subset_size)
				{
					printf("%d", subset[k]);
					break ;
				}
				printf("%d ", subset[k]);
				k++;
			}
			printf("\n");
		}
		return ;
	}
	subset[subset_size] = nums[index];
	find_subsets(nums, size, index + 1, subset, subset_size + 1, target);// ✅ Choice 1: Include nums[index]
	find_subsets(nums, size, index + 1, subset, subset_size, target);// ✅ Choice 2: Skip nums[index]    
}

int	main(int argc, char **argv)
{
	int	target;
	int	size;
	int	nums[size];
	int	i;

	if (argc < 3)
		return (1);
	target = atoi(argv[1]);
	size = argc - 2;
	int subset[size]; // temporary storage for current subset
	// start storing the num
	i = 0;
	while (i < size)
	{
		nums[i] = atoi(argv[i + 2]);
		i++;
	}
	find_subsets(nums, size, 0, subset, 0, target);
	return (0);
}
