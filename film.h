#pragma once
#ifndef _FILM_H
#define _FILM_H
struct film * getFilmByName(char * name, struct film *f);//ͨ�����ֲ�ѯ ����: struct film*(�ҵ�)  NULL(δ�ҵ�)
void printFilminfo(struct film f);
void insertFilm(char *name, char country, char type,
	char year, char is_borrow, float film_price,
	char film_sum, char film_left);
void deleteFilmByName(char * name);
void showAllFilm();
void showFilmList(int start, int end);
void changeFilmLeftNum(int id, int newnum);
void changeFilmPrice(char * name, float newprice);
void changeFilmSumInFilminfo(int newnum, int newnextid);
char * getFilmNameByid(int id);
void borrowfilm(struct cart * head, int id);
int getFilmSumFromFilminfo();
int getFilmIdByName(char *name);
int getIdflagFromFilminfo();
void returnall(int id);//�黹����ӰƬ
void retursinglefilm(int uid, int fid);//�黹����ӰƬ ����
void borrowsinglefilm(struct cart * head, int uid, int fid);//���ĵ�����Ӱ
#endif // !_FILM_H
