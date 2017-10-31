#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include"util.h"
#include"struct.h"
#include"user.h"
#include"page.h"
#include"film.h"
#include"public.h"
extern USERTYPE;

int Homepage()
{
	system("mode con:cols=100 lines=30");//更改窗口大小 字体30
	int s;
	while (1)
	{
		system("cls");
		printf("\n\n\n\n\n");
		printf("\t\t\t\t\t影片管理系统\n\n");
		printf("\t\t\t\t\t注册(1)\n\n");
		printf("\t\t\t\t\t登录(2)\n\n");
		printf("\t\t\t\t\t退出系统(q)\n\n");
		s = Select();
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
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t请输入用户名__________\b\b\b\b\b\b\b\b\b\b");
	gets(name);
	printf("\n\t\t\t\t\t请输入密码__________\b\b\b\b\b\b\b\b\b\b");
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
		color(10,"\n\n\t\t\t\t\t注册成功\n");
	else
		color(12,"\n\n\t\t\t\t\t用户名已被使用,注册失败\n");
	back();
}
void filmpage()
{
		char name[30];
		system("cls");
		printf("\n\n\n\n\t\t\t\t\t请输入影片名:");
		scanf("%s", name);
		getchar();//吸收回车符
		if (getFilmByName(name, &f) == NULL)
		{
			color(12,"\n\t\t\t\t\t未找到相应影片!\n");
			back();
		}
		else
			borrowpage(f);
}
void borrowpage(struct film f)
{
	char c;
	while (1)
	{
		system("cls");
		printFilminfo(f);
		printf("\n加入购物车(1)   返回(q)\n");
		c = Select();
		if (checkselect(c,"1q"))
			break;
	}
	switch (c)
	{
	case '1':
	{
		system("cls");
		if (f.film_left)//有余量
		{
			struct filmborrow fb;//构造并组装购物车
			fb.borrow_time = Get_time();//获得租借时间
			fb.film_id = f.id;
			fb.status = 0;
			addfilm(head, &fb);//加入购物车
			color(10, "添加成功!");
			printf("\n当前购物车有以下影片\n");//TODO判断添加成功
			showcart(head);
		}
		else
			color(12,"影片余量为0，添加失败!\n");
		back();
		break;
	}
	case 'q':
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
		printf("\n\n\n\n\n");
		printf("\t\t\t\t\t1.管理员登录\n\n");
		printf("\t\t\t\t\t2.vip登录\n\n");
		printf("\t\t\t\t\tq.返回\n\n");
		s = Select();
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
void adminpage()
{
	int c;
	while (1)
	{
		system("cls");
		printf("\n\n\n\n\n");
		printf("\t\t\t\t\t影片上架(1)\n\n");
		printf("\t\t\t\t\t影片查找(2)\n\n");
		printf("\t\t\t\t\t显示影片列表(3)\n\n");
		printf("\t\t\t\t\t退出登录(q)\n\n");
		c = Select();
		if (checkselect(c, "1234q"))
		{
			switch (c)
			{
			case '1':
			{
				int i;
				system("cls");
				printf("请输入上架电影的数量:");
				scanf("%d", &i);//TODO判断合法性
				getchar();
				while (i-- > 0)
				{
					struct film f;
					printf("请输入:碟名                 \
国家 类型 年份          状态 价格   总量 余量\n");
					scanf("%s %c %c %c %c %f %hhd %hhd",f.film_name,
						&f.film_country,&f.film_type,&f.film_year,
						&f.is_borrow,&f.film_price,&f.film_sum,&f.film_left);
					insertFilm(f.film_name, f.film_country, f.film_type, f.film_year,
						f.is_borrow, f.film_price, f.film_sum, f.film_left);
				}
				back();
				break;
			}
			case '2':
			{
				system("cls");
				char name[30];
				printf("请输入影片名:");
				scanf("%s", name);
				getchar();
				if (NULL == getFilmByName(name, &f))
				{
					color(12, "无此影片\n");
					back();
				}
				else
					adminfilmoperatepage();
				break;
			}
			case '3':
			{
				adminfilmshowpage();
				break;
			}
			case 'q':
				USERTYPE = 0;
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
		printf("\n\n\n\n\n");
		printf("\t\t\t\t\t显示所有影片(1)\n\n");
		printf("\t\t\t\t\t显示特定区间影片(2)\n\n");
		printf("返回(q)\n");
		c = Select();
		if (c == '1' || c == '2' || c == 'q')
		{
			switch (c)
			{
			case '1':
			{
				int c;
				system("cls");
				showAllFilm();
				printf("\n共有%d部影片\n", getFilmSumFromFilminfo());
				printf("\n返回(q)");
				while (1)
				{
					c = Select();
					if (c == 'q')
						break;
				}
				break;
			}
			case '2':
			{
				int a, b, c;
				system("cls");
				printf("当前电影数:%d\n请输入开始及结束位置:",getFilmSumFromFilminfo());
				scanf("%d %d", &a, &b);
				getchar();
				showFilmList(a, b);
				printf("\n返回(q)");//TODO无法返回
				while (1)
				{
					c = Select();
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
		c = Select();
		if (checkselect(c, "1234q"))
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
				getchar();
				f.film_price = newprice;
				changeFilm(f.id, f);
				color(10,"修改成功!\n");
				back();
				break;
			}
			case '3':
			{
				int newleftnum;
				printf("请输入新余量:______\b\b\b\b\b\b");
				scanf("%d", &newleftnum);
				getchar();
				if (newleftnum > f.film_sum)
					color(12,"错误,余量大于总量!\n");
				else
				{
					f.film_left = newleftnum;
					changeFilm(f.id, f);
					color(10,"修改成功!\n");
				}
				back();
				break;
			}
			case '4':
			{
				int newnum;
				printf("请输入新总量:______\b\b\b\b\b\b");
				scanf("%d", &newnum);
				getchar();
				if (newnum < f.film_left)
					color(12,"错误,总量小于余量!\n");
				else
				{
					f.film_left = newnum;
					changeFilm(f.id, f);
					color(10,"修改成功!\n");
				}
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
	int cartfilmnum = 0;
	while (1)
	{
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t\t\t影片查询(1)\n\n");
		printf("\t\t\t\t\t影片归还(2)\n\n");
		printf("\t\t\t\t\t我的购物车(3)\n\n");
		printf("\t\t\t\t\t个人中心(4)\n\n");
		printf("\t\t\t\t\t充值(5)\n\n");
		printf("\t\t\t\t\t退出登录(q)\n\n");
		s = Select();
		if (!checkselect(s,"12345q"))
			continue;
		switch (s)
		{
		case '1':
			filmpage();
			break;
		case '2':
			returnpage();
			break;
		case '3':
		{
			char c;
			while (1)
			{
				if (head->next)
				{
					system("cls");
					printf("当前购物车有以下影片\n");
					cartfilmnum = showcart(head);
					printf("全部借阅(1) 部分借阅(2) 清空购物车(3) 返回(q)\n");
					c = Select();
					if (checkselect(c, "123q"))
						break;
				}
				else//购物车为空的情况
				{
					system("cls");
					printf("当前购物车为空\n");
					c = 'q';
					back();
					break;
				}
			}
			if (c == '1')
			{
				int filmnum = getvipborrowfilmnum(v.id);
				if (filmnum + cartfilmnum <= MAX_FILM_BORROW_NUM)//判断借阅数量
				{
					borrowfilm(head, v.id);
					color(10,"借阅成功！\n");
					clearcart(head);
				}
				else
					color(12,"借阅数量超出限制,请您先归还一些影片\n");
				back();
				break;
			}
			if (c == '2')
			{
				while (1)
				{
					int fid, f = 1, s;
					printf("请输入您要借阅的影片id:______\b\b\b\b\b\b");
					scanf("%d", &fid);
					getchar();
					cartptr c = head->next;
					while (c)
					{
						if (c->fb->film_id == fid)
						{
							f = 0;
							break;
						}
						c = c->next;
					}
					if (f)//判断id
					{
						color(12, "您输入的id有误！\n");
						printf("重试(1) 返回(q)\n");
						s = Select();
						if (checkselect(s, "1q"))
						{
							if (s == '1')
								continue;
							if (s == 'q')
								break;
						}
					}
					else
					{
						int filmnum = getvipborrowfilmnum(v.id);
						if (filmnum < MAX_FILM_BORROW_NUM)//判断借阅数量
						{
							borrowsinglefilm(head, v.id, fid);
							color(10,"借阅成功！\n");
						}
						else
							color(12,"借阅数量超出限制,请您先归还一些影片\n");
						back();
						break;
					}
				}
			}
			if (c == '3')
			{
				system("cls");
				clearcart(head);
				color(10,"购物车已清空");
				back();
				continue;
			}
			if (c == 'q')
				break;
			break;
		}
		case '4':
		{
			system("cls");
			int flag = 1, num = 0;
			int nowtime = Get_time();
			printf("个人信息:\n\n\t用户名         余额 可借阅影片数(最多可借%d部影片)\n", MAX_FILM_BORROW_NUM);
			printf("\t%-15s%-5d%-5d\n", v.name, v.balance, MAX_FILM_BORROW_NUM - getvipborrowfilmnum(v.id));
			struct cart * c = getvipfilm(v.id);
			c = c->next;
			printf("\n您的借阅信息:\n\n");
			printf("\t影片id  影片名            影片租借金额     影片租借时长(天)\n");
			while (c)
			{
				if (c->fb->status == 0)
				{
					flag = 0;
					num++;
					printf("\t%-4d    %-15s   %-3d              %-d\n", c->fb->film_id,
						getFilmNameByid(c->fb->film_id),
						disk_rent(c->fb->borrow_time, nowtime),
						(nowtime-c->fb->borrow_time)/24);
				}
				c = c->next;
			}
			
			if (flag)
				printf("\t您暂无借阅影片\n");
			else
				printf("\t您当前借阅了%d张影片\n", num);
			printf("\n您的归还信息:\n\n");
			c = getvipfilm(v.id);
			c = c->next;
			flag = 1;
			printf("\t影片名\n");
			while (c)
			{
				if (c->fb->status == 1)
				{
					flag = 0;
					printf("\t%s\n", getFilmNameByid(c->fb->film_id));
				}
				c = c->next;
			}
			if (flag)
				printf("\t您暂无归还任何影片\n");
			back();
			break;
		}
		case '5':
		{
			rechargepage();
			back();
			break;
		}
		case 'q':
			USERTYPE = 0;
			return;
		}
	}
}
void rechargepage()
{
	system("cls");
	int balance;
	printf("您当前余额%d\n请输入您要充值的金额:______\b\b\b\b\b\b", v.balance);
	scanf("%d", &balance);
	getchar();
	v.balance += balance;
	changevip(v, v.id);
	color(10, "充值成功!\n");
	printf("您的余额为%d\n", v.balance);
}
void returnpage()
{
	char s;
	int pay, paysum = 0;
	int nowtime = Get_time();//获取当前时间
	while (1)
	{
		int flag = 1;
		struct cart * c = getvipfilm(v.id);
		c = c->next;
		system("cls");
		printf("您当前借阅了以下影片:\n");
		printf("影片id   影片名            影片租借金额\n");
		while (c)
		{
			if (c->fb->status == 0)
			{
				flag = 0;
				pay = disk_rent(c->fb->borrow_time, nowtime);
				printf("%-4d    %-15s    %-4d\n", c->fb->film_id,
					getFilmNameByid(c->fb->film_id), pay);
				paysum += pay;
			}
			c = c->next;
		}
		if (flag)//没有借阅影片的情况
		{
			printf("您当前没有借阅影片");
			back();
			break;
		}	
		printf("全部归还(1) 部分归还(2) 返回(q)\n");
		s = Select();
		if (!checkselect(s, "12q"))
			continue;
		switch (s)
		{
		case '1':
			printf("您需要支付%d元\n", paysum);
			if (v.balance < paysum)
				color(12,"您的余额不足,请前往个人中心充值\n");
			else
			{
				returnall(v.id);
				v.balance -= paysum;
				changevip(v, v.id);
				color(10, "您已成功归还!");
				printf("支付%d元, 您当前的余额为%d元\n", paysum, v.balance);
			}
			back();
			break;
		case '2':
		{
			int fid, f = 1;
			printf("请输入您要归还的影片id号:______\b\b\b\b\b\b");
			scanf("%d", &fid);
			getchar();//吸收换行符
			c = getvipfilm(v.id);
			c = c->next;
			while (c)
			{
				if (c->fb->status == 0)
				{
					if (c->fb->film_id == fid)//匹配影片id号
					{
						f = 0;
						pay = disk_rent(c->fb->borrow_time, nowtime);
						printf("您需要支付%d元\n", pay);
						if (v.balance < pay)
							color(12,"您的余额不足,请前往个人中心充值\n");
						else
						{
							retursinglefilm(v.id, fid);
							v.balance -= pay;
							changevip(v, v.id);
							color(10, "您已成功归还!\n");
							printf("支付%d元,您当前的余额为%d元\n", pay, v.balance);
						}
					}
				}
				c = c->next;
			}
			if (f)
				color(12,"输入id错误 请重新输入\n");
			back();
			break;
		}
		case 'q':
			return;
		}
	}
}