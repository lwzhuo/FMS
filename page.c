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
	int s;
	while (1)
	{
		system("cls");
		printf("注册(1)\n");
		printf("登录(2)\n");
		printf("退出系统(q)\n");
		s = select();
		if (checkselect(s, "12q"))
		{
			switch (s)
			{
			case '1':
				registrationpage();
				break;
			case '2':
				loginpage();
				break;
			case 'q':
				return 0;
			default:
				break;
			}
		}
	}
	return 0;
}
void registrationpage()
{
	system("cls");
	char name[20], pass[16], c;
	int id = 1, i = 0;
	printf("请输入用户名__________\b\b\b\b\b\b\b\b\b\b");
	gets(name);
	printf("请输入密码__________\b\b\b\b\b\b\b\b\b\b");
	while (c = _getch())//用户密码输入
	{
		if (c != 13)
		{
			putchar('*');
			pass[i++] = c;
		}
		else
		{
			pass[i] = '\0';
			break;
		}
	}
	if (registration(name, pass))
		printf("\n注册成功\n");
	else
		printf("\n用户名已被使用,注册失败\n");
	back();
}
void filmpage()
{
	int s;
	while (1)
	{
		system("cls");
		printf("按照影片名查询(1)\n");
		printf("通过国家查找(2)\n");
		printf("通过影片类型查找(3)\n");
		printf("返回(q)\n");
		s = select();
		if (checkselect(s,"123q"))
			break;
	}
	switch (s)
	{
	case '1':
	{
		char name[30];
		printf("请输入影片名:");
		scanf("%s", name);
		if (getFilmByName(name, &f) == NULL)
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
		c = select();
		if (c == '1' || c == '2')
			break;
	}
	switch (c)
	{
	case '1':
	{
		system("cls");
		struct filmborrow fb;//构造并组装购物车
		fb.borrow_time = Get_time();//获得租借时间
		fb.film_id = f.id;
		addfilm(head, &fb);//加入购物车
		printf("添加成功!\n当前购物车有以下影片\n");//TODO判断添加成功
		showcart(head);
		back();
		break;
	}
	case '2':
		return;
	}
}
void loginpage()
{
	int s;
	while (1)
	{
		if (USERTYPE)//如果已经登录 则不显示以下菜单
			return;
		system("cls");
		printf("1.管理员登录\n");
		printf("2.vip登录\n");
		printf("q.返回\n");
		s = select();
		if (checkselect(s,"12q"))
		{
			if (s == '1')
			{
				adminlogin();
				if (USERTYPE == 2)//检查是否以管理员身份登录
					adminpage();
			}
			if (s == '2')
			{
				viplogin();
				if(USERTYPE==1)//检查是否以vip身份登录
					vippage();
			}
			if (s == 'q')
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
		c = select();
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
		c = select();
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
		c = select();
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
					c = select();
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
					c = select();
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
		c = select();
		if ((c >= '1' && c <= '4') || c == 'q')
		{
			switch (c)
			{
			case '1':
			{
				char name[30];
				printf("请输入影片名:");
				scanf("%s", name);
				if (NULL == getFilmByName(name, &f))
					printf("无此影片\n");
				else
				{
					adminfilmoperatepage();
				}
				//printf("\n返回(q)");//TODO 返回流程修改
				//while (1)
				//{
				//	c = select();
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
		c = select();
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
void vippage()//页面构建范例
{
	char s;
	while (1)
	{
		system("cls");
		printf("影片借阅(1)  影片归还(2) 我的购物车(3) 个人中心(4) 退出登录(q)");
		s = select();
		if (!checkselect(s,"1234q"))
			continue;
		switch (s)
		{
		case '1':
		{
			filmpage();
			break;
		}
		case '2':
			break;
		case '3':
		{
			printf("当前购物车有以下影片\n");
			showcart(head);
			printf("全部借阅(1)\n");//TODO按键
			borrowfilm(head, v.id);
			//clearcart(head);
			break;
		}
		case '4':
			printf("个人信息: 用户名      余额\n");
			printf("%s  %d\n", v.name, v.balance);
			printf("借阅信息:\n");
			showvipfilm(v.id);
			back();
			break;
		case 'q':
			USERTYPE = 0;
			return;
		}
	}
}