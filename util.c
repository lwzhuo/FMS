/*һЩ���ü����롢���������*/
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
int checkselect(int select, char * str)//��������Ƿ�������ѡ����
{
	for (int i = 0; i < strlen(str); i++)
		if (str[i] == select)
			return 1;
	return 0;
}
void back()
{
	int c;
	printf("\n����(q)");//TODO�޷�����
	while (1)
	{
		c = select();
		if (c == 'q')
			return;
	}
}
int Get_time()
{
	time_t lt;
	lt = time(NULL) / (60 * 60);
	return lt;
}   //���ǻ�ȡ��ǰʱ��ĺ��������ص�����19700.1.1��Сʱ��

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
}  //t������ʱ������ʱ���,m�����
/*���ﳵģ����뿪ʼ*/
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
int showcart(struct cart * head)
{
	cartptr p = head;
	if (p->next == NULL)
	{
		printf("���ﳵ��\n");
		return 0;
	}
	printf("ӰƬid   ӰƬ����\n");
	p = p->next;
	while (p)
	{
		printf("%d    %s\n", p->fb->film_id, getFilmNameByid(p->fb->film_id));
		p = p->next;
	}
	return 1;
}
void clearcart(struct cart * head)
{
	struct cart * p = head;
	while (p)
	{
		p = p->next;
		free(p);
	}
}
/*���ﳵģ��������*/