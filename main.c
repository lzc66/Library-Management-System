#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h> 
#include<math.h>
#include<time.h>
#include"tool.h"
#include"view.h"
#include"global.h"
#include"data.h"


int main() 
{
    int i;
	initUserLink();
    initUserData("./data/user.dat");
	initBookData("./data/book.dat");
	initHistoryData("./data/history.dat");
    i=title();
    while(1)
    {
        switch(i)
        {
            case SHOW_MAIN_WIN:
                i = title();
                break;
            case SHOW_WIN_LOGIN:
                i = login();
                break;
            case SHOW_WIN_REGIST:
                i = regist();
                break;
            case SHOW_WIN_BOOK:
                 i = book_manage();
                 break; 
            case SHOW_WIN_USER:
            	i =user_manage();
            	break;
			case SHOW_WIN_LEND:
				i = brBook_manage();
				break;
			case SHOW_WIN_NAVIGATE_ADMIN:
				i =navigate(SHOW_WIN_NAVIGATE_ADMIN);
				break;
			case SHOW_WIN_NAVIGATE_NORMAL:
				i =navigate(SHOW_WIN_NAVIGATE_NORMAL);
				break;
            case SHOW_WIN_ADMIN_MAIN:
				i =admin_win();
				break;  
			case SHOW_WIN_NORMAL_MAIN:
				i = normal_win();
				break;
			case ADMIN_CHANGE_PASSWD:
				i=changePasswd(ADMIN_CHANGE_PASSWD);
				break;
			case NORMAL_CHANGE_PASSWD:
				i=changePasswd(NORMAL_CHANGE_PASSWD);
				break;
			case SHOW_WIN_BOOK_CHANGE:
				i = modifyBook();
				break;
			case SHOW_WIN_BOOK_ADD:	
				i =addBook();
				break;
			case SHOW_WIN_BOOK_DEL:
				i =deleteBook();
				break;
			case SHOW_WIN_BOOK_INQUIRY:
				i =inquiryBook();
				break;
			case SHOW_WIN_USER_INQUIRY:
				i = inquiryUser();
				break; 
			case SHOW_WIN_BOOK_BORROW:
				i = bookBorrow();
				break;
			case SHOW_WIN_BOOK_RET:
				i =bookReturn();
				break;
			case SHOW_WIN_BOOK_CON:
				i =renewBook();
				break;
			case SHOW_WIN_CLASS_RECOM_ADMIN:
				i =book_class_and_recommend(SHOW_WIN_CLASS_RECOM_ADMIN);
				break;
			case SHOW_WIN_CLASS_RECOM_NORMAL:
				i =book_class_and_recommend(SHOW_WIN_CLASS_RECOM_NORMAL);
				break;
			case SHOW_BOOK_CLASS_ADMIN:
				i=book_class(SHOW_BOOK_CLASS_ADMIN);
				break;
			case SHOW_BOOK_CLASS_NORMAL:
				i=book_class(SHOW_BOOK_CLASS_NORMAL);
				break;
			case SHOW_BOOK_RECOM_ADMIN:
				i=book_recommend(SHOW_BOOK_RECOM_ADMIN);
				break;
			case SHOW_BOOK_RECOM_NORMAL:
				i= book_recommend(SHOW_BOOK_RECOM_ADMIN);
				break;
			case SHOW_WIN_SHOW_ADMIN:
				i =show_digital(SHOW_WIN_SHOW_ADMIN);
					break;
			case SHOW_WIN_SHOW_NORMAL:
				i =show_digital(SHOW_WIN_SHOW_NORMAL);
					break;
            case APP_EXIT:
                gotoxy(1,25);
                return 0;
                break;
            default:
                printf("输入的选择不对");
                break;
        }
    }
}