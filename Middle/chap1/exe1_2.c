/*-------------------------------------*/
/* 演習1-2 おみくじ ver2               */ 
/*-------------------------------------*/
/* 前問で作成したプログラムを、出る運勢*/
/* が均等とならないように改良したプログ*/
/* ラムを作成せよ。                    */
/* たとえば、[末吉][凶][大凶]を出にくく*/
/* するとよい。                        */
/*-------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* omikuji number */
/* 大吉:  0～ 9
 * 中吉: 10～24
 * 吉　: 25～44
 * 末吉: 45～54
 * 凶　: 55～64
 * 大凶: 65～69
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
		printf("NUM %2d : [大吉]\n", ans);
	else if ( ans >= CHUKICHI_MIN && ans < KICHI_MIN )
		printf("NUM %2d : [中吉]\n", ans);
	else if ( ans >= KICHI_MIN && ans < SUEKICHI_MIN )
		printf("NUM %2d : [吉]\n", ans);
	else if ( ans >= SUEKICHI_MIN && ans < KYO_MIN )
		printf("NUM %2d : [末吉]\n", ans);
	else if ( ans >= KYO_MIN && ans < DAIKYO_MIN )
		printf("NUM %2d : [凶]\n", ans);
	else if ( ans >= DAIKYO_MIN && ans < (OMIKUJI_MAX_NUM-1) )
		printf("NUM %2d : [大凶]\n", ans);
	else 
		printf("NUM %2d : [は・ず・れ]\n", ans);

	return;
}
