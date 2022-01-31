#ifndef FUNC_H
#define FUNC_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * 	TODO: FIX THE FIND TIMELY FUNCTION
 * 	TODO: FIX THE FIND LOCATION FUNCTION
 * 
**/

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
        // printf("\n");

		if (!checkCirc(routes[i]))
		{
			result = get_time(routes[i], routes[i].downhill);
			printf("\nFrom %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
                routes[i].end, routes[i].start, routes[i].downhill, routes[i].uphill, routes[i].max_height, routes[i].min_height, 
                routes[i].len, result);
			// printf("\n");
		}
	}
}


// int readFromInput(struct route routes[500])
// {
//     int n;
//     scanf("%d", &n);
//     for (int i = 0;i < n;++i)
//     {
//         // printf("Enter the beginning:\n");
//         scanf(" ");
//         fgets(routes[i].start, 50, stdin);
//         // printf("Enter the length, uphill downhill climb, the max height and the min height:\n");
//         scanf("%d %d %d %d %d", &routes[i].len, &routes[i].uphill, &routes[i].downhill, &routes[i].max_height, &routes[i].min_height);
//         // printf("Enter the ending: \n");
//         scanf(" ");
//         fgets(routes[i].end, 50, stdin);
//     }
//     return n;
// }


void findShort(struct route routes[500], int size)
{
	int k;
	scanf("%d", &k);
	// size_t n = sizeof(routes) / sizeof(routes[0]);
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
	int result;

	d[strcspn(d, "\n")] = 0;

	// size_t n = sizeof(routes) / sizeof(routes[0]);
	qsort(routes, size, sizeof(struct route), comp_func);

	for (int i = 0;i < size; ++i)
	{
		remove_newline(&routes[i]);

		if (strcmp(routes[i].start, d) == 0 && strcmp(routes[i].end, d) == 0)
		{
			result = get_time(routes[i], routes[i].uphill);

			printf("From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
                routes[i].start, routes[i].end, routes[i].uphill, routes[i].downhill, routes[i].max_height, routes[i].min_height, 
                routes[i].len, result);
			printf("\n");
		}

		else if (strcmp(routes[i].start, d) != 0 && strcmp(routes[i].end, d) == 0)
		{
			result = get_time(routes[i], routes[i].downhill);

			printf("From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
	            routes[i].end, routes[i].start, routes[i].downhill, routes[i].uphill, routes[i].max_height, routes[i].min_height, 
                routes[i].len, result);
			printf("\n");
		}
	}
}


void findUpHill(struct route routes[500], int size)
{
	// size_t n = sizeof(routes) / sizeof(routes[0]);
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
	// size_t n = sizeof(routes) / sizeof(routes[0]);
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

	// size_t n = sizeof(routes) / sizeof(routes[0]);
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
	double delay, t;
	delay = route.len / 65.0;
	t = up / 10.0;
	return delay + t;
}

void findTimely(struct route routes[500], int size)
{
	int t;
	scanf("%d", &t);

	// size_t n = sizeof(routes) / sizeof(routes[0]);
	qsort(routes, size, sizeof(struct route), comp_func);

	for (int i = 0;i < size; ++i)
	{
		double res = real_time(routes[i], routes[i].uphill);
		int x = get_time(routes[i], routes[i].uphill);
		
		remove_newline(&routes[i]);

		// printf("The real time is %lf and the time is %d \n", res, x);

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


// PART 2 STARTS HERE
// Read a number from the text file 
// read n routes from the file
// close the file
// int readFromFile(struct route routes[500])
// {
// 	int n;
// 	char filename[50];
// 	fgets(filename, 50, stdin);

// 	filename[strcspn(filename, "\n")] = 0;

// 	FILE *fp;

// 	fp = fopen(filename, "r");

// 	if (fp == NULL)
// 	{
// 		printf("Error opening the text file! \nExiting...\n");
// 		return -1;
// 	}
// 	else
// 	{
// 		fscanf(fp, "%d", &n);
// 		for (int i = 0;i < n; ++i)
// 		{
// 			fscanf(fp, "%s", routes[i].start);
// 			fscanf(fp, "%d %d %d %d %d", &routes[i].len, &routes[i].uphill, &routes[i].downhill, &routes[i].max_height, &routes[i].min_height);
// 			fscanf(fp, "%s", routes[i].end);
// 		}
// 	}

// 	fclose(fp);

// 	return n;
// }


void saveData(struct route routes[500], int n)
{
	char str[50];
	fgets(str, 50, stdin);

	str[strcspn(str, "\n")] = 0;

	// sorting the routes in descending order 
	qsort(routes, n, sizeof(struct route), comp_func);

	FILE *fp;

	fp = fopen(str, "w+");

	if (fp == NULL)
	{
		printf("Error opening the file!\nExiting...");
		return;
	}
	else
	{
		for (int i = 0;i < n; ++i)
		{
			int result = get_time(routes[i], routes[i].uphill);
			remove_newline(&routes[i]);

			fprintf(fp, "From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
					routes[i].start, routes[i].end, routes[i].uphill, routes[i].downhill, routes[i].max_height, routes[i].min_height, routes[i].len,
					result);
			fprintf(fp, "\n");

			if (!checkCirc(routes[i]))
			{
				result = get_time(routes[i], routes[i].downhill);
				fprintf(fp, "From %s to %s\nUphill %d, Downhill %d\nMax altitude %d, Min altitude %d\nLength %d, Estimated time %d min\n", 
					routes[i].end, routes[i].start, routes[i].downhill, routes[i].uphill, routes[i].max_height, routes[i].min_height, routes[i].len,
					result);
				fprintf(fp, "\n");
			}
		}
	}

	fclose(fp);
}


struct route* readFromInput(int *k)
{
	int n;
	scanf("%d", &n);

	struct route* routes = (struct route*)malloc(sizeof(struct route) * (n+1));

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

    *k = n;

    return routes;
}


struct route* readFromFile(int *n)
{
	int k;
	char str[50];
	fgets(str, 50, stdin);

	FILE *fp;

	str[strcspn(str, "\n")] = 0;

	fp = fopen(str, "r");

	if (fp == NULL)
	{
		printf("Error opening the file!\nExiting...");
		return NULL;
	}
	else
	{
		fscanf(fp, "%d", &k);

		struct route* routes = (struct route*)malloc(sizeof(struct route) * (k+1));

		for (int i = 0;i < k; ++i)
		{
 			fscanf(fp, "%s", routes[i].start);
 			fscanf(fp, "%d %d %d %d %d", &routes[i].len, &routes[i].uphill, &routes[i].downhill, &routes[i].max_height, &routes[i].min_height);
 			fscanf(fp, "%s", routes[i].end);
		}
	}
	*n = k;
}


#endif 
