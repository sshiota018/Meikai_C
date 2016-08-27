/*------------------------------------------------*/
/* 演習1-3 -999～999までの数当てゲーム            */
/*------------------------------------------------*/
/* 当てさせる数を-999以上999以下の整数とした<<数当*/
/* てゲーム>>を作成せよ。                         */
/* プレーヤが入力できる最大の回数が、どのくらいで */
/* あれば適当であるのかも考察すること。           */
/*------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 使用定数宣言 */
#define NUM_MIN	-999	/* 上限値 */
#define NUM_MAX 999	/* 下限値 */
#define CNT_MAX 10	/* 試行回数 */

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
static void num_input(int * input, char cnt, struct C_List lim);
static char num_judge(int input, int ans);

/* Main モジュール */
int main(void)
{
	/* Value */
	int I_input;			/* ユーザの入力値 */
	int I_answer;		/* 数当てゲームの答え */
	char C_count;			/* 入力回数 */
	char C_flag;			/* 終了フラグ */
	struct C_List limit;	/* 数当てゲームの値の範囲 */

	/* Initialize */
	I_input = 0; C_count = 0;
	C_flag = FAILED;
	srand(time(NULL));
	num_init(&limit);
	I_answer = get_answer(limit);

	usage(limit);

	/* Main Process */
	while( C_count < CNT_MAX && C_flag == FAILED )
	{
		C_count++;
		num_input(&I_input, C_count, limit);
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
	printf("              数当てゲーム              \n");
	printf("----------------------------------------\n");
	printf("・%3d～%3dの範囲の整数を当てよう！\n\n",lim.i_min, lim.i_max);

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
	int ans = -1000;
	int sum = 0;
	int ave = 1;
	
	do{
		if ( lim.i_min <= 0 && lim.i_max <= 0 ){	/* 最小値:負, 最大値:負 */
			sum = abs(lim.i_min) + abs(lim.i_max);
			ave = sum / 2;
			ans = (rand() % sum) - ave;
		}
		else if ( lim.i_min <= 0 && lim.i_max > 0 ){	/* 最小値:負, 最大値:正 */
			sum = abs(lim.i_min) + lim.i_max;
			ave = sum / 2;
			ans = (rand() % (sum+1)) - ave;
		}
		else if ( lim.i_min > 0 && lim.i_max > 0 ){	/* 最小値:正, 最大値:正 */
			sum = lim.i_min + lim.i_max;
			ave = sum / 2;
			ans = (rand() % sum) - ave;
		}
		else{						/* その他の状態 */
			/* fall through */
		}
	}while( ans < lim.i_min && ans > lim.i_max );

	return ans;
}

/* 入力受付 */
static void num_input(int * input, char cnt, struct C_List lim)
{
	char flag;

	flag = SUCCESS;
	do{
		if ( flag == FAILED ){
			printf("%3d～%3dの整数を入力してください\n", lim.i_min, lim.i_max);
		}
		flag = FAILED;

		printf("%2d回目：　いくつかなぁ？：",cnt);
		scanf("%d",input);
		printf("入力→%d\n",*input);
	}while( *input < lim.i_min && *input > lim.i_max );

	return;
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
		printf("もっとおおきいよぉ！！\n");
	}
	else{
		printf("正解だよぉ！！\n");
		flag = SUCCESS;
	}

	return flag;
}
