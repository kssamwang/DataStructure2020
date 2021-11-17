#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstdlib>
 
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
/* P.10 的预定义常量和类型 */
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define MYOVERFLOW    -2
 
typedef int Status;
 
typedef int ElemType;    //可根据需要修改元素的类型
 
class LinkList;    //提前声明，因为定义友元要用到
 
class LNode {
protected:
	ElemType data;    //数据域
	LNode* next;    //指针域
public:
	friend class LinkList;
	//不定义任何函数，相当于struct LNode
};
 
class LinkList {
protected:
	LNode* head;    //头指针
public:
	/* P.19-20的抽象数据类型定义转换为实际的C++语言 */
	LinkList();    //构造函数，替代InitList
	~LinkList();    //析构函数，替代DestroyList
	int    ListLength();
	Status ListPrint();
	Status    ListInsert(int i, ElemType e);
	Status ListUnique();
};
 
 
 
/* 构造函数（初始化线性表） */
LinkList::LinkList()
{
	/* 申请头结点空间，赋值给头指针 */
	head = new LNode;
	if (head == NULL)
		exit(MYOVERFLOW);
 
	head->next = NULL;
}
 
/* 析构函数（删除线性表） */
LinkList::~LinkList()
{
	LNode* q, * p = head;
 
	/* 从头结点开始依次释放（含头结点） */
	while (p) {    //若链表为空，则循环不执行
		q = p->next; //抓住链表的下一个结点
		delete p;
		p = q;
	}
 
	head = NULL;    //头指针置NULL
}
 
/* 求表的长度 */
int LinkList::ListLength()
{
	LNode* p = head->next; //指向首元结点
	int    len = 0;
 
	/* 循环整个链表，进行计数 */
	while (p) {
		p = p->next;
		len++;
	}
 
	return len;
}
 
/* 在指定位置插入一个新元素，插入完以后e在第i个 */
Status LinkList::ListInsert(int i, ElemType e)
{
	LNode* s, * p = head;    //p指向头结点
	int   pos = 0;
 
	/* 寻找第i-1个结点 */
	while (p && pos < i - 1) {
		p = p->next;
		pos++;
	}
 
	if (p == NULL || pos > i - 1)  //i值非法则返回
		return ERROR;
 
	//执行到此表示找到指定位置，p指向第i-1个结点
 
	s = new LNode;
	if (s == NULL)
		return MYOVERFLOW;
 
	s->data = e;     //新结点数据域赋值
	s->next = p->next;    //新结点的next是第i个
	p->next = s;    //第i-1个的next是新结点
 
	return OK;
}
 
/* 打印线性表 */
Status LinkList::ListPrint()
{
	extern int line_count; //在main中定义的打印换行计数器（与算法无关）
	LNode* p = head->next;
	if (!p)
		return ERROR;
 
	while (p)
	{
		printf("%d%c", p->data, (p->next == NULL ? '\n' : ' '));
		p = p->next;
	}
 
	return OK;
}
 
Status LinkList::ListUnique()
{
	LNode* p = head->next;
	while (p)
	{
		LNode* q = head->next;
		LNode* r = p->next;
		int e = p->data;
		bool repeat = false;
		while (q != p)
		{
			if (q->data == e)
			{
				repeat = true;
			}
			if (q->next == p && repeat)
			{
				q->next = p->next;
				break;
			}
			q = q->next;
		}
		if (repeat)
		{
			delete p;
		}
		p = r;
	}
	return OK;
}
 
#define INSERT_NUM        115        //初始插入表中的元素数量
#define MAX_NUM_PER_LINE     10        //每行最多输出的元素个数
 
int main()
{
	LinkList L;
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int t;
		scanf("%d", &t);
		L.ListInsert(i, t);
	}
	L.ListUnique();
	L.ListPrint();
	return 0;
}