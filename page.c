#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"util.h"
#include"struct.h"
#include"user.h"
#include"page.h"
#include"film.h"
#include"public.h"
#include<stdlib.h>
#include<string.h>
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
		char name[30];
		printf("请输入影片名:");
		scanf("%s", name);
		getchar();//吸收回车符
		if (getFilmByName(name, &f) == NULL)
		{
			printf("未找到相应影片!\n");
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
		c = select();
		if (checkselect(c,"1q"))
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
		fb.status = 0;
		addfilm(head, &fb);//加入购物车
		printf("添加成功!\n当前购物车有以下影片\n");//TODO判断添加成功
		showcart(head);
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
void adminpage()
{
	int c;
	while (1)
	{
		system("cls");
		printf("影片上架(1)\n");
		printf("影片查找(2)\n");
		printf("显示影片列表(3)\n");
		printf("退出登录(q)\n");
		c = select();
		if (checkselect(c, "1234q"))
		{
			switch (c)
			{
			case '1':
			{
				int i;
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
					printFilminfo(f);
					insertFilm(f.film_name, f.film_country, f.film_type, f.film_year,
						f.is_borrow, f.film_price, f.film_sum, f.film_left);
				}
				break;
			}
			case '2':
			{
				char name[30];
				printf("请输入影片名:");
				scanf("%s", name);
				if (NULL == getFilmByName(name, &f))
				{
					printf("无此影片\n");
					back();
				}
				else
				{
					adminfilmoperatepage();
				}
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
				getchar();
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
		//printf("  修改电影总量(4)");
		printf("  返回(q)\n");
		c = select();
		if (checkselect(c, "123q"))
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
				changeFilmPrice(f.id, newprice);
				printf("修改成功!\n");
				back();
				break;
			}
			case '3':
			{
				system("cls");
				int num;
				printf("请输入新余量:______\b\b\b\b\b\b");
				scanf("%d", &num);
				getchar();
				if (num > f.film_sum)
					printf("错误,余量大于总量!\n");
				else
				{
					changeFilmLeftNum(f.id, num);
					printf("修改成功!\n");
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
		printf("影片查询(1)  影片归还(2) 我的购物车(3) 个人中心(4) 充值(5) 退出登录(q)");
		s = select();
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
					c = select();
					if (checkselect(c, "123q"))
						break;
				}
				else//购物车为空的情况
				{
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
					printf("借阅成功！\n");
					clearcart(head);
				}
				else
					printf("借阅数量超出限制,请您先归还一些影片\n");
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
						printf("您输入的id有误！重试(1) 返回(q)\n");
						s = select();
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
							printf("借阅成功！\n");
						}
						else
							printf("借阅数量超出限制,请您先归还一些影片\n");
						back();
						break;
					}
				}
			}
			if (c == '3')
			{
				system("cls");
				clearcart(head);
				printf("购物车已清空");
				back();
				continue;
			}
			if (c == 'q')
				break;
			break;
		}
		case '4':
		{
			int flag = 1, num = 0;
			int nowtime = Get_time();
			printf("个人信息:\n\t用户名      余额   可借阅影片数(最多可借%d部影片)\n", MAX_FILM_BORROW_NUM);
			printf("\t%s        %d   %d\n", v.name, v.balance, MAX_FILM_BORROW_NUM - getvipborrowfilmnum(v.id));
			struct cart * c = getvipfilm(v.id);
			c = c->next;
			printf("\n您的借阅信息:\n");
			printf("\t影片id    影片名    影片租借金额     影片租借时长(天)\n");
			while (c)
			{
				if (c->fb->status == 0)
				{
					flag = 0;
					num++;
					printf("\t%d %s   %d    %d\n", c->fb->film_id,
						getFilmNameByid(c->fb->film_id),
						disk_rent(c->fb->borrow_time, nowtime),
						(nowtime-c->fb->borrow_time)/24);
				}
				c = c->next;
			}
			printf("您当前借阅了%d张影片\n", num);
			if (flag)
				printf("\t您暂无借阅影片\n");
			printf("\n您的归还信息:\n");
			c = getvipfilm(v.id);
			c = c->next;
			flag = 1;
			while (c)
			{
				if (c->fb->status == 1)
				{
					flag = 0;
					printf("\t%d %s\n", c->fb->film_id,
						getFilmNameByid(c->fb->film_id));
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
	int balance;
	printf("您当前余额%d\n请输入您要充值的金额:______\b\b\b\b\b\b", v.balance);
	scanf("%d", &balance);
	getchar();
	v.balance += balance;
	changevip(v, v.id);
	printf("充值成功,您的余额为%d\n", v.balance);
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
		printf("影片id    影片名    影片租借金额\n");
		while (c)
		{
			if (c->fb->status == 0)
			{
				flag = 0;
				pay = disk_rent(c->fb->borrow_time, nowtime);
				printf("%-4d     %-20s %-4d\n", c->fb->film_id,
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
		s = select();
		if (!checkselect(s, "12q"))
			continue;
		switch (s)
		{
		case '1':
			printf("您需要支付%d元\n", paysum);
			if (v.balance < paysum)
				printf("您的余额不足,请前往个人中心充值\n");
			else
			{
				returnall(v.id);
				v.balance -= paysum;
				changevip(v, v.id);
				printf("您已成功归还,支付%d元,您当前的余额为%d元\n", paysum, v.balance);
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
							printf("您的余额不足,请前往个人中心充值\n");
						else
						{
							retursinglefilm(v.id, fid);
							v.balance -= pay;
							changevip(v, v.id);
							printf("您已成功归还,支付%d元,您当前的余额为%d元\n", pay, v.balance);
						}
					}
				}
				c = c->next;
			}
			if (f)
				printf("输入id错误 请重新输入\n");
			back();
			break;
		}
		case 'q':
			return;
		}
	}
}