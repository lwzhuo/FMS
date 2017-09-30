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
	//struct vipinfo vinfo;
	//vinfo.num = 0;
	//vinfo.singlevipsize = 48;
	//vinfo.nextid = 1;
	//FILE *f2 = fopen("vipinfo", "wb");
	//fwrite(&vinfo, sizeof(struct vipinfo), 1, f2);
	//fclose(f2);
	//printf("初始化完毕\n");//TODO完成检查
	//viewvipinfo();//查看vip用户信息文件内容
	while (Homepage());
	//showUserlist();//显示用户列表
	return 0;
}
