#ifndef _STRUCT_H
#define _STRUCT_H

/*����Ϊ�ṹ������*/
//��С48�ֽڵ�film�ṹ�� 8�����ݶ���
struct film {
	int id;//id���
	char film_name[30];//����
	char film_country;//����
	char film_type;//����
	char film_year;//���
	char is_borrow;//�ɽ���  0:���ɽ� 1:�ɽ� 2:�¼� 3:��ɾ��
	float film_price;//�۸�
	char film_sum;//����
	char film_left;//����
};
struct filminfo {//��ʾ��Ӱ���ݴ洢�ļ�����Ϣ 12
	int num;
	int singlefilmsize;
	int nextid;
};
struct vip//size 48
{
	int id;
	char name[20];
	char password[16];
	int balance;
	int filmnum;//�ܽ��ĵ�Ӱ��
};
struct vipinfo {//��ʾ��Ӱ���ݴ洢�ļ�����Ϣ size12
	int num;
	int singlevipsize;
	int nextid;
};
struct filmborrow {//��ʾӰƬ�����Ϣ size9
	int film_id;//id
	int borrow_time;// ʱ��
	char status;//��ʾӰƬ�Լ��û�����״̬ ����0 �黹1 ӰƬ�¼�2
};
typedef struct cart *cartptr;
typedef struct cart cartnode;
struct cart {//��ͷ��� ͷ��㲻��ӰƬ��Ϣ
	struct filmborrow * fb;
	cartptr next;
};
struct admin//size 40
{
	int id;
	char name[20];
	char password[16];
};
//ȫ�ֱ��� �������м����ؽ��ڴ� ��Ϊ��������ʱͨ��
struct vip v;
struct film f;
struct cart *head;
#endif // !_STRUCT_H

