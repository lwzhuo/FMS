#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"struct.h"
#include"check.h"
#include"user.h"
extern USERTYPE;
void registration()
{
	char name[20], pass[16], c;
	int id = 1, i = 0;
	printf("�������û���__________\b\b\b\b\b\b\b\b\b\b");
	gets(name);
	printf("����������__________\b\b\b\b\b\b\b\b\b\b");
	while (c = _getch())//�û���������
	{
		if (c != 13)
		{
			putchar('*');
			pass[i++] = c;
		}
		else
		{
			pass[i] = '\0';
			break;
		}
	}
	createvip(1, name, pass);
}
void createvip(int id, char * username, char * password)
{
	char c;
	FILE * fa = fopen("vipuser", "ab+");
	FILE * fb = fopen("vipinfo", "rb");
	struct vip a;
	struct vipinfo b;
	fread(&b, sizeof(struct vipinfo), 1, fb);
	a.id = b.nextid;
	strcpy(a.name, username);
	strcpy(a.password, password);
	a.balance = 0;//��ʼ���˻�����Ӱ��
	a.filmnum = 0;
	fwrite(&a, sizeof(struct vip), 1, fa);
	fclose(fa);
	fclose(fb);
	fa = NULL;
	fb = NULL;
	printf("\nע��ɹ�!����(1)\n");
	while (c = checkselect() != '1');
	return;
}
void viplogin()
{
	struct vip a;
	char name[20], pass[16], c;
	int id = 1, i = 0, flag = 1;
	FILE *f = fopen("vipuser", "rb");
	fread(&a, sizeof(struct admin), 1, f);
	fclose(f);
	while (flag)
	{
		system("cls");
		printf("�������û���__________\b\b\b\b\b\b\b\b\b\b");
		gets(name);
		printf("����������__________\b\b\b\b\b\b\b\b\b\b");
		while (c = _getch())//�������벿��
		{
			if (c != 13)
			{
				putchar('*');
				pass[i++] = c;
			}
			else
			{
				pass[i] = '\0';
				break;
			}
		}
		if (strcmp(a.name, name) == 0 && strcmp(a.password, pass) == 0)
		{
			printf("\n��¼�ɹ�,��ӭ%s %s\n", a.name, a.password);//TODO
			USERTYPE = 1;
			flag = 0;
			printf("\n��¼�ɹ�!����(1)\n");
			while (c = checkselect() != '1');
			return;
		}
		else
		{
			printf("\n�û������������,������!%s %s %s %s\n", a.name, a.password, name, pass);//TODO
			if (flag++ == 3)//���ε�¼����
			{
				printf("�û����������������!����(1)\n");
				while (c = checkselect() != '1');
				return;
			}
		}
	}
}
void adminlogin()
{
	struct admin a;
	char name[20], pass[16], c;
	int id = 1, i = 0;
	FILE *f = fopen("adminuser", "rb");
	fread(&a, sizeof(struct admin), 1, f);
	fclose(f);
	printf("�������û���__________\b\b\b\b\b\b\b\b\b\b");
	gets(name);
	printf("\n����������__________\b\b\b\b\b\b\b\b\b\b");
	while (c = _getch())
	{
		if (c != 13)
		{
			putchar('*');
			pass[i++] = c;
		}
		else
		{
			pass[i] = '\0';
			break;
		}
	}
	if (strcmp(a.name, name) == 0 && strcmp(a.password, pass) == 0)
	{
		printf("��¼�ɹ�!\n");
		USERTYPE = 2;
	}
	else
		printf("��¼ʧ��!\n");
	printf("����(1)\n");
	while (c = checkselect() != '1');
	return;
}
void createadmin(int id, char * username, char * password)
{
	FILE * f = fopen("adminuser", "ab+");
	struct admin a;
	a.id = id;
	strcpy(a.name, username);
	strcpy(a.password, password);
	fwrite(&a, sizeof(struct admin), 1, f);
	fclose(f);
}
void changevipinfo(int newnum, int newid)//δ����
{
	struct vipinfo vf;
	FILE * newfile = fopen("tempvipinfo", "wb");
	FILE * oldfile = fopen("vipinfo", "wb");
	fread(&vf, sizeof(struct vipinfo), 1, oldfile);
	vf.num = newnum;
	vf.nextid = newid;
	fwrite(&vf, sizeof(struct vipinfo), 1, newfile);
	fclose(oldfile);
	fclose(oldfile);
	oldfile = NULL;
	newfile = NULL;
	remove("vipinfo");
	rename("tempvipinfo", "vipinfo");
}