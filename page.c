#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"util.h"
#include"struct.h"
#include"user.h"
#include"page.h"
#include"film.h"
#include"public.h"
#include<stdlib.h>
extern USERTYPE;
void init()//配置文件，请勿外部调用！ 仅在初始化配置文件时调用
{
	/*电影配置文件初始化*/
	struct filminfo info;
	info.num = 0;
	info.singlefilmsize = 48;
	info.nextid = 1;
	FILE *f1 = fopen("filminfo", "wb");
	fwrite(&info, sizeof(struct filminfo), 1, f1);
	fclose(f1);
	/*用户配置文件初始化*/
	struct vipinfo vinfo;
	vinfo.num = 0;
	vinfo.singlevipsize = 48;
	vinfo.nextid = 1;
	FILE *f2 = fopen("vipinfo", "wb");
	fwrite(&vinfo, sizeof(struct vipinfo), 1, f2);
	fclose(f2);
	printf("初始化完毕\n");//TODO完成检查
}
int Homepage()
{
	int c;
	/*菜单展示及输入筛选开始*/
	while (1)
	{
		system("cls");
		/*根据用户是否登录显示不同选项*/
		if (USERTYPE)
		{
			printf("影片查询(1)\n");
			printf("个人主页(2)\n");
		}
		else
		{
			printf("注册(1)\n");
			printf("登录(2)\n");
		}
		printf("退出系统(q)\n");
		c = checkselect();
		if (c == '1' || c == '2' || c == 'q')//筛选输入
			break;
	}
	/*菜单展示及输入筛选结束*/
	/*输入判断开始*/
	if (c == '1')
	{
		if (USERTYPE)
		{
			filmpage();//影片查询页面
			return 1;
		}
		else
		{
			registration();//用户注册页面
			return 1;
		}
	}
	else if (c == '2')
	{
		if (USERTYPE)
		{
			vippage();//TODO 返回路径
		}
		else
		{
			Loginpage();//登录页面
			return 1;
		}
	}
	else if (c == 'q')
		return 0;
	else
		return 0;
	/*输入判断结束*/
}
void filmpage()
{
	int c;
	while (1)
	{
		system("cls");
		printf("按照影片名查询(1)\n");
		printf("通过国家查找(2)\n");
		printf("通过影片类型查找(3)\n");
		printf("返回(q)\n");
		c = checkselect();
		if ((c >= '1' && c <= '3') || c == 'q')
			break;
	}
	switch (c)
	{
	case '1':
	{
		char name[30];
		printf("请输入影片名:");
		scanf("%s", name);
		if (getFilmInfoByName(name, &f) == NULL)
		{
			printf("未找到相应影片!\n");
			back();
		}
		else
			borrowpage(f);
		break;
	}
	case '2':
		break;
	case '3':
		break;
	case 'q':
		break;
	}
}
void borrowpage(struct film f)
{
	char c;
	while (1)
	{
		system("cls");
		printFilminfo(f);
		printf("\n加入购物车(1)   返回(2)\n");
		c = checkselect();
		if (c == '1' || c == '2')
			break;
	}
	switch (c)
	{
	case '1':
	{
		struct filmborrow fb;//构造并组装购物车
		fb.borrow_time = Get_time();//获得租借时间
		fb.film_id = f.id;
		addfilm(head, &fb);//加入购物车
		printf("添加成功!");//TODO判断添加成功
		showcart(head);
		back();
		break;
	}
	case '2':
		return;
	}
}
void Loginpage()
{
	int c;
	while (1)
	{
		if (USERTYPE)//如果已经登录 则不显示以下菜单
			return;
		system("cls");
		printf("1.管理员登录\n");
		printf("2.vip登录\n");
		printf("3.返回\n");
		c = checkselect();
		if (c == '1' || c == '2' || c == '3')
		{
			if (c == '1')
			{
				adminlogin();
				if (USERTYPE == 2)//检查是否以管理员身份已经登录
					adminpage();
			}
			if (c == '2')
				viplogin();
			if (c == '3')
				return ;
		}
	}
}
void adminpage()//退回上一级例子
{
	int c;
	while (1)
	{
		system("cls");
		printf("影片管理(1)\n");
		printf("用户管理(2)\n");
		printf("返回(q)\n");
		c = checkselect();
		if (c == '1' || c == '2' || c == 'q')
		{
			switch (c)
			{
			case '1':
				adminpage_film();
				break;
			case '2':
				adminpage_user();
				break;
			case 'q':
				return;//退出此页面
			}
		}
	}
}
void adminpage_film()
{
	int c;
	while (1)
	{
		system("cls");
		printf("影片上架(1)\n");
		printf("影片查找(2)\n");
		printf("显示影片列表(3)\n");
		printf("返回(q)\n");
		c = checkselect();
		if ((c >='1'&&c<='3')|| c == 'q')
		{
			switch (c)
			{
			case '1':
			{
				int i;
				printf("请输入上架电影的数量:");
				scanf("%d", &i);//TODO判断合法性
				while (i-- > 0)
				{
					struct film f;
					printf("请输入:碟名                 \
国家 类型 年份          状态 价格   总量 余量\n");
					scanf("%s %c %c %c %c %f %hhd %hhd",f.film_name,
						&f.film_country,&f.film_type,&f.film_year,
						&f.is_borrow,&f.film_price,&f.film_sum,&f.film_left);
					printFilminfo(f);
					insertFilm(f.film_name, f.film_country, f.film_type, f.film_year,
						f.is_borrow, f.film_price, f.film_sum, f.film_left);
				}
				break;
			}
			case '2':
				adminfilmsearchpage();
				break;
			case '3':
			{
				adminfilmshowpage();
				break;
			}
			case 'q':
				return;//退出此页面
			}
		}
	}
}
void adminfilmshowpage()//影片显示页面
{
	int c;
	while (1)
	{
		system("cls");
		printf("显示所有影片(1)\n");
		printf("显示特定区间影片(2)\n");
		printf("返回(q)\n");
		c = checkselect();
		if (c == '1' || c == '2' || c == 'q')
		{
			switch (c)
			{
			case '1':
			{
				int c;
				showAllFilm();
				printf("\n共有%d部影片\n", getFilmSumFromFilminfo());
				printf("\n返回(q)");
				while (1)
				{
					c = checkselect();
					if (c == 'q')
						break;
				}
				break;
			}
			case '2':
			{
				int a, b, c;
				printf("当前电影数:%d\n请输入开始及结束位置:",getFilmSumFromFilminfo());
				scanf("%d %d", &a, &b);
				showFilmList(a, b);
				printf("\n返回(q)");//TODO无法返回
				while (1)
				{
					c = checkselect();
					if (c == 'q')
						break;
				}
				break;
			}
			case 'q':
				return;//退出此页面
			}
		}
	}
}
void adminpage_user()
{
	//TODO
}
void adminfilmsearchpage()//TODO
{
	int c;
	while (1)
	{
		system("cls");
		printf("通过名字查找(1)\n");
		printf("通过国家查找(2)\n");
		printf("通过类型查找(3)\n");
		printf("通过年份查找(4)\n");
		printf("返回(q)\n");
		c = checkselect();
		if ((c >= '1' && c <= '4') || c == 'q')
		{
			switch (c)
			{
			case '1':
			{
				char name[30];
				printf("请输入影片名:");
				scanf("%s", name);
				if (NULL == getFilmInfoByName(name, &f))
					printf("无此影片\n");
				else
				{
					adminfilmoperatepage();
				}
				//printf("\n返回(q)");//TODO 返回流程修改
				//while (1)
				//{
				//	c = checkselect();
				//	if (c == 'q')
				//		break;
				//}
				break;
			}
			case '2':
				//TODO
				break;
			case '3':
				//TODO
				break;
			case '4':
				//TODO
				break;
			case 'q':
				return;//退出此页面
			}
		}
	}
}
void adminfilmoperatepage()
{
	//上一个页面找到的电影加载进内存中 供给此页面操作
	int c;
	while (1)
	{
		system("cls");
		printFilminfo(f);//打印上一个页面查找到的电影
		printf("删除这个电影(1)");
		printf("  修改电影价格(2)");
		printf("  修改电影余量(3)");
		printf("  修改电影总量(4)");
		printf("  返回(q)\n");
		c = checkselect();
		if ((c >= '1' && c <= '4') || c == 'q')
		{
			switch (c)
			{
			case '1':
			{
				deleteFilmByName(f.film_name);
				back();
				break;
			}
			case '2':
			{
				float newprice;
				printf("请输入新价格:______\b\b\b\b\b\b");
				scanf("%f", &newprice);
				changeFilmPrice(f.film_name, newprice);
				break;
			}
			case '3':
			{
				int num;
				printf("请输入新余量:______\b\b\b\b\b\b");
				scanf("%d", &num);
				changeFilmLeftNum(f.film_name, num);
				break;
			}
			case '4':
			{
				int num;
				//printf("请输入新总量:______\b\b\b\b\b\b");
				//scanf("%d", &num);
				
				back();
				break;
			}
			case 'q':
				return;//退出此页面
			}
		}
	}
}
void vippage()
{
	char c;
	while (1)
	{
		system("cls");
		printf("购物车(1)  我的借阅信息(2) 退出登录(3) 返回(q)");
		c = checkselect();
		if (c >= '1'&&c <= '3' || c == 'q')
			break;
	}
	switch (c)
	{
	case '1':
	{
		if (showcart(head))//TODO
		{
			borrowfilm(head,v.id);
		}
		back();
		break;
	}
	case '2':
		return;
	case '3':
	{
		USERTYPE = 0;
		return;
	}
	case 'q':
		return;
	}
}
