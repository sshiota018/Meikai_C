#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void usage(void);

int main(void)
{
	int no;
	int ans;
	int failed_cnt = 1;

	/* generate seed */
	srand(time(NULL));
	ans = rand() % 1000;

	usage();

	do {
		/* intput */
		printf("<%2d回目>", failed_cnt);
		printf("いくつかなぁ：");
		scanf("%d",&no);

		/* judge */
		if ( no > ans ){
			printf(" < もっと小さいよぉ！！\n");
			failed_cnt++;
		}
		else if ( no < ans ){
			printf(" < もっと大きいよぉ！！\n");
			failed_cnt++;
		}
		else{
			printf(" < 正解だよぉ\n");
			failed_cnt = 0;
		}

		/* aori */
		if ( failed_cnt > 5 )
			printf(" < 大丈夫かなぁ？\n");

	} while ( no != ans );

	return 0;
}

void usage(void)
{
	printf("#------------------------------\n");
	printf("#          数当てゲーム\n");
	printf("#------------------------------\n");
	printf("・0～999の整数を当ててください。\n");
}
