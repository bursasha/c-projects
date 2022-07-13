#include <stdio.h>
#include <stdlib.h>

#define MAX_REGISTRATION 1000000 // A max possible count of the registered guests, the size of int guest_array.
#define MAX_ID 99999					// A max possible value of the guest ID, is used for the size of int visit_array.

/**
 * Invalidation of an ID number and of the count of general registrations of the guests. Is used at + operation (guest registration).
 *
 * Invalidation is successful:
 * - if ID is less than 0 or is greater than MAX_ID,
 * - if registrations count of guests is greater than MAX_REGISTRATION.
 *
 * @param[in] id guest ID number.
 * @param[in] registrations general count of the registered guests.
 * @returns 1 if invalidation is successful, 0 otherwise.
 */
int idInvalid ( const int id, const int registrations )
{
	return ( id < 0 || id > MAX_ID || registrations > MAX_REGISTRATION );
}

/**
 * Invalidation of the from-to range in the general int guest_array with all registered guests. Is used at ? operation.
 *
 * Invalidation is successful:
 * - if "from" value is less than 0 or is greater than "to" value,
 * - if "to" value is greater than count of the registered guests.
 *
 * @param[in] from start of the range.
 * @param[in] to end of the range.
 * @param[in] registrations general count of the registered guests.
 * @returns 1 if invalidation is successful, 0 otherwise.
 */
int from_toInvalid ( const int from, const int to, const int registrations )
{
	return ( from < 0 || from > to || to >= registrations );
}

/**
 * Printing the number of visits of each registered guest. Is used at + operation.
 *
 * The function accesses the array cell depending on the guest ID number.
 * 
 * @param[out] visit_array a constant array with the number of visits of each registered guest.
 * @param[out] id guest ID number.
 */
void printGuestVisit ( const int *visit_array, const int id )
{
	(visit_array[id] == 1) ? printf ("> prvni navsteva\n") : printf ("> navsteva #%d\n", visit_array[id]);
}

//
/**
 * Function for the quicksort, is used as its fourth argument.
 *
 * Is used for array object comparison.
 *
 * @returns ​a negative integer value if the first argument is less than the second,
 * a positive integer value if the first argument is greater than the second,
 * 0 if the arguments are equal.
 */
int compareIDs ( const void *id_1, const void *id_2 )
{
	return *(int *)id_1 - *(int *)id_2;
}

/**
 * Function writes IDs from the guest_array in range from-to to the range_array and sorts them. Is used at ? operation.
 *
 * @param[in,out] range_array a dynamic array with all guests from the guest_array in range from-to.
 * @param[in] guest_array a constant array with all registered guests.
 * @param[in] from start of the range.
 * @param[in] to end of the range.
 * @param[in] range a count of guests in range from-to.
 */
void write_sortRangeArray ( int *range_array, const int *guest_array, const int from, const int to, const int range )
{
	for (int i = 0, j = from; j <= to; i++, j++)
		range_array[i] = guest_array[j];
	qsort (range_array, range, sizeof(int), compareIDs); // Sorting ID numbers in ascending order.
}

/**
 * Counts a number of the unique guests in the array in the given range and prints it. Is used at ? operation.
 *
 * @param[in] range_array a dynamic array with all guests from the guest_array in range from-to.
 * @param[out] range a count of guests in range from-to.
 */
void countGuestsUnique ( const int *range_array, const int range )
{
	int guests_unique = 0; // A quantity of the unique guests in array.
	for (int i = 0; i < range; i++)
	{
		while (range_array[i] == range_array[i + 1] && i < (range - 1)) // Checking if neighbouring IDs are same, we don't need to count them as unique.
			i++;
		guests_unique++;
	}
	printf("> %d / %d\n", guests_unique, range);
}

int main ( void )
{
	char operation;
	int id;
	int registrations = 0; 				  // A count of all registered guests, at start is 0.
	int from, to;
	int guest_array[MAX_REGISTRATION]; // An array for all registered guests, is able to collect 1000000 ID numbers at all.
	int visit_array[MAX_ID + 1];		  // An array with a counts of visits of each guest with ID number from 0 to 99999.
	int *range_array = NULL;			  // A pointer at a dynamic array with all guests from the guest_array in range from-to.

	printf("Pozadavky:\n");
	while (scanf(" %c", &operation) != EOF)
	{
		if (operation == '+')
		{
			if (scanf(" %d", &id) != 1 || idInvalid(id, registrations))
			{
				printf("Nespravny vstup.\n");
				return 1;
			}
			guest_array[registrations++] = id; // Guest registration.
			visit_array[id]++;					  // Recording the visit of a specific guest.
			printGuestVisit(visit_array, id);
		}

		else if (operation == '?')
		{
			if (scanf(" %d %d", &from, &to) != 2 || from_toInvalid(from, to, registrations))
			{
				printf("Nespravny vstup.\n");
				return 1;
			}
			int range = (to - from) + 1; // A count of guests in range from-to.
			range_array = (int *) malloc ((range + 1) * sizeof(int));
			write_sortRangeArray(range_array, guest_array, from, to, range);
			countGuestsUnique(range_array, range);
			free(range_array), range_array = NULL;
		}

		else
		{
			printf("Nespravny vstup.\n");
			return 1;
		}
	}

	return 0;
}
