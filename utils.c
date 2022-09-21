#include "cub3d.h"

int sum_of_rgb(int t, int r, int g, int b)
{
	return ((t * 16777216) + (65537 * r) + (256 * g) + b);
}