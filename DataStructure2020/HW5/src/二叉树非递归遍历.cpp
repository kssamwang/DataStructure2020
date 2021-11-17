#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <queue>
#include <cstring>
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
struct BiTNode
{
	char data;
	BiTNode* lchild;
	BiTNode* rchild;
};
 
typedef BiTNode* BiTree;
 
 
stack<BiTree>s;
 
int n;
 
void CreateBiTree(BiTree* T)
{
	BiTree cur = *T;
	int sign = 0;
	for(int i = 0;i < 2 * n;i++)
	{
		char str[5] = { '\0' };
		char ch;
		scanf("%s", str);
		if (!strcmp(str, "push"))
		{
			while (*T != NULL)
			{
				T = &((*T)->lchild);
			}
			cin >> ch;
			*T = new(nothrow) BiTNode;
			if (!(*T))exit(-1);
			(*T)->data = ch;
			(*T)->lchild = NULL;
			(*T)->rchild = NULL;
			s.push(*T);
			T = &((*T)->lchild);
			sign = 0;
		}
		else if (!strcmp(str, "pop"))
		{
			T = &(s.top()->rchild);
			s.pop();
		}
	}
	
}
 
 
 
void PostOrderTraverse(BiTree T)
{
	if (!T)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c", T->data);
}
 
int main()
{
	BiTree T = NULL;
	cin >> n;
	CreateBiTree(&T);
	PostOrderTraverse(T);
	return 0;
}