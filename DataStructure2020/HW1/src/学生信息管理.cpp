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
 
#define LIST_INIT_SIZE    10005    //��ʼ��С����Ϊ100���ɰ����޸ģ�
#define LISTINCREMENT    10    //���ռ䲻����ÿ������10���ɰ����޸ģ�
 
typedef struct student {
	char  no[10];
	char  name[20];
} ElemType;
 
typedef struct {
	ElemType* elem;    //��Ŷ�̬����ռ���׵�ַ���������Ϊ��ͷԪ��a1�ĵ�ַ��
	int length;        //��¼��ǰ����
	int listsize;    //��ǰ�����Ԫ�صĸ���
} sqlist;
 
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define MYOVERFLOW    -2
 
#define INSERT_NUM        115        //��ʼ������е�Ԫ������
#define MAX_NUM_PER_LINE     1        //ÿ����������Ԫ�ظ���
 
int line_count = 0;   //��ӡ����ʱ�ļ�����
 
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
 
 
 
/* ��ʼ�����Ա� */
Status InitList(sqlist* L)
{
	L->elem = new(nothrow) ElemType[LIST_INIT_SIZE];
	if (L->elem == NULL)
		exit(MYOVERFLOW);
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
	return OK;
}
 
/* ɾ�����Ա� */
Status DestroyList(sqlist* L)
{
	/* ��δִ�� InitList��ֱ��ִ�б�����������ܳ�����Ϊָ���ʼֵδ�� */
	if (L->elem)
		delete[]L->elem;
	L->length = 0;
	L->listsize = 0;
 
	return OK;
}
 
/* ���ĳ��� */
int ListLength(sqlist L)
{
	return L.length;
}
 
/* ��ָ��λ��ǰ����һ����Ԫ�� */
Status ListInsert(sqlist* L, int i, ElemType e)
{
	ElemType* p, * q; //������㷨��һ�����ʡ�ԣ�������
 
	if (i<1 || i>L->length + 1)   //����Χ�� 1..length+1
		return ERROR;
 
	/* �ռ�����������ռ� */
	if (L->length >= L->listsize)
	{
		ElemType* newbase;
		newbase = new(nothrow) ElemType[L->listsize + LISTINCREMENT];
		if (!newbase)
			return MYOVERFLOW;
 
		for (int i = 0; i < L->listsize; i++)
			memcpy(newbase + i, L->elem + i, sizeof(ElemType));//ԭ�ռ����ݸ��ƹ���
 
		delete[]L->elem;//�ͷ�ԭ�ռ�
 
		L->elem = newbase;
		L->listsize += LISTINCREMENT;
		//L->length��ʱ����
	}
 
	q = &(L->elem[i - 1]);  //��i��Ԫ�أ����µĲ���λ��
	/* �����һ����length����[length-1]�С���ʼ����i��Ԫ�����κ���һ�� */
	for (p = &(L->elem[L->length - 1]); p >= q; --p)
		memcpy(p + 1, p, sizeof(ElemType));    //������strcpy
 
	/* ������Ԫ�أ�����+1 */
	memcpy(q, &e, sizeof(ElemType));
	L->length++;
 
	return OK;
}
 
/* ɾ��ָ��λ�õ�Ԫ�أ�������ɾ��Ԫ�ص�ֵ����e�з��� */
Status ListDelete(sqlist* L, int i, ElemType* e)
{
	ElemType* p, * q; //������㷨��һ�����ʡ�ԣ�������
 
	if (i<1 || i>L->length) //����Χ�� 1..length
		return ERROR;
 
	p = &(L->elem[i - 1]);         //ָ���i��Ԫ��
	memcpy(e, p, sizeof(ElemType));    //ȡ��i��Ԫ�ص�ֵ����e��
	q = &(L->elem[L->length - 1]);    //ָ�����һ��Ԫ�أ�Ҳ���� q = L->elem+L->length-1
 
	/* �ӵ�i+1���������ǰ��һ�� */
	for (++p; p <= q; ++p)
		memcpy((p - 1), p, sizeof(ElemType));
 
	L->length--;    //����-1
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