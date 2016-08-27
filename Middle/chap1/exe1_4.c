/*------------------------------------------------*/
/* 演習1-4 3～999までの3の倍数数当てゲーム        */
/*------------------------------------------------*/
/* 当てさせる数を3以上999以下の3の倍数(3,6,9,..., */ 
/* 999)とした<<数当てゲーム>>を作成せよ。         */
/* 3の倍数でない値が入力された場合に、ただちにゲー*/
/* ムを終了するものと、比較結果を表示せず再入力さ */
/* せる(入力回数としてカウントしない)ものの2つを作*/
/* ること。                                       */
/* プレーヤが入力できる最大の回数が、どのくらいで */
/* あれば適当であるのかも考察すること。           */
/*------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 使用定数宣言 */
#define NUM_MIN	3	/* 上限値 */
#define NUM_MAX 999	/* 下限値 */
#define CNT_MAX 10	/* 試行回数 */
#define TIMES	3	/* 倍数 */

/* 成功/失敗定義 */
enum{
	FAILED = 0,	/* 失敗 */
	SUCCESS		/* 成功 */
};

/* 使用変数宣言 */
struct C_List{
	int i_min;	/* 数当てゲーム上限値 */
	int i_max;	/* 数当てゲーム下限値 */
};


/* 内部関数宣言 */
static void usage(struct C_List lim);
static void num_init(struct C_List * lim);
static int get_answer(struct C_List lim);
static char num_input(int * input, char cnt, struct C_List lim);
static char num_judge(int input, int ans);

/* Main モジュール */
int main(void)
{
	/* Value */
	int I_input;		/* ユーザの入力値 */
	int I_answer;		/* 数当てゲームの答え */
	char C_count;		/* 入力回数 */
	char C_flag;		/* 終了フラグ */
	char C_ret;		/* */
	struct C_List limit;	/* 数当てゲームの値の範囲 */

	/* Initialize */
	I_input = 0; C_count = 0;
	C_flag = FAILED;
	C_ret = FAILED;
	srand(time(NULL));
	num_init(&limit);
	I_answer = get_answer(limit);

	usage(limit);

	/* Main Process */
	while( C_count < CNT_MAX && C_flag == FAILED )
	{
		C_count++;
		/* 入力受付 */
		C_ret = num_input(&I_input, C_count, limit);
		/* 入力が異常終了(=入力値が不正)だった場合 */
		if ( C_ret == FAILED ){
			printf("入力が不正のため終了します。\n");
			break;
		}
		/* 正解判定 */
		C_flag = num_judge(I_input, I_answer);
	}

	if ( C_flag == SUCCESS )
		printf("あなたは%2d回目で当てました。\n", C_count);
	else
		printf("正解は%3dでした。残念！！\n", I_answer);


	return 0;
}

/* Usage */
static void usage(struct C_List lim)
{
	printf("----------------------------------------\n");
	printf("          3の倍数当てゲーム v1          \n");
	printf("----------------------------------------\n");
	printf("・%3d～%3dの範囲の整数を当てよう！\n",lim.i_min, lim.i_max);
	printf("・正解は3の倍数です。\n");
	printf("・3の倍数以外を出力したら即・終・了！！\n");
	printf("\n");
	return;
}

/* 初期化：数当てゲームの範囲設定 */
static void num_init(struct C_List * lim)
{
	lim->i_min = NUM_MIN;
	lim->i_max = NUM_MAX;

	return;
}

/* 正解値の設定 */
static int get_answer(struct C_List lim)
{
	int ans;	/* 正解値 */
	int sum = 0;		/* 設定用変数1: sum */
	int ave = 1;		/* 設定用変数2: average */
	int mod = 0;		/* 設定用変数3: mod */
	
	ans = NUM_MIN-1;

	/* 正解値計算 */
	do{
		if ( lim.i_min <= 0 && lim.i_max <= 0 ){	/* 最小値:負, 最大値:負 */
			ans = -1 * (rand() % abs(lim.i_min));	/* 絶対値の大きい値の剰余 */
		}
		else if ( lim.i_min <= 0 && lim.i_max > 0 ){	/* 最小値:負, 最大値:正 */
			sum = abs(lim.i_min) + lim.i_max;
			ave = sum / 2;
			ans = (rand() % (sum+1)) - ave;
		}
		else if ( lim.i_min > 0 && lim.i_max > 0 ){	/* 最小値:正, 最大値:正 */
			ans = rand() % lim.i_max;		/* 絶対値の大きい値の剰余 */

		}
		else{						/* その他の状態 */
			/* fall through */
		}

		mod = ans % TIMES;		/* 正解値は3の倍数か? */

	}while( ans < lim.i_min && ans > lim.i_max && mod == 0 );

	return ans;
}

/* 入力受付 */
static char num_input(int * input, char cnt, struct C_List lim)
{
	char ret;	/* 戻り値 */
			/* 正常終了: SUCCESS, 異常終了: FAILED */
	int  mod;	/* 入力値判定用変数: 3の剰余 */

	printf("%3d～%3dの範囲の3の倍数を入力してください\n", lim.i_min, lim.i_max);

	printf("%2d回目：　いくつかなぁ？：",cnt);
	scanf("%d",input);
	printf("入力→%d\n",*input);

	/* 入力値の確認 */
	/* 入力値は範囲内か? */
	if ( *input >= lim.i_min && *input <= lim.i_max ){
		/* 入力値は3の倍数か? */
		mod = *input % TIMES;
		if ( mod == 0 )
			ret = SUCCESS;
		else
			ret = FAILED;
	}
	else{
		ret = FAILED;
	}

	return ret;
}

/* 数当て判定 */
static char num_judge(int input, int ans)
{
	char flag;

	flag = FAILED;

	if ( input > ans ){
		printf("もっと小さいよぉ！！\n");
	}
	else if ( input < ans ){
		printf("もっと大きいよぉ！！\n");
	}
	else{
		printf("正解だよぉ！！\n");
		flag = SUCCESS;
	}

	return flag;
}
