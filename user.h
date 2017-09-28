#ifndef _USER_H
#define _USER_H
void registration();
void viplogin();
void adminlogin();
void createvip(int id, char * username, char * password);//创建vip用户
void createadmin(int id, char * username, char * password);//创建管理员用户
void changevipinfo(int newnum, int newid);
#endif // !_USER_H
