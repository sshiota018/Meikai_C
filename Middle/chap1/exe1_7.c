/*-------------------------------------*/
/* 演習1-7 履歴付き数当てゲーム        */ 
/*-------------------------------------*/
/* List1-8のプログラムでの入力履歴表示 */
/* では、正解との差が0であっても符号を */
/* 付けて表示するため、少々みっともな  */
/* い。0に対しては符号を付けないように */
/* 変更せよ。                          */
/*-------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STAGE 10	/* 最大入力回数 */

int main(void)
{
	int i;
	int stage;		/* 入力回数 */
	int no;			/* 読み込んだ値 */
	int ans;		/* 当てさせる数 */
	int num[MAX_STAGE];	/* 読み込んだ値の履歴 */

	/* 正解設定 */
	srand(time(NULL));
	ans = rand()%1000;	/* 0～999の乱数生成 */

	printf("0～999の整数を当ててください。\n\n");

	/* メイン処理 */
	stage = 0;
	do{
		/* 入力受付 */
		printf("残り%d回。いくつかなぁ？：", MAX_STAGE-stage);
		scanf("%d",&no);
		num[stage++] = no;	/* 履歴更新 */

		/* ヒント */
		if ( no > ans )
			printf("　　もっと小さいよぉ！\n");
		else if (no < ans )
			printf("　　もっと大きいよぉ！\n");

	}while( no != ans && stage < MAX_STAGE );

	/* 結果 */
	if ( no != ans )
		printf("正解は%dだよぉ！！残念！！\n",ans);
	else
		printf("正解だよぉ！！%d回で当たったよぉ！！\n",stage);

	puts("\n--- 入力履歴 ---");
	for( i = 0; i < stage; i++ ){
		if ( num[i] - ans == 0 )
			printf(" %2d : %4d %4d\n", i+1, num[i], num[i]-ans);
		else
			printf(" %2d : %4d %+4d\n", i+1, num[i], num[i]-ans);
	}
	return 0;
}
