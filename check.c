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
	printf("\n����(q)");//TODO�޷�����
	while (1)
	{
		c = checkselect();
		if (c == 'q')
			break;
	}
	return;
}