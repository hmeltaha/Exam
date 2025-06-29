#include <stdio.h>
#include <stdlib.h>

void	check_print(int target, char **argv, int *subset_indices,
		int subset_size)
{
	int	sum;
	int	i;

	sum = 0;
	i = 0;
	// Calculate the sum of the subset
	while (i < subset_size)
	{
		sum += atoi(argv[subset_indices[i]]);
		i++;
	}
	// Print the subset if the sum matches the target
	if (sum == target)
	{
		i = 0;
		while (i < subset_size)
		{
			printf("%s", argv[subset_indices[i]]);
			if (i != subset_size - 1)
				printf(" ");
			i++;
		}
		printf("\n");
	}
}

int	main(int argc, char **argv)
{
    int set_size = argc - 2;
	int	target = atoi(argv[1]);
	int	subset_indices[set_size];
	int	subset_size;
	int	j;

	if (argc < 3)
		return(1);
	if   (target==0)
		printf("\n");
	           // Number of elements in the input set
	int total_subsets = 1 << set_size; // Total subsets: 2^(set_size)
	int i = 1; // Start at 1 to skip the empty subset
	while (i < total_subsets)
	{
		subset_size = 0;
		j = 0;
		// Check each bit to determine which elements are in the subset
		while (j < set_size)
		{
			if (i & (1 << j))
				subset_indices[subset_size++] = j + 2; // Map bit position to argv index
			j++;
		}
		// Check and print the subset if it matches the target sum
		check_print(target, argv, subset_indices, subset_size);
		i++;
	}
	return (0);
}
