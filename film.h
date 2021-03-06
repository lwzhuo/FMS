#pragma once
#ifndef _FILM_H
#define _FILM_H
struct film * getFilmByName(char * name, struct film *f);//通过名字查询 返回: struct film*(找到)  NULL(未找到)
void printFilminfo(struct film f);
void insertFilm(char *name, char country, char type,
	char year, char is_borrow, float film_price,
	char film_sum, char film_left);
void deleteFilmByName(char * name);
void showAllFilm();
void showFilmList(int start, int end);
void changeFilm(int id, struct film newfilminfo);
void changeFilmSumInFilminfo(int newnum, int newnextid);
char * getFilmNameByid(int id);
void getFilmById(int id, struct film *f);//通过id查询
void borrowfilm(struct cart * head, int id);
int getFilmSumFromFilminfo();
int getFilmIdByName(char *name);
int getIdflagFromFilminfo();
void returnall(int id);//归还所有影片
void retursinglefilm(int uid, int fid);//归还单个影片 返回
void borrowsinglefilm(struct cart * head, int uid, int fid);//借阅单个电影
void ShowfilmBorrowStatus();//展示所有影片借阅状态
#endif // !_FILM_H
