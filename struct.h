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
	int filmnum;
};
struct vipinfo {//��ʾ��Ӱ���ݴ洢�ļ�����Ϣ size12
	int num;
	int singlevipsize;
	int nextid;
};
struct admin//size 40
{
	int id;
	char name[20];
	char password[16];
};
struct vip v;
struct film f;//ȫ�ֱ��� �������м����ؽ��ڴ� ��Ϊ��������ʱͨ��
#endif // !_STRUCT_H

