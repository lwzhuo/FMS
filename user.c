#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include"struct.h"
#include"util.h"
#include"user.h"
#include"film.h"
#include"public.h"

extern USERTYPE;
int registration(char * name,char * pass)
{
	if (searchVipByName(name, &v))
		return 0;//用户名已被注册
	else
	{
		createvip(name, pass);
		return 1;
	}	
}
void createvip(char * username, char * password)
{
	FILE * fa = fopen("vipuser", "ab+");
	FILE * fb = fopen("vipinfo", "rb");
	struct vip a;
	struct vipinfo b;
	fread(&b, sizeof(struct vipinfo), 1, fb);
	a.id = b.nextid;
	strcpy(a.name, username);
	strcpy(a.password, password);
	a.balance = 0;//初始化账户余额
	a.filmnum = 0;//初始化电影数
	fwrite(&a, sizeof(struct vip), 1, fa);
	fclose(fa);
	fclose(fb);
	fa = NULL;
	fb = NULL;
	changevipinfo(++b.num, ++b.nextid);//修改用户信息文件
	return;
}
void viplogin()
{
	while (1)
	{
		int i = 0;
		char name[20], pass[16], c;
		system("cls");
		printf("\n\n\n\n\n");
		printf("\t\t\t\t\t请输入用户名__________\b\b\b\b\b\b\b\b\b\b");
		gets(name);
		printf("\t\t\t\t\t请输入密码__________\b\b\b\b\b\b\b\b\b\b");
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
		if(searchVipByName(name, &v))
		{
			if (strcmp(v.name, name) == 0 && strcmp(v.password, pass) == 0)
			{
				color(10, "\n\n\t\t\t\t\t登录成功\n");
				printf("\t\t\t\t\t欢迎%s\n", v.name);
				USERTYPE = 1;
				head = cartinit(head);//登录成功后初始化购物车
				back();
				return;
			}
			else
			{
				color(12,"\n\n\t\t\t\t\t用户名或密码错误,请重试!\n");
				back();
				break;
			}
		}
		else
		{
			color(12,"\n\n\t\t\t\t\t此用户名未注册!\n");
			back();
			break;
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
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t请输入用户名__________\b\b\b\b\b\b\b\b\b\b");
	gets(name);
	printf("\n\n\t\t\t\t\t请输入密码__________\b\b\b\b\b\b\b\b\b\b");
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
		color(10,"\n\t\t\t\t\t登录成功!\n");
		USERTYPE = 2;
	}
	else
		color(12,"\n\t\t\t\t\t登录失败!\n");
	back();
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
void changevipinfo(int newnum, int newid)//修改用户信息文件
{
	struct vipinfo vi;
	FILE * newfile = fopen("tempvipinfo", "wb");
	FILE * oldfile = fopen("vipinfo", "rb");
	fread(&vi, sizeof(struct vipinfo), 1, oldfile);
	vi.num = newnum;
	vi.nextid = newid;
	fwrite(&vi, sizeof(struct vipinfo), 1, newfile);
	fclose(oldfile);
	fclose(newfile);
	oldfile = NULL;
	newfile = NULL;
	remove("vipinfo");
	rename("tempvipinfo", "vipinfo");
}
void viewvipinfo()
{
	FILE * f = fopen("vipinfo", "rb");
	struct vipinfo vi;
	fread(&vi, sizeof(struct vipinfo), 1, f);
	printf("用户数量:%d\n用户信息单个大小:%d\n下一个用户id:%d\n",vi.num,vi.singlevipsize,vi.nextid);
	fclose(f);
	f = NULL;
}
int getvipnum()
{
	FILE * f = fopen("vipinfo", "rb");
	struct vipinfo vi;
	fread(&vi, sizeof(struct vipinfo), 1, f);
	fclose(f); f = NULL;
	return vi.num;
}
int getvipmaxfilmborrownum()
{
	FILE * f = fopen("vipinfo", "rb");
	struct vipinfo vi;
	fread(&vi, sizeof(struct vipinfo), 1, f);
	fclose(f); f = NULL;
	return vi.MAX_FILM_BORROW_NUM;
}
void showUserlist()
{
	int i = 0, num = getvipnum();
	FILE * f = fopen("vipuser", "rb");
	struct vip v;
	printf("id     用户名      密码\n");
	while (i < num)
	{
		fseek(f, sizeof(struct vip)*i, SEEK_SET);
		fread(&v, sizeof(struct vip), 1, f);
		printf("%d %10s %10s\n", v.id, v.name, v.password);
		i++;
	}
	fclose(f);
	f = NULL;
	return;
}
int searchVipByName(char * name,struct vip * a)
{
	int i, vipnum = getvipnum();
	FILE * f1 = fopen("vipuser", "rb");
	for (i = 0; i < vipnum; i++)
	{
		fseek(f1, sizeof(struct vip)*i, SEEK_SET);
		fread(a, sizeof(struct vip), 1, f1);
		if (!strcmp(a->name, name))
		{
			fclose(f1);
			return 1;
		}
	}
	fclose(f1);
	return 0;//未找到相应用户
}

struct cart * getvipfilm(int uid)//利用util.c中购物车模块代码
{
	FILE * f = fopen("borrowfilm", "rb");
	FILE * f1 = fopen("vipuser", "rb");
	FILE * f2 = fopen("vipinfo", "rb");
	struct vipinfo vi;
	struct filmborrow fb;
	struct vip tempvip;
	struct cart c;
	struct cart *carthead = &c;
	carthead = cartinit(carthead);
	fread(&vi, sizeof(struct vipinfo), 1, f2);
	fclose(f2); f2 = NULL;
	int vipnum = vi.num, flag = 0, j;//i用户数量 flag游标
	for (j = 0; j < vipnum; j++)//找到用户位置
	{
		fseek(f1, sizeof(struct vip)*j, SEEK_SET);
		fread(&tempvip, sizeof(struct vip), 1, f1);
		if (tempvip.id == uid)
			break;
		flag += tempvip.filmnum;
	}
	for (j = 0; j < tempvip.filmnum; j++)//遍历用户的影片 存入链表中
	{
		fseek(f, sizeof(struct filmborrow)*(flag + j), SEEK_SET);
		fread(&fb, sizeof(struct filmborrow), 1, f);
		addfilm(carthead, &fb);
	}
	fclose(f);
	fclose(f1);
	return carthead;
}
int getVipById(int id,struct vip * a)
{
	int i, vipnum = getvipnum();
	FILE * f1 = fopen("vipuser", "rb");
	for (i = 0; i < vipnum; i++)
	{
		fseek(f1, sizeof(struct vip)*i, SEEK_SET);
		fread(a, sizeof(struct vip), 1, f1);
		if (id == a->id)
		{
			fclose(f1);
			return 1;
		}
	}
	fclose(f1);
	return 0;//未找到相应用户
}
void changevip(struct vip vip, int id)
{
	int i, vipnum = getvipnum();
	FILE * oldf = fopen("vipuser", "rb");
	FILE * newf = fopen("tempvipuser", "wb");
	struct vip temp;
	for (i = 0; i < vipnum; i++)
	{
		fseek(oldf, sizeof(struct vip)*i, SEEK_SET);
		fread(&temp, sizeof(struct vip), 1, oldf);
		if (id == temp.id)
			temp = vip;
		fwrite(&temp, sizeof(struct vip), 1, newf);
	}
	fclose(oldf); oldf = NULL;
	fclose(newf); newf = NULL;
	remove("vipuser");
	rename("tempvipuser", "vipuser");
}
int getvipborrowfilmnum(int id)
{
	int num = 0;
	struct cart * c = getvipfilm(id);
	c = c->next;
	while (c)
	{
		if (c->fb->status == 0)
			num++;
		c = c->next;
	}
	return num;
}
void changeVipBorrowFilmNum()
{
	system("cls");
	int newnum, max = 0, i = 0, vipnum = getvipnum();
	FILE * f = fopen("vipuser", "rb");
	struct vip tempv;
	while (i < vipnum)
	{
		fseek(f, sizeof(struct vip)*i, SEEK_SET);
		fread(&tempv, sizeof(struct vip), 1, f);
		if (max < tempv.filmnum)
			max = tempv.filmnum;
		i++;
	}
	fclose(f);
	f = NULL;
	printf("当前用户可借阅电影最大数目:%d\n", MAX_FILM_BORROW_NUM);
	printf("当前所有用户借阅电影的最大数目:%d\n", max);
	printf("请输入新数量(新数量要大于当前借阅的电影数目最多的用户的借阅数):_______\b\b\b\b\b\b\b");
	scanf("%d", &newnum);
	getchar();
	if (newnum < max)
		color(12, "数值不合法!\n");
	else//修改数值
	{
		MAX_FILM_BORROW_NUM = newnum;
		struct vipinfo vi;
		FILE * newfile = fopen("tempvipinfo", "wb");
		FILE * oldfile = fopen("vipinfo", "rb");
		fread(&vi, sizeof(struct vipinfo), 1, oldfile);
		vi.MAX_FILM_BORROW_NUM = newnum;
		fwrite(&vi, sizeof(struct vipinfo), 1, newfile);
		fclose(oldfile);
		fclose(newfile);
		oldfile = NULL;
		newfile = NULL;
		remove("vipinfo");
		rename("tempvipinfo", "vipinfo");
		color(10, "修改成功!\n");
	}
	back();
}