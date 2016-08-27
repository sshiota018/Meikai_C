/*-------------------------------------*/
/* ���K1-2 ���݂��� ver2               */ 
/*-------------------------------------*/
/* �O��ō쐬�����v���O�������A�o��^��*/
/* ���ϓ��ƂȂ�Ȃ��悤�ɉ��ǂ����v���O*/
/* �������쐬����B                    */
/* ���Ƃ��΁A[���g][��][�勥]���o�ɂ���*/
/* ����Ƃ悢�B                        */
/*-------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* omikuji number */
/* ��g:  0�` 9
 * ���g: 10�`24
 * �g�@: 25�`44
 * ���g: 45�`54
 * ���@: 55�`64
 * �勥: 65�`69
 */
#define DAIKICHI_MIN	((unsigned char)0)
#define CHUKICHI_MIN	((unsigned char)10)
#define KICHI_MIN	((unsigned char)25)
#define SUEKICHI_MIN	((unsigned char)45)
#define KYO_MIN		((unsigned char)55)
#define DAIKYO_MIN	((unsigned char)65)
#define OMIKUJI_MAX_NUM	((unsigned char)70)

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
	unsigned char ans;

	ans = rand() % OMIKUJI_MAX_NUM;

	/* Judge */
	if ( ans >= DAIKICHI_MIN && ans < CHUKICHI_MIN )
		printf("NUM %2d : [��g]\n", ans);
	else if ( ans >= CHUKICHI_MIN && ans < KICHI_MIN )
		printf("NUM %2d : [���g]\n", ans);
	else if ( ans >= KICHI_MIN && ans < SUEKICHI_MIN )
		printf("NUM %2d : [�g]\n", ans);
	else if ( ans >= SUEKICHI_MIN && ans < KYO_MIN )
		printf("NUM %2d : [���g]\n", ans);
	else if ( ans >= KYO_MIN && ans < DAIKYO_MIN )
		printf("NUM %2d : [��]\n", ans);
	else if ( ans >= DAIKYO_MIN && ans < (OMIKUJI_MAX_NUM-1) )
		printf("NUM %2d : [�勥]\n", ans);
	else 
		printf("NUM %2d : [�́E���E��]\n", ans);

	return;
}
