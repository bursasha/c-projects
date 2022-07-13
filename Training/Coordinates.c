#include <stdio.h>
#include <math.h>
#include <float.h>
#define DBL_EPSILON __DBL_EPSILON__

double sideLength(double x1, double y1, double x2, double y2)
{
	double side = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	return side;
}

double triangleArea(double side1, double side2, double side3)
{
	double p = (side1 + side2 + side3) / 2;
	double formula = p * (p - side1) * (p - side2) * (p - side3);
	double triangle_area = sqrt(formula);
	return triangle_area;
}

void trianglesComparison(double area, double area_1, double area_2, double area_3)
{
	if (fabs(area - area_1 - area_2 - area_3) <= 100 * DBL_EPSILON * (fabs(area_1) + fabs(area_2) + fabs(area_3)))
	{
		printf("Point is inside!\n");
	}
	else printf("Point is not inside!\n");
}


int main() 
{
	double ax = 0, ay = 0, bx = 0, by = 0, cx = 0, cy = 0, px = 0, py = 0;

	printf("Enter coordinates of 3 triangle apexes and of another 1 point:\n");
	while (scanf(" %lf %lf %lf %lf %lf %lf %lf %lf", &ax, &ay, &bx, &by, &cx, &cy, &px, &py) != EOF)
	{
		double side_ab = fabs(sideLength(ax, ay, bx, by));
		double side_bc = fabs(sideLength(bx, by, cx, cy));
		double side_ac = fabs(sideLength(ax, ay, cx, cy));

		double area_abc = triangleArea(side_ab, side_bc, side_ac);

		double side_ap = fabs(sideLength(ax, ay, px, py));
		double side_bp = fabs(sideLength(bx, by, px, py));
		double side_cp = fabs(sideLength(cx, cy, px, py));

		double area_abp = triangleArea(side_ab, side_ap, side_bp);
		double area_bcp = triangleArea(side_bc, side_bp, side_cp);
		double area_acp = triangleArea(side_ac, side_ap, side_cp);

		trianglesComparison(area_abc, area_abp, area_bcp, area_acp);
	}

	return 0;
}