/*-------------------------------------*/
/* ���K1-8 ����t�������ăQ�[��2       */ 
/*-------------------------------------*/
/* List1-8��do����for����p���ď�������*/
/* ���v���O�������쐬����B            */
/*-------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STAGE 10	/* �ő���͉� */

int main(void)
{
	int i;
	int stage;		/* ���͉� */
	int no;			/* �ǂݍ��񂾒l */
	int ans;		/* ���Ă����鐔 */
	int num[MAX_STAGE];	/* �ǂݍ��񂾒l�̗��� */

	/* ����ݒ� */
	srand(time(NULL));
	ans = rand()%1000;	/* 0�`999�̗������� */

	printf("0�`999�̐����𓖂ĂĂ��������B\n\n");

	/* ���C������ */
	for ( stage = 0; stage < MAX_STAGE; stage++ ){
		/* ���͎�t */
		printf("�c��%d��B�������Ȃ��H�F", MAX_STAGE-stage);
		scanf("%d",&no);
		num[stage] = no;	/* �����X�V */

		/* �q���g */
		if ( no > ans )		/* �������傫�� */
			printf("�@�@�����Ə������悧�I\n");
		else if (no < ans )	/* ������菬���� */
			printf("�@�@�����Ƒ傫���悧�I\n");
		else			/* �����ƈ�v */
			break;
	}

//	stage = 0;
//	do{
//		/* ���͎�t */
//		printf("�c��%d��B�������Ȃ��H�F", MAX_STAGE-stage);
//		scanf("%d",&no);
//		num[stage++] = no;	/* �����X�V */
//
//		/* �q���g */
//		if ( no > ans )
//			printf("�@�@�����Ə������悧�I\n");
//		else if (no < ans )
//			printf("�@�@�����Ƒ傫���悧�I\n");
//
//	}while( no != ans && stage < MAX_STAGE );

	/* ���� */
	if ( no != ans )
		printf("������%d���悧�I�I�c�O�I�I\n",ans);
	else
		printf("�������悧�I�I%d��œ��������悧�I�I\n",stage);

	puts("\n--- ���͗��� ---");
	for( i = 0; i < stage; i++ ){
		if ( num[i] - ans == 0 )
			printf(" %2d : %4d %4d\n", i+1, num[i], num[i]-ans);
		else
			printf(" %2d : %4d %+4d\n", i+1, num[i], num[i]-ans);
	}
	return 0;
}
