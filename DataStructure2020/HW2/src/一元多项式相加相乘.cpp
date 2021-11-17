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
 
class Ploy;    //提前声明，因为定义友元要用到
 
class LNode {
public:
	int coef;
	int expo;
	LNode* next;    //指针域
	friend class Ploy;
	friend ostream& operator<<(ostream& out, const Ploy& a);
	//不定义任何函数，相当于struct LNode
};
 
class Ploy {
protected:
	LNode* head;    //头指针
public:
	/* P.19-20的抽象数据类型定义转换为实际的C++语言 */
	Ploy();    //构造函数，替代InitList
	Ploy(const Ploy &p);
	~Ploy();    //析构函数，替代DestroyList
	void Ploy_add_ele(const int p, const int e);
	Ploy Ploy_mul_ele(const int c, const int e);
	Ploy& operator=(const Ploy& p);
	Ploy operator+(const Ploy& p);
	Ploy Ploy_mul(const Ploy& a);
	friend ostream & operator<<(ostream& out, const Ploy& a);
};
 
 
 
/* 构造函数（初始化线性表） */
Ploy::Ploy()
{
	/* 申请头结点空间，赋值给头指针 */
	head = new LNode;
	if (head == NULL)
		exit(MYOVERFLOW);
 
	head->next = NULL;
}
 
/* 构造函数（初始化线性表） */
Ploy::Ploy(const Ploy &p)
{
	/* 申请头结点空间，赋值给头指针 */
	head = new LNode;
	if (head == NULL)
		exit(MYOVERFLOW);
 
	LNode* q = head;
	LNode* r = p.head;
	while (r->next)
	{
		q->next = new(nothrow) LNode;
		if (!q->next)exit(MYOVERFLOW);
		q->next->coef = r->next->coef;
		q->next->expo = r->next->expo;
		q->next->next = r->next->next;
		q = q->next;
		r = r->next;
	}
}
 
/* 析构函数（删除线性表） */
Ploy::~Ploy()
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
 
Ploy& Ploy::operator=(const Ploy& p)
{
	LNode* t = head->next;
	LNode* s;
	while (t)
	{
		s = t->next;
		delete t;
		t = s;
	}
 
	LNode* q = head;
	LNode* r = p.head;
	while (r->next)
	{
		q->next = new(nothrow) LNode;
		if (!q->next)exit(MYOVERFLOW);
		q->next->coef = r->next->coef;
		q->next->expo = r->next->expo;
		q->next->next = r->next->next;
		q = q->next;
		r = r->next;
	}
	return *this;
}
 
Ploy Ploy::operator+(const Ploy& p)
{
	Ploy PC;
	LNode* q = head->next;
	while (q)
	{
		PC.Ploy_add_ele(q->coef, q->expo);
		q = q->next;
	}
	q = p.head->next;
	while (q)
	{
		PC.Ploy_add_ele(q->coef, q->expo);
		q = q->next;
	}
	return PC;
}
 
void Ploy::Ploy_add_ele(const int c, const int e)
{
	if (!c)return;
	LNode* l = head;
	LNode* r = l->next;
	while (r)
	{
		if (r->expo == e)//该指数=r节点指数
		{
			r->coef += c;
			if (r->coef == 0)//加后系数0
			{
				l->next = r->next;
				delete r;
			}
			return;
		}
		else if (r->expo > e)//该指数未出现过，插在l和r之间
		{
			LNode* s = new(nothrow) LNode;
			if (!s)exit(MYOVERFLOW);
			s->expo = e;
			s->coef = c;
			l->next = s;
			s->next = r;
			return;
		}
 
		l = l->next;
		r = r->next;
	}
 
	//r移动到了NULL,还没有插进去，此时尾节点是l
	l->next = new(nothrow) LNode;
	if (!l->next)exit(MYOVERFLOW);
	l->next->expo = e;
	l->next->coef = c;
	l->next->next = NULL;
	return;
}
 
Ploy Ploy::Ploy_mul_ele(const int c, const int e)
{
	Ploy temp;
	if (!c)return temp;
	LNode* q = head->next;
	while (q)
	{
		temp.Ploy_add_ele(q->coef * c, q->expo + e);
		q = q->next;
	}
 
	return temp;
}
 
Ploy Ploy::Ploy_mul(const Ploy& a)
{
	Ploy res;
	LNode* q = a.head->next;
	while (q)
	{
		Ploy temp = *this;
		temp = temp.Ploy_mul_ele(q->coef, q->expo);
		res = res + temp;
		q = q->next;
	}
	return res;
}
 
ostream& operator<<(ostream& out,const Ploy& a)
{
	LNode* p = a.head->next;
	if (!p)
		return out;
 
	while (p)
	{
		out << p->coef << " " << p->expo << (p->next == NULL ? '\n' : ' ');
		p = p->next;
	}
 
	return out;
}
 
 
int main()
{
	Ploy PA, PB;
	int n, m;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int e, c;
		scanf("%d%d", &c, &e);
		PA.Ploy_add_ele(c, e);
	}
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
	{
		int e, c;
		scanf("%d%d", &c, &e);
		PB.Ploy_add_ele(c, e);
	}
 
	int command;
	scanf("%d", &command);
	if (command == 0 || command == 2)
	{
		cout << PA + PB;
	}
	if (command == 1 || command == 2)
	{
		Ploy PC = PA.Ploy_mul(PB);
		cout << PC;
	}
 
	return 0;
}