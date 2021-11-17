#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
struct node {
	int data;
	node* next;
};
 
struct node* head = NULL;
 
void release() 
{
	node* p = head;
	node* q = p->next;
	while (p->next != NULL)
	{
		q = p->next;
		delete p;
		p = q;
	}
}
 
int Delete(const int e)
{
	int count = 0;
	node* p = head;
	node* q = p->next;
	while (q != NULL)
	{
		if (q->data == e)
		{
			p->next = q->next;
			delete q;
			q = p->next;
			count++;
		}
		else
		{
			p = p->next;
			q = p->next;
		}
	}
	return count;
}
 
void printres()
{
	node* p = head;
	node* q = p->next;
	while (p->next != NULL)
	{
		q = p->next;
		printf("%d", q->data);
		p = q;
		if(p->next != NULL)
			printf(" ");
	}
}
 
int main()
{
	int n;
	scanf("%d", &n);
	head = new(nothrow) node;
	if (head == NULL)
		return 0;
 
	struct node* p = head;
	for (int i = 0;i < n;i++)
	{
		node* t = new(nothrow) node;
		if (t == NULL)
			release();
		scanf("%d", &(t->data));
		t->next = NULL;
		p->next = t;
		p = p->next;
	}
 
	int m,e;
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &e);
		printf("%d\n", Delete(e));
	}
 
	printres();
	release();
 
	return 0;
}