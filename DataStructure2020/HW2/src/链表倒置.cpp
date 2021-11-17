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
 
typedef int ElemType;    //�ɸ�����Ҫ�޸�Ԫ�ص�����
 
class LinkList;    //��ǰ��������Ϊ������ԪҪ�õ�
 
class LNode {
protected:
	ElemType data;    //������
	LNode* next;    //ָ����
public:
	friend class LinkList;
	//�������κκ������൱��struct LNode
};
 
class LinkList {
protected:
	LNode* head;    //ͷָ��
public:
	/* P.19-20�ĳ����������Ͷ���ת��Ϊʵ�ʵ�C++���� */
	LinkList();    //���캯�������InitList
	~LinkList();    //�������������DestroyList
	int    ListLength();
	Status ListPrint();
	Status    ListInsert(int i, ElemType e);
	Status ListReverse(const int start, const int end);
};
 
 
 
/* ���캯������ʼ�����Ա� */
LinkList::LinkList()
{
	/* ����ͷ���ռ䣬��ֵ��ͷָ�� */
	head = new LNode;
	if (head == NULL)
		exit(MYOVERFLOW);
 
	head->next = NULL;
}
 
/* ����������ɾ�����Ա� */
LinkList::~LinkList()
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
 
/* ���ĳ��� */
int LinkList::ListLength()
{
	LNode* p = head->next; //ָ����Ԫ���
	int    len = 0;
 
	/* ѭ�������������м��� */
	while (p) {
		p = p->next;
		len++;
	}
 
	return len;
}
 
/* ��ָ��λ�ò���һ����Ԫ�أ��������Ժ�e�ڵ�i�� */
Status LinkList::ListInsert(int i, ElemType e)
{
	LNode* s, * p = head;    //pָ��ͷ���
	int   pos = 0;
 
	/* Ѱ�ҵ�i-1����� */
	while (p && pos < i - 1) {
		p = p->next;
		pos++;
	}
 
	if (p == NULL || pos > i - 1)  //iֵ�Ƿ��򷵻�
		return ERROR;
 
	//ִ�е��˱�ʾ�ҵ�ָ��λ�ã�pָ���i-1�����
 
	s = new LNode;
	if (s == NULL)
		return MYOVERFLOW;
 
	s->data = e;     //�½��������ֵ
	s->next = p->next;    //�½���next�ǵ�i��
	p->next = s;    //��i-1����next���½��
 
	return OK;
}
 
/* ��ӡ���Ա� */
Status LinkList::ListPrint()
{
	extern int line_count; //��main�ж���Ĵ�ӡ���м����������㷨�޹أ�
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
 
/* ����������[strat,end]��Ԫ��*/
Status LinkList::ListReverse(const int start, const int end)
{
	const int len = ListLength();
	if (start <= 0 || end <= 0 || start > len || end > len || start >= end)
		return ERROR;
 
	LNode* p_start = head;
	LNode* p_end = head;
	int pos_start = 0;
	int pos_end = 0;
 
	while (pos_start < start - 1)//ѭ������ʱ��p_startͣ��startǰһλ
	{
		p_start = p_start->next;
		pos_start++;
	}
 
	while (pos_end < end)//ѭ������ʱ��p_endͣ��end
	{
		p_end = p_end->next;
		pos_end++;
	}
 
	LNode* p = p_start->next;//pָ���start��Ԫ��
	LNode* q = p->next;//qָ��ԭ����p����һλ
	LNode* r;
	p_start->next = p_end;
	p->next = p_end->next;
	while (p != p_end)
	{
		r = q->next;
		q->next = p;
		p = q;
		q = r;
	}
	return OK;
}
 
 
#define INSERT_NUM        115        //��ʼ������е�Ԫ������
#define MAX_NUM_PER_LINE     10        //ÿ����������Ԫ�ظ���
 
int main()
{
	LinkList L;
	int n, k;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int t;
		scanf("%d", &t);
		L.ListInsert(i, t);
	}
	scanf("%d", &k);
	for (int i = 1; i <= k; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		if (L.ListReverse(l, r) == OK)
			L.ListPrint();
		else
			printf("0");
	}
	return 0;
}