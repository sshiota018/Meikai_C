#include <stdio.h>

int main(void)
{
	int no;
	int ans = 7;

	/* announce */
	printf("0�`9�̐����𓖂ĂĂ��������B\n\n");

	/* input integure */
	printf("�������ȁF");
	scanf("%d", &no);

	/* judge */
	if ( no > ans )
		printf("�����Ə������悧�I�I\n");
	else if( no < ans )
		printf("�����Ƒ傫���悧�I�I\n");
	else
		printf("�����ł����I�I\n");

	return 0;
}