#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include<time.h>
#include <limits.h>

#define NORMAL_SHOW 1
#define PASSWD_SHOW 0

#define SHOW_MAIN_WIN 1
#define SHOW_WIN_LOGIN 2
#define SHOW_WIN_REGIST 3
#define SHOW_WIN_BOOK 4
#define SHOW_WIN_USER 5
#define SHOW_WIN_LEND 6
#define SHOW_WIN_CLASS_RECOM_ADMIN 7
#define SHOW_WIN_CLASS_RECOM_NORMAL 8
#define SHOW_WIN_NAVIGATE_ADMIN 9
#define SHOW_WIN_NAVIGATE_NORMAL 10
#define SHOW_WIN_BOOK_CHANGE 11
#define SHOW_WIN_BOOK_ADD 12
#define SHOW_WIN_BOOK_DEL 13
#define SHOW_WIN_BOOK_INQUIRY 14 
#define SHOW_WIN_NORMAL_MAIN 15
#define SHOW_WIN_ADMIN_MAIN 16
#define SHOW_WIN_BOOK_BORROW 17
#define SHOW_WIN_BOOK_RET 18
#define SHOW_WIN_BOOK_CON 19
#define ADMIN_CHANGE_PASSWD 20
#define NORMAL_CHANGE_PASSWD 21
#define SHOW_WIN_USER_INQUIRY 22
#define SHOW_BOOK_CLASS_ADMIN 23
#define SHOW_BOOK_CLASS_NORMAL 24
#define SHOW_BOOK_RECOM_ADMIN 25
#define SHOW_BOOK_RECOM_NORMAL 26
#define SHOW_WIN_SHOW_ADMIN 27
#define SHOW_WIN_SHOW_NORMAL 28

#define APP_EXIT 99 

#define INPUT_ESC -1

#define ENGLISH 1
#define NUMBER 2
#define NO_LIMIT 3

#define SHOW_SYS_DATE 0	//显示日期
#define SHOW_SYS_TIME 1	//显示全部时间

#define LOGIN_ERROR 0
#define LOGIN_NORMAL 1
#define LOGIN_ADMIN 2

#define REG_OK 1
#define REG_ERROR 0

#define CHECK_PWD_OK 1
#define CHECK_PWD_ERROR 0

#define CHANGE_PWD_OK 1
#define CHANGE_PWD_ERROR 0

#define MAX_BOOKS 100
#define MAX_TITLE_LEN 100
#define MAX_AUTHOR_LEN 100
#define MAX_QUEUE_SIZE 10     //最大队列容量
#define MAX_HISTORY_SIZE 50   //最大借阅记录容量
#define MAX_CATEGORY_LEN 50
#define MAX_SHELVES 10
#define MAX_USER_COUNT 100

#define KEY_LEFT 75
#define KEY_RIGHT 77

#define SATISFY 1
#define NOT_SATISFY 0

#define IS_CHILD 1
#define NOT_CHILD 0

#define REQUEST_TRUE 1
#define REQUEST_FALSE 0

typedef struct user
{
	char userName[20];
	char passwd[20];
	int role;  //管理员是1，普通用户是2
	int id;
}USER;

typedef struct userlink
{
	USER user;
	struct userlink*next;
}USERLINK;

typedef struct
 {
    char isbn[20];           // ISBN号
    char title[MAX_TITLE_LEN]; // 书名
    char author[MAX_AUTHOR_LEN]; // 作者
    char publishDate[11];    // 出版日期 (yyyy-mm-dd)
	int count; //书本余量 
	char category[MAX_CATEGORY_LEN];
} BOOK;

typedef struct 
{
    int bookIndex;        // 图书的索引
    char userName[20];    // 用户名
    char borrowTime[20];    // 借书时间
	char category[MAX_CATEGORY_LEN];
} BorrowRequest;

// 借阅历史栈节点
typedef struct 
{
	char userName[20];
    int bookIndex;        // 图书的索引
    char borrowTime[20];    // 借书时间
    char returnTime[20];    // 归还时间
    float lateFee;        // 超期罚款
	char category[MAX_CATEGORY_LEN];
} BorrowHistory;

// 借阅队列
typedef struct 
{
    BorrowRequest requests[MAX_QUEUE_SIZE];
    int front;
    int rear;
} BorrowQueue;

// 借阅历史栈
typedef struct
 {
    BorrowHistory history[MAX_HISTORY_SIZE];
    int top;
} BorrowHistoryStack;

typedef struct CategoryNode
{
    char category[MAX_CATEGORY_LEN]; // 分类名称
    BOOK books[MAX_BOOKS];           // 存储图书列表【链表】
    struct CategoryNode* left;       // 左子树
    struct CategoryNode* right;      // 右子树
} CategoryNode;

// 书架结构体
typedef struct
{
    int id;                  // 书架编号
    char category[50];       // 书架类别
} Shelf;

// 图的邻接表结构
typedef struct
{
    int dest;                // 目标节点编号
    int weight;              // 边的权重（即通道的距离或耗时）
    struct EdgeNode* next;   // 指向下一条边
} EdgeNode;

typedef struct 
{
    EdgeNode* head;          // 指向第一条边
} AdjList[MAX_SHELVES];

// 存储所有书架
extern Shelf shelves[MAX_SHELVES];
extern AdjList libraryGraph; 
extern USER loginingUser;
extern USERLINK*userLink;
extern BOOK books[MAX_BOOKS];
extern BorrowQueue borrowQueue ;
extern BorrowHistoryStack borrowHistoryStack ;
extern CategoryNode* root;
extern int bookIndexes[MAX_BOOKS];
extern int userIndexes[MAX_USER_COUNT];
extern char userNames[MAX_USER_COUNT][50];
extern int userIndexes[MAX_USER_COUNT];
extern int bookBorrowCount[MAX_BOOKS];
extern 	int shelfIndex;
extern int dist[MAX_SHELVES];
extern int	prev[MAX_SHELVES];

#endif
 