#include <stdio.h>

int main(void)
{
	int no;
	int ans = 7;

	/* announce */
	printf("0～9の整数を当ててください。\n\n");

	/* input integure */
	printf("いくつかな：");
	scanf("%d", &no);

	/* judge */
	if ( no > ans )
		printf("もっと小さいよぉ！！\n");
	else if( no < ans )
		printf("もっと大きいよぉ！！\n");
	else
		printf("正解ですぅ！！\n");

	return 0;
}