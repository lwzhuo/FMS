#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"util.h"
#include"struct.h"
#include"user.h"
#include"page.h"
#include"film.h"
#include"public.h"
#include<stdlib.h>
#include<string.h>
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
		char name[30];
		printf("������ӰƬ��:");
		scanf("%s", name);
		getchar();//���ջس���
		if (getFilmByName(name, &f) == NULL)
		{
			printf("δ�ҵ���ӦӰƬ!\n");
			back();
		}
		else
			borrowpage(f);
}
void borrowpage(struct film f)
{
	char c;
	while (1)
	{
		system("cls");
		printFilminfo(f);
		printf("\n���빺�ﳵ(1)   ����(q)\n");
		c = select();
		if (checkselect(c,"1q"))
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
		fb.status = 0;
		addfilm(head, &fb);//���빺�ﳵ
		printf("��ӳɹ�!\n��ǰ���ﳵ������ӰƬ\n");//TODO�ж���ӳɹ�
		showcart(head);
		back();
		break;
	}
	case 'q':
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
void adminpage()
{
	int c;
	while (1)
	{
		system("cls");
		printf("ӰƬ�ϼ�(1)\n");
		printf("ӰƬ����(2)\n");
		printf("��ʾӰƬ�б�(3)\n");
		printf("�˳���¼(q)\n");
		c = select();
		if (checkselect(c, "1234q"))
		{
			switch (c)
			{
			case '1':
			{
				int i;
				printf("�������ϼܵ�Ӱ������:");
				scanf("%d", &i);//TODO�жϺϷ���
				getchar();
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
			{
				char name[30];
				printf("������ӰƬ��:");
				scanf("%s", name);
				if (NULL == getFilmByName(name, &f))
				{
					printf("�޴�ӰƬ\n");
					back();
				}
				else
				{
					adminfilmoperatepage();
				}
				break;
			}
			case '3':
			{
				adminfilmshowpage();
				break;
			}
			case 'q':
				USERTYPE = 0;
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
				getchar();
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
		//printf("  �޸ĵ�Ӱ����(4)");
		printf("  ����(q)\n");
		c = select();
		if (checkselect(c, "123q"))
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
				getchar();
				changeFilmPrice(f.id, newprice);
				printf("�޸ĳɹ�!\n");
				back();
				break;
			}
			case '3':
			{
				system("cls");
				int num;
				printf("������������:______\b\b\b\b\b\b");
				scanf("%d", &num);
				getchar();
				if (num > f.film_sum)
					printf("����,������������!\n");
				else
				{
					changeFilmLeftNum(f.id, num);
					printf("�޸ĳɹ�!\n");
				}
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
	int cartfilmnum = 0;
	while (1)
	{
		system("cls");
		printf("ӰƬ��ѯ(1)  ӰƬ�黹(2) �ҵĹ��ﳵ(3) ��������(4) ��ֵ(5) �˳���¼(q)");
		s = select();
		if (!checkselect(s,"12345q"))
			continue;
		switch (s)
		{
		case '1':
			filmpage();
			break;
		case '2':
			returnpage();
			break;
		case '3':
		{
			char c;
			while (1)
			{
				if (head->next)
				{
					system("cls");
					printf("��ǰ���ﳵ������ӰƬ\n");
					cartfilmnum = showcart(head);
					printf("ȫ������(1) ���ֽ���(2) ��չ��ﳵ(3) ����(q)\n");
					c = select();
					if (checkselect(c, "123q"))
						break;
				}
				else//���ﳵΪ�յ����
				{
					printf("��ǰ���ﳵΪ��\n");
					c = 'q';
					back();
					break;
				}
			}
			if (c == '1')
			{
				int filmnum = getvipborrowfilmnum(v.id);
				if (filmnum + cartfilmnum <= MAX_FILM_BORROW_NUM)//�жϽ�������
				{
					borrowfilm(head, v.id);
					printf("���ĳɹ���\n");
					clearcart(head);
				}
				else
					printf("����������������,�����ȹ黹һЩӰƬ\n");
				back();
				break;
			}
			if (c == '2')
			{
				while (1)
				{
					int fid, f = 1, s;
					printf("��������Ҫ���ĵ�ӰƬid:______\b\b\b\b\b\b");
					scanf("%d", &fid);
					getchar();
					cartptr c = head->next;
					while (c)
					{
						if (c->fb->film_id == fid)
						{
							f = 0;
							break;
						}
						c = c->next;
					}
					if (f)//�ж�id
					{
						printf("�������id��������(1) ����(q)\n");
						s = select();
						if (checkselect(s, "1q"))
						{
							if (s == '1')
								continue;
							if (s == 'q')
								break;
						}
					}
					else
					{
						int filmnum = getvipborrowfilmnum(v.id);
						if (filmnum < MAX_FILM_BORROW_NUM)//�жϽ�������
						{
							borrowsinglefilm(head, v.id, fid);
							printf("���ĳɹ���\n");
						}
						else
							printf("����������������,�����ȹ黹һЩӰƬ\n");
						back();
						break;
					}
				}
			}
			if (c == '3')
			{
				system("cls");
				clearcart(head);
				printf("���ﳵ�����");
				back();
				continue;
			}
			if (c == 'q')
				break;
			break;
		}
		case '4':
		{
			int flag = 1, num = 0;
			int nowtime = Get_time();
			printf("������Ϣ:\n\t�û���      ���   �ɽ���ӰƬ��(���ɽ�%d��ӰƬ)\n", MAX_FILM_BORROW_NUM);
			printf("\t%s        %d   %d\n", v.name, v.balance, MAX_FILM_BORROW_NUM - getvipborrowfilmnum(v.id));
			struct cart * c = getvipfilm(v.id);
			c = c->next;
			printf("\n���Ľ�����Ϣ:\n");
			printf("\tӰƬid    ӰƬ��    ӰƬ�����     ӰƬ���ʱ��(��)\n");
			while (c)
			{
				if (c->fb->status == 0)
				{
					flag = 0;
					num++;
					printf("\t%d %s   %d    %d\n", c->fb->film_id,
						getFilmNameByid(c->fb->film_id),
						disk_rent(c->fb->borrow_time, nowtime),
						(nowtime-c->fb->borrow_time)/24);
				}
				c = c->next;
			}
			printf("����ǰ������%d��ӰƬ\n", num);
			if (flag)
				printf("\t�����޽���ӰƬ\n");
			printf("\n���Ĺ黹��Ϣ:\n");
			c = getvipfilm(v.id);
			c = c->next;
			flag = 1;
			while (c)
			{
				if (c->fb->status == 1)
				{
					flag = 0;
					printf("\t%d %s\n", c->fb->film_id,
						getFilmNameByid(c->fb->film_id));
				}
				c = c->next;
			}
			if (flag)
				printf("\t�����޹黹�κ�ӰƬ\n");
			back();
			break;
		}
		case '5':
		{
			rechargepage();
			back();
			break;
		}
		case 'q':
			USERTYPE = 0;
			return;
		}
	}
}
void rechargepage()
{
	int balance;
	printf("����ǰ���%d\n��������Ҫ��ֵ�Ľ��:______\b\b\b\b\b\b", v.balance);
	scanf("%d", &balance);
	getchar();
	v.balance += balance;
	changevip(v, v.id);
	printf("��ֵ�ɹ�,�������Ϊ%d\n", v.balance);
}
void returnpage()
{
	char s;
	int pay, paysum = 0;
	int nowtime = Get_time();//��ȡ��ǰʱ��
	while (1)
	{
		int flag = 1;
		struct cart * c = getvipfilm(v.id);
		c = c->next;
		system("cls");
		printf("����ǰ����������ӰƬ:\n");
		printf("ӰƬid    ӰƬ��    ӰƬ�����\n");
		while (c)
		{
			if (c->fb->status == 0)
			{
				flag = 0;
				pay = disk_rent(c->fb->borrow_time, nowtime);
				printf("%-4d     %-20s %-4d\n", c->fb->film_id,
					getFilmNameByid(c->fb->film_id), pay);
				paysum += pay;
			}
			c = c->next;
		}
		if (flag)//û�н���ӰƬ�����
		{
			printf("����ǰû�н���ӰƬ");
			back();
			break;
		}	
		printf("ȫ���黹(1) ���ֹ黹(2) ����(q)\n");
		s = select();
		if (!checkselect(s, "12q"))
			continue;
		switch (s)
		{
		case '1':
			printf("����Ҫ֧��%dԪ\n", paysum);
			if (v.balance < paysum)
				printf("��������,��ǰ���������ĳ�ֵ\n");
			else
			{
				returnall(v.id);
				v.balance -= paysum;
				changevip(v, v.id);
				printf("���ѳɹ��黹,֧��%dԪ,����ǰ�����Ϊ%dԪ\n", paysum, v.balance);
			}
			back();
			break;
		case '2':
		{
			int fid, f = 1;
			printf("��������Ҫ�黹��ӰƬid��:______\b\b\b\b\b\b");
			scanf("%d", &fid);
			getchar();//���ջ��з�
			c = getvipfilm(v.id);
			c = c->next;
			while (c)
			{
				if (c->fb->status == 0)
				{
					if (c->fb->film_id == fid)//ƥ��ӰƬid��
					{
						f = 0;
						pay = disk_rent(c->fb->borrow_time, nowtime);
						printf("����Ҫ֧��%dԪ\n", pay);
						if (v.balance < pay)
							printf("��������,��ǰ���������ĳ�ֵ\n");
						else
						{
							retursinglefilm(v.id, fid);
							v.balance -= pay;
							changevip(v, v.id);
							printf("���ѳɹ��黹,֧��%dԪ,����ǰ�����Ϊ%dԪ\n", pay, v.balance);
						}
					}
				}
				c = c->next;
			}
			if (f)
				printf("����id���� ����������\n");
			back();
			break;
		}
		case 'q':
			return;
		}
	}
}