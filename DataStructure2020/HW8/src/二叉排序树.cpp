#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
struct node
{
	int value;
	int count;
	node* lchild;
	node* rchild;
};
 
typedef struct node* BST;
 
void insert(BST& root, int newvalue)
{
	if (!root)//�����½��
	{
		root = new node;
		root->value = newvalue;
		root->count = 1;
		root->lchild = root->rchild = NULL;
	}
	else
	{
		if (newvalue < root->value)//������������
			insert(root->lchild, newvalue);
		else if (newvalue > root->value)//������������
			insert(root->rchild, newvalue);
		else//��ֵ���нڵ�
		{
			root->count++;
		}
	}
}
 
node* GetPri(BST root, int v)//��rootΪ��������Ѱ�ұ�vС�����ֵ
{
	if (!root)return NULL;
 
	if (root->value >= v)//��������Ѱ��
		GetPri(root->lchild, v);
	else
	{
		node* temp = GetPri(root->rchild, v);//��������Ѱ��
		if (temp)
			return temp;
		else//������û�ҵ�����ǰ�ڵ���Ǵ�
			return root;
	}
}
 
bool erase(BST& root, int v)//����rootΪ���Ķ�����������ɾ��ֵΪv�Ľڵ�
{
	if (!root)
		return false;
 
	if (root->value > v)//��������ɾ��
		return erase(root->lchild, v);
	else if (root->value < v)//��������ɾ��
		return erase(root->rchild, v);
	else
	{
		if (root->count > 1)//��������1��������ɾ���ڵ㣬����-1
		{
			root->count--;
		}
		else//Ҫɾ���ڵ�
		{
			node* t = root;
			if (!root->rchild)//�������գ�������������
			{
				root = root->lchild;
				delete t;
			}
			else if (!root->lchild)//�������գ�������������
			{
				root = root->rchild;
				delete t;
			}
			else//������
			{
				node* s = root->lchild;
				while (s->rchild)
				{
					t = s;
					s = s->rchild;
				}//s�������������ұ�ɾ�ڵ��ֱ��ǰ����s��һ��û���������Ľڵ�
				root->count = s->count;
				root->value = s->value;
				//s�����ݸ��Ƶ���ɾ���ڵ��λ��
				if (t != root)//t��ԭ��s��˫��
					t->rchild = s->lchild;
				else//s���ǵ�����ɾ�ڵ����������ֱ�ӽ���
					t->lchild = s->lchild;
 
				delete s;//s�����Ѿ��ƶ�����ɾ��λ�ô��棬ԭs��ɾ
			}
		}
		return true;
	}
}
 
node* Getmin(BST root)//����rootΪ���Ķ�����������ȡ��Сֵ
{
	node* p = root;
	while (p->lchild)
		p = p->lchild;
	return p;
}
 
int GetCount(BST root, int v)//����rootΪ���Ķ�����������ȡv�ĳ��ִ���
{
	if (!root)
		return 0;
 
	if (root->value == v)
		return root->count;
	else if (v < root->value)
		return GetCount(root->lchild, v);
	else
		return GetCount(root->rchild, v);
}
 
int main()
{
	BST bst = NULL;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int op;
		scanf("%d", &op);
		int x;
		if (op != 4)
			scanf("%d", &x);
		if (op == 1)
		{
			insert(bst, x);
		}
		else if (op == 2)
		{
			if (!erase(bst, x))
				printf("None\n");
		}
		else if (op == 3)
			printf("%d\n", GetCount(bst, x));
		else if (op == 4 && bst)
			printf("%d\n", Getmin(bst)->value);
		else if (op == 5)
		{
			node* t = GetPri(bst, x);
			if (t)
				printf("%d\n", t->value);
			else
				printf("None\n");
		}
	}
	return 0;
}