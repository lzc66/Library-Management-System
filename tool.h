#ifndef _TOOL_H_
#define _TOOL_H_

#include"global.h"
#include<windows.h>
#include<time.h>
#include<stdio.h>
#include<conio.h>
#include <limits.h>
#include"data.h"


void paintWindow(int startX,int startY,int width,int height);

void paintButton(int startX,int startY,int width,int height,char text[]);

void paintExcel(int startX,int startY,int width,int height,int cow,int col); 

void gotoxy(int x, int y);

int getUserInput(char str[],int minLen,int maxLen,int flag,int limit);

void getSystemTime(char str[],int opt);

int checkLogin(USER user_info);

int regUser(USER user_reg);

int getMaxId();

int checkPwd(char str[],char pwd[]);

int changePwd(char newpwd[],char configpwd[]);

int getAllBookCount();

int getBookIndex();

int checkBookInquiryInput(char str[],BOOK book);

void paintBookData(int start,int BookClass,int row,BOOK book[]);

int checkChildStr(char str[],char userStr[]);

int checkUserInquiryInput(char str[],USER user);

void paintUserData(int start,int UserCount,int row,USER user[]);

int compareBooks(const void* a, const void* b, int sortBy);

void quickSort(BOOK arr[], int low, int high, int sortBy);

int partition(BOOK arr[], int low, int high, int sortBy);

void enqueueBorrowRequest(int bookIndex, const char* userName);

int dequeueBorrowRequest() ;

int getBookClass();

time_t stringToTime(char timeStr[]);

float calculateLateFee(char borrowTime[]);

void paintHistoryData(int start,int HistoryCount,int row,BorrowHistory history[]);

int checkBookClassInquiryInput(char str[],BOOK book);

int checkBookClassInquiryInput(char str[],BOOK book);

void paintBookClassData(int start,int BookClass,int row,BOOK book[]);

CategoryNode* createCategoryNode(const char* category);

CategoryNode* insertCategory(CategoryNode* root, const char* category);

void addBookToCategory(CategoryNode* root, BOOK book);

CategoryNode* findCategory(CategoryNode* root, char category[]);

void BuildTree();

void initShelves();

void addEdge(int u, int v, int weight);

void initLibraryGraph();

void dijkstra(int start, int* dist, int* prev);

void printPath(int start, int end, int* prev); 

void countBookBorrowings(BorrowHistoryStack stack, int* bookBorrowCount);

void countUserBorrowings(BorrowHistoryStack stack, int* userBorrowCount, char userNames[MAX_USER_COUNT][50]);

int partitionForCount(int* arr, int* indexArr, int low, int high);

void quickSortForCount(int* arr, int* indexArr, int low, int high);

void bookIndexAfterReorder(BorrowHistoryStack stack);

void userIndexAfterReorder(BorrowHistoryStack stack,char userNames[MAX_USER_COUNT][50]); 

#endif