#ifndef _USER_H
#define _USER_H
int registration(char * name, char * pass);
void viplogin();
void adminlogin();
void createvip(char * username, char * password);//����vip�û�
void createadmin(int id, char * username, char * password);//��������Ա�û�
void changevipinfo(int newnum, int newid);//����vip�����ļ�
void viewvipinfo();//��̽�û���Ϣ�ļ�����(������)
void showUserlist();
int searchVipByName(char * name, struct vip *);
struct vip * getVipById(int id);
#endif // !_USER_H
