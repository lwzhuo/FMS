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
	{
		return m + 1;
	}
	else
		return m;
}  //t是两个时间相距的时间差,m是租金；