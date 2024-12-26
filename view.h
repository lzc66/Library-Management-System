#ifndef _VIEW_H_  //如果该文件是第一个被#include 那么 ifndef就会编译为1
#define _VIEW_H_

#include"global.h"
#include<windows.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include <limits.h>



int login();

int regist();

int title();

int admin_win();

int normal_win();

int book_manage();

int user_manage();

int changePasswd(int model);

int modifyBook();

int addBook();

int deleteBook();

int inquiryBook();

int inquiryUser();

int bookBorrow();

int bookReturn();

int renewBook();

int brBook_manage();

int book_class_and_recommend(int model);

int book_class(int model);

int book_recommend(int model);

int navigate_admin();

int navigate_normal();

int show_digital(int model);

#endif