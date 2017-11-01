//包含各个.c文件需要的全局变量或信息
#define FILMSIZE 48
#define COUNTRYNUM 10
#define YEARNUM 10
#define TYPENUM 22
int FILMCONUT;//电影总数
int MAX_FILM_BORROW_NUM;//用户可借阅电影最大数
char *COUNTRY[COUNTRYNUM] = { "内地", "香港", "美国" ,"欧洲" ,
"韩国", "日本" ,"台湾", "泰国" ,
"印度" ,"其他" };
char *YEAR[YEARNUM] = { "2017", "2016", "2015", "2014",
"2013 - 2011", "2010 - 2006",
"2005 - 2000", "90年代", "80年代",
"其他" };
char *TYPE[TYPENUM] = { "院线", "剧情", "喜剧", "动作", "爱情",
"犯罪", "冒险", "战争" ,"惊悚", "悬疑",
"恐怖" ,"科幻" ,"奇幻", "家庭", "动画",
"音乐", "歌舞" ,"历史", "传记", "武侠",
"伦理", "记录" };
char *IS_BORROW[4] = { "不可借","可借","已下架","已删除" };

