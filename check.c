#include<stdio.h>
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