#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int retry;

	/* generate seed */
	srand(time(NULL));

	printf("0～RAND_MAX(%d)の乱数が生成可能です。\n", RAND_MAX);

	do {
		printf("\n乱数%dを生成しました。\n"rand());

		printf("もう一度？...(1)はい  (2)いいえ：");
		scanf("%d",&retry);

	} while ( retry == 1 );

	return 0;
}