#define _CRT_SECURE_NO_WARNINGS
/*一些常用检测代码、工具类代码*/
#include<stdio.h>
#include "time.h"
#include"struct.h"
#include"stdlib.h"
#include"film.h"
char select()
{
	char c = getchar();
	while (getchar() != '\n');
	return c;
}
int checkselect(int select, char * str)//检查输入是否在所给选项内
{
	for (int i = 0; i < strlen(str); i++)
		if (str[i] == select)
			return 1;
	return 0;
}
void back()
{
	int c;
	printf("\n返回(q)");//TODO无法返回
	while (1)
	{
		c = select();
		if (c == 'q')
			return;
	}
}
/*时间计费模块开始*/
int Get_time()
{
	time_t lt;
	lt = time(NULL) / (60 * 60);
	return lt;
}   //这是获取当前时间的函数，返回的是离19700.1.1的小时；

int disk_rent(long borrow_t1, long back_t2)
{
	long m, n, t;
	t = back_t2 - borrow_t1 + 1;
	m = t / 72;
	n = t % 72;
	if (n != 0)
		return m + 1;
	else
		return m;
}  //t是两个时间相距的时间差,m是租金

char * showborrowtime(long borrowtime)
{
	int nowtime = Get_time();
	int hour = nowtime - borrowtime;
	char *msg;
	msg = (char *)malloc(sizeof(char) * 20);
	if (hour == 0)
		sprintf(msg, "刚刚借阅");
	else if (hour > 0 && hour < 24)
		sprintf(msg, "借阅%d小时", hour);
	else
		sprintf(msg, "借阅%d天", hour / 24);
	return msg;
}
/*时间计费模块结束*/

/*购物车模块代码开始*/
struct cart * cartinit(struct cart * head)
{
	head = (cartptr)malloc(sizeof(cartnode));
	head->next = NULL;
	return head;
}
void addfilm(struct cart *head, struct filmborrow *b)
{
	cartptr p = head->next, temp;
	temp = (cartptr)malloc(sizeof(cartnode));
	temp->fb = (struct filmborrow *)malloc(sizeof(struct filmborrow));
	temp->fb->film_id = b->film_id;
	temp->fb->borrow_time = b->borrow_time;
	temp->fb->status = b->status;
	head->next = temp;
	temp->next = p;
}
int showcart(struct cart * head)
{
	cartptr p = head;
	int filmnum = 0;
	if (p->next == NULL)
	{
		printf("购物车空\n");
		return 0;
	}
	printf("影片id    影片名字\n");
	p = p->next;
	while (p)
	{
		filmnum++;
		printf("%-4d    %10s\n", p->fb->film_id, getFilmNameByid(p->fb->film_id));
		p = p->next;
	}
	return filmnum;
}
void clearcart(struct cart * head)
{
	struct cart * p = head->next, *temp;
	head->next = NULL;
	while (p)
	{
		temp = p->next;
		free(p->fb);
		free(p);
		p = temp;
	}
}
/*购物车模块代码结束*/