#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

// All const values of J in minute, hour, day, 28-31 days, year.
#define MINUTE 200
#define HOUR 12200
#define DAY 292886
#define DAYS_28 8200808
#define DAYS_29 8493694
#define DAYS_30 8786580
#define DAYS_31 9079466
#define YEAR 106903390

// Const arrays with J in the time ranges 00-10 and 10-00, array of the year monthes.
const int ONES_ARRAY[] = {4, 9, 11, 14, 17, 18, 23, 27, 28, 30};
const int TENS_ARRAY[] = {34, 69, 101, 134, 167, 200};
const int MONTHS_ARRAY[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// minutesCount - counts J in min1-min2 range.
int minutesCount(int min1, int min2, int *flag)
{
	int min1_tens = min1 / 10, min1_ones = min1 % 10, min2_tens = min2 / 10, min2_ones = min2 % 10; // Count of tens and ones in min1 and min2
	int min1_tens_result, min1_ones_result, min2_tens_result, min2_ones_result, minutes;

	if (min1_tens == 0)
		min1_tens_result = 0;
	else
		min1_tens_result = TENS_ARRAY[(min1_tens - 1)]; // Element in array TENS_ARRAY
	if (min1_ones == 0)
		min1_ones_result = 0;
	else
		min1_ones_result = ONES_ARRAY[(min1_ones - 1)]; // Element in array ONES_ARRAY
	int min1_range = min1_tens_result + min1_ones_result;

	if (min2_tens == 0)
		min2_tens_result = 0;
	else
		min2_tens_result = TENS_ARRAY[(min2_tens - 1)]; // Element in array TENS_ARRAY
	if (min2_ones == 0)
		min2_ones_result = 0;
	else
		min2_ones_result = ONES_ARRAY[(min2_ones - 1)]; // Element in array ONES_ARRAY
	int min2_range = min2_tens_result + min2_ones_result;

	if (min2 > min1)
		minutes = (min2_range - min1_range) + (min2 - min1) * MINUTE;
	else if (min2 < min1)
	{
		minutes = (MINUTE - min1_range + min2_range) + (60 + min2 - min1) * MINUTE;
		*flag = 1;
	}
	else
		minutes = 0;

	return minutes;
}

// hoursCount - counts J in day1-day2 range.
int hoursCount(int hour1, int hour2, int *flag)
{
	int hour1_tens = hour1 / 10, hour1_ones = hour1 % 10, hour2_tens = hour2 / 10, hour2_ones = hour2 % 10; // Count of tens and ones in hour1 and hour2
	int hour1_tens_result, hour1_ones_result, hour2_tens_result, hour2_ones_result, hours;
	int decrement = 0;

	if (hour1_tens == 0)
		hour1_tens_result = 0;
	else
		hour1_tens_result = TENS_ARRAY[(hour1_tens - 1)]; // Element in array TENS_ARRAY
	if (hour1_ones == 0)
		hour1_ones_result = 0;
	else
		hour1_ones_result = ONES_ARRAY[(hour1_ones - 1)]; // Element in array ONES_ARRAY
	int hour1_range = hour1_tens_result + hour1_ones_result;

	if (hour2_tens == 0)
		hour2_tens_result = 0;
	else
		hour2_tens_result = TENS_ARRAY[(hour2_tens - 1)]; // Element in array TENS_ARRAY
	if (hour2_ones == 0)
		hour2_ones_result = 0;
	else
		hour2_ones_result = ONES_ARRAY[(hour2_ones - 1)]; // Element in array ONES_ARRAY
	int hour2_range = hour2_tens_result + hour2_ones_result;

	if (*flag)
		decrement = -1;
	if (hour2 > hour1)
	{
		hours = (hour2_range - hour1_range) + (hour2 - hour1 + decrement) * HOUR;
		*flag = 0;
	}
	else if (hour2 < hour1)
	{
		hours = (86 - hour1_range + hour2_range) + (24 + hour2 - hour1 + decrement) * HOUR;
		*flag = 1;
	}
	else hours = 0;
	
	decrement = 0;	

	return hours;
}

// daysCount - counts J in day1-day2 range.
int daysCount(int day1, int day2, int month1, int *flag)
{
	int days, decrement = 0;

	if (*flag)
		decrement = -1;
	if (day2 > day1)
	{
		days = (day2 - day1 + decrement) * DAY;
		*flag = 0;
	}
	else if (day2 < day1)
	{
		days = (MONTHS_ARRAY[(month1 - 1)] + day2 - day1 + decrement) * DAY;
		*flag = 1;
	}
	else
		days = 0;
	
	decrement = 0;

	return days;
}

// monthsCount - counts J in month1-month2 range.
int monthsCount(int month1, int month2, int min1, int min2, int hour1, int hour2,
					 int day1, int day2, int *minutes, int *hours, int *days, int *flag)
{
	int months = 0, decrement = 0;

	if (*flag)
		decrement = -1;

	if (month2 > month1)
	{
		for (int i = month1 - 1; i < month2 - 1 + decrement; i++)
			months += MONTHS_ARRAY[i];
		months *= DAY;
		*flag = 0;
	}
	else if (month2 < month1)
	{
		int inverse_minutes = minutesCount(min2, min1, flag);
		printf("inv min = %d\n", inverse_minutes);
		int inverse_hours = hoursCount(hour2, hour1, flag);
		printf("inv hours = %d\n", inverse_hours);
		int inverse_days = daysCount(day2, day1, month2, flag);
		printf("inv days = %d\n", inverse_days);
		if (!*flag)
			decrement = 0;
		// else if (*flag)
		// 	decrement = -1;
		for (int i = month2 - 1; i < month1 - 1 + decrement; i++)
			months += MONTHS_ARRAY[i];
		months = YEAR - (months * DAY + inverse_days + inverse_hours + inverse_minutes) - (*minutes + *hours + *days);
		*flag = 1;
	}
	else
		months = 0;
	
	decrement = 0;

	return months;
}

// yearsCount - counts J in year1-year2 range.
long long int yearsCount(int year1, int year2, int *flag)
{
	long long int years = 0, decrement = 0;

	if (*flag)
		decrement = -1;
	if (year2 >= year1)
		years = (year2 - year1 + decrement) * YEAR;

	return years;
}

// isLeapYear - checks if the year is leap.
int isLeapYear(int year)
{
	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0 && year % 4000 != 0))
		return 1;
	else
		return 0;
}

// leapCount - count of leap years in range year1-year2.
int leapCount(int year1, int year2, int month1, int month2)
{
	int leap_range1 = (year1 / 4) - (year1 / 100) + (year1 / 400) - (year1 / 4000);
	// printf("%d\n", leap_range1);
	int leap_range2 = (year2 / 4) - (year2 / 100) + (year2 / 400) - (year2 / 4000);
	// printf("%d\n", leap_range2);
	int leap_count = leap_range2 - leap_range1;
	if (month1 < 3 && isLeapYear(year1))
	{
		leap_count++;
	}
	if (month2 < 3 && isLeapYear(year2))
	{
		leap_count--;
	}
	// printf("leap years = %d\n", leap_count);
	return leap_count;
}

// isValid - dates values validation.
int isValid(int y1, int m1, int d1, int h1, int i1, int y2, int m2, int d2, int h2, int i2)
{
	if (!((y1 > 1599 && y2 > 1599 && y1 <= y2) && (m1 > 0 && m1 < 13 && m2 > 0 && m2 < 13) &&
		 (d1 > 0 && d1 < 32 && d2 > 0 && d2 < 32) &&
		 (h1 >= 0 && h1 < 24 && h2 >= 0 && h2 < 24) &&
		 (i1 >= 0 && i1 < 60 && i2 >= 0 && i2 < 60)) ||
		 ((m1 == 4 || m1 == 6 || m1 == 9 || m1 == 11) && d1 > 30) || 
		 ((m2 == 4 || m2 == 6 || m2 == 9 || m2 == 11) && d2 > 30) ||
		 ((m1 == 1 || m1 == 3 || m1 == 5 || m1 == 7 || m1 == 8 || m1 == 10 || m1 == 12) && d1 > 31) || 
		 ((m2 == 1 || m2 == 3 || m2 == 5 || m2 == 7 || m2 == 8 || m2 == 10 || m2 == 12) && d2 > 31) ||
		 (isLeapYear(y1) && m1 == 2 && d1 > 29) || (isLeapYear(y2) && m2 == 2 && d2 > 29) ||
		 (!isLeapYear(y1) && m1 == 2 && d1 > 28) || (!isLeapYear(y2) && m2 == 2 && d2 > 28) ||
		 (y1 == y2 && m1 > m2) || (y1 == y2 && m1 == m2 && d1 > d2) || (y1 == y2 && m1 == m2 && d1 == d2 && h1 > h2) ||
		 (y1 == y2 && m1 == m2 && d1 == d2 && h1 == h2 && i1 > i2)
		 )
		 return 0;
	else return 1;
}

int energyConsumption(int y1, int m1, int d1, int h1, int i1,
							 int y2, int m2, int d2, int h2, int i2, long long int *consumption)
{
	int flag = 0;
	// long long int pidor = 0;

	if (!isValid(y1, m1, d1, h1, i1, y2, m2, d2, h2, i2)) return 0;

	int minutes = minutesCount(i1, i2, &flag);
	printf("minutes = %d\n", minutes);
	int hours = hoursCount(h1, h2, &flag);
	printf("hours = %d\n", hours);
	int days = daysCount(d1, d2, m1, &flag);
	printf("days = %d\n", days);
	int months = monthsCount(m1, m2, i1, i2, h1, h2, d1, d2, &minutes, &hours, &days, &flag);
	printf("months = %d\n", months);
	long long int years = yearsCount(y1, y2, &flag);
	printf("years = %lld\n", years);
	long long int leap_count = leapCount(y1, y2, m1, m2);
	printf("leap = %lld\n", leap_count);
	// pidor = leap_count * DAY;
	// printf("pidorasy zaebali! = %lld\n", pidor);
	*consumption = minutes + hours + days + months + years + leap_count * DAY;

	return 1;
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
	long long int consumption;

	// energyConsumption(2000, 10, 31, 0, 0, 2000, 12, 24, 0, 0, &consumption);
	// printf("%lld\n", consumption);

	// energyConsumption(1861, 8, 30, 4, 59, 2016, 8, 4, 11, 21, &consumption);
	// printf("%lld\n", consumption);

	energyConsumption(1996, 2, 28, 4, 59, 2100, 9, 4, 11, 21, &consumption);
	printf("%lld\n", consumption);

	// assert(energyConsumption(2000, 3, 1, 0, 0,
	// 								 2025, 4, 1, 0, 0, &consumption) == 1 &&
	// 		 consumption == 2683421532LL);

	// assert(energyConsumption(1861, 8, 30, 4, 59,
	// 								 2016, 8, 4, 11, 21, &consumption) == 1 &&
	// 		 consumption == 16573617784LL); !!!!!!
	// assert(energyConsumption(1996, 2, 28, 4, 59,
	// 								 2100, 9, 4, 11, 21, &consumption) == 1 &&
	// 		 consumption == 11180707866LL);
	// assert(energyConsumption(2391, 6, 5, 0, 12,
	// 								 2425, 2, 28, 3, 54, &consumption) == 1 &&
	// 		 consumption == 3608986441LL);

	// assert(energyConsumption(1900, 1, 1, 13, 15,
	// 								 2100, 10, 5, 11, 21, &consumption) == 1 &&
	// 		 consumption == 21476135651LL);
	// assert(energyConsumption(1899, 1, 1, 13, 21,
	// 								 2199, 10, 5, 11, 20, &consumption) == 1 &&
	// 		 consumption == 32173502489LL);

	// assert(energyConsumption(2021, 10, 1, 13, 15,
	// 								 2021, 10, 1, 18, 45, &consumption) == 1 &&
	// 		 consumption == 67116LL);
	// assert(energyConsumption(2021, 10, 1, 13, 15,
	// 								 2021, 10, 2, 11, 20, &consumption) == 1 &&
	// 		 consumption == 269497LL);
	// assert(energyConsumption(2021, 1, 1, 13, 15,
	// 								 2021, 10, 5, 11, 20, &consumption) == 1 &&
	// 		 consumption == 81106033LL);
	// assert(energyConsumption(2024, 1, 1, 13, 15,
	// 								 2024, 10, 5, 11, 20, &consumption) == 1 &&
	// 		 consumption == 81398919LL);
	// assert(energyConsumption(1900, 1, 1, 13, 15,
	// 								 1900, 10, 5, 11, 20, &consumption) == 1 &&
	// 		 consumption == 81106033LL);
	// assert(energyConsumption(2021, 10, 1, 0, 0,
	// 								 2021, 10, 1, 12, 0, &consumption) == 1 &&
	// 		 consumption == 146443LL);
	// assert(energyConsumption(2021, 10, 1, 0, 15,
	// 								 2021, 10, 1, 0, 25, &consumption) == 1 &&
	// 		 consumption == 2035LL);
	// assert(energyConsumption(2021, 10, 1, 12, 0,
	// 								 2021, 10, 1, 12, 0, &consumption) == 1 &&
	// 		 consumption == 0LL);
	// assert(energyConsumption(2021, 10, 1, 12, 0,
	// 								 2021, 10, 1, 12, 1, &consumption) == 1 &&
	// 		 consumption == 204LL);
	// assert(energyConsumption(2021, 11, 1, 12, 0,
	// 								 2021, 10, 1, 12, 0, &consumption) == 0);
	// assert(energyConsumption(2021, 10, 32, 12, 0,
	// 								 2021, 11, 10, 12, 0, &consumption) == 0);
	// assert(energyConsumption(2100, 2, 29, 12, 0,
	// 								 2100, 2, 29, 12, 0, &consumption) == 0);
	// assert(energyConsumption(2400, 2, 29, 12, 0,
	// 								 2400, 2, 29, 12, 0, &consumption) == 1 &&
	// 		 consumption == 0LL);
	return 0;
}
#endif /* __PROGTEST__ */
