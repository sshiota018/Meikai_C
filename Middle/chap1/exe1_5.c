/*------------------------------------------------*/
/* ���K1-5 �����͈͌���̐����ăQ�[��             */
/*------------------------------------------------*/
/* ���Ă����鐔�͈̔͂����O�Ɍ��肷��̂ł͂Ȃ��A */
/* �v���O�������s���ɗ����Ō��肷��<<�����ăQ�[��>*/
/* >���쐬����B                                  */
/* ���Ƃ��΁A�������ē���ꂽ2�̗�����23��8,124 */
/* �ł���΁A23�ȏ�8124�ȉ��̐��𓖂Ă�����悤�� */
/* ����B                                         */
/* �Ȃ��A�v���[�������͂ł���ő�̉񐔂́A���Ă� */
/* ���鐔�͈̔͂ɉ����ēK�؂Ȓl�Ɏ����I��(�v���O��*/
/* �����ł̌v�Z�ɂ����)�ݒ肷�邱�ƁB            */
/*------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* �g�p�萔�錾 */
//#define NUM_MIN	3	/* ����l */
//#define NUM_MAX 999	/* �����l */
//#define CNT_MAX 10	/* ���s�� */
//#define TIMES	3	/* �{�� */
/* ���s�񐔃��x��(4�i�K) */
#define LEVEL_EASY 5
#define LEVEL_NORMAL 10
#define LEVEL_HARD 20
#define LEVEL_VERYHARD 30

/* ����/���s��` */
enum{
	FAILED = 0,	/* ���s */
	SUCCESS		/* ���� */
};

/* �g�p�ϐ��錾 */
struct C_List{
	int i_min;	/* �����ăQ�[������l */
	int i_max;	/* �����ăQ�[�������l */
};

static char count_max = 127;	/* �����ăQ�[��*/

/* �����֐��錾 */
static void usage(struct C_List lim);
static void num_init(struct C_List * lim);
static int get_answer(struct C_List lim);
static char num_input(int * input, char cnt, struct C_List lim);
static char num_judge(int input, int ans);

/* Main ���W���[�� */
int main(void)
{
	/* Value */
	int I_input;		/* ���[�U�̓��͒l */
	int I_answer;		/* �����ăQ�[���̓��� */
	char C_count;		/* ���͉� */
	char C_flag;		/* �I���t���O */
	char C_ret;		/* �߂�l */
	struct C_List limit;	/* �����ăQ�[���̒l�͈̔� */

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
		/* ���͎�t */
		C_ret = num_input(&I_input, C_count, limit);
		/* ���͂��ُ�I��(=���͒l���s��)�������ꍇ */
		if ( C_ret == FAILED ){
			printf("���͂��s���̂��ߏI�����܂��B\n");
			break;
		}
		/* ���𔻒� */
		C_flag = num_judge(I_input, I_answer);
	}

	if ( C_flag == SUCCESS )
		printf("���Ȃ���%2d��ڂœ��Ă܂����B\n", C_count);
	else
		printf("������%3d�ł����B�c�O�I�I\n", I_answer);


	return 0;
}

/* Usage */
static void usage(struct C_List lim)
{
	printf("----------------------------------------\n");
	printf("          �����͈͐����ăQ�[��          \n");
	printf("----------------------------------------\n");
	printf("�E%3d�`%3d�͈̔͂̐����𓖂Ă悤�I\n\n",lim.i_min, lim.i_max);
	return;
}

/* �������F�����ăQ�[���͈̔͐ݒ� */
static void num_init(struct C_List * lim)
{
	int 		num1,num2;	/* �͈͒l�i�[�ϐ� */
	unsigned int	delta; 		/* ���s�񐔌���p�ϐ��F�͈͍��i�[*/
	int		tmp1,tmp2;	/* ��������p�ϐ��F�����i�[ */
	char		mod;		/* ��������p�ϐ��F��]�i�[ */

	/* �����擾 */
	num1 = rand();
	do{
		num2 = rand();
	}while( num1 == num2 );

	/* �K���ɕ������� */
	/* �ʗ�������������� */
	tmp1 = rand() % 100;
	do{
		tmp2 = rand() % 100;
	}while( tmp1 == tmp2 );
	
	mod = tmp1 % 2;
	if ( mod == 1 ) num1 = -1 * num1;
	mod = tmp2 % 2;
	if ( mod == 1 ) num2 = -1 * num2;

	/* �͈͐ݒ� */
	if ( num1 < num2 ){
		lim->i_min = num1;
		lim->i_max = num2;
	}
	else{
		lim->i_min = num2;
		lim->i_max = num1;
	}

	/* ���s�񐔌��� */
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

/* ����l�̐ݒ� */
static int get_answer(struct C_List lim)
{
	int ans;	/* ����l */
	int tmp;	/* �ݒ�p�ϐ�: �������� */
	int mod;	/* �ݒ�p�ϐ�: ��������� */
	ans = lim.i_min-1;

	printf("-----����l���蒆-----\n");
	/* ����l�v�Z */
	do{
		if ( lim.i_min <= 0 && lim.i_max <= 0 ){	/* �ŏ��l:��, �ő�l:�� */
			ans = -1 * (rand() % abs(lim.i_min));	/* ��Βl�̑傫���l�̏�] */
		}
		else if ( lim.i_min <= 0 && lim.i_max > 0 ){	/* �ŏ��l:��, �ő�l:�� */
			ans = rand() % lim.i_max;
			/* �K���ɐ��������� */
			/* �ʗ���������������Ŕ��f */
			do{
				tmp = rand();
			}while( tmp == ans );
			mod = tmp % 2;
			if ( tmp == 1 ) ans = -1 * ans;
		}
		else if ( lim.i_min > 0 && lim.i_max > 0 ){	/* �ŏ��l:��, �ő�l:�� */
			ans = rand() % lim.i_max;		/* ��Βl�̑傫���l�̏�] */
		}
		else{						/* ���̑��̏�� */
			/* fall through */
		}
	}while( ans < lim.i_min || ans > lim.i_max );		/* ����l�������l��菬���� or ����l���傫�� �� �Č��� */
	printf("--------����I�I------\n");

	return ans;
}

/* ���͎�t */
static char num_input(int * input, char cnt, struct C_List lim)
{
	char ret;	/* �߂�l */
			/* ����I��: SUCCESS, �ُ�I��: FAILED */

	printf("�c��%d�񂾂悧�I�I\n",count_max-cnt);
	do{
		printf("%3d�`%3d�͈̔͂̐�������͂��Ă�������\n", lim.i_min, lim.i_max);

		printf("%2d��ځF�@�������Ȃ��H�F",cnt);
		scanf("%d",input);
		printf("���́�%d\n",*input);

		/* ���͒l�̊m�F */
		/* ���͒l�͔͈͓���? */
		if ( *input >= lim.i_min && *input <= lim.i_max ){
			ret = SUCCESS;
		}
		else{
			ret = FAILED;
			printf("�͈͂킩���Ă邩�Ȃ��H\n");
		}
		
	}while( ret != SUCCESS );

	return ret;
}

/* �����Ĕ��� */
static char num_judge(int input, int ans)
{
	char flag;

	flag = FAILED;

	if ( input > ans ){
		printf("�����Ə������悧�I�I\n");
	}
	else if ( input < ans ){
		printf("�����Ƒ傫���悧�I�I\n");
	}
	else{
		printf("�������悧�I�I\n");
		flag = SUCCESS;
	}

	return flag;
}
