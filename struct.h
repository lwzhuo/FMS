#ifndef _STRUCT_H
#define _STRUCT_H

/*以下为结构体数据*/
//大小48字节的film结构体 8个数据对象
struct film {
	int id;//id编号
	char film_name[30];//碟名
	char film_country;//国家
	char film_type;//类型
	char film_year;//年份
	char is_borrow;//可借标记  0:不可借 1:可借 2:下架 3:已删除
	float film_price;//价格
	char film_sum;//总量
	char film_left;//余量
};
struct filminfo {//标示电影数据存储文件的信息 12
	int num;
	int singlefilmsize;
	int nextid;
};
struct vip//size 48
{
	int id;
	char name[20];
	char password[16];
	int balance;
	int filmnum;//总借阅电影数
};
struct vipinfo {//标示电影数据存储文件的信息 size12
	int num;
	int singlevipsize;
	int nextid;
};
struct filmborrow {//标示影片租借信息 size9
	int film_id;//id
	int borrow_time;// 时间
	char status;//显示影片以及用户借阅状态 正常0 归还1 影片下架2
};
typedef struct cart *cartptr;
typedef struct cart cartnode;
struct cart {//有头结点 头结点不放影片信息
	struct filmborrow * fb;
	cartptr next;
};
struct admin//size 40
{
	int id;
	char name[20];
	char password[16];
};
//全局变量 程序运行即加载进内存 作为程序运行时通物
struct vip v;
struct film f;
struct cart *head;
#endif // !_STRUCT_H

