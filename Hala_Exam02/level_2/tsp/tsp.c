#include "tsp.h"


void tsp(int *p, int start, int end, float *x, float *y, float *min)
{
	if (start == end)
	{
		float total = 0.0f;
		int i = 0;
		while (i < end)
		{
			total += dis(x[p[i]], y[p[i]], x[p[i + 1]], y[p[i + 1]]);
			i++;
		}
		total += dis(x[p[end]], y[p[end]], x[p[0]], y[p[0]]);
		if (total < *min)
			*min = total;
	}
	int i = start;
	while (i <= end)
	{
		swap(&p[start], &p[i]);
		tsp(p, start + 1, end, x, y, min);
		swap(&p[start], &p[i]);
		i++;
	}
}

int main()
{
	int i = 0;
	int p[11];
	float min = FLT_MAX;
	float x[11], y[11];
	while (fscanf( stdin,"%f , %f", &x[i], &y[i]) == 2)
	{
		p[i] = i;
		i++;
	}
	tsp(p, 0, i - 1, x, y, &min);
	printf("%.2f\n", min);
	return 0;
}