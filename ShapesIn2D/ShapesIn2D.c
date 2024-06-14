#include <stdio.h>
#include <math.h>
#define DBL_EPSILON __DBL_EPSILON__

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Checks if the given input represents a valid square.
 *
 * This function verifies that the input represents a valid square with a positive side length.
 *
 * @param inputData - Number of input values read.
 * @param fig - Character representing the figure type ('S' for square).
 * @param side1 - The length of the side of the square.
 * @return 1 if the input represents a valid square, 0 otherwise.
 */
int isSquare(int inputData, char fig, double side1)
{
	return inputData == 1 && fig == 'S' && side1 > 0;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Checks if the given input represents a valid rectangle.
 *
 * This function verifies that the input represents a valid rectangle with positive side lengths and different sides.
 *
 * @param inputData - Number of input values read.
 * @param fig - Character representing the figure type ('R' for rectangle).
 * @param side1 - The length of the first side of the rectangle.
 * @param side2 - The length of the second side of the rectangle.
 * @return 1 if the input represents a valid rectangle, 0 otherwise.
 */
int isRectangle(int inputData, char fig, double side1, double side2)
{
	return inputData == 2 && fig == 'R' && side1 > 0 && side2 > 0 && side1 != side2;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Checks if the given input represents a valid triangle.
 *
 * This function verifies that the input represents a valid triangle with positive side lengths and satisfies the triangle inequality.
 *
 * @param inputData - Number of input values read.
 * @param fig - Character representing the figure type ('T' for triangle).
 * @param side1 - The length of the first side of the triangle.
 * @param side2 - The length of the second side of the triangle.
 * @param side3 - The length of the third side of the triangle.
 * @return 1 if the input represents a valid triangle, 0 otherwise.
 */
int isTriangle(int inputData, char fig, double side1, double side2, double side3)
{
	return inputData == 3 && fig == 'T' && side1 > 0 && side2 > 0 && side3 > 0 &&
	((side1 + side2) > side3) && ((side1 + side3) > side2) && ((side2 + side3) > side1) &&
	!(fabs(side1 + side2 - side3) <= 100 * DBL_EPSILON * (fabs(side1) + fabs(side2) + fabs(side3))) &&
	!(fabs(side1 + side3 - side2) <= 100 * DBL_EPSILON * (fabs(side1) + fabs(side2) + fabs(side3))) &&
	!(fabs(side2 + side3 - side1) <= 100 * DBL_EPSILON * (fabs(side1) + fabs(side2) + fabs(side3)));
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Validates the given input data for the shape.
 *
 * This function checks if the given input data corresponds to a valid square, rectangle, or triangle.
 *
 * @param inputData - Number of input values read.
 * @param fig - Character representing the figure type ('S' for square, 'R' for rectangle, 'T' for triangle).
 * @param side1 - The length of the first side.
 * @param side2 - The length of the second side.
 * @param side3 - The length of the third side.
 * @return 1 if the input data is valid, 0 otherwise.
 */
int isValid(int inputData, char fig, double side1, double side2, double side3)
{
	return isSquare(inputData, fig, side1) || isRectangle(inputData, fig, side1, side2) || 
	isTriangle(inputData, fig, side1, side2, side3);
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Calculates the perimeter of the given shape.
 *
 * This function computes the perimeter of a square, rectangle, or triangle based on the given dimensions.
 *
 * @param per - Initial perimeter value (usually 0).
 * @param fig - Character representing the figure type ('S' for square, 'R' for rectangle, 'T' for triangle).
 * @param side1 - The length of the first side.
 * @param side2 - The length of the second side (if applicable).
 * @param side3 - The length of the third side (if applicable).
 * @return The perimeter of the shape.
 */
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

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Calculates the area of the given shape.
 *
 * This function computes the area of a square, rectangle, or triangle based on the given dimensions.
 *
 * @param area - Initial area value (usually 0).
 * @param fig - Character representing the figure type ('S' for square, 'R' for rectangle, 'T' for triangle).
 * @param side1 - The length of the first side.
 * @param side2 - The length of the second side (if applicable).
 * @param side3 - The length of the third side (if applicable).
 * @return The area of the shape.
 */
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

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Compares two sizes and returns the comparison sign.
 *
 * This function compares two sizes (e.g., areas or perimeters) and returns the appropriate comparison sign ('=', '>', '<').
 *
 * @param sign - Initial sign value (usually '\0').
 * @param size1 - The first size to compare.
 * @param size2 - The second size to compare.
 * @return The comparison sign.
 */
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

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief
 * Returns the name of the shape in Czech.
 *
 * This function returns the name of the shape (square, rectangle, or triangle) in Czech based on the given character.
 *
 * @param fig - Character representing the figure type ('S' for square, 'R' for rectangle, 'T' for triangle).
 * @return The name of the shape in Czech.
 */
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

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

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
