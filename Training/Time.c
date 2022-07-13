#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int h1, h2, m1, m2, s1, s2, ms1, ms2, h, m, s, ms;

	printf("Zadejte cas t1:\n");

	if (scanf(" %d : %d : %d , %d", &h1, &m1, &s1, &ms1) != 4 || 
	(h1 < 0 || h1 > 23) || (m1 < 0 || m1 > 59) || (s1 < 0 || s1 > 59) || (ms1 < 0 || ms1 > 999))
	{
		printf("Nespravny vstup.\n");
		return 1;
	};


	printf("Zadejte cas t2:\n");

	if (scanf(" %d : %d : %d , %d", &h2, &m2, &s2, &ms2) != 4 ||
	(h2 < 0 || h2 > 23) || (m2 < 0 || m2 > 59) || (s2 < 0 || s2 > 59) || (ms2 < 0 || ms2 > 999))
	{
		printf("Nespravny vstup.\n");
		return 1;
	};


	if ((h2 == h1 && m2 >= m1 && s2 >= s1 && ms2 >= ms1) || h2 > h1) 
	{
		if (ms2 >= ms1)
		{
			ms = ms2 - ms1;
		}
		else if (ms2 < ms1)
		{
			ms = (ms2 + 1000) - ms1;
			s2--;
		};

		if (s2 >= s1)
		{
			s = s2 - s1;
		}
		else if (s2 < s1)
		{
			s = (s2 + 60) - s1;
			m2--;
		};

		if (m2 >= m1)
		{
			m = m2 - m1;
		}
		else if (m2 < m1)
		{
			m = (m2 + 60) - m1;
			h2--;
		};

		h = h2 - h1;

		printf("Doba: %2d:%02d:%02d,%03d\n", h, m, s, ms);
		return 0;
	}

	else 
	{
		printf("Nespravny vstup.\n");
		return 1;
	};
	

}