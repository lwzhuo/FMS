#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"struct.h"
#include"page.h"
#include"user.h"//ceshi
#include"film.h"//ceshi
int USERTYPE = 0;//0 δ��¼ 1 vip 2 ����Ա

int main()
{
	//createadmin(1, "admin", "admin");//����Ա�ʻ�����
	//printf("%d %d\n", sizeof(struct vipinfo), sizeof(struct filminfo));
	//init();//�����ļ���ʼ��
	//struct vipinfo vinfo;
	//vinfo.num = 0;
	//vinfo.singlevipsize = 48;
	//vinfo.nextid = 1;
	//FILE *f2 = fopen("vipinfo", "wb");
	//fwrite(&vinfo, sizeof(struct vipinfo), 1, f2);
	//fclose(f2);
	//printf("��ʼ�����\n");//TODO��ɼ��
	//viewvipinfo();//�鿴vip�û���Ϣ�ļ�����
	while (Homepage());
	//showUserlist();//��ʾ�û��б�
	return 0;
}
