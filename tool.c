#include"tool.h"

void paintWindow(int startX,int startY,int width,int height)  //��ӡ����
{
    int i=0;
    int j=0;
    gotoxy(startX,startY);
    printf("�X");
    for(i=0;i<width-2;i++)
    {
        printf("�T");
    }
    printf("�[\n");
    for(j=0;j<height-2;j++)
    {
        gotoxy(startX,startY+1+j);
        printf("�U");
        for(i=0;i<width-2;i++)
        {
        printf(" ");
        }
        printf("�U\n");
    }
    gotoxy(startX,startY+height-1);

    printf("�^");
    for(i=0;i<width-2;i++)
    {
        printf("�T");
    }
    printf("�a\n");
}

void paintButton(int startX,int startY,int width,int height,char text[])  //��ӡ��ť
{
    paintWindow(startX,startY,width,height);
    gotoxy(startX+(width-strlen(text))/2,startY+1);
    printf("%s",text);
}

void paintExcel(int startX,int startY,int width,int height,int cow,int col) //��ӡ��� 
{
	int i=0;
	int j=0;
	int k=0;
	gotoxy(startX,startY);
	printf("��");
	for(i=0;i<cow-1;i++)
	{
		for(j=0;j<width;j++)
		{
			printf("��");
		}
			printf("��");
	}
	for(i=0;i<width;i++)
	{
		printf("��");
	}
	printf("��\n");
	for(j=0;j<cow+1;j++)
	{
		for(i=1;i<height;i++)
		{
		gotoxy(startX+(width+1)*j,startY+i);
			printf("��");
		}
	}
	
	for(k=1;k<col;k++)
	{
		gotoxy(startX,startY+k*height);
		printf("��");
	for(i=0;i<cow-1;i++)
	{
		for(j=0;j<width;j++)
		{
			printf("��");
		}
			printf("��");
	}
	for(i=0;i<width;i++)
		{
			printf("��");
		}
	printf("��\n");
	
		for(j=0;j<cow+1;j++)
		{
			for(i=1;i<height;i++)
			{
				gotoxy(startX+(width+1)*j,startY+i+height*k);
				printf("��");
			}
		}
	}
		
	gotoxy(startX,startY+col*height);
	printf("��");
	for(i=0;i<cow-1;i++)
	{
		for(j=0;j<width;j++)
		{
			printf("��");
		}
			printf("��");
	}
	for(j=0;j<width;j++)
	{
		printf("��");
	}
	printf("��\n");

}

void gotoxy(int x, int y)//�β�
{
    HANDLE hOut;
    COORD pos = {x, y};
    // ������ʼλ����1�У���3�У� 0�ǵ�1�� 2�ǵ�3��
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
    //printf("��λ���λ������(%d,%d)\n",pos.X,pos.Y);
}

int getUserInput(char str[],int minLen,int maxLen,int flag,int limit) //��ʾ��������ҽ�������Ϊ��������������鲻��Ҫ��С��
{
	//�û�����
	int i=0;
	char ch;
	//maxLen��ʾ�������������ַ�
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
    time(&current_time); // ��ȡϵͳʱ���
	time_info = localtime(&current_time); // ��ʱ���ת��Ϊ�ṹ���ʾ
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
	//Ҫɨ��userArray�ṹ�������п��е�λ�ã��ҵ��ռ�λ�ÿ�����ȥ
	//����Ҫע����û�����Ҫ��ͬ
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
  //memcpyҲ�ǿ���ʵ���ڴ濽��
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
	for(i=0;i<4;i++)   //ÿһҳֻ��������¼
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
	for(i=0;i<4;i++)   //ÿһҳֻ��������¼
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
				printf("����Ա");
			}
			else printf("��ͨ�û�");
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
    case 0:  // ��ISBN����
        return strcmp(bookA->isbn, bookB->isbn);
    case 1:  // ����������
        return strcmp(bookA->title, bookB->title);
    case 2:  // ����������
        return strcmp(bookA->author, bookB->author);
    case 3:  // ��������������
        return strcmp(bookA->publishDate, bookB->publishDate);
    default:
        return 0;  // Ĭ�ϲ�����
    }
}

// ��������
void quickSort(BOOK arr[], int low, int high, int sortBy) 
{
    if (low < high) {
        int pivotIndex = partition(arr, low, high, sortBy);
        quickSort(arr, low, pivotIndex - 1, sortBy);  // ��������������
        quickSort(arr, pivotIndex + 1, high, sortBy); // ��������������
    }
}

// �ָ��
int partition(BOOK arr[], int low, int high, int sortBy) 
{
    BOOK pivot = arr[high]; // ѡ�����һ��Ԫ����Ϊpivot
    int i = low - 1;  // i�Ƿָ��
    int j;
	BOOK temp;
    for (j = low; j < high; j++) 
	{
        if (compareBooks(&arr[j], &pivot, sortBy) < 0) 
		{
            i++;
            // ���� arr[i] �� arr[j]
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // �� pivot �ŵ���ȷ��λ��
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1; // ���� pivot ������
}

void enqueueBorrowRequest(int bookIndex, const char* userName)
 {
	char strTime[50];

	BorrowRequest request;
	getSystemTime(strTime,SHOW_SYS_DATE);
    if ((borrowQueue.rear+1)%MAX_QUEUE_SIZE == borrowQueue.front)
	{
        printf("������������������޷������������\n");
        return;
    }

    request.bookIndex = bookIndex;
    strcpy(request.userName, userName);
	strcpy(request.category,books[bookIndex].category);
    strcpy(request.borrowTime,strTime);  // ��ǰʱ��
	borrowQueue.rear =(borrowQueue.rear+1)%MAX_QUEUE_SIZE;
    borrowQueue.requests[borrowQueue.rear] = request;
	gotoxy(10,17);
    printf("���������Ѽ�����У�ͼ�顶%s��, �û���%s\n", books[bookIndex].title, request.userName);
}

int dequeueBorrowRequest() 
{
	BorrowRequest emptyRequest= {-1,"",""};
    if (borrowQueue.front == borrowQueue.rear)
	{
        printf("�����������Ϊ�գ�\n");
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
{     //���㳬�޷���
    const int borrowPeriod = 30; // 30��
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
        lateFee = ((int)diff- borrowPeriod) *0.2; // ��������
    }
    return lateFee;
}

void paintHistoryData(int start,int HistoryCount,int row,BorrowHistory history[])
{
		int i=0;
	for(i=0;i<4;i++)   //ÿһҳֻ��������¼
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
	for(i=0;i<4;i++)   //ÿһҳֻ��������¼
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

//�����µ����ڵ㵽�����������С���ʱû��ͼ��ֻ�����
CategoryNode* insertCategory(CategoryNode* root, const char* category)
 {
    if (root == NULL) 
	{
        return createCategoryNode(category);
    }

    // �����ֵ�˳����롾��С�Ҵ�
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

// ��ͼ����ӵ���Ӧ�����
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
        // ������С�ڵ�ǰ�ڵ㣬��������������
        addBookToCategory(root->left, book);
    }
    else 
	{
        // ��������ڵ�ǰ�ڵ㣬��������������
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

//��ʼ����ܣ�������������Ŀʱ�����ʵ������޸ģ�
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

    // ������ܿ��Լ�����ʼ��
}


//��ʼ��ͼ

//��ӱߵĺ�����u,vΪ�ߵ��������㣩
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
	// ��ʼ���ڽӱ�
    for (i = 0; i < MAX_SHELVES; i++) 
	{
        libraryGraph[i].head = NULL;
    }

    // �������0�����1֮���о���5��ͨ�������1�����2֮���о���2��ͨ��
    addEdge(0, 1, 5);
    addEdge(1, 2, 2);
    addEdge(0, 3, 7);
    addEdge(2, 3, 3);
	addEdge(0, 4, 4);
    addEdge(1, 4, 6);
    addEdge(2, 4, 8);
    addEdge(3, 4, 1);
    // �����������ӿ��Լ������
}

//Dijkstra�㷨ʵ�ֵ�Ե����·�����㣨�����Բ��ɴﶥ��ķ�����
void dijkstra(int start, int* dist, int* prev) 
{
	int i;
	int j;
	EdgeNode* edge;
    int visited[MAX_SHELVES] = { 0 };
    for (i = 0; i < MAX_SHELVES; i++) 
	{
        dist[i] = INT_MAX;   // ����ÿ���ڵ�ĳ�ʼ����Ϊ�����
        prev[i] = -1;        // ��¼ǰ���ڵ�
    }
    dist[start] = 0;         // ��ʼ�ڵ�ľ���Ϊ0

    for (i = 0; i < MAX_SHELVES; i++) 
	{
        int u = -1;
        // ���Ҿ�����������δ���ʽڵ�
        for (j = 0; j < MAX_SHELVES; j++)
		 {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) 
			{
                u = j;
            }
        }

        if (dist[u] == INT_MAX) break; // ���ʣ�µĽڵ㶼���ɴ�����

        visited[u] = 1;  // ��ǵ�ǰ�ڵ�Ϊ�ѷ���

        // �����ڽӽڵ�����·��
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


// ��ӡ·��
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

    // ���Ŀ����ܲ��ɴ�
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
        printf("     �U    Shelf %d (%s)", end, shelves[end].category);
        return;
    }

    printPath(start, prev[end], prev);
    if (start != end)
	 {
        printf(" -> \n");
    }
    printf("     �U    Shelf %d (%s)", end, shelves[end].category);
}

//ͳ��ÿ��ͼ��Ľ��Ĵ���������ͼ������Ϊ�±���������������ջ������������������ʷջָ�룬ͼ�����������ָ�룩
void countBookBorrowings(BorrowHistoryStack stack, int* bookBorrowCount) 
{
    int i = 0;
    for ( i = 0; i <= stack.top; i++) 
    {
        bookBorrowCount[stack.history[i].bookIndex]++;
    }
}

// ͳ��ÿ���û��Ľ��Ĵ�����������������ʷջָ�룬�û�����������ָ�룬�û���������ά���顿��
void countUserBorrowings(BorrowHistoryStack stack, int* userBorrowCount, char userNames[MAX_USER_COUNT][50]) 
{
    int i = 0;
    for (i = 0; i <= stack.top; i++)
    {
        int userIndex = -1;
        // �����û��Ƿ��Ѿ�����
        int j = 0;
        for (j = 0; j < MAX_USER_COUNT; j++) 
        {
            if (strcmp(userNames[j], stack.history[i].userName) == 0) 
            {
                userIndex = j;
                break;
            }
        }

        // ����û������ڣ���¼���û�(��ӵ�userName��ά����)
        
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

        // ͳ�ƽ��Ĵ���
        if (userIndex != -1) 
        {
            userBorrowCount[userIndex]++;  //�˴���userIndex��Ӧ���û��ַ�����ΪuserName[userIndex]
        }
    }
}

// ��������Ļ��ֺ���
int partitionForCount(int* arr, int* indexArr, int low, int high)
{
    int pivot = arr[high];  // ѡ�����һ��Ԫ����Ϊpivot
    int i = (low - 1);  // С�� pivot ��Ԫ������
    int j;
	int temp;
	int tempIndex;
    for ( j = low; j < high; j++) 
    {
        if (arr[j] > pivot) 
        {  // �����ǰԪ�ش��� pivot����������
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            // ͬʱ����ͼ������
            tempIndex = indexArr[i];
            indexArr[i] = indexArr[j];
            indexArr[j] = tempIndex;
        }
    }

    // �� pivot �ŵ���ȷ��λ��
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    // ͬʱ����ͼ������
    tempIndex = indexArr[i + 1];
    indexArr[i + 1] = indexArr[high];
    indexArr[high] = tempIndex;

    return i + 1;
}

// ����������
void quickSortForCount(int* arr, int* indexArr, int low, int high)
{
    if (low < high) 
    {
        int pivot = partitionForCount(arr, indexArr, low, high);
        quickSortForCount(arr, indexArr, low, pivot - 1);
        quickSortForCount(arr, indexArr, pivot + 1, high);
    }
}

//���ػ���ͼ���������ͼ���������飨�����
void bookIndexAfterReorder(BorrowHistoryStack stack)
{
	  int i;
	  
    countBookBorrowings(stack, bookBorrowCount);
    //����ͼ����������
    for (i = 0; i < MAX_BOOKS; i++)
    {
        bookIndexes[i] = i;
    }
    //�Խ���������ʱͬʱ������������
    quickSortForCount(bookBorrowCount, bookIndexes, 0, MAX_BOOKS - 1);
}

//���ػ����û����������û��������飨�����
void userIndexAfterReorder(BorrowHistoryStack stack,char userNames[MAX_USER_COUNT][50]) 
{
	int i;
	int userBorrowCount[MAX_USER_COUNT]={0};
    userBorrowCount[MAX_USER_COUNT];
    countUserBorrowings(stack,userBorrowCount,userNames);
    //�����û���������
    for (i = 0; i < MAX_USER_COUNT; i++) 
    {
        userIndexes[i] = i;
    }
    //�Խ���������ʱͬʱ������������
    quickSortForCount(userBorrowCount, userIndexes, 0, MAX_USER_COUNT - 1);
}