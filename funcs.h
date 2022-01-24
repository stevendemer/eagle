#ifndef FUNC_H
#define FUNC_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct route 
{
	char start[50];
	char end[50];
	int len;
	int min_height;
	int max_height;
	int uphill;
	int downhill;
};

void remove_newline(struct route *route)
{
	route->start[strcspn(route->start, "\n")] = 0;
	route->end[strcspn(route->end, "\n")] = 0;
}

void swap(struct route* x, struct route* y)
{
    struct route tmp = *x;
    *x = *y;
    *y = tmp;
}

// return < 0 if x goes before y 
// 0 if the values are equal 
// > 0 if the value of x goes after y
int comp_func(const void *x, const void *y)
{
	const struct route *left = x;
	const struct route *right = y;
	return (left->len < right->len) - (right->len < left->len);
}


int isUp(struct route route)
{
	if (abs(route.uphill - route.downhill) > 0)
		return 1;
	return 0;
}

int isDown(struct route route)
{
	if (abs(route.downhill - route.uphill) > 0)
		return 1;
	return 0;
}

// checks to see if the route ends in the same place 
int checkCirc(struct route route)
{
    if (strcmp(route.start, route.end) == 0)
            return 1;
    return 0;
}

void run_sort(struct route routes[500])
{
	size_t n = sizeof(routes) / sizeof(routes[0]);
	qsort(routes, n, sizeof(struct route), comp_func);
}

int get_time(struct route route, int up)
{
	double total_time, delay;
	total_time = route.len / 65.0;
	delay = up / 10.0;
	int res = (int)round(total_time + delay);
	return res;
}

void printData(struct route routes[500], int size)
{
	// size_t n = sizeof(routes) / sizeof(routes[0]);
	qsort(routes, size, sizeof(struct route), comp_func);

	for (int i = 0;i < size; ++i)
	{
		int result = get_time(routes[i], routes[i].uphill);
		remove_newline(&routes[i]);

        printf("From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
                routes[i].start, routes[i].end, routes[i].uphill, routes[i].downhill, routes[i].max_height, routes[i].min_height, 
                routes[i].len, result);
        printf("\n");

		if (!checkCirc(routes[i]))
		{
			result = get_time(routes[i], routes[i].downhill);
			printf("\nFrom %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
                routes[i].end, routes[i].start, routes[i].downhill, routes[i].uphill, routes[i].max_height, routes[i].min_height, 
                routes[i].len, result);
			printf("\n");
		}
	}
}


int readFromInput(struct route routes[500])
{
    int n;
    scanf("%d", &n);
    for (int i = 0;i < n;++i)
    {
        // printf("Enter the beginning:\n");
        scanf(" ");
        fgets(routes[i].start, 50, stdin);
        // printf("Enter the length, uphill downhill climb, the max height and the min height:\n");
        scanf("%d %d %d %d %d", &routes[i].len, &routes[i].uphill, &routes[i].downhill, &routes[i].max_height, &routes[i].min_height);
        // printf("Enter the ending: \n");
        scanf(" ");
        fgets(routes[i].end, 50, stdin);
    }
    return n;
}


void findShort(struct route routes[500], int size)
{
	int k;
	scanf("%d", &k);
	size_t n = sizeof(routes) / sizeof(routes[0]);
	qsort(routes, size, sizeof(struct route), comp_func);

	for (int i = 0;i < size; ++i)
	{
		if (routes[i].len <= k)
		{
			int result = get_time(routes[i], routes[i].uphill);
			remove_newline(&routes[i]);

			printf("From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
                routes[i].start, routes[i].end, routes[i].uphill, routes[i].downhill, routes[i].max_height, routes[i].min_height, 
                routes[i].len, result);
			printf("\n");

			if (!checkCirc(routes[i]))
			{
				result = get_time(routes[i], routes[i].downhill);
				printf("From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
					routes[i].end, routes[i].start, routes[i].downhill, routes[i].uphill, routes[i].max_height, routes[i].min_height, 
					routes[i].len, result);
				printf("\n");
			}
		}
	}
}


void findLocation(struct route routes[500], int size)
{
	char d[50];
	fgets(d, 50, stdin);

	size_t n = sizeof(routes) / sizeof(routes[0]);
	qsort(routes, size, sizeof(struct route), comp_func);

	for (int i = 0;i < size; ++i)
	{
		remove_newline(&routes[i]);

		if (strcmp(routes[i].start, d) == 0)
		{
			int result = get_time(routes[i], routes[i].uphill);
			printf("From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
                routes[i].start, routes[i].end, routes[i].uphill, routes[i].downhill, routes[i].max_height, routes[i].min_height, 
                routes[i].len, result);
		}
		else if (strcmp(routes[i].end, d) == 0)
		{
			int result = get_time(routes[i], routes[i].downhill);

			printf("From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
                routes[i].end, routes[i].start, routes[i].downhill, routes[i].uphill, routes[i].max_height, routes[i].min_height, 
                routes[i].len, result);
		}
	}
}


void findUpHill(struct route routes[500], int size)
{
	size_t n = sizeof(routes) / sizeof(routes[0]);
	qsort(routes, size, sizeof(struct route), comp_func);

	int result;

	for (int i = 0;i < size; ++i)
	{
		remove_newline(&routes[i]);

		if ((abs(routes[i].uphill)) - (abs(routes[i].downhill)) > 0)
		{
			result = get_time(routes[i], routes[i].uphill);

			printf("From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated min %d min", 
			routes[i].start, routes[i].end, routes[i].uphill, routes[i].downhill, routes[i].max_height, routes[i].min_height, routes[i].len, result);	
			printf("\n");
		}

		if (!checkCirc(routes[i]))
		{
			if ((abs(routes[i].uphill) - (abs(routes[i].downhill))) > 0)
			{
				result = get_time(routes[i], routes[i].downhill);

				printf("From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated min %d min", 
				routes[i].end, routes[i].start, routes[i].downhill, routes[i].uphill, routes[i].max_height, routes[i].min_height, routes[i].len, result);	
				printf("\n");
			}
		}
	}
}


void findDownHill(struct route routes[500], int size)
{
	size_t n = sizeof(routes) / sizeof(routes[0]);
	qsort(routes, size, sizeof(struct route), comp_func);

	int result;

	for (int i = 0;i < size; ++i)
	{
		remove_newline(&routes[i]);

		if ((abs(routes[i].downhill) - (abs(routes[i].uphill))) > 0)
		{
			result = get_time(routes[i], routes[i].uphill);

			printf("From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
                routes[i].start, routes[i].end, routes[i].uphill, routes[i].downhill, routes[i].max_height, routes[i].min_height, 
                routes[i].len, result);
			printf("\n");
		}

		if (!checkCirc(routes[i]))
		{
			if ((abs(routes[i].uphill) - (abs(routes[i].downhill))) > 0)
			{
				result = get_time(routes[i], routes[i].downhill);

				printf("From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
                routes[i].end, routes[i].start, routes[i].downhill, routes[i].uphill, routes[i].max_height, routes[i].min_height, 
                routes[i].len, result);
                printf("\n");
			}
		}
	}
}


void findAltitude(struct route routes[500], int size)
{
	int min, max;
	scanf("%d %d", &min, &max);

	size_t n = sizeof(routes) / sizeof(routes[0]);
	qsort(routes, size, sizeof(struct route), comp_func);

	for (int i = 0;i < size; ++i)
	{
		remove_newline(&routes[i]);

		if (routes[i].min_height >= min && routes[i].max_height <= max)
		{
			int result = get_time(routes[i], routes[i].uphill);
			printf("From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
			routes[i].start, routes[i].end, routes[i].uphill, routes[i].downhill, routes[i].max_height, routes[i].min_height, 
			routes[i].len, result);
			printf("\n");
	
			if (!checkCirc(routes[i]))
			{
				result = get_time(routes[i], routes[i].downhill);
				printf("From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
					routes[i].end, routes[i].start, routes[i].downhill, routes[i].uphill, routes[i].max_height, routes[i].min_height, 
					routes[i].len, result);
				printf("\n");
			}
		}
	}
}

double real_time(struct route route, int up)
{
	double delay, t, x;
	delay = route.len / 65.0;
	t = up / 10.0;
	return delay + t;
}


void findTimely(struct route routes[500], int size)
{
	int t;
	scanf("%d", &t);

	size_t n = sizeof(routes) / sizeof(routes[0]);
	qsort(routes, size, sizeof(struct route), comp_func);

	for (int i = 0;i < size; ++i)
	{
		double res = real_time(routes[i], routes[i].uphill);
		int x = get_time(routes[i], routes[i].uphill);
		
		remove_newline(&routes[i]);

		if (res <= t)
		{
			printf("From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
			routes[i].start, routes[i].end, routes[i].uphill, routes[i].downhill, routes[i].max_height, routes[i].min_height, 
			routes[i].len, x);
			printf("\n");


			if (!checkCirc(routes[i]))
			{
				res = real_time(routes[i], routes[i].downhill);
				x = get_time(routes[i], routes[i].downhill);

				if (res <= t)
				{
					printf("From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
					routes[i].end, routes[i].start, routes[i].downhill, routes[i].uphill, routes[i].max_height, routes[i].min_height, 
					routes[i].len, x);
					printf("\n");

				}
			}
		}
	}
}


#endif 
