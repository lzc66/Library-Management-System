#ifndef _DATA_H_
#define _DATA_H_
#include "global.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tool.h"

void initUserLink();

void initUserData(char*fileName);

int addUserToFile(char*fileName,USER reg_user);

int dataUpdate(char*fileName,void*data,int position,int size);

void initBookData(char*fileName);

int addBookToFile(char*fileName,BOOK newBook);

void rebuildFile(char*fileName,void*data,int count,int size);

void initHistoryData(char*fileName);

int addHistoryToFile(char*fileName,BorrowHistory history);

#endif 