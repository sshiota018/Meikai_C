#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int retry;

	/* generate seed */
	srand(time(NULL));

	printf("0�`RAND_MAX(%d)�̗����������\�ł��B\n", RAND_MAX);

	do {
		printf("\n����%d�𐶐����܂����B\n"rand());

		printf("������x�H...(1)�͂�  (2)�������F");
		scanf("%d",&retry);

	} while ( retry == 1 );

	return 0;
}