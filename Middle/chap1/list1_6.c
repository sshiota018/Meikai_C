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
		printf("<%2d���>", failed_cnt);
		printf("�������Ȃ��F");
		scanf("%d",&no);

		/* judge */
		if ( no > ans ){
			printf(" < �����Ə������悧�I�I\n");
			failed_cnt++;
		}
		else if ( no < ans ){
			printf(" < �����Ƒ傫���悧�I�I\n");
			failed_cnt++;
		}
		else{
			printf(" < �������悧\n");
			failed_cnt = 0;
		}

		/* aori */
		if ( failed_cnt > 5 )
			printf(" < ���v���Ȃ��H\n");

	} while ( no != ans );

	return 0;
}

void usage(void)
{
	printf("#------------------------------\n");
	printf("#          �����ăQ�[��\n");
	printf("#------------------------------\n");
	printf("�E0�`999�̐����𓖂ĂĂ��������B\n");
}
