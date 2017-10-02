#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"util.h"
#include"struct.h"
#include"user.h"
#include"page.h"
#include"film.h"
#include"public.h"
#include<stdlib.h>
extern USERTYPE;
void init()//�����ļ��������ⲿ���ã� ���ڳ�ʼ�������ļ�ʱ����
{
	/*��Ӱ�����ļ���ʼ��*/
	struct filminfo info;
	info.num = 0;
	info.singlefilmsize = 48;
	info.nextid = 1;
	FILE *f1 = fopen("filminfo", "wb");
	fwrite(&info, sizeof(struct filminfo), 1, f1);
	fclose(f1);
	/*�û������ļ���ʼ��*/
	struct vipinfo vinfo;
	vinfo.num = 0;
	vinfo.singlevipsize = 48;
	vinfo.nextid = 1;
	FILE *f2 = fopen("vipinfo", "wb");
	fwrite(&vinfo, sizeof(struct vipinfo), 1, f2);
	fclose(f2);
	printf("��ʼ�����\n");//TODO��ɼ��
}
int Homepage()
{
	int c;
	/*�˵�չʾ������ɸѡ��ʼ*/
	while (1)
	{
		system("cls");
		/*�����û��Ƿ��¼��ʾ��ͬѡ��*/
		if (USERTYPE)
		{
			printf("ӰƬ��ѯ(1)\n");
			printf("������ҳ(2)\n");
		}
		else
		{
			printf("ע��(1)\n");
			printf("��¼(2)\n");
		}
		printf("�˳�ϵͳ(q)\n");
		c = checkselect();
		if (c == '1' || c == '2' || c == 'q')//ɸѡ����
			break;
	}
	/*�˵�չʾ������ɸѡ����*/
	/*�����жϿ�ʼ*/
	if (c == '1')
	{
		if (USERTYPE)
		{
			filmpage();//ӰƬ��ѯҳ��
			return 1;
		}
		else
		{
			registration();//�û�ע��ҳ��
			return 1;
		}
	}
	else if (c == '2')
	{
		if (USERTYPE)
		{
			vippage();//TODO ����·��
		}
		else
		{
			Loginpage();//��¼ҳ��
			return 1;
		}
	}
	else if (c == 'q')
		return 0;
	else
		return 0;
	/*�����жϽ���*/
}
void filmpage()
{
	int c;
	while (1)
	{
		system("cls");
		printf("����ӰƬ����ѯ(1)\n");
		printf("ͨ�����Ҳ���(2)\n");
		printf("ͨ��ӰƬ���Ͳ���(3)\n");
		printf("����(q)\n");
		c = checkselect();
		if ((c >= '1' && c <= '3') || c == 'q')
			break;
	}
	switch (c)
	{
	case '1':
	{
		char name[30];
		printf("������ӰƬ��:");
		scanf("%s", name);
		if (getFilmInfoByName(name, &f) == NULL)
		{
			printf("δ�ҵ���ӦӰƬ!\n");
			back();
		}
		else
			borrowpage(f);
		break;
	}
	case '2':
		break;
	case '3':
		break;
	case 'q':
		break;
	}
}
void borrowpage(struct film f)
{
	char c;
	while (1)
	{
		system("cls");
		printFilminfo(f);
		printf("\n���빺�ﳵ(1)   ����(2)\n");
		c = checkselect();
		if (c == '1' || c == '2')
			break;
	}
	switch (c)
	{
	case '1':
	{
		struct filmborrow fb;//���첢��װ���ﳵ
		fb.borrow_time = Get_time();//������ʱ��
		fb.film_id = f.id;
		addfilm(head, &fb);//���빺�ﳵ
		printf("��ӳɹ�!");//TODO�ж���ӳɹ�
		showcart(head);
		back();
		break;
	}
	case '2':
		return;
	}
}
void Loginpage()
{
	int c;
	while (1)
	{
		if (USERTYPE)//����Ѿ���¼ ����ʾ���²˵�
			return;
		system("cls");
		printf("1.����Ա��¼\n");
		printf("2.vip��¼\n");
		printf("3.����\n");
		c = checkselect();
		if (c == '1' || c == '2' || c == '3')
		{
			if (c == '1')
			{
				adminlogin();
				if (USERTYPE == 2)//����Ƿ��Թ���Ա����Ѿ���¼
					adminpage();
			}
			if (c == '2')
				viplogin();
			if (c == '3')
				return ;
		}
	}
}
void adminpage()//�˻���һ������
{
	int c;
	while (1)
	{
		system("cls");
		printf("ӰƬ����(1)\n");
		printf("�û�����(2)\n");
		printf("����(q)\n");
		c = checkselect();
		if (c == '1' || c == '2' || c == 'q')
		{
			switch (c)
			{
			case '1':
				adminpage_film();
				break;
			case '2':
				adminpage_user();
				break;
			case 'q':
				return;//�˳���ҳ��
			}
		}
	}
}
void adminpage_film()
{
	int c;
	while (1)
	{
		system("cls");
		printf("ӰƬ�ϼ�(1)\n");
		printf("ӰƬ����(2)\n");
		printf("��ʾӰƬ�б�(3)\n");
		printf("����(q)\n");
		c = checkselect();
		if ((c >='1'&&c<='3')|| c == 'q')
		{
			switch (c)
			{
			case '1':
			{
				int i;
				printf("�������ϼܵ�Ӱ������:");
				scanf("%d", &i);//TODO�жϺϷ���
				while (i-- > 0)
				{
					struct film f;
					printf("������:����                 \
���� ���� ���          ״̬ �۸�   ���� ����\n");
					scanf("%s %c %c %c %c %f %hhd %hhd",f.film_name,
						&f.film_country,&f.film_type,&f.film_year,
						&f.is_borrow,&f.film_price,&f.film_sum,&f.film_left);
					printFilminfo(f);
					insertFilm(f.film_name, f.film_country, f.film_type, f.film_year,
						f.is_borrow, f.film_price, f.film_sum, f.film_left);
				}
				break;
			}
			case '2':
				adminfilmsearchpage();
				break;
			case '3':
			{
				adminfilmshowpage();
				break;
			}
			case 'q':
				return;//�˳���ҳ��
			}
		}
	}
}
void adminfilmshowpage()//ӰƬ��ʾҳ��
{
	int c;
	while (1)
	{
		system("cls");
		printf("��ʾ����ӰƬ(1)\n");
		printf("��ʾ�ض�����ӰƬ(2)\n");
		printf("����(q)\n");
		c = checkselect();
		if (c == '1' || c == '2' || c == 'q')
		{
			switch (c)
			{
			case '1':
			{
				int c;
				showAllFilm();
				printf("\n����%d��ӰƬ\n", getFilmSumFromFilminfo());
				printf("\n����(q)");
				while (1)
				{
					c = checkselect();
					if (c == 'q')
						break;
				}
				break;
			}
			case '2':
			{
				int a, b, c;
				printf("��ǰ��Ӱ��:%d\n�����뿪ʼ������λ��:",getFilmSumFromFilminfo());
				scanf("%d %d", &a, &b);
				showFilmList(a, b);
				printf("\n����(q)");//TODO�޷�����
				while (1)
				{
					c = checkselect();
					if (c == 'q')
						break;
				}
				break;
			}
			case 'q':
				return;//�˳���ҳ��
			}
		}
	}
}
void adminpage_user()
{
	//TODO
}
void adminfilmsearchpage()//TODO
{
	int c;
	while (1)
	{
		system("cls");
		printf("ͨ�����ֲ���(1)\n");
		printf("ͨ�����Ҳ���(2)\n");
		printf("ͨ�����Ͳ���(3)\n");
		printf("ͨ����ݲ���(4)\n");
		printf("����(q)\n");
		c = checkselect();
		if ((c >= '1' && c <= '4') || c == 'q')
		{
			switch (c)
			{
			case '1':
			{
				char name[30];
				printf("������ӰƬ��:");
				scanf("%s", name);
				if (NULL == getFilmInfoByName(name, &f))
					printf("�޴�ӰƬ\n");
				else
				{
					adminfilmoperatepage();
				}
				//printf("\n����(q)");//TODO ���������޸�
				//while (1)
				//{
				//	c = checkselect();
				//	if (c == 'q')
				//		break;
				//}
				break;
			}
			case '2':
				//TODO
				break;
			case '3':
				//TODO
				break;
			case '4':
				//TODO
				break;
			case 'q':
				return;//�˳���ҳ��
			}
		}
	}
}
void adminfilmoperatepage()
{
	//��һ��ҳ���ҵ��ĵ�Ӱ���ؽ��ڴ��� ������ҳ�����
	int c;
	while (1)
	{
		system("cls");
		printFilminfo(f);//��ӡ��һ��ҳ����ҵ��ĵ�Ӱ
		printf("ɾ�������Ӱ(1)");
		printf("  �޸ĵ�Ӱ�۸�(2)");
		printf("  �޸ĵ�Ӱ����(3)");
		printf("  �޸ĵ�Ӱ����(4)");
		printf("  ����(q)\n");
		c = checkselect();
		if ((c >= '1' && c <= '4') || c == 'q')
		{
			switch (c)
			{
			case '1':
			{
				deleteFilmByName(f.film_name);
				back();
				break;
			}
			case '2':
			{
				float newprice;
				printf("�������¼۸�:______\b\b\b\b\b\b");
				scanf("%f", &newprice);
				changeFilmPrice(f.film_name, newprice);
				break;
			}
			case '3':
			{
				int num;
				printf("������������:______\b\b\b\b\b\b");
				scanf("%d", &num);
				changeFilmLeftNum(f.film_name, num);
				break;
			}
			case '4':
			{
				int num;
				//printf("������������:______\b\b\b\b\b\b");
				//scanf("%d", &num);
				
				back();
				break;
			}
			case 'q':
				return;//�˳���ҳ��
			}
		}
	}
}
void vippage()
{
	char c;
	while (1)
	{
		system("cls");
		printf("���ﳵ(1)  �ҵĽ�����Ϣ(2) �˳���¼(3) ����(q)");
		c = checkselect();
		if (c >= '1'&&c <= '3' || c == 'q')
			break;
	}
	switch (c)
	{
	case '1':
	{
		if (showcart(head))//TODO
		{
			borrowfilm(head,v.id);
		}
		back();
		break;
	}
	case '2':
		return;
	case '3':
	{
		USERTYPE = 0;
		return;
	}
	case 'q':
		return;
	}
}
