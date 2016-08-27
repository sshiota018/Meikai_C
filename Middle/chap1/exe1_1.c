/*-------------------------------------*/
/* ���K1-1 ���݂���                    */ 
/*-------------------------------------*/
/* <<���݂���>>�̃v���O�������쐬����B*/
/* 0�`6�̗����𐶐����A���̒l�ɉ����āA*/
/* [��g][���g][���g][�g][���g][��]    */
/* [�勥]��\�����邱�ƁB              */
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
		printf("[��g]\n");
		break;
	case CHUKICHI:
		printf("[���g]\n");
		break;
	case KICHI:
		printf("[�g]\n");
		break;
	case SUEKICHI:
		printf("[���g]\n");
		break;
	case KYO:
		printf("[��]\n");
		break;
	case DAIKYO:
		printf("[�勥]\n");
		break;
	default:
		printf("[�́E���E��]\n");
		break;
	}

	return;
}
