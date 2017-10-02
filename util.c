/*一些常用检测代码、工具类代码*/
#include<stdio.h>
#include "time.h"
#include"struct.h"
#include"stdlib.h"
#include"film.h"
char checkselect()
{
	char c = getchar();
	while (getchar() != '\n');
	return c;
}
void back()
{
	int c;
	printf("\n返回(q)");//TODO无法返回
	while (1)
	{
		c = checkselect();
		if (c == 'q')
			break;
	}
	return;
}
int Get_time()
{
	time_t lt;
	lt = time(NULL) / (60 * 60);
	return lt;
}   //这是获取当前时间的函数，返回的是离19700.1.1的小时；

int disk_rent(long borrow_t1, long back_t2)
{
	long m, n, t;
	t = back_t2 - borrow_t1;
	m = t / 72;
	n = t % 72;
	if (n != 0)
		return m + 1;
	else
		return m;
}  //t是两个时间相距的时间差,m是租金
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
	head->next = temp;
	temp->next = p;
}
int showcart(struct cart *head)
{
	cartptr p = head;
	if (p->next == NULL)
	{
		printf("购物车空\n");
		return 0;
	}
	p = p->next;
	while (p)
	{
		printf("%d    %s\n", p->fb->film_id, getFilmNameByid(p->fb->film_id));
		p = p->next;
	}
	return 1;
}
/*购物车模块代码结束*/