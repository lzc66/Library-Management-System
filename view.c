#include"view.h"

char strRole[20]={0};
USERLINK* userLink=NULL;
USER loginingUser={0};	
BOOK books[MAX_BOOKS]={{"12321","你好世界","klw","2010-10-21",2,"art"}}; 
int bookCount =0;
BOOK bookData[MAX_BOOKS]={0};
USER userData[100]={0};
BorrowQueue borrowQueue = { {0}, 0, 0 };
BorrowHistoryStack borrowHistoryStack = { {0}, -1 };
CategoryNode* root = NULL;
int bookIndexes[MAX_BOOKS];
int userIndexes[MAX_USER_COUNT];
char userNames[MAX_USER_COUNT][50];
int userIndexes[MAX_USER_COUNT];
int bookBorrowCount[MAX_BOOKS]={0};

int title()//主界面
{
    int i=0;
	system("cls");
	//printf("%s",userLink->user.userName);
    paintWindow(5,3,33,20);
    gotoxy(14,5);
    printf("欢迎来到图书管理系统！");
    paintButton(14,7,15,3,"1-登录");
    paintButton(14,12,15,3,"2-注册");
    paintButton(14,16,15,3,"3-退出");
    gotoxy(14,19);
    printf("请选择：");
    scanf("%d",&i);
    switch(i)
    {
    case 1:
        return SHOW_WIN_LOGIN;
        break;
    case 2:
        return SHOW_WIN_REGIST;
        break;
    case 3:
        return APP_EXIT;
        break;
    default:
        gotoxy(14,20);
        printf("输入的选择不对");
        Sleep(1000);
        return SHOW_MAIN_WIN;
        break;
    }
}

int login()//登录界面 
{
		int result;
		char strTime[50]={0};
		USER login_user={0};
		USERLINK*p =userLink;
        system("cls");
        paintWindow(5,5,50,20);
        gotoxy(14,7);
        printf("进入登录界面!\n");
        gotoxy(22,8);
        getSystemTime(strTime,SHOW_SYS_DATE);
        printf("日期:%s\n",strTime);
        gotoxy(10,10);
        printf("用户名:");
        paintWindow(17,9,15,3);
        gotoxy(10,14);
        printf("密 码:");
        paintWindow(17,13,15,3);
        gotoxy(10,20);
        printf("提示:按回车登录验证，ESC返回\n");
        gotoxy(19,10);
		result = getUserInput(login_user.userName,1,10,1,1);
		strcpy(loginingUser.userName,login_user.userName);
		if(result==INPUT_ESC)
		{
			return SHOW_MAIN_WIN;
		}
		gotoxy(19,14);
		result =getUserInput(login_user.passwd,1,10,0,2);
		if(result==INPUT_ESC)
		{
			return SHOW_MAIN_WIN;
		}
		gotoxy(16,18);
		result=checkLogin(login_user);
		if(result==LOGIN_ERROR)
		{
			printf("登录失败! 按任意键继续\n");
			getch();
			return SHOW_WIN_LOGIN;
		}
		else if(result==LOGIN_NORMAL)
		{
			while(p)
			{
				if(strcmp(loginingUser.userName,p->user.userName)==0)
				{
					loginingUser = p->user;
				}
				p=p->next;
			}

					strcpy(strRole,"普通用户");
		
			printf("登录成功! 按任意键继续\n");
			getch();
			return SHOW_WIN_NORMAL_MAIN;
		}
		else if(result==LOGIN_ADMIN)
		{
			while(p)
			{
				if(strcmp(loginingUser.userName,p->user.userName)==0)
				{
					loginingUser = p->user;
				}
				p=p->next;
			}
			
				strcpy(strRole,"管理员");
			printf("登录成功! 按任意键继续\n");
			getch();
			return SHOW_WIN_ADMIN_MAIN;
		}
}

int regist()//注册界面 
{
		USER reg_user={0};
		FILE*fp;
		int result;
		char configPwd[20]={0};
		char strNum[10];
		char strTime[50];
        system("cls");
        paintWindow(5,5,50,30);
        gotoxy(14,7);
        printf("欢迎进入注册界面!");
        gotoxy(22,8);
        getSystemTime(strTime,SHOW_SYS_DATE);
        printf("日期:%s\n",strTime);
        gotoxy(10,10);
        printf("用 户 名");
        paintWindow(19,9,15,3);
        gotoxy(10,14);
        printf("密    码");
        paintWindow(19,13,15,3);
        gotoxy(10,18);
        printf("确认密码");
        paintWindow(19,17,15,3);
        gotoxy(10,22);
        printf("角色:   ");
        paintWindow(19,21,15,3);
        gotoxy(10,25);
        printf("提示:按回车登录验证，ESC返回\n");
        gotoxy(21,10);
        result = getUserInput(reg_user.userName,4,8,1,1);

		if(result==INPUT_ESC)
		{
			return SHOW_MAIN_WIN;
		}
		gotoxy(21,14);
		result =getUserInput(reg_user.passwd,6,10,0,2);
		if(result==INPUT_ESC)
		{
			return SHOW_MAIN_WIN;
		}
		gotoxy(21,18);
		result = getUserInput(configPwd,6,10,0,2);
		if(result==INPUT_ESC)
		{
			return SHOW_MAIN_WIN;
		}
		gotoxy(21,22);
		result =getUserInput(strNum,1,1,1,2);
		//把字符串转为整型
		reg_user.role=atoi(strNum);
		if(result==INPUT_ESC)
		{
			return SHOW_MAIN_WIN;
		}	
		gotoxy(10,28);
		if(strcmp(configPwd,reg_user.passwd)!=0)
		{
			printf("两次密码输入不一致，按任意键重新!");
			getch();
			return SHOW_WIN_REGIST;
		}
		result= regUser(reg_user);
		if(result==REG_OK)
		{
			
			printf("注册成功，按任意键返回");
			getch();
			return	SHOW_MAIN_WIN;
		}
		else if(result==REG_ERROR)
		{
			printf("注册失败，按任意键继续");
			getch();
			return SHOW_WIN_REGIST;
		}
}

int admin_win()//管理员界面 
{
    int i=0;
	char strTime[50];
    system("cls");
    paintWindow(5,1,55,38);
    gotoxy(19,4);
    printf("欢迎来到管理员主界面！"); 
	gotoxy(10,8);
	getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s           日期:%s\n",loginingUser.userName,strRole,strTime);
    paintButton(19,10,21,3,"1-图书管理");
    paintButton(19,13,21,3,"2-用户管理");
    paintButton(19,16,21,3,"3-借阅管理");
    paintButton(19,19,21,3,"4-图书分类和推荐");
    paintButton(19,22,21,3,"5-图书馆布局和导航");
	paintButton(19,25,21,3,"6-图书数据图");
    paintButton(19,28,21,3,"7-修改密码");
    paintButton(19,31,21,3,"8-退出");
    gotoxy(19,35);
    printf("请选择：");
    scanf("%d",&i);
    switch(i)
    {
    case 0:
    	return SHOW_MAIN_WIN;
    	break;
    case 1:
        return SHOW_WIN_BOOK;
        break;
    case 2:
        return SHOW_WIN_USER;
        break;
    case 3:
        return SHOW_WIN_LEND;
        break;
    case 4:
        return SHOW_WIN_CLASS_RECOM_ADMIN;
        break;
    case 5:
        return SHOW_WIN_NAVIGATE_ADMIN;
        break;
	case 6:
		return SHOW_WIN_SHOW_ADMIN;
		break;
    case 7:
    	return ADMIN_CHANGE_PASSWD;
    	break;
    case 8:
    	system("cls");
        return APP_EXIT;
        break;
    default:
        gotoxy(19,37);
        printf("输入的选择不对");
        Sleep(1000);
        return SHOW_WIN_ADMIN_MAIN;
        break;
    }
}

int normal_win()//普通用户界面 
{
	int i=0;
	char strTime[50];
    system("cls");
    paintWindow(5,1,55,38);
    gotoxy(19,4);
    printf("欢迎来到普通用户主界面！"); 
	gotoxy(10,8);
	getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s           日期:%s\n",loginingUser.userName,strRole,strTime);
    paintButton(19,10,21,3,"1-图书借阅");
    paintButton(19,13,21,3,"2-图书归还");
    paintButton(19,16,21,3,"3-图书续借");
	paintButton(19,19,21,3,"4-图书分类和推荐");
    paintButton(19,22,21,3,"5-图书馆布局和导航");
	paintButton(19,25,21,3,"6-图书数据图");
    paintButton(19,28,21,3,"7-修改密码");
    paintButton(19,31,21,3,"8-退出");
	gotoxy(19,35);
    printf("请选择：");
    scanf("%d",&i);
	switch(i)
    {
    case 0:
    	return SHOW_MAIN_WIN;
    	break;
    case 1:
        return SHOW_WIN_BOOK_BORROW;
        break;
    case 2:
        return SHOW_WIN_BOOK_RET;
        break;
    case 3:
        return SHOW_WIN_BOOK_CON;
        break;
	case 4:
        return SHOW_WIN_CLASS_RECOM_NORMAL;
        break;
    case 5:
        return SHOW_WIN_NAVIGATE_NORMAL;
        break;
	case 6:
		return SHOW_WIN_SHOW_NORMAL;
		break;
	 case 7:
    	return NORMAL_CHANGE_PASSWD;
    	break;
    case 8:
    	system("cls");
        return APP_EXIT;
        break;
	default:
        gotoxy(19,37);
        printf("输入的选择不对");
        Sleep(1000);
        return SHOW_WIN_ADMIN_MAIN;
        break;
    }

}

int book_manage()//图书管理界面 
{
    int i=0;
    char strTime[50];
    system("cls");
    paintWindow(5,5,49,26);
    gotoxy(21,7);
    printf("图书管理界面");
    gotoxy(10,8);
	getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s           日期:%s\n",loginingUser.userName,strRole,strTime);
    paintButton(21,11,15,3,"1-图书修改");
    paintButton(21,14,15,3,"2-图书加入");
    paintButton(21,17,15,3,"3-图书删除");
    paintButton(21,20,15,3,"4-图书查询");
    gotoxy(21,24); 
    printf("提示:输入0 返回!\n");
    gotoxy(21,26);
    printf("请选择：");
    scanf("%d",&i);
    switch(i)
    {
    case 0:
        return SHOW_WIN_ADMIN_MAIN;
        break;
    case 1:
        return SHOW_WIN_BOOK_CHANGE;
        break;
    case 2:
        return SHOW_WIN_BOOK_ADD;
        break;
    case 3:
        return SHOW_WIN_BOOK_DEL;
        break;
    case 4:
    	return SHOW_WIN_BOOK_INQUIRY;
    	break;
    default:
        gotoxy(21,29);
        printf("输入的选择不对");
        Sleep(1000);
        return SHOW_WIN_BOOK;
        break;
    }
}

int user_manage()
{
	int i=0;
    char strTime[50];
    system("cls");
    paintWindow(5,5,49,26);
    gotoxy(21,7);
    printf("用户管理界面");
    gotoxy(10,8);
	getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s           日期:%s\n",loginingUser.userName,strRole,strTime);
    paintButton(21,11,15,3,"1-用户查询");
    gotoxy(21,24);
    printf("提示:输入0 返回!\n");
    gotoxy(21,26);
    printf("请选择：");
    scanf("%d",&i);
    switch(i)
    {
    	case 0:
        return SHOW_MAIN_WIN;
        break;
        case 1:
        return SHOW_WIN_USER_INQUIRY;
        break;
        default:
        gotoxy(21,29);
        printf("输入的选择不对");
        Sleep(1000);
        return SHOW_WIN_USER;
        break;
    }
}

int changePasswd(int model)//密码修改界面（通用）
{
	char oldpasswd[10]={0};
	char newpasswd[10]={0};
	char againpasswd[10]={0};
	int result;
	char strTime[50];
	int i;
	system("cls");
	paintWindow(5,5,50,20);
	gotoxy(14,7);
	printf("欢迎来到修改密码页面");
	gotoxy(10,8);
	getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s          日期:%s\n",loginingUser.userName,strRole,strTime);
	gotoxy(11,10);
	printf("旧  密  码:");
	paintWindow(22,9,15,3);
	gotoxy(11,14);
	printf("新  密  码:");
	paintWindow(22,13,15,3);
	gotoxy(11,18);
	printf("确认新密码:");
	paintWindow(22,17,15,3);
	gotoxy(11,20);
	printf("提示:按回车登录验证，ESC返回\n");
    gotoxy(24,10);
	result = getUserInput(oldpasswd,6,10,0,2);
	if(result==INPUT_ESC)
	{
		if(model==ADMIN_CHANGE_PASSWD)
		{
			return SHOW_WIN_ADMIN_MAIN;
		}
		else if(model==NORMAL_CHANGE_PASSWD)
		{
			return SHOW_WIN_NORMAL_MAIN;
		}
	}
	gotoxy(24,14);
	result =getUserInput(newpasswd,6,10,0,2);
	if(result==INPUT_ESC)
	{
		if(model==ADMIN_CHANGE_PASSWD)
		{
			return SHOW_WIN_ADMIN_MAIN;
		}
		else if(model==NORMAL_CHANGE_PASSWD)
		{
			return SHOW_WIN_NORMAL_MAIN;
		}
	}
	gotoxy(24,18);
	result =getUserInput(againpasswd,6,10,0,2);
	if(result==INPUT_ESC)
	{
		if(model==ADMIN_CHANGE_PASSWD)
		{
			return SHOW_WIN_ADMIN_MAIN;
		}
		else if(model==NORMAL_CHANGE_PASSWD)
		{
			return SHOW_WIN_NORMAL_MAIN;
		}
	}
	result=checkPwd(loginingUser.userName,oldpasswd);
	if(result==CHECK_PWD_ERROR)
	{
		printf("密码错误!按任意键继续");
		getch();
		if(model==ADMIN_CHANGE_PASSWD)
			{
				return ADMIN_CHANGE_PASSWD;
			}
			else if(model==NORMAL_CHANGE_PASSWD)
			{
				return NORMAL_CHANGE_PASSWD;
			}
	}
	else if(result==CHECK_PWD_OK)
	{
		result=changePwd(newpasswd,againpasswd);
		if(result==CHANGE_PWD_OK)
		{
			
			gotoxy(23,22);
			printf("密码修改成功，按任意键返回");
			getch();
			return SHOW_WIN_LOGIN;
		}
		else
		{
		gotoxy(23,22);
		printf("密码修改失败，按任意键继续");
		getch();
			if(model==ADMIN_CHANGE_PASSWD)
			{
				return ADMIN_CHANGE_PASSWD;
			}
			else if(model==NORMAL_CHANGE_PASSWD)
			{
				return NORMAL_CHANGE_PASSWD;
			}
		}
	}

}

int modifyBook()
 {
    char isbn[20]={0};
    char strTime[50];
	int result;
	int i;
	bookCount = getAllBookCount();
	system("cls");
     paintWindow(5,5,49,26);
    gotoxy(21,7);
    printf("欢迎来到图书修改界面");
    gotoxy(10,9);
    getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s           日期:%s\n",loginingUser.userName,strRole,strTime);
    gotoxy(10,11);
    printf("请输入要修改的图书ISBN: ");
    gotoxy(35,11);
	result =getUserInput(isbn,1,10,1,3);
	if(result==INPUT_ESC)
	{
		return SHOW_WIN_BOOK;
	}
    for (i = 0; i < sizeof(books)/sizeof(BOOK); i++)
	 {
        if (strcmp(books[i].isbn, isbn) == 0) 
		{
			gotoxy(10,14);
            printf("请输入新的书名: ");
            gotoxy(38,14);
            scanf(" %[^\n]%*c", books[i].title);
            gotoxy(10,17);
            printf("请输入新的作者: ");
            gotoxy(38,17); 
            scanf(" %[^\n]%*c", books[i].author);
			gotoxy(10,20);
			printf("请输入新的类别: ");
            gotoxy(38,20); 
            scanf(" %[^\n]%*c", books[i].category);
            gotoxy(6,23);
            printf("请输入新的出版日期 (yyyy-mm-dd): ");
            gotoxy(38,23);
            scanf("%s", books[i].publishDate);
            gotoxy(10,26);
            printf("图书信息修改成功,按任意键返回!\n");
			dataUpdate("./data/book.dat",&books[i],sizeof(BOOK)*i,sizeof(BOOK));
			initBookData("./data/book.dat");
            getch();
            return SHOW_WIN_BOOK;
        }
    }
    gotoxy(10,26);
    printf("未找到该图书! 修改失败！\n");
    Sleep(1000);
    return SHOW_WIN_BOOK_CHANGE;
}

int addBook() 
{
	BOOK newBook={0};
	char strTime[50];
	int result;
	int i;
	char strCount[20];
	int count;
	bookCount = getAllBookCount();
	system("cls");
    paintWindow(5,5,49,28);
    gotoxy(21,7);
    printf("欢迎来到图书添加界面"); 
    gotoxy(10,8);
    getSystemTime(strTime,SHOW_SYS_DATE);
    printf("日期:%s\n",strTime);
    gotoxy(10,11);
    printf("ISBN:");
    paintWindow(17,10,15,3);
    gotoxy(10,14);
    printf("书 名:");
    paintWindow(17,13,15,3);
    gotoxy(10,17); 
     printf("作 者:");
    paintWindow(17,16,15,3);
    gotoxy(8,20);
    printf("出版日期:");
    paintWindow(17,19,15,3);
    gotoxy(8,23);
    printf("书本类别:");
    paintWindow(17,22,15,3);
	gotoxy(8,26);
    printf("书本数量:");
    paintWindow(17,25,15,3);
	gotoxy(10,31);
    printf("提示:按回车登录验证，ESC返回\n");
    gotoxy(19,11);
	result =getUserInput(newBook.isbn,1,10,1,3);
	if(result==INPUT_ESC)
	{
		return SHOW_WIN_BOOK;
	}
	 gotoxy(19,14);
	result =getUserInput(newBook.title,1,10,1,3);
	if(result==INPUT_ESC)
	{
		return SHOW_WIN_BOOK;
	}
	 gotoxy(19,17);
	result =getUserInput(newBook.author,1,10,1,3);
	if(result==INPUT_ESC)
	{
		return SHOW_WIN_BOOK;
	}
	 gotoxy(19,20);
	result =getUserInput(newBook.publishDate,1,11,1,3);
	if(result==INPUT_ESC)
	{
		return SHOW_WIN_BOOK;
	}
	gotoxy(19,23);
	result =getUserInput(newBook.category,1,11,1,3);
	if(result==INPUT_ESC)
	{
		return SHOW_WIN_BOOK;
	}
	gotoxy(19,26);
	result =getUserInput(strCount,1,11,1,2);
	if(result==INPUT_ESC)
	{
		return SHOW_WIN_BOOK;
	}
	newBook.count =atoi(strCount);
    if (bookCount+newBook.count > MAX_BOOKS) 
	{
       gotoxy(10,29);
       printf("书架已满,添加书籍失败,按任意键返回\n");
       getch();
       return SHOW_WIN_BOOK;
    }
	
for(i=0;i<sizeof(books)/sizeof(BOOK);i++)
{
	if(strcmp(books[i].isbn,"")==0)
	{
		count =getBookClass();
		books[i] = newBook;
		addBookToFile("./data/book.dat",newBook);
		rebuildFile("./data/book.dat",books,count,sizeof(BOOK));
		initBookData("./data/book.dat");
		break;
	}
}
    gotoxy(10,29);
    printf("图书添加成功!\n");
    Sleep(1000);
    return SHOW_WIN_BOOK;
}

int deleteBook()
{
    char isbn[20]={0};
    char strTime[50];
	int result;
	int i;
	int j;
	int count;
	bookCount = getAllBookCount();
	system("cls");
    paintWindow(5,5,49,26);
   gotoxy(21,7);
    printf("欢迎来到图书删除界面");
    gotoxy(10,9);
    getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s           日期:%s\n",loginingUser.userName,strRole,strTime);
    gotoxy(10,11);
    printf("请输入要删除的图书ISBN: ");
    gotoxy(35,11);
    result =getUserInput(isbn,1,10,1,3);
    printf("%s",isbn);
    getch(); 
	if(result==INPUT_ESC)
	{
		return SHOW_WIN_BOOK;
	}
    for ( i = 0; i < (sizeof(books)/sizeof(BOOK)); i++)
	 {
        if (strcmp(books[i].isbn, isbn) == 0)
		 {
            for (j = i; j < (sizeof(books)/sizeof(BOOK)) - 1; j++) 
			{
                books[j] = books[j + 1]; // 向前移动数据
				if(strcmp(books[j].isbn,"")==0)
				{
			
					break;
				}
            }
			count =getBookClass();
            bookCount-=books[i].count;
            gotoxy(10,14);
            printf("图书删除成功,按任意键返回\n");
			count =getBookIndex();
			rebuildFile("./data/book.dat",books,count-1,sizeof(BOOK));
			initBookData("./data/book.dat");
            getch();
            return SHOW_WIN_BOOK;
        }
    }
    gotoxy(10,14);
    printf("未找到该图书! 删除失败！\n");
    Sleep(1000); 
    return SHOW_WIN_BOOK_DEL;
}

int inquiryBook()
{
	int result;
	char ch;
	char info[20]={0};
	char strTime[50];
	static int pageNow=1; //当前页数  //static表示静态变量,他会记录下上次调用这个函数时给他赋的值，而不是重新赋值为1
	static int pageCount=0;	//总页数
	static int flag=0;
	int bookClass;
	int row=13;
	int start=0;
	int i;
	static int count=0;
	int a;
	system("cls");
	paintWindow(5,5,75,25);
	gotoxy(25,7);
	printf("欢迎来到图书查询界面");
	gotoxy(10,8);
	getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s                           日期:%s\n",loginingUser.userName,strRole,strTime);
	gotoxy(26,10);
	printf("查询图书信息");
	paintWindow(38,9,15,3);
	paintExcel(10,12,11,2,5,5);
	gotoxy(14,13);
	printf("ISBN");
	gotoxy(26,13);
	printf("书名");
	gotoxy(38,13);
	printf("作者");
	gotoxy(50,13);
	printf("发布日期");
	gotoxy(62,13);
	printf("余量");
	if(flag==0)
	{
		count=0;
		memset(bookData,0,sizeof(bookData));
		gotoxy(40,10);
		result=getUserInput(info,0,10,NORMAL_SHOW,NO_LIMIT);
		if(result==INPUT_ESC)
		{
			return SHOW_WIN_BOOK;
		}
		else
		{
			for(i=0;i<sizeof(books)/sizeof(BOOK);i++)
			{
				if(strcmp(books[i].author,"")==0)
				{
					break;
				}
				result=checkBookInquiryInput(info,books[i]);
				if(result==SATISFY)
				{
					bookData[count]=books[i];
					count++;
				}
				
			}
			if(count==0)
			{
					gotoxy(32,24);
					printf("未找到符合要求的书本");
					getch();
					return SHOW_WIN_BOOK_INQUIRY;
			}
		}
		flag=1;
	}
	bookClass=count;
	pageCount=bookClass%4==0?bookClass/4:bookClass/4+1;
	start=(pageNow-1)*4;
	gotoxy(10,24);
	printf("<- -> 左右键翻页 %d/%d",pageNow,pageCount);
	paintBookData(start,bookClass,row,bookData);
	while(1)
	{
		ch=getch();
		if(ch==-32)  //说明你按下了键盘上的左右键
		{
			ch=getch();
			if(ch==KEY_LEFT)
			{
				if(pageNow>1)
				{
					pageNow--;
					return SHOW_WIN_BOOK_INQUIRY;
				}
				else 
				{
					gotoxy(32,24);
					printf("已经是第一页了!");
					getch();
					return SHOW_WIN_BOOK_INQUIRY;
				}
			}
			else if(ch==KEY_RIGHT)
			{
				//要先检查当前页面是否是最后一面
				if(pageNow<pageCount)
				{
					pageNow++;
					return SHOW_WIN_BOOK_INQUIRY;
				}
				else 
				{
					gotoxy(32,24);
					printf("已经是最后一页了!");
					getch();
					return SHOW_WIN_BOOK_INQUIRY;
				}
			}
		}
		else if(ch==27)
		{
			count=0;
			flag=0;
			pageNow=1; 
			pageCount=0;
			return SHOW_WIN_BOOK;
		}
	}
}

int inquiryUser()
{
	int result;
	char ch;
	char info[20]={0};
	char strTime[50];
	static int pageNow=1; //当前页数  //static表示静态变量,他会记录下上次调用这个函数时给他赋的值，而不是重新赋值为1
	static int pageCount=0;	//总页数
	static int flag=0;
	int UserCount=0;
	int row=13;
	int start=0;
	static int count=0;
	USERLINK*p =userLink;
	system("cls");
	paintWindow(5,5,75,25);
	gotoxy(25,7);
	printf("欢迎来到用户查询界面");
	gotoxy(10,8);
	getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s                           日期:%s\n",loginingUser.userName,strRole,strTime);
	gotoxy(26,10);
	printf("查询用户信息");
	paintWindow(38,9,15,3);
	paintExcel(10,12,11,2,4,5);
	gotoxy(14,13);
	printf("ID");
	gotoxy(26,13);
	printf("用户名");
	gotoxy(38,13);
	printf("密码");
	gotoxy(50,13);
	printf("身份");
	if(flag==0)
	{
		count=0;
		memset(userData,0,sizeof(userData));
		gotoxy(40,10);
		result=getUserInput(info,0,10,NORMAL_SHOW,NO_LIMIT);
		if(result==INPUT_ESC)
		{
			return SHOW_WIN_USER;
		}
		else
		{
			while(p)
			{
				if(!p->next)
				{
					break;
				}
				result=checkUserInquiryInput(info,p->user);
				if(result==SATISFY)
				{
					userData[count]=p->user;
					count++;
				}
				p=p->next;
			}
			if(count==0)
			{
					gotoxy(32,24);
					printf("未找到符合要求的用户");
					getch();
					return SHOW_WIN_USER_INQUIRY;
			}
		}
		flag=1;
	}
	UserCount=count;
	pageCount=UserCount%4==0?UserCount/4:UserCount/4+1;
	start=(pageNow-1)*4;
	gotoxy(10,24);
	printf("<- -> 左右键翻页 %d/%d",pageNow,pageCount);
	paintUserData(start,UserCount,row,userData);
	while(1)
	{
		ch=getch();
		if(ch==-32)  //说明你按下了键盘上的左右键
		{
			ch=getch();
			if(ch==KEY_LEFT)
			{
				if(pageNow>1)
				{
					pageNow--;
					return SHOW_WIN_USER_INQUIRY;
				}
				else 
				{
					gotoxy(32,24);
					printf("已经是第一页了!");
					getch();
					return SHOW_WIN_USER_INQUIRY;
				}
			}
			else if(ch==KEY_RIGHT)
			{
				//要先检查当前页面是否是最后一面
				if(pageNow<pageCount)
				{
					pageNow++;
					return SHOW_WIN_USER_INQUIRY;
				}
				else 
				{
					gotoxy(32,24);
					printf("已经是最后一页了!");
					getch();
					return SHOW_WIN_USER_INQUIRY;
				}
			}
		}
		else if(ch==27)
		{
			count=0;
			flag=0;
			pageNow=1; 
			pageCount=0;
			return SHOW_WIN_USER;
		}
	}
}

int bookBorrow()
{
	char isbn[20]={0};
    char strTime[50];
	int result;
	int i;
	int j;
	int count;
	int bookClass;
	char userName[50];
    int bookIndex;
	BorrowRequest request={0}; 
	BorrowHistory history;
	system("cls");

    paintWindow(5,5,56,26);
    gotoxy(21,7);
    printf("欢迎来到图书借阅界面");
    gotoxy(10,9);
    getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s           日期:%s\n",loginingUser.userName,strRole,strTime);
	gotoxy(10,12);
	printf("请输入用户名: ");
    scanf("%s", userName);
	gotoxy(10,14);
	bookClass=getBookClass();
    printf("请输入借阅图书的索引（0~%d）: ", bookClass - 1);
    scanf("%d", &bookIndex);
		
    if (bookIndex >= 0 && bookIndex < bookClass)
	{			gotoxy(9,17);
                enqueueBorrowRequest(bookIndex, userName);
                if (borrowQueue.front == borrowQueue.rear) 
				{
					 printf("没有待处理的借阅请求！\n");
					return SHOW_WIN_NORMAL_MAIN;
				}
				result =  dequeueBorrowRequest() ;
				if(result == REQUEST_FALSE)
				{
					request.bookIndex=-1;
				}
				else
				{
					borrowQueue.front =(borrowQueue.front+1)%MAX_QUEUE_SIZE;
					request =borrowQueue.requests[borrowQueue.front];
				}
				if (request.bookIndex == -1) 
				{
					getch();
					return SHOW_WIN_NORMAL_MAIN; // 队列为空
				}
				if (books[request.bookIndex].count == 0)
				{
					gotoxy(9,19);
					printf("图书《%s》目前不可借，借阅失败！\n", books[request.bookIndex].title);
					getch();
					return SHOW_WIN_BOOK_BORROW;
				}
				books[request.bookIndex].count--; // 标记为不可借
				gotoxy(9,19);
				printf("用户:%s成功借阅图书《%s》！\n", request.userName, books[request.bookIndex].title);
				rebuildFile("./data/book.dat",books,bookClass,sizeof(BOOK));
				initBookData("./data/book.dat");
				// 记录借阅历史
				history.bookIndex = request.bookIndex;
				strcpy(history.userName,request.userName);
				strcpy(history.borrowTime,request.borrowTime);
				strcpy(history.returnTime,"");
				strcpy(history.category,request.category);
				history.lateFee = 0;
				borrowHistoryStack.history[++borrowHistoryStack.top] = history;
				addHistoryToFile("./data/history.dat",history);
				initHistoryData("./data/history.dat");
				getch();
				return SHOW_WIN_NORMAL_MAIN;
     }
     else 
	 {
				gotoxy(10,17);
                printf("无效的图书索引！\n");
				getch();
				return SHOW_WIN_NORMAL_MAIN;
     }
}

int bookReturn()
{
	char isbn[20]={0};
    char strTime[50];
	int result;
	int i;
	int j;
	int count;
	int bookClass;
	char userName[50];
    int bookIndex;
	BorrowRequest request={0}; 
	BorrowHistory history;
	system("cls");
    paintWindow(5,5,56,26);
    gotoxy(21,7);
    printf("欢迎来到图书归还界面");
    gotoxy(10,9);
    getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s           日期:%s\n",loginingUser.userName,strRole,strTime);
	gotoxy(10,12);
	printf("请输入用户名: ");
    scanf("%s", userName);
	gotoxy(10,14);
	bookClass=getBookClass();
    printf("请输入归还图书的索引（0~%d）: ", bookClass - 1);
    scanf("%d", &bookIndex);
	if (bookIndex < 0 && bookIndex >= bookClass)
	{
		getch();
		gotoxy(10,16);
        printf("无效的图书索引！\n");
        return SHOW_WIN_NORMAL_MAIN;
    }
    // 更新借阅历史栈
    for (i = borrowHistoryStack.top; i >= 0; i--)
	{
        if (borrowHistoryStack.history[i].bookIndex == bookIndex && strcmp(borrowHistoryStack.history[i].returnTime,"")==0 && strcmp(borrowHistoryStack.history[i].userName,userName)==0) 
		{
            strcpy(borrowHistoryStack.history[i].returnTime,strTime); // 设置归还时间
            borrowHistoryStack.history[i].lateFee = calculateLateFee(borrowHistoryStack.history[i].borrowTime); // 计算罚款
			gotoxy(10,16);
            printf("图书《%s》归还成功！超期罚款：%.2f 元\n", books[bookIndex].title, borrowHistoryStack.history[i].lateFee);
			books[bookIndex].count++;
			rebuildFile("./data/book.dat",books,bookClass,sizeof(BOOK));
			dataUpdate("./data/history.dat",&borrowHistoryStack.history[i],sizeof(BorrowHistory)*i,sizeof(BorrowHistory));
			getch();
            return SHOW_WIN_NORMAL_MAIN;
        }
    }
	gotoxy(10,16);
	printf("未查询到借阅历史，或已归还成功!");
	getch();
	return SHOW_WIN_NORMAL_MAIN;
}

int renewBook()
{
	char isbn[20]={0};
    char strTime[50];
	int result;
	int i;
	int j;
	int count;
	int bookClass;
	char userName[50];
    int bookIndex;
	BorrowRequest request={0}; 
	BorrowHistory history;
	system("cls");

    paintWindow(5,5,56,26);
    gotoxy(21,7);
    printf("欢迎来到图书续借界面");
    gotoxy(10,9);
    getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s           日期:%s\n",loginingUser.userName,strRole,strTime);
	gotoxy(10,12);
	printf("请输入用户名: ");
    scanf("%s", userName);
	gotoxy(10,14);
	bookClass=getBookClass();
    printf("请输入续借图书的索引（0~%d）: ", bookClass - 1);
    scanf("%d", &bookIndex);
	if (bookIndex < 0 && bookIndex >= bookClass)
	{
		getch();
		gotoxy(10,16);
        printf("无效的图书索引！\n");
        return SHOW_WIN_NORMAL_MAIN;
    }	
	for (i = borrowHistoryStack.top; i >= 0; i--)
	{
        if (borrowHistoryStack.history[i].bookIndex == bookIndex && strcmp(borrowHistoryStack.history[i].returnTime,"")==0 && strcmp(borrowHistoryStack.history[i].userName,userName)==0) 
		{
            strcpy(borrowHistoryStack.history[i].borrowTime,strTime); // 延长借阅时间
			borrowHistoryStack.history[i].lateFee = calculateLateFee(borrowHistoryStack.history[i].borrowTime); 
            borrowHistoryStack.history[i].lateFee = 0; // 续借时不计算罚款
			gotoxy(10,18);
            printf("图书《%s》续借成功！\n", books[bookIndex].title);
			dataUpdate("./data/history.dat",&borrowHistoryStack.history[i],sizeof(BorrowHistory)*i,sizeof(BorrowHistory));
			getch();
            return SHOW_WIN_NORMAL_MAIN;
        }
    }
}

int brBook_manage()
{
	int result;
	char ch;
	char info[20]={0};
	char strTime[50];
	static int pageNow=1; //当前页数  //static表示静态变量,他会记录下上次调用这个函数时给他赋的值，而不是重新赋值为1
	static int pageCount=0;	//总页数
	static int flag=0;
	int HistoryCount=0;
	int row=13;
	int start=0;
	static int count=0;
	system("cls");
	paintWindow(5,5,75,25);
	gotoxy(25,7);
	printf("欢迎来到借阅管理界面");
	gotoxy(10,8);
	getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s                           日期:%s\n",loginingUser.userName,strRole,strTime);
	gotoxy(26,10);
	printf("查询用户借阅信息");
	paintWindow(38,9,15,3);
	paintExcel(10,12,11,2,5,5);
	gotoxy(14,13);
	printf("用户名");
	gotoxy(26,13);
	printf("借阅书本");
	gotoxy(38,13);
	printf("借阅时间");
	gotoxy(50,13);
	printf("归还时间");
	gotoxy(62,13);
	printf("费用");
	if(flag==0)
	{
		count=0;
		memset(userData,0,sizeof(userData));
		gotoxy(40,10);
		result=getUserInput(info,0,10,NORMAL_SHOW,NO_LIMIT);
		if(result==INPUT_ESC)
		{
			return SHOW_WIN_ADMIN_MAIN;
		}
		else
		{
			count = borrowHistoryStack.top+1;
			if(count==0)
			{
					gotoxy(32,24);
					printf("未找到符合要求的历史记录");
					getch();
					return SHOW_WIN_ADMIN_MAIN;
			}
		}
		flag=1;
	}
	HistoryCount=count;
	pageCount=HistoryCount%4==0?HistoryCount/4:HistoryCount/4+1;
	start=(pageNow-1)*4;
	gotoxy(10,24);
	printf("<- -> 左右键翻页 %d/%d",pageNow,pageCount);
	paintHistoryData(start,HistoryCount,row,borrowHistoryStack.history);
	while(1)
	{
		ch=getch();
		if(ch==-32)  //说明你按下了键盘上的左右键
		{
			ch=getch();
			if(ch==KEY_LEFT)
			{
				if(pageNow>1)
				{
					pageNow--;
					return SHOW_WIN_LEND;
				}
				else 
				{
					gotoxy(32,24);
					printf("已经是第一页了!");
					getch();
					return SHOW_WIN_LEND;
				}
			}
			else if(ch==KEY_RIGHT)
			{
				//要先检查当前页面是否是最后一面
				if(pageNow<pageCount)
				{
					pageNow++;
					return SHOW_WIN_LEND;
				}
				else 
				{
					gotoxy(32,24);
					printf("已经是最后一页了!");
					getch();
					return SHOW_WIN_LEND;
				}
			}
		}
		else if(ch==27)
		{
			count=0;
			flag=0;
			pageNow=1; 
			pageCount=0;
			return SHOW_WIN_ADMIN_MAIN;
		}
	}
}

int book_class_and_recommend(int model)
{
	char strTime[50];
	int i=0;
	system("cls");
    paintWindow(5,5,49,26);
    gotoxy(21,7);
    printf("图书分类和推荐界面");
    gotoxy(10,8);
	getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s           日期:%s\n",loginingUser.userName,strRole,strTime);
    paintButton(19,11,18,3,"1-图书分类查询");
	paintButton(19,16,18,3,"2-今日图书推荐");
	gotoxy(21,20);
	printf("请选择:");
	gotoxy(21,24);
    printf("提示:输入0 返回!\n");
	gotoxy(30,20);
	scanf("%d",&i);
	switch(i)
	{
		case 0:
		if(model==SHOW_WIN_CLASS_RECOM_ADMIN)
		{
			return SHOW_WIN_ADMIN_MAIN;
		}
		else if(model==SHOW_WIN_CLASS_RECOM_NORMAL)
		{
			return SHOW_WIN_NORMAL_MAIN;
		}
		break;
		case 1:
			if(model==SHOW_WIN_CLASS_RECOM_ADMIN)
		{
			return SHOW_BOOK_CLASS_ADMIN;
		}
		else if(model==SHOW_WIN_CLASS_RECOM_NORMAL)
		{
			return SHOW_BOOK_CLASS_NORMAL;
		}
			break;
		case 2:
			if(model==SHOW_WIN_CLASS_RECOM_ADMIN)
		{
			return SHOW_BOOK_RECOM_ADMIN;
		}
		else if(model==SHOW_WIN_CLASS_RECOM_NORMAL)
		{
			return SHOW_BOOK_RECOM_NORMAL;
		}
			break;
		default:
        gotoxy(21,22);
        printf("输入的选择不对");
		Sleep(1000);
		return model;
		break;
	}   
}

int book_class(int model)
{
	int i;
	int result;
	char ch;
	char info[20]={0};
	char strTime[50];
	static int pageNow=1; //当前页数  //static表示静态变量,他会记录下上次调用这个函数时给他赋的值，而不是重新赋值为1
	static int pageCount=0;	//总页数
	static int flag=0;
	int BookCount=0;
	int row=13;
	int start=0;
	static int count=0;
	CategoryNode* findTree;
	system("cls");
	paintWindow(5,5,75,25);
	gotoxy(25,7);
	printf("欢迎来到分类查询界面");
	gotoxy(10,8);
	getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s                           日期:%s\n",loginingUser.userName,strRole,strTime);
	gotoxy(26,10);
	printf("查询图书类别界面");
	paintWindow(38,9,15,3);
	paintExcel(10,12,11,2,4,5);
	gotoxy(14,13);
	printf("图书类别");
	gotoxy(26,13);
	printf("ISBN");
	gotoxy(38,13);
	printf("图书名");
	gotoxy(50,13);
	printf("余量");
	if(flag==0)
	{
		count=0;
		memset(bookData,0,sizeof(bookData));
		gotoxy(40,10);
		result=getUserInput(info,0,10,NORMAL_SHOW,NO_LIMIT);
		if(result==INPUT_ESC)
		{
			if(model==SHOW_BOOK_CLASS_ADMIN)
			{
				return SHOW_WIN_CLASS_RECOM_ADMIN;
			}
			else if(model==SHOW_BOOK_CLASS_NORMAL)
			{
				return SHOW_WIN_CLASS_RECOM_NORMAL;
			}
		}
		else
		{
				BuildTree();
				findTree=findCategory(root,info);
				for(i=0;i<sizeof(books)/sizeof(BOOK);i++)
				{
					if(findTree==NULL)
					{
						break;
					}
					if(strcmp(findTree->books[i].author,"")==0)
					{
						break;
					}
					bookData[count]=findTree->books[i];
					count++;
				}
			if(count==0)
			{
					gotoxy(32,24);
					printf("未找到符合要求的类别");
					getch();
					return model;
			}
		}
		flag=1;
	}
	BookCount=count;
	pageCount=BookCount%4==0?BookCount/4:BookCount/4+1;
	start=(pageNow-1)*4;
	gotoxy(10,24);
	printf("<- -> 左右键翻页 %d/%d",pageNow,pageCount);
	paintBookClassData(start,BookCount,row,bookData);
	while(1)
	{
		ch=getch();
		if(ch==-32)  //说明你按下了键盘上的左右键
		{
			ch=getch();
			if(ch==KEY_LEFT)
			{
				if(pageNow>1)
				{
					pageNow--;
					return model;
				}
				else 
				{
					gotoxy(32,24);
					printf("已经是第一页了!");
					getch();
					return model;
				}
			}
			else if(ch==KEY_RIGHT)
			{
				//要先检查当前页面是否是最后一面
				if(pageNow<pageCount)
				{
					pageNow++;
					return model;
				}
				else 
				{
					gotoxy(32,24);
					printf("已经是最后一页了!");
					getch();
					return model;
				}
			}
		}
		else if(ch==27)
		{
			count=0;
			flag=0;
			pageNow=1; 
			pageCount=0;
			if(model==SHOW_BOOK_CLASS_ADMIN)
			{
				return SHOW_WIN_CLASS_RECOM_ADMIN;
			}
			else if(model==SHOW_BOOK_CLASS_NORMAL)
			{
				return SHOW_WIN_CLASS_RECOM_NORMAL;
			}
		}
	}

}

int book_recommend(int model)
{
	char strTime[50];
	int i=0;
	system("cls");
    paintWindow(5,5,49,26);
    gotoxy(21,7);
    printf("图书推荐界面");
    gotoxy(10,8);
	getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s           日期:%s\n",loginingUser.userName,strRole,strTime);
	bookIndexAfterReorder(borrowHistoryStack);
	for(i=0;i<3;i++)
	{
		printf("     ║    书名:%s 作者:%s 余量:%d\n",books[bookIndexes[i]].title,books[bookIndexes[i]].author,books[bookIndexes[i]].count);
	}
	gotoxy(10,21);
	printf("按任意键返回!");
	getch();
	if(model==SHOW_BOOK_RECOM_ADMIN)
	{
		return SHOW_WIN_CLASS_RECOM_ADMIN;
	}
	else if(model==SHOW_BOOK_RECOM_NORMAL)
	{
		return SHOW_WIN_CLASS_RECOM_NORMAL;
	}
}

int navigate(int model)
{
	char strTime[50];
	int i=0;
	int dist[MAX_SHELVES];
	int	prev[MAX_SHELVES];
    int startShelf;
	int targetShelf; 
	system("cls");
    paintWindow(5,5,62,26);
    gotoxy(25,7);
    printf("导航界面");
    gotoxy(10,8);
	getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s              日期:%s\n",loginingUser.userName,strRole,strTime);
	gotoxy(10,13);
	printf("请输入你所在书架:");
	scanf("%d",&startShelf);
	gotoxy(10,15);
	printf("请输入你想去的书架:");
	scanf("%d",&targetShelf);
	initShelves();
    initLibraryGraph();
    // 计算最短路径
    dijkstra(startShelf, dist, prev);
    // 检查目标书架是否可达
    if (dist[targetShelf] == INT_MAX)
    {
		gotoxy(10,17);
        printf("No path from Shelf %d (%s) to Shelf %d (%s).\n",
            startShelf, shelves[startShelf].category,
            targetShelf, shelves[targetShelf].category);
    }
    else
    {
		gotoxy(10,17);
        printf("Shelf %d (%s) to Shelf %d (%s):\n",
            startShelf, shelves[startShelf].category,
            targetShelf, shelves[targetShelf].category);
        printPath(startShelf, targetShelf, prev);
        printf("\n");
    }
	getch();
	if(model==SHOW_WIN_NAVIGATE_ADMIN)
	{
		return SHOW_WIN_ADMIN_MAIN;
	}
	else if(model==SHOW_WIN_NAVIGATE_NORMAL)
	{
		return SHOW_WIN_NORMAL_MAIN;
	}
}

int show_digital(int model)
{
	int i;
	char strTime[50];
	char str[20];
	system("cls");
    paintWindow(5,5,62,26);
    gotoxy(25,7);
    printf("导航界面");
    gotoxy(10,8);
	getSystemTime(strTime,SHOW_SYS_DATE);
	printf("欢迎%s,%s              日期:%s\n",loginingUser.userName,strRole,strTime);
	userIndexAfterReorder(borrowHistoryStack,userNames) ;
	bookIndexAfterReorder(borrowHistoryStack);
	gotoxy(10,11);
	printf("最活跃用户前三名\n");
	for(i=0;i<3;i++)
	{
		printf("     ║  No:%d  用户名:%s\n",i+1,userNames[userIndexes[i]]);
	}
	gotoxy(10,19);
	printf("借阅量最大的书籍\n");
	for(i=0;i<3;i++)
	{
		gotoxy(0,19+(i*4));
		if(bookBorrowCount[i]==0)
		{
			break;
		}
		printf("     ║  No:%d  书名:%s 借阅量:%d\n",i+1,books[bookIndexes[i]].title,bookBorrowCount[i]);
		paintExcel(40,17+(i*4),(bookBorrowCount[i]+1)*2,3,1,1);
	}
	
	
	getch();
	if(model==SHOW_WIN_SHOW_ADMIN)
	{
		return SHOW_WIN_ADMIN_MAIN;
	}
	else if(model==SHOW_WIN_SHOW_NORMAL)
	{
		return SHOW_WIN_NORMAL_MAIN;
	}
}

