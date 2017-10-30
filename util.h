char Select();//输入筛选
void back();//返回键
int Get_time();
int disk_rent(long borrow_t1, long back_t2);
struct cart * cartinit(struct cart * head);
void addfilm(struct cart *head, struct filmborrow *fb);
int showcart(struct cart *head);//返回购物车中影片数量
int checkselect(int select, char * str);
void clearcart(struct cart * head);
char * showborrowtime(long borrowtie);
void color(int x, char *str);