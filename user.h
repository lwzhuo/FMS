#ifndef _USER_H
#define _USER_H
void registration();
void viplogin();
void adminlogin();
void createvip(int id, char * username, char * password);//����vip�û�
void createadmin(int id, char * username, char * password);//��������Ա�û�
void changevipinfo(int newnum, int newid);
#endif // !_USER_H
