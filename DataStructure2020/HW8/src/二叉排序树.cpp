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
	if (!root)//建立新结点
	{
		root = new node;
		root->value = newvalue;
		root->count = 1;
		root->lchild = root->rchild = NULL;
	}
	else
	{
		if (newvalue < root->value)//在左子树插入
			insert(root->lchild, newvalue);
		else if (newvalue > root->value)//在右子树插入
			insert(root->rchild, newvalue);
		else//该值已有节点
		{
			root->count++;
		}
	}
}
 
node* GetPri(BST root, int v)//以root为根的树中寻找比v小的最大值
{
	if (!root)return NULL;
 
	if (root->value >= v)//在左子树寻找
		GetPri(root->lchild, v);
	else
	{
		node* temp = GetPri(root->rchild, v);//在右子树寻找
		if (temp)
			return temp;
		else//右子树没找到，当前节点就是答案
			return root;
	}
}
 
bool erase(BST& root, int v)//在以root为根的二叉排序树中删除值为v的节点
{
	if (!root)
		return false;
 
	if (root->value > v)//左子树中删除
		return erase(root->lchild, v);
	else if (root->value < v)//右子树中删除
		return erase(root->rchild, v);
	else
	{
		if (root->count > 1)//数量大于1，不是真删除节点，数量-1
		{
			root->count--;
		}
		else//要删除节点
		{
			node* t = root;
			if (!root->rchild)//右子树空，接左子树即可
			{
				root = root->lchild;
				delete t;
			}
			else if (!root->lchild)//左子树空，接右子树即可
			{
				root = root->rchild;
				delete t;
			}
			else//都不空
			{
				node* s = root->lchild;
				while (s->rchild)
				{
					t = s;
					s = s->rchild;
				}//s：在左子树中找被删节点的直接前驱，s是一个没有右子树的节点
				root->count = s->count;
				root->value = s->value;
				//s的数据复制到被删除节点的位置
				if (t != root)//t是原本s的双亲
					t->rchild = s->lchild;
				else//s就是当初被删节点的左子树，直接接上
					t->lchild = s->lchild;
 
				delete s;//s数据已经移动到被删除位置代替，原s被删
			}
		}
		return true;
	}
}
 
node* Getmin(BST root)//在以root为根的二叉排序树中取最小值
{
	node* p = root;
	while (p->lchild)
		p = p->lchild;
	return p;
}
 
int GetCount(BST root, int v)//在以root为根的二叉排序树中取v的出现次数
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