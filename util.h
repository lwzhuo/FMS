char Select();//����ɸѡ
void back();//���ؼ�
int Get_time();
int disk_rent(long borrow_t1, long back_t2);
struct cart * cartinit(struct cart * head);
void addfilm(struct cart *head, struct filmborrow *fb);
int showcart(struct cart *head);//���ع��ﳵ��ӰƬ����
int checkselect(int select, char * str);
void clearcart(struct cart * head);
char * showborrowtime(long borrowtie);
void color(int x, char *str);