#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct ITEM - структура для хранения названия продукта и количества его проданных штук.
typedef struct
{
	char title[100];
	int quantity;
} ITEM;

// int item_bufferNotValid - проверка валидности названия введенного продукта, проверка длины. // еще добавить проверку на вайтспэйсы!
int item_bufferNotValid(const char *item_buffer)
{
	return (strlen(item_buffer) <= 0 || strlen(item_buffer) > 99);
}

// int operation_signNotValid - проверка валидности знака операции.
int operation_signNotValid(const char operation_sign)
{
	return (operation_sign != '+' && operation_sign != '#' && operation_sign != '?');
}

// int elementsCompare - функция для qsort, сравнивает 2 соседние структуры на параметр title, если тайтлы одинаковы возвращает 0, если нет то 1 или -1. Оставить ссылку на источник!
int elementsCompare(const void *first, const void *second)
{
	const ITEM *arg_1 = (ITEM *)first;
	const ITEM *arg_2 = (ITEM *)second;
	return (arg_2->quantity) - (arg_1->quantity);
}

// int itemInsideArray - проверка наличия введенного продукта в массиве items.
int itemInsideArray(ITEM *items, const int item_count, const char *item_buffer)
{
	for (int i = 0; i < item_count; i++)
	{
		if (strcmp(item_buffer, items[i].title) == 0)
			return i;
	}
	return -1;
}

// int items_trackedRepeatCheck - повышает прогоняемый элемент i если количество соседних товаров одинаковое.
int items_trackedRepeatCheck(ITEM *items, const int item_count, int i)
{
	while (i + 1 < item_count)
	{
		if (items[i].quantity == items[i + 1].quantity)
			i++;
		else
			break;
	}
	return i;
}

// int items_trackedPrint - печатает отслеживаемые товары и их количество, а также их общее количество.
int items_trackedPrint(ITEM *items, const int first_repeat, const int last_repeat, int tracked_sold, const char operation_sign)
{
	if (first_repeat < last_repeat)
	{
		for (int j = first_repeat; j <= last_repeat; j++)
		{
			tracked_sold += items[j].quantity;
			if (operation_sign == '#')
				printf("%d.-%d. %s, %dx\n", (first_repeat + 1), (last_repeat + 1), items[j].title, items[j].quantity);
		}
	}
	else
	{
		tracked_sold += items[first_repeat].quantity;
		if (operation_sign == '#')
			printf("%d. %s, %dx\n", (first_repeat + 1), items[first_repeat].title, items[first_repeat].quantity);
	}
	return tracked_sold;
}

void itemsTracked(ITEM *items, const int const_tracked_count, const int item_count, const char operation_sign)
{
	int first_repeat = 0, last_repeat = 0, tracked_count = const_tracked_count, tracked_sold = 0;
	if (item_count < const_tracked_count)
		tracked_count = item_count;
	for (int i = 0; i < tracked_count; i++)
	{
		first_repeat = i;
		i = items_trackedRepeatCheck(items, item_count, i);
		last_repeat = i;
		tracked_sold = items_trackedPrint(items, first_repeat, last_repeat, tracked_sold, operation_sign);
	}
	printf("Nejprodavanejsi zbozi: prodano %d kusu\n", tracked_sold);
}

int main()
{
	int const_tracked_count; // количество отслеживаемых топовых продуктов.
	int scanf_data; // принимает коилчество вводных данных на сканфе.
	char operation_sign; // введенный знак операции.
	char *item_buffer; // буфер для хранения названия продукта, проверяем длину названия и наличие вайтспэйсов.
	ITEM *items = NULL; // указатель на массив структур.
	int item_count = 0; // количество проданных уникальных продуктов, количество структур в массиве.
	int memory_amount = 100; // начальное количество выделяемой динамической памяти под массив структур.
	
	printf("Pocet sledovanych:\n");
	if (scanf(" %d", &const_tracked_count) != 1 || const_tracked_count <= 0) // ввод и проверка числа для количества отслеживаемых продуктов.
	{
		printf("Nespravny vstup.\n");
		return 1;
	}

	printf("Pozadavky:\n");
	while ((scanf_data = scanf(" %c", &operation_sign)) != feof(stdin)) // цикл для ввода знака операции и возможного последующего ввода названия продукта.
	{
		if (feof(stdin) && scanf_data != 0)
		{
			free(items);
			return 1;
		}

		if (operation_signNotValid(operation_sign)) // проверка знака операции.
		{
			free(items);
			printf("Nespravny vstup.\n");
			return 1;
		}

		if (operation_sign == '+')
		{
			item_buffer = (char *)malloc(1000 * sizeof(char));	// выделение памяти для названия продукта.
			if (scanf(" %s", item_buffer) != 1 || item_bufferNotValid(item_buffer)) // проверка названия продукта.
			{
				free(item_buffer), free(items); // освобождение памяти под название продукта и массив структур.
				printf("Nespravny vstup.\n");
				return 1;
			}
			if (items == NULL)
				items = (ITEM *)malloc(memory_amount * sizeof(*items)); // если массив еще пустой, мы его создаем с памятью под 100 структур.
			else
			{
				int item_index = itemInsideArray(items, item_count, item_buffer);
				if (item_index == -1)
				{
					if (item_count == memory_amount)
						items = (ITEM *)realloc(items, (memory_amount *= 2) * sizeof(*items));
				}
				else
				{
					items[item_index].quantity++;
					free(item_buffer);
					continue;
				}
			}
			strcpy(items[item_count].title, item_buffer);
			items[item_count].quantity = 1;
			item_count++;
			free(item_buffer);
		}

		if (operation_sign == '#' || operation_sign == '?')
		{
			qsort(items, item_count, sizeof(*items), elementsCompare);
			itemsTracked(items, const_tracked_count, item_count, operation_sign);
		}
	}

	return 0;
}
