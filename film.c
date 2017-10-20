#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"struct.h"
#include<stdlib.h>
#include"public.h"
#include"film.h"
struct film * getFilmByName(char * name, struct film *f)//ͨ�����ֲ�ѯ
{
	int index = 0;
	FILE *file = fopen("filmbinary", "ab+");
	FILMCONUT = getFilmSumFromFilminfo();
	while (index < FILMCONUT)
	{
		fseek(file, FILMSIZE * index, SEEK_SET);
		fread(f, FILMSIZE, 1, file);
		index++;
		if (!strcmp(name, f->film_name))
		{
			fclose(file);
			file = NULL;
			return f;
		}
	}
	fclose(file);
	file = NULL;
	return NULL;
}
void printFilminfo(struct film f)//��ӡĳ���ṹ������
{
	printf("id   ����                 \
���� ���� ���          ״̬ �۸�   ���� ����\n");
	printf("%-4d %-20s %-3s %-3s %-13s %-3s \
%-6.2f %-4d %-4d\n", f.id, f.film_name,
COUNTRY[f.film_country - '0'], TYPE[f.film_type - '0'],
YEAR[f.film_year - '0'], IS_BORROW[f.is_borrow - '0'],
f.film_price, f.film_sum, f.film_left);
	return;
}
void insertFilm(char *name, char country, char type,
	char year, char is_borrow, float film_price,
	char film_sum, char film_left)//����ӰƬ��Ϣ
{
	FILE *file = fopen("filmbinary", "ab+");
	int id;
	id = getIdflagFromFilminfo();
	/*��װ�ṹ�忪ʼ*/
	struct film f;
	strcpy(f.film_name, name);
	f.id = id;
	f.film_country = country;
	f.film_type = type;
	f.film_year = year;
	f.is_borrow = is_borrow;
	f.film_price = film_price;
	f.film_sum = film_sum;
	f.film_left = film_left;
	/*��װ�ṹ�����*/
	printf("getfilm:%d %s %s %s %s %s %.2f %d %d ", f.id, f.film_name,
		COUNTRY[f.film_country - '0'], TYPE[f.film_type - '0'],
		YEAR[f.film_year - '0'], IS_BORROW[f.is_borrow - '0'],
		f.film_price, f.film_sum, f.film_left);
	if (fwrite(&f, sizeof(struct film), 1, file))
	{
		printf("����ɹ�!\n");
		changeFilmSumInFilminfo(getFilmSumFromFilminfo() + 1, id + 1);//id����ӰƬ+1
	}
	else
		printf("����ʧ��!\n");
	fclose(file);
	file = NULL;
}
void deleteFilmByName(char * name)
{
	struct film f;
	int id = getFilmIdByName(name);//��δ�ҵ���Ӧ��Ӱ ����-1
	if (id == -1)
	{
		printf("�޴˵�Ӱ\n");
		return;
	}
	int i, j;
	i = j = 0;
	FILE *newfile = fopen("tempfilmbinary", "wb");
	FILE *oldfile = fopen("filmbinary", "rb");
	FILMCONUT = getFilmSumFromFilminfo();
	do
	{
		fseek(oldfile, FILMSIZE*i, SEEK_SET);
		fread(&f, sizeof(struct film), 1, oldfile);
		if (f.id == id)
		{
			i++;
			continue;
		}
		fseek(newfile, FILMSIZE*j, SEEK_SET);
		fwrite(&f, sizeof(struct film), 1, newfile);
		i++;
		j++;
	}while (i < FILMCONUT);
	_fcloseall();
	if (remove("filmbinary") == 0)//TODOɾ���ж�
	{
		printf("ɾ���ɹ�\n");
		FILMCONUT--;
		changeFilmSumInFilminfo(FILMCONUT,-1);//TODO
	}
	else
		perror("ɾ��ʧ��:");
	rename("tempfilmbinary", "filmbinary");
	newfile = NULL;
	oldfile = NULL;
}
void showAllFilm()
{
	int a = getFilmSumFromFilminfo();
	showFilmList(1, a);
	return;
}
void showFilmList(int start, int end)//��ʾһ�������ڵ�ӰƬ��Ϣ
{
	int num = 0;
	int max = getFilmSumFromFilminfo();
	struct film f;
	if (start < 1)
	{
		printf("��ʼλ�ó���\n");
		return;
	}
	if (end>max)
	{
		printf("����λ�ó�������Ӱ����\n");
		return;
	}
	if (end < start)
	{
		printf("����λ��Ӧ���ڿ�ʼλ��\n");
		return;
	}
	FILE *file = fopen("filmbinary", "rb");
	printf("��� id   ����                 \
���� ���� ���          ״̬ �۸�   ���� ����\n");
	start--;
	end--;
	while (start <= end)
	{
		num++;
		fseek(file, FILMSIZE * start, SEEK_SET);
		fread(&f, sizeof(struct film), 1, file);
		printf("%-4d %-4d %-20s %-3s %-3s %-13s %-3s \
%-6.2f %-4d %-4d\n", num, f.id, f.film_name,
COUNTRY[f.film_country - '0'], TYPE[f.film_type - '0'],
YEAR[f.film_year - '0'], IS_BORROW[f.is_borrow - '0'],
f.film_price, f.film_sum, f.film_left);
		start++;
	}
	return;
}
void changeFilmLeftNum(int id, int newnum)//����ӰƬʣ��������
{
	struct film f;
	int i = 0;
	FILE *newfile = fopen("tempfilmbinary", "wb");
	FILE *oldfile = fopen("filmbinary", "rb");
	FILMCONUT = getFilmSumFromFilminfo();//�緵��-1 ����û�ҵ�
	if (id == -1)
	{
		printf("�޴˵�Ӱ\n");
		return;
	}
	while (i < FILMCONUT)
	{
		fseek(oldfile, FILMSIZE*i, SEEK_SET);
		fread(&f, sizeof(struct film), 1, oldfile);
		if (f.id == id)
		{
			f.film_left = newnum;
		}
		fseek(newfile, FILMSIZE*i, SEEK_SET);
		fwrite(&f, sizeof(struct film), 1, newfile);
		i++;
	}
	_fcloseall();
	remove("filmbinary");
	rename("tempfilmbinary", "filmbinary");
}
void changeFilmPrice(int id, float newprice)//�޸�ӰƬ�۸�
{
	struct film f;
	int i = 0;
	FILE *newfile = fopen("tempfilmbinary", "wb");
	FILE *oldfile = fopen("filmbinary", "rb");
	FILMCONUT = getFilmSumFromFilminfo();//�緵��-1 ����û�ҵ�
	if (id == -1)
	{
		printf("�޴˵�Ӱ\n");
		return;
	}
	while (i < FILMCONUT)
	{
		fseek(oldfile, FILMSIZE*i, SEEK_SET);
		fread(&f, sizeof(struct film), 1, oldfile);
		if (f.id == id)
		{
			f.film_price = newprice;
		}
		fseek(newfile, FILMSIZE*i, SEEK_SET);
		fwrite(&f, sizeof(struct film), 1, newfile);
		i++;
	}
	_fcloseall();
	remove("filmbinary");
	rename("tempfilmbinary", "filmbinary");
	oldfile = NULL;
	oldfile = NULL;
}
char * getFilmNameByid(int id)
{
	FILE * file = fopen("filmbinary", "rb");
	int i = getFilmSumFromFilminfo(), j;
	for (j = 0; j < i; j++)
	{
		fseek(file, sizeof(struct film)*j, SEEK_SET);
		fread(&f, sizeof(struct film), 1, file);
		if (f.id == id)
		{
			fclose(file);
			return f.film_name;
		}
	}
	fclose(file);
	return NULL;//δ�ҵ�
}
void borrowfilm(struct cart * head,int uid)
{
	FILE * f = fopen("borrowfilm", "rb");
	FILE * tempf = fopen("tempborrowfilm", "wb");
	FILE * f1 = fopen("vipuser", "rb");
	FILE * tempf1 = fopen("tempvipuser", "wb");
	FILE * f2 = fopen("vipinfo", "rb");
	struct vipinfo vi;
	struct filmborrow fb;
	struct vip tempv;
	fread(&vi, sizeof(struct vipinfo), 1, f2);
	fclose(f2); f2 = NULL;
	int vipnum = vi.num, flag = 0, i, j, x;//i�û����� flag�α�
	for (j = 0; j < vipnum; j++)
	{
		fseek(f1, sizeof(struct vip)*j, SEEK_SET);
		fread(&tempv, sizeof(struct vip), 1, f1);//���뵥���û���Ϣ
		if (tempv.filmnum != 0)//�ж��û��Ƿ����ӰƬ
		{
			for (x = 0; x < tempv.filmnum; x++)//��Ӱ�����ļ�д��
			{
				fseek(f, sizeof(struct filmborrow)*(flag + x), SEEK_SET);
				fread(&fb, sizeof(struct filmborrow), 1, f);
				fseek(tempf, sizeof(struct filmborrow)*(flag + x), SEEK_SET);
				fwrite(&fb, sizeof(struct filmborrow), 1, tempf);
			}
			flag += tempv.filmnum;//�α�����û�����ӰƬ���� �α����
		}
		
		if(tempv.id==uid)//�ҵ���Ӧ�û� ��ʼд���ļ� ��Ӱ�����ļ��Լ��û��ļ�
		{
			i = 0;
			struct cart * p = head->next;
			while (p)
			{
				fseek(tempf, sizeof(struct filmborrow)*(flag + i), SEEK_SET);
				fwrite((p->fb), sizeof(struct filmborrow), 1, tempf);
				i++;
				p = p->next;
			}
			flag += i;//�α����
			tempv.filmnum += i;//���˽���������
		}
		fseek(tempf1, sizeof(struct vip)*j, SEEK_SET);
		fwrite(&tempv, sizeof(struct vip), 1, tempf1);//д�뵥���û���Ϣ
	}
	fclose(f); f = NULL;
	fclose(tempf); tempf = NULL;
	fclose(f1); f1 = NULL;
	fclose(tempf1); tempf1 = NULL;
	remove("vipuser");
	remove("borrowfilm");
	rename("tempborrowfilm", "borrowfilm");
	rename("tempvipuser", "vipuser");
}
/*�����ļ��޸�*/
void changeFilmSumInFilminfo(int newnum,int newnextid)//�޸������ļ��е�Ӱ��Ŀ
{
	struct filminfo info;
	FILE *oldfile = fopen("filminfo", "rb");
	FILE *newfile = fopen("tempfilminfo", "wb");
	fread(&info, sizeof(struct filminfo), 1, oldfile);
	info.num = newnum;
	if (newnextid != -1)//����-1 ������޸�ӰƬ������ ���޸���һ��ӰƬ��id
		info.nextid = newnextid;
	fwrite(&info, sizeof(struct filminfo), 1, newfile);
	_fcloseall();
	remove("filminfo");
	rename("tempfilminfo", "filminfo");
	//FILMCONUT = newnum;TODO
}
int getFilmSumFromFilminfo()//��ȡ�����ļ��е�Ӱ����
{
	int sum = 0;
	struct filminfo info;
	FILE *f = fopen("filminfo", "rb");
	fread(&info, sizeof(struct filminfo), 1, f);
	fclose(f);
	return info.num;
}
int getIdflagFromFilminfo()//��ȡ�����ļ���id���
{
	int sum = 0;
	struct filminfo info;
	FILE *f = fopen("filminfo", "rb");
	fread(&info, sizeof(struct filminfo), 1, f);
	fclose(f);
	return info.nextid;
}
int getFilmIdByName(char *name)//ͨ��ӰƬ���ֲ���ӰƬid
{
	struct film f;
	int index = 0;
	FILE *file = fopen("filmbinary", "rb");
	FILMCONUT = getFilmSumFromFilminfo();
	while (index < FILMCONUT)
	{
		fseek(file, FILMSIZE * index, SEEK_SET);
		fread(&f, sizeof(struct film), 1, file);
		if (!strcmp(name, f.film_name))
		{
			fclose(file);
			file = NULL;
			return f.id;
		}
		index++;
	}
	fclose(file);
	file = NULL;
	return -1;//δ�ҵ�
}
void returnall(int uid)
{
	int pay = 0;
	FILE * f = fopen("borrowfilm", "rb");
	FILE * tempf = fopen("tempborrowfilm", "wb");
	FILE * f1 = fopen("vipuser", "rb");
	FILE * f2 = fopen("vipinfo", "rb");
	struct vipinfo vi;
	struct filmborrow fb;
	struct vip tempv;
	fread(&vi, sizeof(struct vipinfo), 1, f2);
	fclose(f2); f2 = NULL;
	int vipnum = vi.num, flag = 0, i, j, x;//i�û����� flag�α�
	for (j = 0; j < vipnum; j++)
	{
		fseek(f1, sizeof(struct vip)*j, SEEK_SET);
		fread(&tempv, sizeof(struct vip), 1, f1);//���뵥���û���Ϣ
		if (tempv.filmnum != 0)//�ж��û��Ƿ����ӰƬ
		{
			for (x = 0; x < tempv.filmnum; x++)//��Ӱ�����ļ�д��
			{
				fseek(f, sizeof(struct filmborrow)*(flag + x), SEEK_SET);
				fread(&fb, sizeof(struct filmborrow), 1, f);
				if (tempv.id == uid)//ƥ���û�
					if (fb.status == 0)//ƥ�����״̬
						fb.status = 1;//�޸��û�����״̬
				fseek(tempf, sizeof(struct filmborrow)*(flag + x), SEEK_SET);
				fwrite(&fb, sizeof(struct filmborrow), 1, tempf);
			}
			flag += tempv.filmnum;//�α�����û�����ӰƬ���� �α����
		}
	}
	fclose(f); f = NULL;
	fclose(tempf); tempf = NULL;
	fclose(f1); f1 = NULL;
	remove("borrowfilm");
	rename("tempborrowfilm", "borrowfilm");
}
void retursinglefilm(int uid, int fid)
{
	int pay = 0;
	FILE * f = fopen("borrowfilm", "rb");
	FILE * tempf = fopen("tempborrowfilm", "wb");
	FILE * f1 = fopen("vipuser", "rb");
	FILE * f2 = fopen("vipinfo", "rb");
	struct vipinfo vi;
	struct filmborrow fb;
	struct vip tempv;
	fread(&vi, sizeof(struct vipinfo), 1, f2);
	fclose(f2); f2 = NULL;
	int vipnum = vi.num, flag = 0, i, j;//i�û����� flag�α�
	for (j = 0; j < vipnum; j++)
	{
		fseek(f1, sizeof(struct vip)*j, SEEK_SET);
		fread(&tempv, sizeof(struct vip), 1, f1);//���뵥���û���Ϣ
		if (tempv.filmnum != 0)//�ж��û��Ƿ����ӰƬ
		{
			for (int x = 0; x < tempv.filmnum; x++)//��Ӱ�����ļ�д��
			{
				fseek(f, sizeof(struct filmborrow)*(flag + x), SEEK_SET);
				fread(&fb, sizeof(struct filmborrow), 1, f);
				if (tempv.id == uid)//ƥ���û�
					if (fb.status == 0)//ƥ�����״̬
						if(fb.film_id==fid)//ƥ��ӰƬid
							fb.status = 1;//�޸��û�����״̬
				fseek(tempf, sizeof(struct filmborrow)*(flag + x), SEEK_SET);
				fwrite(&fb, sizeof(struct filmborrow), 1, tempf);
			}
			flag += tempv.filmnum;//�α�����û�����ӰƬ���� �α����
		}
	}
	fclose(f); f = NULL;
	fclose(tempf); tempf = NULL;
	fclose(f1); f1 = NULL;
	remove("borrowfilm");
	rename("tempborrowfilm", "borrowfilm");
}
void borrowsinglefilm(struct cart * head, int uid, int fid)
{
	FILE * f = fopen("borrowfilm", "rb");
	FILE * tempf = fopen("tempborrowfilm", "wb");
	FILE * f1 = fopen("vipuser", "rb");
	FILE * tempf1 = fopen("tempvipuser", "wb");
	FILE * f2 = fopen("vipinfo", "rb");
	struct vipinfo vi;
	struct filmborrow fb;
	struct vip tempv;
	fread(&vi, sizeof(struct vipinfo), 1, f2);
	fclose(f2); f2 = NULL;
	int vipnum = vi.num, flag = 0, j, x;//i�û����� flag�α�
	for (j = 0; j < vipnum; j++)
	{
		fseek(f1, sizeof(struct vip)*j, SEEK_SET);
		fread(&tempv, sizeof(struct vip), 1, f1);//���뵥���û���Ϣ
		if (tempv.filmnum != 0)//�ж��û��Ƿ����ӰƬ
		{
			for (x = 0; x < tempv.filmnum; x++)//��Ӱ�����ļ�д��
			{
				fseek(f, sizeof(struct filmborrow)*(flag + x), SEEK_SET);
				fread(&fb, sizeof(struct filmborrow), 1, f);
				fseek(tempf, sizeof(struct filmborrow)*(flag + x), SEEK_SET);
				fwrite(&fb, sizeof(struct filmborrow), 1, tempf);
			}
			flag += tempv.filmnum;//�α�����û�����ӰƬ���� �α����
		}

		if (tempv.id == uid)//�ҵ���Ӧ�û� ��ʼд���ļ� ��Ӱ�����ļ��Լ��û��ļ�
		{
			struct cart * p = head , *temp;
			while (p)
			{
				if (p->next->fb->film_id == fid)
				{
					fseek(tempf, sizeof(struct filmborrow)*(flag + 0), SEEK_SET);
					fwrite((p->next->fb), sizeof(struct filmborrow), 1, tempf);
					temp = p->next;
					p->next = p->next->next;//ɾ�����ﳵ��ӰƬ
					free(temp);
					break;
				}
				p = p->next;
			}
			flag += 1;//�α����
			tempv.filmnum += 1;//���˽���������
		}
		fseek(tempf1, sizeof(struct vip)*j, SEEK_SET);
		fwrite(&tempv, sizeof(struct vip), 1, tempf1);//д�뵥���û���Ϣ
	}
	fclose(f); f = NULL;
	fclose(tempf); tempf = NULL;
	fclose(f1); f1 = NULL;
	fclose(tempf1); tempf1 = NULL;
	remove("vipuser");
	remove("borrowfilm");
	rename("tempborrowfilm", "borrowfilm");
	rename("tempvipuser", "vipuser");
}