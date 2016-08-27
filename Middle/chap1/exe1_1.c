/*-------------------------------------*/
/* ‰‰K1-1 ‚¨‚İ‚­‚¶                    */ 
/*-------------------------------------*/
/* <<‚¨‚İ‚­‚¶>>‚ÌƒvƒƒOƒ‰ƒ€‚ğì¬‚¹‚æB*/
/* 0`6‚Ì—”‚ğ¶¬‚µA‚»‚Ì’l‚É‰‚¶‚ÄA*/
/* [‘å‹g][’†‹g][¬‹g][‹g][––‹g][‹¥]    */
/* [‘å‹¥]‚ğ•\¦‚·‚é‚±‚ÆB              */
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
		printf("[‘å‹g]\n");
		break;
	case CHUKICHI:
		printf("[’†‹g]\n");
		break;
	case KICHI:
		printf("[‹g]\n");
		break;
	case SUEKICHI:
		printf("[––‹g]\n");
		break;
	case KYO:
		printf("[‹¥]\n");
		break;
	case DAIKYO:
		printf("[‘å‹¥]\n");
		break;
	default:
		printf("[‚ÍE‚¸E‚ê]\n");
		break;
	}

	return;
}
