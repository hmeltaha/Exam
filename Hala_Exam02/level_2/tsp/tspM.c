#include <stdio.h>     // for printf, fscanf, stdin
#include <stdlib.h>    // for general utilities (not strictly needed here)
#include <float.h>     // for FLT_MAX (maximum float value)
#include <math.h>      // for sqrtf (square root for floats)

// Calculate distance between two points using the Euclidean formula
float dis(float x0, float y0, float x1, float y1)
{
	float dx = x1 - x0;                          // difference in x
	float dy = y1 - y0;                          // difference in y
	return sqrtf(dx * dx + dy * dy);             // return the straight-line distance
}

// Swap two integers (used to rearrange cities)
void swap(int *a, int *b)
{
	int tmp = *a;     // store a's value temporarily
	*a = *b;          // assign b to a
	*b = tmp;         // assign tmp (original a) to b
}

// Recursively try every order of visiting cities to find shortest path
void tsp(int *p, int start, int end, float *x, float *y, float *min)
{
	if (start == end) // base case: a full permutation is ready
	{
		float total = 0;
		int i = 0;
		// sum distance from city i to i+1
		while (i < end)
		{
			total += dis(x[p[i]], y[p[i]], x[p[i + 1]], y[p[i + 1]]);
			i++;
		}
		// add distance to return to the starting city
		total += dis(x[p[end]], y[p[end]], x[p[0]], y[p[0]]);
		// update shortest distance found
		if (total < *min)
			*min = total;
		return;
	}
	int i = start;
	while (i <= end)
	{
		swap(&p[start], &p[i]);           // fix one city in position
		tsp(p, start + 1, end, x, y, min);// recursively permute the rest
		swap(&p[start], &p[i]);           // backtrack: undo the swap
		i++;
	}
}

int main(void)
{
	float x[11];                 // x-coordinates of cities
	float y[11];                 // y-coordinates of cities
	float min = FLT_MAX;        // start with max float, will store min path length
	int p[11];                  // array to hold city indices (0 to n-1)
	int i = 0;                  // counter for reading cities
	// Read coordinates from input (up to 11 points)
	while (i < 11 && fscanf(stdin, "%f , %f\n", &x[i], &y[i]) == 2)
	{
		p[i] = i;               // fill permutation array with city indices
		i++;
	}
	// Find the shortest round-trip route
	tsp(p, 0, i - 1, x, y, &min);
	// Print the shortest distance with 2 decimal places
	printf("%.2f\n", min);
	return 0; // success
}
