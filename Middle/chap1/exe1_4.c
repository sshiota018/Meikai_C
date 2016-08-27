/*------------------------------------------------*/
/* ���K1-4 3�`999�܂ł�3�̔{�������ăQ�[��        */
/*------------------------------------------------*/
/* ���Ă����鐔��3�ȏ�999�ȉ���3�̔{��(3,6,9,..., */ 
/* 999)�Ƃ���<<�����ăQ�[��>>���쐬����B         */
/* 3�̔{���łȂ��l�����͂��ꂽ�ꍇ�ɁA�������ɃQ�[*/
/* �����I��������̂ƁA��r���ʂ�\�������ē��͂� */
/* ����(���͉񐔂Ƃ��ăJ�E���g���Ȃ�)���̂�2����*/
/* �邱�ƁB                                       */
/* �v���[�������͂ł���ő�̉񐔂��A�ǂ̂��炢�� */
/* ����ΓK���ł���̂����l�@���邱�ƁB           */
/*------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* �g�p�萔�錾 */
#define NUM_MIN	3	/* ����l */
#define NUM_MAX 999	/* �����l */
#define CNT_MAX 10	/* ���s�� */
#define TIMES	3	/* �{�� */

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
	char C_ret;		/* */
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
	while( C_count < CNT_MAX && C_flag == FAILED )
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
	printf("          3�̔{�����ăQ�[�� v1          \n");
	printf("----------------------------------------\n");
	printf("�E%3d�`%3d�͈̔͂̐����𓖂Ă悤�I\n",lim.i_min, lim.i_max);
	printf("�E������3�̔{���ł��B\n");
	printf("�E3�̔{���ȊO���o�͂����瑦�E�I�E���I�I\n");
	printf("\n");
	return;
}

/* �������F�����ăQ�[���͈̔͐ݒ� */
static void num_init(struct C_List * lim)
{
	lim->i_min = NUM_MIN;
	lim->i_max = NUM_MAX;

	return;
}

/* ����l�̐ݒ� */
static int get_answer(struct C_List lim)
{
	int ans;	/* ����l */
	int sum = 0;		/* �ݒ�p�ϐ�1: sum */
	int ave = 1;		/* �ݒ�p�ϐ�2: average */
	int mod = 0;		/* �ݒ�p�ϐ�3: mod */
	
	ans = NUM_MIN-1;

	/* ����l�v�Z */
	do{
		if ( lim.i_min <= 0 && lim.i_max <= 0 ){	/* �ŏ��l:��, �ő�l:�� */
			ans = -1 * (rand() % abs(lim.i_min));	/* ��Βl�̑傫���l�̏�] */
		}
		else if ( lim.i_min <= 0 && lim.i_max > 0 ){	/* �ŏ��l:��, �ő�l:�� */
			sum = abs(lim.i_min) + lim.i_max;
			ave = sum / 2;
			ans = (rand() % (sum+1)) - ave;
		}
		else if ( lim.i_min > 0 && lim.i_max > 0 ){	/* �ŏ��l:��, �ő�l:�� */
			ans = rand() % lim.i_max;		/* ��Βl�̑傫���l�̏�] */

		}
		else{						/* ���̑��̏�� */
			/* fall through */
		}

		mod = ans % TIMES;		/* ����l��3�̔{����? */

	}while( ans < lim.i_min && ans > lim.i_max && mod == 0 );

	return ans;
}

/* ���͎�t */
static char num_input(int * input, char cnt, struct C_List lim)
{
	char ret;	/* �߂�l */
			/* ����I��: SUCCESS, �ُ�I��: FAILED */
	int  mod;	/* ���͒l����p�ϐ�: 3�̏�] */

	printf("%3d�`%3d�͈̔͂�3�̔{������͂��Ă�������\n", lim.i_min, lim.i_max);

	printf("%2d��ځF�@�������Ȃ��H�F",cnt);
	scanf("%d",input);
	printf("���́�%d\n",*input);

	/* ���͒l�̊m�F */
	/* ���͒l�͔͈͓���? */
	if ( *input >= lim.i_min && *input <= lim.i_max ){
		/* ���͒l��3�̔{����? */
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
