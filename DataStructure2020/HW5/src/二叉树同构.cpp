#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
const int N = 10;
 
struct BiTNode
{
	char data;//字母
	int lchild;//左子树数组下标
	int rchild;//右子树数组下标
	int depth;//该节点深度
};
 
struct BT
{
	BiTNode Tree[N];
	int n;           //节点数
	int height;      //树高
	int root;        //数根节点
	BT()//构造函数
	{
		for (int i = 0; i < N; i++)
		{
			Tree[i].depth = 0;
			Tree[i].data = '\0';
			Tree[i].lchild = -1;//重要！0是合法节点编号
			Tree[i].rchild = -1;//重要！0是合法节点编号
		}
		height = 0;
		n = 0;
		root = -1;
	};
	
	void input()//输入
	{
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			char l, r;
			cin >> Tree[i].data >> l >> r;
			if (l != '-')Tree[i].lchild = l - '0';
			if (r != '-')Tree[i].rchild = r - '0';
		}
 
	};
	void renewdepth(const int i, const int newdepth)//递归更新节点深度
	{
		Tree[i].depth = newdepth;
		if (newdepth == 1)
			root = i;//最后一个深度1开始递归的，必为树根
		height = (height > newdepth ? height : newdepth);//更新树高
		int l = Tree[i].lchild;
		if (l >= 0 && l < n)
			renewdepth(l, newdepth + 1);//递归更新左子树所有节点深度
		int r = Tree[i].rchild;
		if (r >= 0 && r < n)
			renewdepth(r, newdepth + 1);//递归更新右子树所有节点深度
	};
};
 
BT t1, t2;
 
 
/* 树t1中以root1为根的子树 与 树t2中以root2为根的子树 是否同构*/
int yesorno(BT t1,BT t2,const int root1, const int root2)
{
	if (root1 == -1 && root2 == -1)//两棵子树都是空树(树根空)，同构
		return 1;
	if (root1 == -1 && root2 != -1)//两棵子树一个空一个非空，不同构
		return 0;
	if (root1 != -1 && root2 == -1)//两棵子树一个空一个非空，不同构
		return 0;
	if (t1.Tree[root1].data != t2.Tree[root2].data)//树根不等，不同构
		return 0;
	else//到此处，两子树根都非空，树根相等
	{
		int root1_l = t1.Tree[root1].lchild;
		int root1_r = t1.Tree[root1].rchild;
		int root2_l = t2.Tree[root2].lchild;
		int root2_r = t2.Tree[root2].rchild;
		//1左子树与2左子树同构 且 1右子树与2右子树同构，1和2整棵树同构
		if (yesorno(t1, t2, root1_l, root2_l) && yesorno(t1, t2, root1_r, root2_r))
			return 1;
		//1左子树与2右子树同构 且 1右子树与2左字子树同构，1和2整棵树同构
		if (yesorno(t1, t2, root1_l, root2_r) && yesorno(t1, t2, root1_r, root2_l))
			return 1;
		return 0;
	}
}
 
int main()
{
	t1.input();//输入二叉树1
	t2.input();//输入二叉树2
	for (int i = 0; i < t1.n; i++)//更新二叉树1的高度
	{
		if (t1.Tree[i].depth == 0)
			t1.renewdepth(i, 1);
	}
	for (int i = 0; i < t2.n; i++)//更新二叉树2的高度
	{
		if (t2.Tree[i].depth == 0)
			t2.renewdepth(i, 1);
	}
	cout << (yesorno(t1,t2,t1.root,t2.root) ? "Yes" : "No") << endl;
	cout << t1.height << endl;
	cout << t2.height << endl;
	return 0;
}