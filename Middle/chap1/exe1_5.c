/*------------------------------------------------*/
/* 演習1-5 乱数範囲決定の数当てゲーム             */
/*------------------------------------------------*/
/* 当てさせる数の範囲を事前に決定するのではなく、 */
/* プログラム実行時に乱数で決定する<<数当てゲーム>*/
/* >を作成せよ。                                  */
/* たとえば、生成して得られた2つの乱数が23と8,124 */
/* であれば、23以上8124以下の数を当てさせるように */
/* する。                                         */
/* なお、プレーヤが入力できる最大の回数は、当てさ */
/* せる数の範囲に応じて適切な値に自動的に(プログラ*/
/* ム内での計算によって)設定すること。            */
/*------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 使用定数宣言 */
//#define NUM_MIN	3	/* 上限値 */
//#define NUM_MAX 999	/* 下限値 */
//#define CNT_MAX 10	/* 試行回数 */
//#define TIMES	3	/* 倍数 */
/* 試行回数レベル(4段階) */
#define LEVEL_EASY 5
#define LEVEL_NORMAL 10
#define LEVEL_HARD 20
#define LEVEL_VERYHARD 30

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

static char count_max = 127;	/* 数当てゲーム*/

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
	char C_ret;		/* 戻り値 */
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
	printf("          乱数範囲数当てゲーム          \n");
	printf("----------------------------------------\n");
	printf("・%3d～%3dの範囲の整数を当てよう！\n\n",lim.i_min, lim.i_max);
	return;
}

/* 初期化：数当てゲームの範囲設定 */
static void num_init(struct C_List * lim)
{
	int 		num1,num2;	/* 範囲値格納変数 */
	unsigned int	delta; 		/* 試行回数決定用変数：範囲差格納*/
	int		tmp1,tmp2;	/* 符号決定用変数：乱数格納 */
	char		mod;		/* 符号決定用変数：剰余格納 */

	/* 乱数取得 */
	num1 = rand();
	do{
		num2 = rand();
	}while( num1 == num2 );

	/* 適当に符号決定 */
	/* 別乱数が奇数か偶数か */
	tmp1 = rand() % 100;
	do{
		tmp2 = rand() % 100;
	}while( tmp1 == tmp2 );
	
	mod = tmp1 % 2;
	if ( mod == 1 ) num1 = -1 * num1;
	mod = tmp2 % 2;
	if ( mod == 1 ) num2 = -1 * num2;

	/* 範囲設定 */
	if ( num1 < num2 ){
		lim->i_min = num1;
		lim->i_max = num2;
	}
	else{
		lim->i_min = num2;
		lim->i_max = num1;
	}

	/* 試行回数決定 */
	delta = abs((lim->i_max) - (lim->i_min));
	if ( delta > 0 && delta <= 100 ){
		count_max = LEVEL_EASY;
	}
	else if ( delta > 100 && delta <= 1000 ){
		count_max = LEVEL_NORMAL;
	}
	else if ( delta > 1000 && delta <= 10000 ){
		count_max = LEVEL_HARD;
	}
	else{
		count_max = LEVEL_VERYHARD;
	}

	return;
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
