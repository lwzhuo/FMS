#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"struct.h"
#include"page.h"
#include"user.h"//ceshi
#include"film.h"//ceshi
int USERTYPE = 0;//0 未登录 1 vip 2 管理员

int main()
{
	//createadmin(1, "admin", "admin");//管理员帐户创建
	//printf("%d %d\n", sizeof(struct vipinfo), sizeof(struct filminfo));
	//init();//配置文件初始化
	while (Homepage());
	return 0;
}
