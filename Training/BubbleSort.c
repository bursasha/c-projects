#include <stdio.h>

int main()
{
	int new_array[20];
	int elements_number;
	int element_swap;

	printf("Enter count of elements:\n");
	scanf(" %d", &elements_number);

	printf("Enter %d integers:\n", elements_number);

	for (int i = 0; i < elements_number; i++) scanf("%d", &new_array[i]);
	for (int i = 0; i < elements_number - 1; i++)
	{
		for (int j = 0; j < elements_number - i - 1; j++)
		{
			if (new_array[j] > new_array[j + 1])
			{
				element_swap = new_array[j];
				new_array[j] = new_array[j + 1];
				new_array[j + 1] = element_swap;
			}
		}
	}

	printf("Bubble sort: ");
	for (int i = 0; i < elements_number; i++) printf("%d ", new_array[i]);
	printf("\n");

	return 0;
}
