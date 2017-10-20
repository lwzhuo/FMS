#ifndef _USER_H
#define _USER_H
int registration(char * name, char * pass);
void viplogin();
void adminlogin();
void createvip(char * username, char * password);//创建vip用户
void createadmin(int id, char * username, char * password);//创建管理员用户
void changevipinfo(int newnum, int newid);//更改vip配置文件
void viewvipinfo();//窥探用户信息文件内容(调试用)
void showUserlist();
int getvipnum();
int searchVipByName(char * name, struct vip *);//未使用
int getVipById(int id, struct vip *);//未使用
void changevip(struct vip vip, int id);
struct cart * getvipfilm(int uid);
int getvipborrowfilmnum(int id);
#endif // !_USER_H
