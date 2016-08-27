/*------------------------------------------------*/
/* ���K1-6 ���x���ݒ�ł��鐔���ăQ�[��           */
/*------------------------------------------------*/
/* �J�n���Ƀv���[���Ƀ��x����I��������<<�����ăQ */
/* �[��>>���쐬����B�Ⴆ�΁A�ȉ��̂悤�ɕ\������ */
/* �I�������邱�ƁB                               */
/*�@ ���x����I��ł�������                       */
/*   (1)1�`9                                      */
/*   (2)1�`99                                     */
/*   (3)1�`999                                    */
/*   (4)1�`9999                                   */
/*   �F                                           */
/*------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* �g�p�萔�錾 */
/* ���s�񐔃��x��(4�i�K) */
#define COUNT_NUM_EASY 5
#define COUNT_NUM_NORMAL 10
#define COUNT_NUM_HARD 20
#define COUNT_NUM_VERYHARD 30

/* ����/���s��` */
enum{
	FAILED = 0,	/* ���s */
	SUCCESS		/* ���� */
};

enum{
	DUMMY = 0,	/* (0) dummy */
	EASY,		/* (1) LEVEL_EASY */
	NORMAL,		/* (2) LEVEL_NORMAL */
	HARD,		/* (3) LEVEL_HARD */
	VERYHARD,	/* (4) LEVEL_VERYHARD */

	LEVEL_NUM_MAX	/* LEVEL �v�f�� */
};

/* �g�p�ϐ��錾 */
struct C_List{
	int i_min;	/* �����ăQ�[������l */
	int i_max;	/* �����ăQ�[�������l */
};

/* �����ăQ�[�� ���x�����̉���/����l */
struct C_List Level_Limit[LEVEL_NUM_MAX] =
{
	{    0,    0},  /* (0) dummy 		: 1 �`    2 */
	{    1,    9},	/* (1) LEVEL_EASY	: 1 �`    9 */
	{    1,   99},	/* (2) LEVEL_NORMAL	: 1 �`   99 */
	{    1,  999},	/* (3) LEVEL_HARD	: 1 �`  999 */
	{    1, 9999}	/* (4) LEVEL_VERY_HARD	: 1 �` 9999 */
};

/* �����ăQ�[�� ���x�����̎��s�� */
static const char Level_Count[LEVEL_NUM_MAX] =
{
	0,			/* (0) dummy */
	COUNT_NUM_EASY,		/* (1) LEVEL_EASY */
	COUNT_NUM_NORMAL,	/* (2) LEVEL_NORMAL */
	COUNT_NUM_HARD,		/* (3) LEVEL_HARD */
	COUNT_NUM_VERYHARD	/* (4) LEVEL_VERYHARD */
};

static char count_max;		/* �����ăQ�[�����s�񐔊i�[�ϐ� */

/* �����֐��錾 */
static void usage(void);
//static void usage(struct C_List lim);
static char num_init(struct C_List * lim);
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

	if ( C_ret == FAILED )
		printf("���x���I�����Ԉ���Ă��܂��B���x��(1)�`(4)�܂ŁA�����œ��͂��Ă��������B\n");
	else if ( C_flag == SUCCESS )
		printf("���Ȃ���%2d��ڂœ��Ă܂����B\n", C_count);
	else
		printf("������%3d�ł����B�c�O�I�I\n", I_answer);


	return 0;
}

/* Usage */
static void usage(void)
{
	printf("----------------------------------------\n");
	printf("              �����ăQ�[��              \n");
	printf("----------------------------------------\n");
	return;
}

//static void usage(struct C_List lim)
//{
//	printf("----------------------------------------\n");
//	printf("              �����ăQ�[��              \n");
//	printf("----------------------------------------\n");
//	printf("�E%3d�`%3d�͈̔͂̐����𓖂Ă悤�I\n\n",lim.i_min, lim.i_max);
//	return;
//}

/* �������F�����ăQ�[���͈̔͐ݒ� */
static char num_init(struct C_List * lim)
{
	int input;	/* ���͎�t */
	char ret;	/* �߂�l */
			/* ����I��: SUCCESS, �ُ�I��: FAILED */

	/* �����ăQ�[�� ���x���ݒ� */
	printf("�����ăQ�[���̃��x����I��ł��������B\n");
	printf("  (1) 1 �` 9 \n");
	printf("  (2) 1 �` 99 \n");
	printf("  (3) 1 �` 999 \n");
	printf("  (4) 1 �` 9999 \n");
	printf(" ���x���́H -> ");
	scanf("%d",&input);

	/* �͈̓`�F�b�N */
	switch( input ){
		/* ���x���� EASY, NORMAL, HARD, VERYHARD �̂Ƃ� */
		case EASY:
		case NORMAL:
		case HARD:
		case VERYHARD:
			*lim = Level_Limit[input];
			count_max = Level_Count[input];
			ret = SUCCESS;
			printf("���x��%d��I�����܂����B\n", input);
			printf("�E%3d�`%3d�͈̔͂̐����𓖂Ă悤�I\n\n",lim->i_min, lim->i_max);
			break;
		/* ���x������L�ȊO */
		case DUMMY:
		default:
			*lim = Level_Limit[DUMMY];
			count_max = Level_Count[DUMMY];
			ret = FAILED;
			break;

	}

	return ret;
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
