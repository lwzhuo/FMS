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
	int s;
	while (1)
	{
		system("cls");
		printf("ע��(1)\n");
		printf("��¼(2)\n");
		printf("�˳�ϵͳ(q)\n");
		s = select();
		if (checkselect(s, "12q"))
		{
			switch (s)
			{
			case '1':
				registrationpage();
				break;
			case '2':
				loginpage();
				break;
			case 'q':
				return 0;
			default:
				break;
			}
		}
	}
	return 0;
}
void registrationpage()
{
	system("cls");
	char name[20], pass[16], c;
	int id = 1, i = 0;
	printf("�������û���__________\b\b\b\b\b\b\b\b\b\b");
	gets(name);
	printf("����������__________\b\b\b\b\b\b\b\b\b\b");
	while (c = _getch())//�û���������
	{
		if (c != 13)
		{
			putchar('*');
			pass[i++] = c;
		}
		else
		{
			pass[i] = '\0';
			break;
		}
	}
	if (registration(name, pass))
		printf("\nע��ɹ�\n");
	else
		printf("\n�û����ѱ�ʹ��,ע��ʧ��\n");
	back();
}
void filmpage()
{
	int s;
	while (1)
	{
		system("cls");
		printf("����ӰƬ����ѯ(1)\n");
		printf("ͨ�����Ҳ���(2)\n");
		printf("ͨ��ӰƬ���Ͳ���(3)\n");
		printf("����(q)\n");
		s = select();
		if (checkselect(s,"123q"))
			break;
	}
	switch (s)
	{
	case '1':
	{
		char name[30];
		printf("������ӰƬ��:");
		scanf("%s", name);
		if (getFilmByName(name, &f) == NULL)
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
		c = select();
		if (c == '1' || c == '2')
			break;
	}
	switch (c)
	{
	case '1':
	{
		system("cls");
		struct filmborrow fb;//���첢��װ���ﳵ
		fb.borrow_time = Get_time();//������ʱ��
		fb.film_id = f.id;
		addfilm(head, &fb);//���빺�ﳵ
		printf("��ӳɹ�!\n��ǰ���ﳵ������ӰƬ\n");//TODO�ж���ӳɹ�
		showcart(head);
		back();
		break;
	}
	case '2':
		return;
	}
}
void loginpage()
{
	int s;
	while (1)
	{
		if (USERTYPE)//����Ѿ���¼ ����ʾ���²˵�
			return;
		system("cls");
		printf("1.����Ա��¼\n");
		printf("2.vip��¼\n");
		printf("q.����\n");
		s = select();
		if (checkselect(s,"12q"))
		{
			if (s == '1')
			{
				adminlogin();
				if (USERTYPE == 2)//����Ƿ��Թ���Ա��ݵ�¼
					adminpage();
			}
			if (s == '2')
			{
				viplogin();
				if(USERTYPE==1)//����Ƿ���vip��ݵ�¼
					vippage();
			}
			if (s == 'q')
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
		c = select();
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
		c = select();
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
		c = select();
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
					c = select();
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
					c = select();
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
		c = select();
		if ((c >= '1' && c <= '4') || c == 'q')
		{
			switch (c)
			{
			case '1':
			{
				char name[30];
				printf("������ӰƬ��:");
				scanf("%s", name);
				if (NULL == getFilmByName(name, &f))
					printf("�޴�ӰƬ\n");
				else
				{
					adminfilmoperatepage();
				}
				//printf("\n����(q)");//TODO ���������޸�
				//while (1)
				//{
				//	c = select();
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
		c = select();
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
void vippage()//ҳ�湹������
{
	char s;
	while (1)
	{
		system("cls");
		printf("ӰƬ����(1)  ӰƬ�黹(2) �ҵĹ��ﳵ(3) ��������(4) �˳���¼(q)");
		s = select();
		if (!checkselect(s,"1234q"))
			continue;
		switch (s)
		{
		case '1':
		{
			filmpage();
			break;
		}
		case '2':
			break;
		case '3':
		{
			printf("��ǰ���ﳵ������ӰƬ\n");
			showcart(head);
			printf("ȫ������(1)\n");//TODO����
			borrowfilm(head, v.id);
			//clearcart(head);
			break;
		}
		case '4':
			printf("������Ϣ: �û���      ���\n");
			printf("%s  %d\n", v.name, v.balance);
			printf("������Ϣ:\n");
			showvipfilm(v.id);
			back();
			break;
		case 'q':
			USERTYPE = 0;
			return;
		}
	}
}