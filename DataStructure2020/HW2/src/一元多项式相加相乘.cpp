#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstdlib>
 
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
/* P.10 ��Ԥ���峣�������� */
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define MYOVERFLOW    -2
 
typedef int Status;
 
class Ploy;    //��ǰ��������Ϊ������ԪҪ�õ�
 
class LNode {
public:
	int coef;
	int expo;
	LNode* next;    //ָ����
	friend class Ploy;
	friend ostream& operator<<(ostream& out, const Ploy& a);
	//�������κκ������൱��struct LNode
};
 
class Ploy {
protected:
	LNode* head;    //ͷָ��
public:
	/* P.19-20�ĳ����������Ͷ���ת��Ϊʵ�ʵ�C++���� */
	Ploy();    //���캯�������InitList
	Ploy(const Ploy &p);
	~Ploy();    //�������������DestroyList
	void Ploy_add_ele(const int p, const int e);
	Ploy Ploy_mul_ele(const int c, const int e);
	Ploy& operator=(const Ploy& p);
	Ploy operator+(const Ploy& p);
	Ploy Ploy_mul(const Ploy& a);
	friend ostream & operator<<(ostream& out, const Ploy& a);
};
 
 
 
/* ���캯������ʼ�����Ա� */
Ploy::Ploy()
{
	/* ����ͷ���ռ䣬��ֵ��ͷָ�� */
	head = new LNode;
	if (head == NULL)
		exit(MYOVERFLOW);
 
	head->next = NULL;
}
 
/* ���캯������ʼ�����Ա� */
Ploy::Ploy(const Ploy &p)
{
	/* ����ͷ���ռ䣬��ֵ��ͷָ�� */
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
 
/* ����������ɾ�����Ա� */
Ploy::~Ploy()
{
	LNode* q, * p = head;
 
	/* ��ͷ��㿪ʼ�����ͷţ���ͷ��㣩 */
	while (p) {    //������Ϊ�գ���ѭ����ִ��
		q = p->next; //ץס�������һ�����
		delete p;
		p = q;
	}
 
	head = NULL;    //ͷָ����NULL
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
		if (r->expo == e)//��ָ��=r�ڵ�ָ��
		{
			r->coef += c;
			if (r->coef == 0)//�Ӻ�ϵ��0
			{
				l->next = r->next;
				delete r;
			}
			return;
		}
		else if (r->expo > e)//��ָ��δ���ֹ�������l��r֮��
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
 
	//r�ƶ�����NULL,��û�в��ȥ����ʱβ�ڵ���l
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