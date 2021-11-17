#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#pragma warning(disable:4005)
#endif
 
#define LIST_INIT_SIZE    10005    //初始大小定义为100（可按需修改）
#define LISTINCREMENT    10    //若空间不够，每次增长10（可按需修改）
 
typedef struct student {
	char  no[10];
	char  name[20];
} ElemType;
 
typedef struct {
	ElemType* elem;    //存放动态申请空间的首地址（可以理解为表头元素a1的地址）
	int length;        //记录当前长度
	int listsize;    //当前分配的元素的个数
} sqlist;
 
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define MYOVERFLOW    -2
 
#define INSERT_NUM        115        //初始插入表中的元素数量
#define MAX_NUM_PER_LINE     1        //每行最多输出的元素个数
 
int line_count = 0;   //打印链表时的计数器
 
typedef int Status;
 
Status    InitList(sqlist* L);
Status    DestroyList(sqlist* L);
Status    ClearList(sqlist* L);
Status    ListEmpty(sqlist L);
int    ListLength(sqlist L);
Status    GetElem(sqlist L, int i, ElemType* e);
int    LocateElem(sqlist L, ElemType e, Status(*compare)(ElemType e1, ElemType e2));
Status    PriorElem(sqlist L, ElemType cur_e, ElemType* pre_e);
Status    NextElem(sqlist L, ElemType cur_e, ElemType* next_e);
Status    ListInsert(sqlist* L, int i, ElemType e);
Status    ListDelete(sqlist* L, int i, ElemType* e);
Status    ListTraverse(sqlist L, Status(*visit)(ElemType e));
 
 
 
/* 初始化线性表 */
Status InitList(sqlist* L)
{
	L->elem = new(nothrow) ElemType[LIST_INIT_SIZE];
	if (L->elem == NULL)
		exit(MYOVERFLOW);
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
	return OK;
}
 
/* 删除线性表 */
Status DestroyList(sqlist* L)
{
	/* 若未执行 InitList，直接执行本函数，则可能出错，因为指针初始值未定 */
	if (L->elem)
		delete[]L->elem;
	L->length = 0;
	L->listsize = 0;
 
	return OK;
}
 
/* 求表的长度 */
int ListLength(sqlist L)
{
	return L.length;
}
 
/* 在指定位置前插入一个新元素 */
Status ListInsert(sqlist* L, int i, ElemType e)
{
	ElemType* p, * q; //如果是算法，一般可以省略，程序不能
 
	if (i<1 || i>L->length + 1)   //合理范围是 1..length+1
		return ERROR;
 
	/* 空间已满则扩大空间 */
	if (L->length >= L->listsize)
	{
		ElemType* newbase;
		newbase = new(nothrow) ElemType[L->listsize + LISTINCREMENT];
		if (!newbase)
			return MYOVERFLOW;
 
		for (int i = 0; i < L->listsize; i++)
			memcpy(newbase + i, L->elem + i, sizeof(ElemType));//原空间数据复制过来
 
		delete[]L->elem;//释放原空间
 
		L->elem = newbase;
		L->listsize += LISTINCREMENT;
		//L->length暂时不变
	}
 
	q = &(L->elem[i - 1]);  //第i个元素，即新的插入位置
	/* 从最后一个【length放在[length-1]中】开始到第i个元素依次后移一格 */
	for (p = &(L->elem[L->length - 1]); p >= q; --p)
		memcpy(p + 1, p, sizeof(ElemType));    //不能用strcpy
 
	/* 插入新元素，长度+1 */
	memcpy(q, &e, sizeof(ElemType));
	L->length++;
 
	return OK;
}
 
/* 删除指定位置的元素，并将被删除元素的值放入e中返回 */
Status ListDelete(sqlist* L, int i, ElemType* e)
{
	ElemType* p, * q; //如果是算法，一般可以省略，程序不能
 
	if (i<1 || i>L->length) //合理范围是 1..length
		return ERROR;
 
	p = &(L->elem[i - 1]);         //指向第i个元素
	memcpy(e, p, sizeof(ElemType));    //取第i个元素的值放入e中
	q = &(L->elem[L->length - 1]);    //指向最后一个元素，也可以 q = L->elem+L->length-1
 
	/* 从第i+1到最后，依次前移一格 */
	for (++p; p <= q; ++p)
		memcpy((p - 1), p, sizeof(ElemType));
 
	L->length--;    //长度-1
	return OK;
}
 
 
 
 
int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
 
	sqlist   L;
 
	InitList(&L);
 
	int n = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		ElemType s;
		cin >> s.no >> s.name;
		ListInsert(&L, i, s);
	}
 
	while (1)
	{
		string command;
		cin >> command;
		if (command == "end")
		{
			cout << ListLength(L);
			break;
		}
		else if (command == "insert")
		{
			int pos;
			cin >> pos;
			ElemType s;
			cin >> s.no >> s.name;
			if (ListInsert(&L, pos, s) == OK)
				cout << "0" << endl;
			else
				cout << "-1" << endl;
		}
		else if (command == "remove")
		{
			int pos;
			cin >> pos;
			ElemType s;
			if (ListDelete(&L, pos, &s) == OK)
				cout << "0" << endl;
			else
				cout << "-1" << endl;
		}
		else if (command == "check")
		{
			cin >> command;
			if (command == "no")
			{
				string no;
				cin >> no;
				int j = 0;
				while (j < L.length && strcmp(L.elem[j].no, no.c_str()) != 0)j++;
				if (j < L.length)
					cout << j + 1 << " " << L.elem[j].no << " " << L.elem[j].name << endl;
				else
					cout << "-1" << endl;
			}
			else if (command == "name")
			{
				string name;
				cin >> name;
				int j = 0;
				while (j < L.length && strcmp(L.elem[j].name, name.c_str()) != 0)j++;
				if (j < L.length)
					cout << j + 1 << " " << L.elem[j].no << " " << L.elem[j].name << endl;
				else
					cout << "-1" << endl;
			}
		}
	}
 
	DestroyList(&L);
 
	return 0;
}