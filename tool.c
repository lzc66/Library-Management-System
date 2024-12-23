#include"tool.h"

void paintWindow(int startX,int startY,int width,int height)  //打印窗口
{
    int i=0;
    int j=0;
    gotoxy(startX,startY);
    printf("╔");
    for(i=0;i<width-2;i++)
    {
        printf("═");
    }
    printf("╗\n");
    for(j=0;j<height-2;j++)
    {
        gotoxy(startX,startY+1+j);
        printf("║");
        for(i=0;i<width-2;i++)
        {
        printf(" ");
        }
        printf("║\n");
    }
    gotoxy(startX,startY+height-1);

    printf("╚");
    for(i=0;i<width-2;i++)
    {
        printf("═");
    }
    printf("╝\n");
}

void paintButton(int startX,int startY,int width,int height,char text[])  //打印按钮
{
    paintWindow(startX,startY,width,height);
    gotoxy(startX+(width-strlen(text))/2,startY+1);
    printf("%s",text);
}

void paintExcel(int startX,int startY,int width,int height,int cow,int col) //打印表格 
{
	int i=0;
	int j=0;
	int k=0;
	gotoxy(startX,startY);
	printf("┌");
	for(i=0;i<cow-1;i++)
	{
		for(j=0;j<width;j++)
		{
			printf("─");
		}
			printf("┬");
	}
	for(i=0;i<width;i++)
	{
		printf("─");
	}
	printf("┐\n");
	for(j=0;j<cow+1;j++)
	{
		for(i=1;i<height;i++)
		{
		gotoxy(startX+(width+1)*j,startY+i);
			printf("│");
		}
	}
	
	for(k=1;k<col;k++)
	{
		gotoxy(startX,startY+k*height);
		printf("├");
	for(i=0;i<cow-1;i++)
	{
		for(j=0;j<width;j++)
		{
			printf("─");
		}
			printf("┼");
	}
	for(i=0;i<width;i++)
		{
			printf("─");
		}
	printf("┤\n");
	
		for(j=0;j<cow+1;j++)
		{
			for(i=1;i<height;i++)
			{
				gotoxy(startX+(width+1)*j,startY+i+height*k);
				printf("│");
			}
		}
	}
		
	gotoxy(startX,startY+col*height);
	printf("└");
	for(i=0;i<cow-1;i++)
	{
		for(j=0;j<width;j++)
		{
			printf("─");
		}
			printf("┴");
	}
	for(j=0;j<width;j++)
	{
		printf("─");
	}
	printf("┘\n");

}

void gotoxy(int x, int y)//形参
{
    HANDLE hOut;
    COORD pos = {x, y};
    // 光标的起始位（第1列，第3行） 0是第1列 2是第3行
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
    //printf("定位光标位置搜索(%d,%d)\n",pos.X,pos.Y);
}

int getUserInput(char str[],int minLen,int maxLen,int flag,int limit) //表示这个参数我接收数组为参数，这里的数组不需要大小。
{
	//用户输入
	int i=0;
	char ch;
	//maxLen表示允许输入的最大字符
	while(1)
	{
		ch=getch();
		if(i>=maxLen)
		{
			return 0;
		}
		if(ch==13)
		{
			if(i>=minLen&&i<=maxLen)
			{
				break;
			}
		}
		else if(ch==27)
		{
			return INPUT_ESC;
		}
		else if(ch=='\b')
		{
			if(i>0)
			{
				printf("\b \b");
				i--;
				str[i]='\0';
				continue;
			}
		}
		else
		{
			if(limit==ENGLISH)
			{
				if(ch<='z'&&ch>='a'||ch<='Z'&&ch>='A')
				{
						str[i]=ch;
				}
				else
				{
					continue;
				}
			}
			else if(limit==NUMBER)
			{
				if(ch<='9'&&ch>='0')
				{
						str[i]=ch;
				}
				else
				{
					continue;
				}
			}	
			else if(limit==NO_LIMIT)
			{
				str[i]=ch;
			}

			if(flag==NORMAL_SHOW)
			{
				putch(str[i]);
			}
			else if(flag==PASSWD_SHOW)
			{
				putch('*');
			}
			i++;
		}
	
	}
		printf("\n");
		return 0;
}

void getSystemTime(char str[],int opt)
{
    time_t current_time;
	struct tm *time_info;
    time(&current_time); // 获取系统时间戳
	time_info = localtime(&current_time); // 将时间戳转换为结构体表示
	if(opt==SHOW_SYS_DATE)
	{
    	sprintf(str,"%d-%d-%d",time_info->tm_year + 1900,time_info->tm_mon + 1,time_info->tm_mday);
	}
	else if(opt==SHOW_SYS_TIME)
	{
		sprintf(str,"%d-%d-%d-%d:%d:%d",time_info->tm_year + 1900,time_info->tm_mon + 1,time_info->tm_mday,time_info->tm_hour,time_info->tm_min,time_info->tm_sec);
	}
}

int checkLogin(USER user_info)
{

	int i=0;
	USERLINK*p =userLink;
	while(p)
	{
		if(strcmp(p->user.userName,user_info.userName)==0&&strcmp(p->user.passwd,user_info.passwd)==0)
		{
			if(p->user.role==1)
			{
				return LOGIN_ADMIN;
			}
			else if(p->user.role==2)
			{
				return LOGIN_NORMAL;
			}
		}
		p=p->next;
	}
	return LOGIN_ERROR;
}

int regUser(USER user_reg)
{
	//要扫描userArray结构数组里有空闲的位置，找到空间位置拷贝进去
	//而且要注册的用户名不要相同
	int result;
	int index=0;
	int user_id=0;
	USERLINK*p =userLink;

	while(p)
	{
		if(strcmp(user_reg.userName,p->user.userName)==0)
		{

			getch();
			return REG_ERROR;
		}
		p=p->next;
	}
	if(user_reg.role!=1&&user_reg.role!=2)
	{
		return REG_ERROR;
	}
	user_reg.id=getMaxId();
  //memcpy也是可以实现内存拷贝
	//memcpy(&userArray[index],&user_reg,sizeof(USER))
	result=addUserToFile("./data/user.dat",user_reg);
	if(result==0)
	{
		initUserData("./data/user.dat");
		return REG_OK;
	}
	else
	{
		return REG_ERROR;
	}
}

int getMaxId()
{
	int max=0;
	USERLINK*p =userLink;
	while(p)
	{

		if(max<p->user.id)
		{
			max=p->user.id;
		}
		p=p->next;
	}
	return max+1;
}

int checkPwd(char str[],char pwd[])
{
	USERLINK*p =userLink;
	while(p)
	{
		if(strcmp(p->user.userName,str)==0&&strcmp(p->user.passwd,pwd)==0)
		{
			return CHECK_PWD_OK;
		}
		p=p->next;
	}
	return CHECK_PWD_ERROR;
}

int changePwd(char newpwd[],char configpwd[])
{
	int i=0;
	int result;
	USERLINK*p =userLink;
	if(strcmp(newpwd,configpwd)==0)
	{
			memset(loginingUser.passwd,0,sizeof(loginingUser.passwd));
			strcpy(loginingUser.passwd,configpwd);
			while(p)
			{
				if(strcmp(loginingUser.userName,p->user.userName)==0)
				{
					p->user=loginingUser;
					result=dataUpdate("./data/user.dat",&p->user,sizeof(USER)*i,sizeof(USER));
					if(result==0)
					{
						return CHANGE_PWD_OK;
					}
					else
					{
						return CHANGE_PWD_ERROR;
					}
				}
				i++;
				p=p->next;
			}
			return CHANGE_PWD_OK;
	}
	return CHANGE_PWD_ERROR;
}

int getAllBookCount()
{
	int i=0;
	int count=0;
	for(i=0;i<sizeof(books)/sizeof(BOOK);i++)
	{
		count += books[i].count;
	}
	return count;
}

int getBookIndex()
{
	int i=0;
	for(i=0;i<sizeof(books)/sizeof(BOOK);i++)
	{
		if(strcmp(books[i].isbn,"")==0)
		{
			break;
		}
	}
	return i;
}

int checkBookInquiryInput(char str[],BOOK book)
{
	int result;
	result=checkChildStr(str,book.isbn);
	if(result==IS_CHILD)
	{
		return SATISFY;
	}
	result=checkChildStr(str,book.title);
	
	if(result==IS_CHILD)
	{
		return SATISFY;
	}
	result=checkChildStr(str,book.publishDate);
	if(result==IS_CHILD)
	{
		return SATISFY;
	}
	result=checkChildStr(str,book.author);
	if(result==IS_CHILD)
	{
		return SATISFY;
	}
	result=checkChildStr(str,book.category);
	if(result==IS_CHILD)
	{
		return SATISFY;
	}
	return NOT_SATISFY;
}

int checkChildStr(char str[],char userStr[])
{
	if(strstr(userStr,str))
	{
		return IS_CHILD;
	}
    return NOT_CHILD;
}

void paintBookData(int start,int BookClass,int row,BOOK book[])
{
	int i=0;
	for(i=0;i<4;i++)   //每一页只有四条记录
	{
		if(start<BookClass)
		{
			gotoxy(14,row+(i+1)*2);
			printf("%s",book[start].isbn);
			gotoxy(26,row+(i+1)*2);
			printf("%s",book[start].title);
			gotoxy(38,row+(i+1)*2);
			printf("%s",book[start].author);
			gotoxy(48,row+(i+1)*2);
			printf("%s",book[start].publishDate);
			gotoxy(62,row+(i+1)*2);
			printf("%d",book[start].count);	
			printf("\n");
			start++;
		}
	}
}


int checkUserInquiryInput(char str[],USER user)
{
	int result;
	char strId[10];
	char strRole[10];
	sprintf(strId,"%d",user.id);
	sprintf(strRole,"%d",user.role);
	result=checkChildStr(str,strId);
	if(result==IS_CHILD)
	{
		return SATISFY;
	}
	result=checkChildStr(str,strRole);
	
	if(result==IS_CHILD)
	{
		return SATISFY;
	}
	result=checkChildStr(str,user.userName);
	if(result==IS_CHILD)
	{
		return SATISFY;
	}
	return NOT_SATISFY;
}

void paintUserData(int start,int UserCount,int row,USER user[])
{
		int i=0;
	for(i=0;i<4;i++)   //每一页只有四条记录
	{
		if(start<UserCount)
		{
			gotoxy(14,row+(i+1)*2);
			printf("%d",user[start].id);
			gotoxy(26,row+(i+1)*2);
			printf("%s",user[start].userName);
			gotoxy(38,row+(i+1)*2);
			printf("*******");
			gotoxy(48,row+(i+1)*2);
			if(user[start].role==1)
			{
				printf("管理员");
			}
			else printf("普通用户");
			printf("\n");
			start++;
		}
	}
}


int compareBooks(const void* a, const void* b, int sortBy)
 {
    BOOK* bookA = (BOOK*)a;
    BOOK* bookB = (BOOK*)b;

    switch (sortBy) {
    case 0:  // 按ISBN排序
        return strcmp(bookA->isbn, bookB->isbn);
    case 1:  // 按书名排序
        return strcmp(bookA->title, bookB->title);
    case 2:  // 按作者排序
        return strcmp(bookA->author, bookB->author);
    case 3:  // 按出版日期排序
        return strcmp(bookA->publishDate, bookB->publishDate);
    default:
        return 0;  // 默认不排序
    }
}

// 快速排序
void quickSort(BOOK arr[], int low, int high, int sortBy) 
{
    if (low < high) {
        int pivotIndex = partition(arr, low, high, sortBy);
        quickSort(arr, low, pivotIndex - 1, sortBy);  // 对左子数组排序
        quickSort(arr, pivotIndex + 1, high, sortBy); // 对右子数组排序
    }
}

// 分割函数
int partition(BOOK arr[], int low, int high, int sortBy) 
{
    BOOK pivot = arr[high]; // 选择最后一个元素作为pivot
    int i = low - 1;  // i是分割点
    int j;
	BOOK temp;
    for (j = low; j < high; j++) 
	{
        if (compareBooks(&arr[j], &pivot, sortBy) < 0) 
		{
            i++;
            // 交换 arr[i] 和 arr[j]
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // 将 pivot 放到正确的位置
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1; // 返回 pivot 的索引
}

void enqueueBorrowRequest(int bookIndex, const char* userName)
 {
	char strTime[50];

	BorrowRequest request;
	getSystemTime(strTime,SHOW_SYS_DATE);
    if ((borrowQueue.rear+1)%MAX_QUEUE_SIZE == borrowQueue.front)
	{
        printf("借阅请求队列已满，无法处理更多请求！\n");
        return;
    }

    request.bookIndex = bookIndex;
    strcpy(request.userName, userName);
	strcpy(request.category,books[bookIndex].category);
    strcpy(request.borrowTime,strTime);  // 当前时间
	borrowQueue.rear =(borrowQueue.rear+1)%MAX_QUEUE_SIZE;
    borrowQueue.requests[borrowQueue.rear] = request;
	gotoxy(10,17);
    printf("借阅请求已加入队列：图书《%s》, 用户：%s\n", books[bookIndex].title, request.userName);
}

int dequeueBorrowRequest() 
{
	BorrowRequest emptyRequest= {-1,"",""};
    if (borrowQueue.front == borrowQueue.rear)
	{
        printf("借阅请求队列为空！\n");
		return REQUEST_FALSE;
    }
    return REQUEST_TRUE;
}

int getBookClass()
{
	int i;
	int count=0;
	for(i=0;i<sizeof(books)/sizeof(BOOK);i++)
	{
			if(strcmp(books[i].author,"")==0)
			{
				break;
			}
			count++;	
	}
	return count;
}

time_t stringToTime(char timeStr[]) 
{
    struct tm tm = {0};
    sscanf(timeStr, "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    return mktime(&tm);
}

float calculateLateFee(char borrowTime[]) 
{     //计算超限罚金
    const int borrowPeriod = 30; // 30天
    float lateFee = 0;
	char currentTime[20];
	double diff;
	time_t time1;
	time_t time2;
	getSystemTime(currentTime,SHOW_SYS_DATE);
	time1 = stringToTime(currentTime);
    time2 = stringToTime( borrowTime);
	diff = difftime(time1, time2) / (60 * 60 * 24);
    if ((int)diff> borrowPeriod)
	{
        lateFee = ((int)diff- borrowPeriod) *0.2; // 逾期天数
    }
    return lateFee;
}

void paintHistoryData(int start,int HistoryCount,int row,BorrowHistory history[])
{
		int i=0;
	for(i=0;i<4;i++)   //每一页只有四条记录
	{
		if(start<HistoryCount)
		{
			gotoxy(14,row+(i+1)*2);
			printf("%s",history[start].userName);
			gotoxy(26,row+(i+1)*2);
			printf("%s",books[history[start].bookIndex].title);
			gotoxy(36,row+(i+1)*2);
			printf("%s",history[start].borrowTime);
			gotoxy(48,row+(i+1)*2);
			printf("%s",history[start].returnTime);
			gotoxy(62,row+(i+1)*2);
			history[start].lateFee = calculateLateFee(borrowHistoryStack.history[i].borrowTime);
			printf("%.2f",history[start].lateFee);
			printf("\n");
			start++;
		}
	}
}

int checkBookClassInquiryInput(char str[],BOOK book)
{
	int result;
	result=checkChildStr(str,book.category);
	if(result==IS_CHILD)
	{
		return SATISFY;
	}
	return NOT_SATISFY;
}

void paintBookClassData(int start,int BookClass,int row,BOOK book[])
{
	int i=0;
	for(i=0;i<4;i++)   //每一页只有四条记录
	{
		if(start<BookClass)
		{
			gotoxy(14,row+(i+1)*2);
			printf("%s",book[start].category);
			gotoxy(26,row+(i+1)*2);
			printf("%s",book[start].isbn);
			gotoxy(38,row+(i+1)*2);
			printf("%s",book[start].title);
			gotoxy(48,row+(i+1)*2);
			printf("%d",book[start].count);
			printf("\n");
			start++;
		}
	}
}

CategoryNode* createCategoryNode(const char* category)
 {
    CategoryNode* newNode = (CategoryNode*)malloc(sizeof(CategoryNode));
    strcpy(newNode->category, category);
	memset(newNode->books,0,sizeof(books));
    newNode->left = newNode->right = NULL;
    return newNode;
}

//插入新的类别节点到二叉搜索树中【此时没有图书只有类别】
CategoryNode* insertCategory(CategoryNode* root, const char* category)
 {
    if (root == NULL) 
	{
        return createCategoryNode(category);
    }

    // 根据字典顺序插入【左小右大】
    if (strcmp(category, root->category) < 0) 
	{
        root->left = insertCategory(root->left, category);
    }
    else if (strcmp(category, root->category) > 0)
	 {
        root->right = insertCategory(root->right, category);
    }

    return root;
}

// 将图书添加到对应类别中
void addBookToCategory(CategoryNode* root, BOOK book) 
{
	int i=0;
    if (root == NULL)
	{
		return;
	}
    if (strcmp(book.category, root->category) == 0)
	{
        for(i=0;i<MAX_BOOKS;i++)
		{
			if(strcmp(root->books[i].author,"")==0)
			{
				root->books[i]=book;
				break;
			}
		}
    }
    else if (strcmp(book.category, root->category) < 0) 
	{
        // 如果类别小于当前节点，继续查找左子树
        addBookToCategory(root->left, book);
    }
    else 
	{
        // 如果类别大于当前节点，继续查找右子树
        addBookToCategory(root->right, book);
    }
}

CategoryNode* findCategory(CategoryNode* root, char category[]) 
{
    if (root == NULL) return NULL;

    /*if(checkChildStr(category,root->category)==IS_CHILD)
	{
		return root;
	}*/
	if(strcmp(category ,root->category)==0)
	{
		return root;
	}
    else if (strcmp(category, root->category) < 0) {
        return findCategory(root->left, category);
    }
    else {
        return findCategory(root->right, category);
    }
}

void BuildTree()
{
	int i =0;
	root = NULL;
	for(i=0;i<sizeof(books)/sizeof(BOOK);i++)
	{
		if(strcmp(books[i].author,"")==0)
		{
			break;
		}
		root = insertCategory(root,books[i].category);
	}
	for(i=0;i<sizeof(books)/sizeof(BOOK);i++)
	{
		if(strcmp(books[i].author,"")==0)
		{
			break;
		}
		addBookToCategory(root,books[i]);
	}
}

//初始化书架（范例，融入项目时请根据实际情况修改）
void initShelves()
 {
    strcpy(shelves[0].category, "Computer Science");
    shelves[0].id = 0;

    strcpy(shelves[1].category, "Literature");
    shelves[1].id = 1;

    strcpy(shelves[2].category, "History");
    shelves[2].id = 2;

    strcpy(shelves[3].category, "Mathematics");
    shelves[3].id = 3;

	strcpy(shelves[4].category, "Art");
    shelves[4].id = 4;

    // 更多书架可以继续初始化
}


//初始化图

//添加边的函数（u,v为边的两个顶点）
void addEdge(int u, int v, int weight) 
{
    EdgeNode* edge1; 
	EdgeNode* edge2;
	edge1 = (EdgeNode*)malloc(sizeof(EdgeNode));
    edge1->dest = v;
    edge1->weight = weight;
    edge1->next = libraryGraph[u].head;
    libraryGraph[u].head = edge1;

    edge2 = (EdgeNode*)malloc(sizeof(EdgeNode));
    edge2->dest = u;
    edge2->weight = weight;
    edge2->next = libraryGraph[v].head;
    libraryGraph[v].head = edge2;
}

void initLibraryGraph() 
{
    int i; 
	// 初始化邻接表
    for (i = 0; i < MAX_SHELVES; i++) 
	{
        libraryGraph[i].head = NULL;
    }

    // 假设书架0和书架1之间有距离5的通道，书架1和书架2之间有距离2的通道
    addEdge(0, 1, 5);
    addEdge(1, 2, 2);
    addEdge(0, 3, 7);
    addEdge(2, 3, 3);
	addEdge(0, 4, 4);
    addEdge(1, 4, 6);
    addEdge(2, 4, 8);
    addEdge(3, 4, 1);
    // 更多的书架连接可以继续添加
}

//Dijkstra算法实现点对点最短路径计算（包括对不可达顶点的反馈）
void dijkstra(int start, int* dist, int* prev) 
{
	int i;
	int j;
	EdgeNode* edge;
    int visited[MAX_SHELVES] = { 0 };
    for (i = 0; i < MAX_SHELVES; i++) 
	{
        dist[i] = INT_MAX;   // 设置每个节点的初始距离为无穷大
        prev[i] = -1;        // 记录前驱节点
    }
    dist[start] = 0;         // 起始节点的距离为0

    for (i = 0; i < MAX_SHELVES; i++) 
	{
        int u = -1;
        // 查找距离起点最近的未访问节点
        for (j = 0; j < MAX_SHELVES; j++)
		 {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) 
			{
                u = j;
            }
        }

        if (dist[u] == INT_MAX) break; // 如果剩下的节点都不可达，则结束

        visited[u] = 1;  // 标记当前节点为已访问

        // 更新邻接节点的最短路径
        for (edge = libraryGraph[u].head; edge != NULL; edge = edge->next)
		 {
            int v = edge->dest;
            int weight = edge->weight;
            if (dist[u] + weight < dist[v])
			 {
                dist[v] = dist[u] + weight;
                prev[v] = u;
            }
        }
    }
}


// 打印路径
void printPath(int start, int end, int* prev) 
{
    if (end == -1)
	 {
		gotoxy(10,19);
        printf("No path from Shelf %d (%s) to Shelf %d (%s).\n",
            start, shelves[start].category,
            end, shelves[end].category);
        return;
    }

    // 如果目标书架不可达
    if (end != start && prev[end] == -1) 
	{
		gotoxy(10,19);
        printf("No path from Shelf %d (%s) to Shelf %d (%s).\n",
            start, shelves[start].category,
            end, shelves[end].category);
        return;
    }

    if (start == end)
	 {
        printf("     ║    Shelf %d (%s)", end, shelves[end].category);
        return;
    }

    printPath(start, prev[end], prev);
    if (start != end)
	 {
        printf(" -> \n");
    }
    printf("     ║    Shelf %d (%s)", end, shelves[end].category);
}

//统计每本图书的借阅次数，对以图书索引为下标的数组操作（遍历栈），（参数：借阅历史栈指针，图书借阅量数组指针）
void countBookBorrowings(BorrowHistoryStack stack, int* bookBorrowCount) 
{
    int i = 0;
    for ( i = 0; i <= stack.top; i++) 
    {
        bookBorrowCount[stack.history[i].bookIndex]++;
    }
}

// 统计每个用户的借阅次数（参数：借阅历史栈指针，用户借阅量数组指针，用户名单【二维数组】）
void countUserBorrowings(BorrowHistoryStack stack, int* userBorrowCount, char userNames[MAX_USER_COUNT][50]) 
{
    int i = 0;
    for (i = 0; i <= stack.top; i++)
    {
        int userIndex = -1;
        // 检查该用户是否已经存在
        int j = 0;
        for (j = 0; j < MAX_USER_COUNT; j++) 
        {
            if (strcmp(userNames[j], stack.history[i].userName) == 0) 
            {
                userIndex = j;
                break;
            }
        }

        // 如果用户不存在，记录该用户(添加到userName二维数组)
        
        if (userIndex == -1) {
            for (j = 0; j < MAX_USER_COUNT; j++)
            {
                if (userNames[j][0] == '\0') 
                {
                    strcpy(userNames[j], stack.history[i].userName);
                    userBorrowCount[j] = 0;
                    userIndex = j;
                    break;
                }
            }
        }

        // 统计借阅次数
        if (userIndex != -1) 
        {
            userBorrowCount[userIndex]++;  //此处的userIndex对应的用户字符串即为userName[userIndex]
        }
    }
}

// 快速排序的划分函数
int partitionForCount(int* arr, int* indexArr, int low, int high)
{
    int pivot = arr[high];  // 选择最后一个元素作为pivot
    int i = (low - 1);  // 小于 pivot 的元素索引
    int j;
	int temp;
	int tempIndex;
    for ( j = low; j < high; j++) 
    {
        if (arr[j] > pivot) 
        {  // 如果当前元素大于 pivot，交换它们
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            // 同时交换图书索引
            tempIndex = indexArr[i];
            indexArr[i] = indexArr[j];
            indexArr[j] = tempIndex;
        }
    }

    // 将 pivot 放到正确的位置
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    // 同时交换图书索引
    tempIndex = indexArr[i + 1];
    indexArr[i + 1] = indexArr[high];
    indexArr[high] = tempIndex;

    return i + 1;
}

// 快速排序函数
void quickSortForCount(int* arr, int* indexArr, int low, int high)
{
    if (low < high) 
    {
        int pivot = partitionForCount(arr, indexArr, low, high);
        quickSortForCount(arr, indexArr, low, pivot - 1);
        quickSortForCount(arr, indexArr, pivot + 1, high);
    }
}

//返回基于图书借阅量的图书索引数组（排序后）
void bookIndexAfterReorder(BorrowHistoryStack stack)
{
	  int i;
	  
    countBookBorrowings(stack, bookBorrowCount);
    //创建图书索引数组
    for (i = 0; i < MAX_BOOKS; i++)
    {
        bookIndexes[i] = i;
    }
    //对借阅量快排时同时操作索引数组
    quickSortForCount(bookBorrowCount, bookIndexes, 0, MAX_BOOKS - 1);
}

//返回基于用户借阅量的用户索引数组（排序后）
void userIndexAfterReorder(BorrowHistoryStack stack,char userNames[MAX_USER_COUNT][50]) 
{
	int i;
	int userBorrowCount[MAX_USER_COUNT]={0};
    userBorrowCount[MAX_USER_COUNT];
    countUserBorrowings(stack,userBorrowCount,userNames);
    //创建用户索引数组
    for (i = 0; i < MAX_USER_COUNT; i++) 
    {
        userIndexes[i] = i;
    }
    //对借阅量快排时同时操作索引数组
    quickSortForCount(userBorrowCount, userIndexes, 0, MAX_USER_COUNT - 1);
}