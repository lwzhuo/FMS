#include<stdio.h>
#include "time.h"
char checkselect()
{
	char c = getchar();
	while (getchar() != '\n');
	return c;
}
void back()
{
	int c;
	printf("\n����(q)");//TODO�޷�����
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
}   //���ǻ�ȡ��ǰʱ��ĺ��������ص�����19700.1.1��Сʱ��

int disk_rent(long borrow_t1, long back_t2)
{
	long m, n, t;
	t = back_t2 - borrow_t1;
	m = t / 72;
	n = t % 72;
	if (n != 0)
	{
		return m + 1;
	}
	else
		return m;
}  //t������ʱ������ʱ���,m�����