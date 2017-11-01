#ifndef _PAGE_H
#define _PAGE_H
int Homepage();//登录页面(所有页面最底层) 返回: 1:停留主页面 0:退出
void filmpage();//影片页面
void loginpage();//登录页面
void borrowpage(struct film f);//借阅页面
void adminpage();//管理员页面
void init();//初始化配置文件
void adminuserpage();//管理员用户管理页面
void adminfilmpage();//管理员电影管理页面
void adminfilmshowpage();//管理员电影显示页面
void adminfilmoperatepage();//管理员影片操作
void vippage();
void registrationpage();
void rechargepage();//账户充值页面
void returnpage();//账户影片归还页面
#endif // !_PAGE_H

