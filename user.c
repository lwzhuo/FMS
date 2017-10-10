#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"struct.h"
#include"util.h"
#include"user.h"
#include"film.h"

extern USERTYPE;
int registration(char * name,char * pass)
{
	if (searchVipByName(name, &v))
		return 0;//�û����ѱ�ע��
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
	a.balance = 0;//��ʼ���˻����
	a.filmnum = 0;//��ʼ����Ӱ��
	fwrite(&a, sizeof(struct vip), 1, fa);
	fclose(fa);
	fclose(fb);
	fa = NULL;
	fb = NULL;
	changevipinfo(++b.num, ++b.nextid);//�޸��û���Ϣ�ļ�
	return;
}
void viplogin()
{
	while (1)
	{
		int i = 0;
		char name[20], pass[16], c;
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
		if(searchVipByName(name, &v))
		{
			if (strcmp(v.name, name) == 0 && strcmp(v.password, pass) == 0)
			{
				printf("\n��¼�ɹ�,��ӭ%s\n", v.name);
				USERTYPE = 1;
				head = cartinit(head);//��¼�ɹ����ʼ�����ﳵ
				back();
				return;
			}
			else
			{
				printf("\n�û������������,������!\n");
				back();
			}
		}
		else
		{
			printf("\n���û���δע��!\n");
			back();
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
	while (c = select() != '1');
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
void changevipinfo(int newnum, int newid)//�޸��û���Ϣ�ļ�
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
	printf("�û�����:%d\n�û���Ϣ������С:%d\n��һ���û�id:%d\n",vi.num,vi.singlevipsize,vi.nextid);
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
void showUserlist()
{
	int i = 0, num = getvipnum();
	FILE * f = fopen("vipuser", "rb");
	struct vip v;
	printf("id     �û���      ����\n");
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
	return 0;//δ�ҵ���Ӧ�û�
}

struct cart * getvipfilm(int uid)//����util.c�й��ﳵģ�����
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
	int vipnum = vi.num, flag = 0, j;//i�û����� flag�α�
	for (j = 0; j < vipnum; j++)//�ҵ��û�λ��
	{
		fseek(f1, sizeof(struct vip)*j, SEEK_SET);
		fread(&tempvip, sizeof(struct vip), 1, f1);
		if (tempvip.id == uid)
			break;
		flag += tempvip.filmnum;
	}
	for (j = 0; j < tempvip.filmnum; j++)//�����û���ӰƬ ����������
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
	return 0;//δ�ҵ���Ӧ�û�
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