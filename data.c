#include"data.h"

void initUserLink()
{
		userLink = (USERLINK*)malloc(sizeof(USERLINK));
	    strcpy(userLink->user.userName, "admin");
		strcpy(userLink->user.passwd, "123456");
		userLink->user.role = 1;
		userLink->user.id = 1001;
		userLink->next = NULL;
}

void initUserData(char*fileName)
{
	FILE*fp=NULL;
	int i=0;
	USERLINK*p = userLink;
	USERLINK*newNode;
	fp=fopen(fileName,"rb");
	if(!fp)
	{
		
		//说明文件不存在
		fp=fopen(fileName,"wb+");
		fwrite(&userLink->user,sizeof(USER),1,fp);
	}
	rewind(fp);//使文件指针重新至于文件开头
	while(fread(&p->user,sizeof(USER),1,fp))
	{
		newNode =(USERLINK*)malloc(sizeof(USERLINK));
        newNode->next = NULL;
		p->next=newNode;
		p=p->next;
	}
	fclose(fp);
}

int addUserToFile(char*fileName,USER reg_user)
{
	FILE*fp=NULL;
	fp=fopen(fileName,"ab");
	if(!fp)
	{
		return -1;
	}
	fwrite(&reg_user,sizeof(USER),1,fp);
	fclose(fp);
	return 0;
}

int dataUpdate(char*fileName,void*data,int position,int size)
{
	FILE*fp=NULL;
	int i;
	fp=fopen(fileName,"rb+");
	if(!fp)
	{
		return -1;
	}
	fseek(fp,position,SEEK_SET);
	fwrite(data,size,1,fp);
	fclose(fp);
	return 0;
}

void initBookData(char*fileName)
{
	FILE*fp=NULL;
	int i=0;
	fp=fopen(fileName,"rb");
	if(!fp)
	{
		//说明文件不存在
		fp=fopen(fileName,"wb+");
		fwrite(books,sizeof(BOOK),1,fp);
	}
	rewind(fp);//使文件指针重新至于文件开头
	while(fread(&books[i],sizeof(BOOK),1,fp))
	{
		i++;
	}
	fclose(fp);
	
}

int addBookToFile(char*fileName,BOOK newBook)
{
	FILE*fp=NULL;
	fp=fopen(fileName,"ab");
	if(!fp)
	{
		return -1;
	}
	fwrite(&newBook,sizeof(BOOK),1,fp);
	fclose(fp);
	return 0;
}

void rebuildFile(char*fileName,void*data,int count,int size)
{
	FILE*fp=NULL;
	fp=fopen(fileName,"wb+");
	rewind(fp);
	fwrite(data,size,count,fp);
	fclose(fp);
}

void initHistoryData(char*fileName)
{
	FILE*fp=NULL;
	int i=0;
	fp=fopen(fileName,"rb");
	if(!fp)
	{
		//说明文件不存在
		fp=fopen(fileName,"wb+");
	}
	rewind(fp);//使文件指针重新至于文件开头
	while(fread(&borrowHistoryStack.history[i],sizeof(BorrowHistory),1,fp))
	{
		i++;
	}
	borrowHistoryStack.top=i-1;
	fclose(fp);
}

int addHistoryToFile(char*fileName,BorrowHistory history)
{
	FILE*fp=NULL;
	fp=fopen(fileName,"ab");
	if(!fp)
	{
		return -1;
	}
	fwrite(&history,sizeof(BorrowHistory),1,fp);
	fclose(fp);
	return 0;
}

