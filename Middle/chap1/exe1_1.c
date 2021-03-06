/*-------------------------------------*/
/* 演習1-1 おみくじ                    */ 
/*-------------------------------------*/
/* <<おみくじ>>のプログラムを作成せよ。*/
/* 0〜6の乱数を生成し、その値に応じて、*/
/* [大吉][中吉][小吉][吉][末吉][凶]    */
/* [大凶]を表示すること。              */
/*-------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* omikuji number */
enum{
	DAIKICHI	= 0,
	CHUKICHI,
	SHOKICHI,
	KICHI,
	SUEKICHI,
	KYO,
	DAIKYO,
	MAX_NUM
};

static void omikuji(void);

int main(void)
{
	/* Initialize */
	srand(time(NULL));
	omikuji();

	return 0;
}


static void omikuji(void)
{
	char ans;

	ans = rand() % MAX_NUM;

	/* Judge */
	switch(ans){
	case DAIKICHI:
		printf("[大吉]\n");
		break;
	case CHUKICHI:
		printf("[中吉]\n");
		break;
	case KICHI:
		printf("[吉]\n");
		break;
	case SUEKICHI:
		printf("[末吉]\n");
		break;
	case KYO:
		printf("[凶]\n");
		break;
	case DAIKYO:
		printf("[大凶]\n");
		break;
	default:
		printf("[は・ず・れ]\n");
		break;
	}

	return;
}
