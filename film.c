#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"struct.h"
#include<stdlib.h>
#include"public.h"
#include"film.h"
struct film * getFilmByName(char * name, struct film *f)//通过名字查询
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
void printFilminfo(struct film f)//打印某个结构体内容
{
	printf("id   碟名                 \
国家 类型 年份          状态 价格   总量 余量\n");
	printf("%-4d %-20s %-3s %-3s %-13s %-3s \
%-6.2f %-4d %-4d\n", f.id, f.film_name,
COUNTRY[f.film_country - '0'], TYPE[f.film_type - '0'],
YEAR[f.film_year - '0'], IS_BORROW[f.is_borrow - '0'],
f.film_price, f.film_sum, f.film_left);
	return;
}
void insertFilm(char *name, char country, char type,
	char year, char is_borrow, float film_price,
	char film_sum, char film_left)//插入影片信息
{
	FILE *file = fopen("filmbinary", "ab+");
	int id;
	id = getIdflagFromFilminfo();
	/*组装结构体开始*/
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
	/*组装结构体结束*/
	printf("getfilm:%d %s %s %s %s %s %.2f %d %d ", f.id, f.film_name,
		COUNTRY[f.film_country - '0'], TYPE[f.film_type - '0'],
		YEAR[f.film_year - '0'], IS_BORROW[f.is_borrow - '0'],
		f.film_price, f.film_sum, f.film_left);
	if (fwrite(&f, sizeof(struct film), 1, file))
	{
		printf("插入成功!\n");
		changeFilmSumInFilminfo(getFilmSumFromFilminfo() + 1, id + 1);//id数和影片+1
	}
	else
		printf("插入失败!\n");
	fclose(file);
	file = NULL;
}
void deleteFilmByName(char * name)
{
	struct film f;
	int id = getFilmIdByName(name);//如未找到相应电影 返回-1
	if (id == -1)
	{
		printf("无此电影\n");
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
	if (remove("filmbinary") == 0)//TODO删除判断
	{
		printf("删除成功\n");
		FILMCONUT--;
		changeFilmSumInFilminfo(FILMCONUT,-1);//TODO
	}
	else
		perror("删除失败:");
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
void showFilmList(int start, int end)//显示一个区间内的影片信息
{
	int num = 0;
	int max = getFilmSumFromFilminfo();
	struct film f;
	if (start < 1)
	{
		printf("起始位置出错\n");
		return;
	}
	if (end>max)
	{
		printf("结束位置超过最大电影总数\n");
		return;
	}
	if (end < start)
	{
		printf("结束位置应大于开始位置\n");
		return;
	}
	FILE *file = fopen("filmbinary", "rb");
	printf("序号 id   碟名                 \
国家 类型 年份          状态 价格   总量 余量\n");
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
void changeFilmLeftNum(int id, int newnum)//更改影片剩余库存数量
{
	struct film f;
	int i = 0;
	FILE *newfile = fopen("tempfilmbinary", "wb");
	FILE *oldfile = fopen("filmbinary", "rb");
	FILMCONUT = getFilmSumFromFilminfo();//如返回-1 代表没找到
	if (id == -1)
	{
		printf("无此电影\n");
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
void changeFilmPrice(int id, float newprice)//修改影片价格
{
	struct film f;
	int i = 0;
	FILE *newfile = fopen("tempfilmbinary", "wb");
	FILE *oldfile = fopen("filmbinary", "rb");
	FILMCONUT = getFilmSumFromFilminfo();//如返回-1 代表没找到
	if (id == -1)
	{
		printf("无此电影\n");
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
	return NULL;//未找到
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
	int vipnum = vi.num, flag = 0, i, j, x;//i用户数量 flag游标
	for (j = 0; j < vipnum; j++)
	{
		fseek(f1, sizeof(struct vip)*j, SEEK_SET);
		fread(&tempv, sizeof(struct vip), 1, f1);//读入单个用户信息
		if (tempv.filmnum != 0)//判断用户是否借阅影片
		{
			for (x = 0; x < tempv.filmnum; x++)//电影借阅文件写入
			{
				fseek(f, sizeof(struct filmborrow)*(flag + x), SEEK_SET);
				fread(&fb, sizeof(struct filmborrow), 1, f);
				fseek(tempf, sizeof(struct filmborrow)*(flag + x), SEEK_SET);
				fwrite(&fb, sizeof(struct filmborrow), 1, tempf);
			}
			flag += tempv.filmnum;//游标加上用户借阅影片数量 游标后移
		}
		
		if(tempv.id==uid)//找到相应用户 开始写入文件 电影借阅文件以及用户文件
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
			flag += i;//游标后移
			tempv.filmnum += i;//个人借阅数增加
		}
		fseek(tempf1, sizeof(struct vip)*j, SEEK_SET);
		fwrite(&tempv, sizeof(struct vip), 1, tempf1);//写入单个用户信息
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
/*配置文件修改*/
void changeFilmSumInFilminfo(int newnum,int newnextid)//修改配置文件中电影数目
{
	struct filminfo info;
	FILE *oldfile = fopen("filminfo", "rb");
	FILE *newfile = fopen("tempfilminfo", "wb");
	fread(&info, sizeof(struct filminfo), 1, oldfile);
	info.num = newnum;
	if (newnextid != -1)//输入-1 代表仅修改影片总数量 不修改下一个影片的id
		info.nextid = newnextid;
	fwrite(&info, sizeof(struct filminfo), 1, newfile);
	_fcloseall();
	remove("filminfo");
	rename("tempfilminfo", "filminfo");
	//FILMCONUT = newnum;TODO
}
int getFilmSumFromFilminfo()//获取配置文件中电影总数
{
	int sum = 0;
	struct filminfo info;
	FILE *f = fopen("filminfo", "rb");
	fread(&info, sizeof(struct filminfo), 1, f);
	fclose(f);
	return info.num;
}
int getIdflagFromFilminfo()//获取配置文件中id标记
{
	int sum = 0;
	struct filminfo info;
	FILE *f = fopen("filminfo", "rb");
	fread(&info, sizeof(struct filminfo), 1, f);
	fclose(f);
	return info.nextid;
}
int getFilmIdByName(char *name)//通过影片名字查找影片id
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
	return -1;//未找到
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
	int vipnum = vi.num, flag = 0, i, j, x;//i用户数量 flag游标
	for (j = 0; j < vipnum; j++)
	{
		fseek(f1, sizeof(struct vip)*j, SEEK_SET);
		fread(&tempv, sizeof(struct vip), 1, f1);//读入单个用户信息
		if (tempv.filmnum != 0)//判断用户是否借阅影片
		{
			for (x = 0; x < tempv.filmnum; x++)//电影借阅文件写入
			{
				fseek(f, sizeof(struct filmborrow)*(flag + x), SEEK_SET);
				fread(&fb, sizeof(struct filmborrow), 1, f);
				if (tempv.id == uid)//匹配用户
					if (fb.status == 0)//匹配借阅状态
						fb.status = 1;//修改用户借阅状态
				fseek(tempf, sizeof(struct filmborrow)*(flag + x), SEEK_SET);
				fwrite(&fb, sizeof(struct filmborrow), 1, tempf);
			}
			flag += tempv.filmnum;//游标加上用户借阅影片数量 游标后移
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
	int vipnum = vi.num, flag = 0, i, j;//i用户数量 flag游标
	for (j = 0; j < vipnum; j++)
	{
		fseek(f1, sizeof(struct vip)*j, SEEK_SET);
		fread(&tempv, sizeof(struct vip), 1, f1);//读入单个用户信息
		if (tempv.filmnum != 0)//判断用户是否借阅影片
		{
			for (int x = 0; x < tempv.filmnum; x++)//电影借阅文件写入
			{
				fseek(f, sizeof(struct filmborrow)*(flag + x), SEEK_SET);
				fread(&fb, sizeof(struct filmborrow), 1, f);
				if (tempv.id == uid)//匹配用户
					if (fb.status == 0)//匹配借阅状态
						if(fb.film_id==fid)//匹配影片id
							fb.status = 1;//修改用户借阅状态
				fseek(tempf, sizeof(struct filmborrow)*(flag + x), SEEK_SET);
				fwrite(&fb, sizeof(struct filmborrow), 1, tempf);
			}
			flag += tempv.filmnum;//游标加上用户借阅影片数量 游标后移
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
	int vipnum = vi.num, flag = 0, j, x;//i用户数量 flag游标
	for (j = 0; j < vipnum; j++)
	{
		fseek(f1, sizeof(struct vip)*j, SEEK_SET);
		fread(&tempv, sizeof(struct vip), 1, f1);//读入单个用户信息
		if (tempv.filmnum != 0)//判断用户是否借阅影片
		{
			for (x = 0; x < tempv.filmnum; x++)//电影借阅文件写入
			{
				fseek(f, sizeof(struct filmborrow)*(flag + x), SEEK_SET);
				fread(&fb, sizeof(struct filmborrow), 1, f);
				fseek(tempf, sizeof(struct filmborrow)*(flag + x), SEEK_SET);
				fwrite(&fb, sizeof(struct filmborrow), 1, tempf);
			}
			flag += tempv.filmnum;//游标加上用户借阅影片数量 游标后移
		}

		if (tempv.id == uid)//找到相应用户 开始写入文件 电影借阅文件以及用户文件
		{
			struct cart * p = head , *temp;
			while (p)
			{
				if (p->next->fb->film_id == fid)
				{
					fseek(tempf, sizeof(struct filmborrow)*(flag + 0), SEEK_SET);
					fwrite((p->next->fb), sizeof(struct filmborrow), 1, tempf);
					temp = p->next;
					p->next = p->next->next;//删除购物车的影片
					free(temp);
					break;
				}
				p = p->next;
			}
			flag += 1;//游标后移
			tempv.filmnum += 1;//个人借阅数增加
		}
		fseek(tempf1, sizeof(struct vip)*j, SEEK_SET);
		fwrite(&tempv, sizeof(struct vip), 1, tempf1);//写入单个用户信息
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