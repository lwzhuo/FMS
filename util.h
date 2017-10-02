char checkselect();//ÊäÈëÉ¸Ñ¡
void back();//·µ»Ø¼ü
int Get_time();
int disk_rent(long borrow_t1, long back_t2);
struct cart * cartinit(struct cart * head);
void addfilm(struct cart *head, struct filmborrow *fb);
int showcart(struct cart *head);