#ifndef _PAGE_H
#define _PAGE_H
int Homepage();//登录页面(所有页面最底层) 返回: 1:停留主页面 0:退出
void filmpage();//影片页面
void Loginpage();//登录页面
void borrowpage(struct film f);//借阅页面
void adminpage();//管理员页面
void adminpage_film();//电影管理页面
void adminpage_user();//用户管理页面
void init();//初始化配置文件
void adminfilmshowpage();//管理员电影显示页面
void adminfilmsearchpage();//管理员电影查找页面
void adminfilmoperatepage();//管理员影片操作
void vippage();
#endif // !_PAGE_H

