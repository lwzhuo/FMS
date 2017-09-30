#ifndef _USER_H
#define _USER_H
void registration();
void viplogin();
void adminlogin();
void createvip(char * username, char * password);//创建vip用户
void createadmin(int id, char * username, char * password);//创建管理员用户
void changevipinfo(int newnum, int newid);//更改vip配置文件
void viewvipinfo();//窥探用户信息文件内容(调试用)
void showUserlist();
void searchVipByName(char * name, struct vip *);
#endif // !_USER_H
