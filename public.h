#pragma once
#ifndef _PUBLIC_H
#define _PUBLIC_H
#define FILMSIZE 48
#define COUNTRYNUM 10
#define YEARNUM 10
#define TYPENUM 22
#define MAX_FILM_BORROW_NUM 5//���������ĵ�Ӱ��
extern int FILMCONUT;//��Ӱ����
extern char *COUNTRY[COUNTRYNUM];
extern char *YEAR[YEARNUM];
extern char *TYPE[TYPENUM];
extern char *IS_BORROW[4];
extern struct vip v;
extern struct film f;
#endif // !_PUBLIC_H

