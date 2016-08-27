/*------------------------------------------------*/
/* ���K1-3 -999�`999�܂ł̐����ăQ�[��            */
/*------------------------------------------------*/
/* ���Ă����鐔��-999�ȏ�999�ȉ��̐����Ƃ���<<����*/
/* �ăQ�[��>>���쐬����B                         */
/* �v���[�������͂ł���ő�̉񐔂��A�ǂ̂��炢�� */
/* ����ΓK���ł���̂����l�@���邱�ƁB           */
/*------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* �g�p�萔�錾 */
#define NUM_MIN	-999	/* ����l */
#define NUM_MAX 999	/* �����l */
#define CNT_MAX 10	/* ���s�� */

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
static void num_input(int * input, char cnt, struct C_List lim);
static char num_judge(int input, int ans);

/* Main ���W���[�� */
int main(void)
{
	/* Value */
	int I_input;			/* ���[�U�̓��͒l */
	int I_answer;		/* �����ăQ�[���̓��� */
	char C_count;			/* ���͉� */
	char C_flag;			/* �I���t���O */
	struct C_List limit;	/* �����ăQ�[���̒l�͈̔� */

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
		printf("���Ȃ���%2d��ڂœ��Ă܂����B\n", C_count);
	else
		printf("������%3d�ł����B�c�O�I�I\n", I_answer);


	return 0;
}

/* Usage */
static void usage(struct C_List lim)
{
	printf("----------------------------------------\n");
	printf("              �����ăQ�[��              \n");
	printf("----------------------------------------\n");
	printf("�E%3d�`%3d�͈̔͂̐����𓖂Ă悤�I\n\n",lim.i_min, lim.i_max);

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
	int ans = -1000;
	int sum = 0;
	int ave = 1;
	
	do{
		if ( lim.i_min <= 0 && lim.i_max <= 0 ){	/* �ŏ��l:��, �ő�l:�� */
			sum = abs(lim.i_min) + abs(lim.i_max);
			ave = sum / 2;
			ans = (rand() % sum) - ave;
		}
		else if ( lim.i_min <= 0 && lim.i_max > 0 ){	/* �ŏ��l:��, �ő�l:�� */
			sum = abs(lim.i_min) + lim.i_max;
			ave = sum / 2;
			ans = (rand() % (sum+1)) - ave;
		}
		else if ( lim.i_min > 0 && lim.i_max > 0 ){	/* �ŏ��l:��, �ő�l:�� */
			sum = lim.i_min + lim.i_max;
			ave = sum / 2;
			ans = (rand() % sum) - ave;
		}
		else{						/* ���̑��̏�� */
			/* fall through */
		}
	}while( ans < lim.i_min && ans > lim.i_max );

	return ans;
}

/* ���͎�t */
static void num_input(int * input, char cnt, struct C_List lim)
{
	char flag;

	flag = SUCCESS;
	do{
		if ( flag == FAILED ){
			printf("%3d�`%3d�̐�������͂��Ă�������\n", lim.i_min, lim.i_max);
		}
		flag = FAILED;

		printf("%2d��ځF�@�������Ȃ��H�F",cnt);
		scanf("%d",input);
		printf("���́�%d\n",*input);
	}while( *input < lim.i_min && *input > lim.i_max );

	return;
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
		printf("�����Ƃ��������悧�I�I\n");
	}
	else{
		printf("�������悧�I�I\n");
		flag = SUCCESS;
	}

	return flag;
}
