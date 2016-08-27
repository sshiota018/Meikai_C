/*------------------------------------------------*/
/* 演習1-6 レベル設定できる数当てゲーム           */
/*------------------------------------------------*/
/* 開始時にプレーヤにレベルを選択させる<<数当てゲ */
/* ーム>>を作成せよ。例えば、以下のように表示して */
/* 選択させること。                               */
/*　 レベルを選んでください                       */
/*   (1)1～9                                      */
/*   (2)1～99                                     */
/*   (3)1～999                                    */
/*   (4)1～9999                                   */
/*   ：                                           */
/*------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 使用定数宣言 */
/* 試行回数レベル(4段階) */
#define COUNT_NUM_EASY 5
#define COUNT_NUM_NORMAL 10
#define COUNT_NUM_HARD 20
#define COUNT_NUM_VERYHARD 30

/* 成功/失敗定義 */
enum{
	FAILED = 0,	/* 失敗 */
	SUCCESS		/* 成功 */
};

enum{
	DUMMY = 0,	/* (0) dummy */
	EASY,		/* (1) LEVEL_EASY */
	NORMAL,		/* (2) LEVEL_NORMAL */
	HARD,		/* (3) LEVEL_HARD */
	VERYHARD,	/* (4) LEVEL_VERYHARD */

	LEVEL_NUM_MAX	/* LEVEL 要素数 */
};

/* 使用変数宣言 */
struct C_List{
	int i_min;	/* 数当てゲーム上限値 */
	int i_max;	/* 数当てゲーム下限値 */
};

/* 数当てゲーム レベル毎の下限/上限値 */
struct C_List Level_Limit[LEVEL_NUM_MAX] =
{
	{    0,    0},  /* (0) dummy 		: 1 ～    2 */
	{    1,    9},	/* (1) LEVEL_EASY	: 1 ～    9 */
	{    1,   99},	/* (2) LEVEL_NORMAL	: 1 ～   99 */
	{    1,  999},	/* (3) LEVEL_HARD	: 1 ～  999 */
	{    1, 9999}	/* (4) LEVEL_VERY_HARD	: 1 ～ 9999 */
};

/* 数当てゲーム レベル毎の試行回数 */
static const char Level_Count[LEVEL_NUM_MAX] =
{
	0,			/* (0) dummy */
	COUNT_NUM_EASY,		/* (1) LEVEL_EASY */
	COUNT_NUM_NORMAL,	/* (2) LEVEL_NORMAL */
	COUNT_NUM_HARD,		/* (3) LEVEL_HARD */
	COUNT_NUM_VERYHARD	/* (4) LEVEL_VERYHARD */
};

static char count_max;		/* 数当てゲーム試行回数格納変数 */

/* 内部関数宣言 */
static void usage(void);
//static void usage(struct C_List lim);
static char num_init(struct C_List * lim);
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
	char C_ret;		/* 戻り値 */
	struct C_List limit;	/* 数当てゲームの値の範囲 */

	usage();

	/* Initialize */
	I_input = 0; C_count = 0;
	C_flag = FAILED;
	C_ret = FAILED;
	srand(time(NULL));

	C_ret = num_init(&limit);
	
	I_answer = get_answer(limit);

	// usage(limit);

	/* Main Process */
	while( C_count < count_max && C_flag == FAILED )
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

	if ( C_ret == FAILED )
		printf("レベル選択が間違っています。レベル(1)～(4)まで、数字で入力してください。\n");
	else if ( C_flag == SUCCESS )
		printf("あなたは%2d回目で当てました。\n", C_count);
	else
		printf("正解は%3dでした。残念！！\n", I_answer);


	return 0;
}

/* Usage */
static void usage(void)
{
	printf("----------------------------------------\n");
	printf("              数当てゲーム              \n");
	printf("----------------------------------------\n");
	return;
}

//static void usage(struct C_List lim)
//{
//	printf("----------------------------------------\n");
//	printf("              数当てゲーム              \n");
//	printf("----------------------------------------\n");
//	printf("・%3d～%3dの範囲の整数を当てよう！\n\n",lim.i_min, lim.i_max);
//	return;
//}

/* 初期化：数当てゲームの範囲設定 */
static char num_init(struct C_List * lim)
{
	int input;	/* 入力受付 */
	char ret;	/* 戻り値 */
			/* 正常終了: SUCCESS, 異常終了: FAILED */

	/* 数当てゲーム レベル設定 */
	printf("数当てゲームのレベルを選んでください。\n");
	printf("  (1) 1 ～ 9 \n");
	printf("  (2) 1 ～ 99 \n");
	printf("  (3) 1 ～ 999 \n");
	printf("  (4) 1 ～ 9999 \n");
	printf(" レベルは？ -> ");
	scanf("%d",&input);

	/* 範囲チェック */
	switch( input ){
		/* レベルが EASY, NORMAL, HARD, VERYHARD のとき */
		case EASY:
		case NORMAL:
		case HARD:
		case VERYHARD:
			*lim = Level_Limit[input];
			count_max = Level_Count[input];
			ret = SUCCESS;
			printf("レベル%dを選択しました。\n", input);
			printf("・%3d～%3dの範囲の整数を当てよう！\n\n",lim->i_min, lim->i_max);
			break;
		/* レベルが上記以外 */
		case DUMMY:
		default:
			*lim = Level_Limit[DUMMY];
			count_max = Level_Count[DUMMY];
			ret = FAILED;
			break;

	}

	return ret;
}

/* 正解値の設定 */
static int get_answer(struct C_List lim)
{
	int ans;	/* 正解値 */
	int tmp;	/* 設定用変数: 符号決定 */
	int mod;	/* 設定用変数: 奇数か偶数か */
	ans = lim.i_min-1;

	printf("-----正解値決定中-----\n");
	/* 正解値計算 */
	do{
		if ( lim.i_min <= 0 && lim.i_max <= 0 ){	/* 最小値:負, 最大値:負 */
			ans = -1 * (rand() % abs(lim.i_min));	/* 絶対値の大きい値の剰余 */
		}
		else if ( lim.i_min <= 0 && lim.i_max > 0 ){	/* 最小値:負, 最大値:正 */
			ans = rand() % lim.i_max;
			/* 適当に正負をつける */
			/* 別乱数が奇数か偶数かで判断 */
			do{
				tmp = rand();
			}while( tmp == ans );
			mod = tmp % 2;
			if ( tmp == 1 ) ans = -1 * ans;
		}
		else if ( lim.i_min > 0 && lim.i_max > 0 ){	/* 最小値:正, 最大値:正 */
			ans = rand() % lim.i_max;		/* 絶対値の大きい値の剰余 */
		}
		else{						/* その他の状態 */
			/* fall through */
		}
	}while( ans < lim.i_min || ans > lim.i_max );		/* 正解値が下限値より小さい or 上限値より大きい → 再決定 */
	printf("--------決定！！------\n");

	return ans;
}

/* 入力受付 */
static char num_input(int * input, char cnt, struct C_List lim)
{
	char ret;	/* 戻り値 */
			/* 正常終了: SUCCESS, 異常終了: FAILED */

	printf("残り%d回だよぉ！！\n",count_max-cnt);
	do{
		printf("%3d～%3dの範囲の整数を入力してください\n", lim.i_min, lim.i_max);

		printf("%2d回目：　いくつかなぁ？：",cnt);
		scanf("%d",input);
		printf("入力→%d\n",*input);

		/* 入力値の確認 */
		/* 入力値は範囲内か? */
		if ( *input >= lim.i_min && *input <= lim.i_max ){
			ret = SUCCESS;
		}
		else{
			ret = FAILED;
			printf("範囲わかってるかなぁ？\n");
		}
		
	}while( ret != SUCCESS );

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
