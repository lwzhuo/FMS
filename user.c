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
	printf("请输入用户名__________\b\b\b\b\b\b\b\b\b\b");
	gets(name);
	printf("请输入密码__________\b\b\b\b\b\b\b\b\b\b");
	while (c = _getch())//用户密码输入
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
	a.balance = 0;//初始化账户余额及电影数
	a.filmnum = 0;
	fwrite(&a, sizeof(struct vip), 1, fa);
	fclose(fa);
	fclose(fb);
	fa = NULL;
	fb = NULL;
	printf("\n注册成功!返回(1)\n");
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
		printf("请输入用户名__________\b\b\b\b\b\b\b\b\b\b");
		gets(name);
		printf("请输入密码__________\b\b\b\b\b\b\b\b\b\b");
		while (c = _getch())//密码输入部分
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
			printf("\n登录成功,欢迎%s %s\n", a.name, a.password);//TODO
			USERTYPE = 1;
			flag = 0;
			printf("\n登录成功!返回(1)\n");
			while (c = checkselect() != '1');
			return;
		}
		else
		{
			printf("\n用户名或密码错误,请重试!%s %s %s %s\n", a.name, a.password, name, pass);//TODO
			if (flag++ == 3)//三次登录机会
			{
				printf("用户名或密码错误三次!返回(1)\n");
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
	printf("请输入用户名__________\b\b\b\b\b\b\b\b\b\b");
	gets(name);
	printf("\n请输入密码__________\b\b\b\b\b\b\b\b\b\b");
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
		printf("登录成功!\n");
		USERTYPE = 2;
	}
	else
		printf("登录失败!\n");
	printf("返回(1)\n");
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
void changevipinfo(int newnum, int newid)//未测试
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