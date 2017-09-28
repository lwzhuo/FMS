#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"struct.h"
#include<string.h>
#include"public.h"
#include"film.h"
struct film * getFilmInfoByName(char * name, struct film *f)//通过名字查询
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
	printf("id   碟名                 \
国家 类型 年份          状态 价格   总量 余量\n");
	start--;
	end--;
	while (start <= end)
	{
		fseek(file, FILMSIZE * start, SEEK_SET);
		fread(&f, sizeof(struct film), 1, file);
		printf("%-4d %-20s %-3s %-3s %-13s %-3s \
%-6.2f %-4d %-4d\n", f.id, f.film_name,
COUNTRY[f.film_country - '0'], TYPE[f.film_type - '0'],
YEAR[f.film_year - '0'], IS_BORROW[f.is_borrow - '0'],
f.film_price, f.film_sum, f.film_left);
		start++;
	}
	return;
}
void changeFilmLeftNum(char * name, int newnum)//更改影片剩余库存数量
{
	struct film f;
	int id = getFilmIdByName(name);
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
void changeFilmPrice(char * name, float newprice)//修改影片价格
{
	struct film f;
	int id = getFilmIdByName(name);
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