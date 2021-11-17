#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
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
 
void CreateBiTree(BiTree* T)
{
	char ch;
	scanf("%c", &ch);
	if (ch == '#')
		T = NULL;
	else
	{
		*T = new(nothrow) BiTNode;
		if (!*T)exit(-1);
		(*T)->data = ch;
		(*T)->lchild = NULL;
		(*T)->rchild = NULL;
		CreateBiTree(&((*T)->lchild));
		CreateBiTree(&((*T)->rchild));
	}
}
 
void PreOrderTraverse(BiTree T)
{
	if (!T)return;
	printf("%c", T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}
 
void InOrderTraverse(BiTree T)
{
	if (!T)return;
	InOrderTraverse(T->lchild);
	printf("%c", T->data);
	InOrderTraverse(T->rchild);
}
 
void PostOrderTraverse(BiTree T)
{
	if (!T)return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c", T->data);
}
 
void LevelOrderTraverse(BiTree T)
{
	queue<BiTree>q;
	q.push(T);
	while (!q.empty())
	{
		BiTree bit = q.front();
		char ch = bit->data;
		q.pop();
		printf("%c", ch);
		if (bit->lchild)
			q.push(bit->lchild);
		if (bit->rchild)
			q.push(bit->rchild);
	}
}
 
void DrawGraph(BiTree T,const int depth)
{
	if (!T)return;
	DrawGraph(T->rchild, depth + 1);
	for (int i = 0; i < 5 * depth; i++)
		printf(" ");
	printf("%c\n", T->data);
	DrawGraph(T->lchild, depth + 1);
}
 
int main()
{
	BiTree T = NULL;
	CreateBiTree(&T);
	PreOrderTraverse(T); printf("\n");
	InOrderTraverse(T); printf("\n");
	PostOrderTraverse(T); printf("\n");
	LevelOrderTraverse(T); printf("\n");
	DrawGraph(T, 0);
	return 0;
}