#include <stdio.h>
#include <math.h>
#define DBL_EPSILON __DBL_EPSILON__


int isSquare(int inputData, char fig, double side1)
{
	return inputData == 1 && fig == 'S' && side1 > 0;
}

int isRectangle(int inputData, char fig, double side1, double side2)
{
	return inputData == 2 && fig == 'R' && side1 > 0 && side2 > 0 && side1 != side2;
}

int isTriangle(int inputData, char fig, double side1, double side2, double side3)
{
	return inputData == 3 && fig == 'T' && side1 > 0 && side2 > 0 && side3 > 0 &&
	((side1 + side2) > side3) && ((side1 + side3) > side2) && ((side2 + side3) > side1) &&
	!(fabs(side1 + side2 - side3) <= 100 * DBL_EPSILON * (fabs(side1) + fabs(side2) + fabs(side3))) &&
	!(fabs(side1 + side3 - side2) <= 100 * DBL_EPSILON * (fabs(side1) + fabs(side2) + fabs(side3))) &&
	!(fabs(side2 + side3 - side1) <= 100 * DBL_EPSILON * (fabs(side1) + fabs(side2) + fabs(side3)));
}


int isValid(int inputData, char fig, double side1, double side2, double side3)
{
	return isSquare(inputData, fig, side1) || isRectangle(inputData, fig, side1, side2) || 
	isTriangle(inputData, fig, side1, side2, side3);
}


double perimeterFigure(double per, char fig, double side1, double side2, double side3)
{
	switch(fig)
	{
		case 'S':
			per = 4 * side1;
			break;

		case 'R':
			per = 2 * (side1 + side2);
			break;

		case 'T':
			per = side1 + side2 + side3;
			break;
	}
	return per;
}


double areaFigure(double area, char fig, double side1, double side2, double side3)
{
	double p, formula;

	switch (fig)
	{
	case 'S':
		area = pow(side1, 2);
		break;

	case 'R':
		area = side1 * side2;
		break;

	case 'T':
		p = (side1 + side2 + side3) / 2;
		formula = p * (p - side1) * (p - side2) * (p - side3);
		area = sqrt(formula);
		break;
	}
	return area;
}

char comparisonSign(char sign, double size1, double size2)
{
	if (fabs(size2 - size1) <= 100 * DBL_EPSILON * (fabs(size1) + fabs(size2)))
	{
		sign = '=';
	}
	else if (size1 > size2) 
	{
		sign = '>';
	}
	else if (size1 < size2) 
	{
		sign = '<';
	}
	return sign;
}


const char *nameFigure(char fig)
{
	if (fig == 'S')
	{
		return "ctverec";
	}
	
	else if(fig == 'R')
	{
		return "obdelnik";
	}

	else 
	{
		return "trojuhelnik";
	}	
}


int main() 
{
	char fig1 = '\0', fig2 = '\0', sign1 = '\0', sign2 = '\0';
	int inputData1 = 0, inputData2 = 0;
	double a1 = 0, b1 = 0, c1 = 0, a2 = 0, b2 = 0, c2 = 0, per1 = 0, per2 = 0, area1 = 0, area2 = 0;

	printf("Obrazec #1\n");

	scanf(" %c", &fig1);
	
	switch(fig1)
	{
		case 'S':
			inputData1 = scanf(" %lf", &a1);
			break;
		
		case 'R':
			inputData1 = scanf(" %lf %lf", &a1, &b1);
			break;

		case 'T':
			inputData1 = scanf(" %lf %lf %lf", &a1, &b1, &c1);
			break;
	}

	if (!isValid(inputData1, fig1, a1, b1, c1))
	{
		printf("Nespravny vstup.\n");
		return 1;
	}


	printf("Obrazec #2\n");

	scanf(" %c", &fig2);

	switch (fig2)
	{
	case 'S':
		inputData2 = scanf(" %lf", &a2);
		break;

	case 'R':
		inputData2 = scanf(" %lf %lf", &a2, &b2);
		break;

	case 'T':
		inputData2 = scanf(" %lf %lf %lf", &a2, &b2, &c2);
		break;
	}

	if (!isValid(inputData2, fig2, a2, b2, c2))
	{
		printf("Nespravny vstup.\n");
		return 1;
	}


	per1 = perimeterFigure(per1, fig1, a1, b1, c1);
	per2 = perimeterFigure(per2, fig2, a2, b2, c2);
	printf("Obvod: %s #1 %c %s #2\n", nameFigure(fig1), comparisonSign(sign1, per1, per2), nameFigure(fig2));
	
	area1 = areaFigure(area1, fig1, a1, b1, c1);
	area2 = areaFigure(area2, fig2, a2, b2, c2);
	printf("Obsah: %s #1 %c %s #2\n", nameFigure(fig1), comparisonSign(sign2, area1, area2), nameFigure(fig2));

	return 0;

}
