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
	char data;//��ĸ
	int lchild;//�����������±�
	int rchild;//�����������±�
	int depth;//�ýڵ����
};
 
struct BT
{
	BiTNode Tree[N];
	int n;           //�ڵ���
	int height;      //����
	int root;        //�����ڵ�
	BT()//���캯��
	{
		for (int i = 0; i < N; i++)
		{
			Tree[i].depth = 0;
			Tree[i].data = '\0';
			Tree[i].lchild = -1;//��Ҫ��0�ǺϷ��ڵ���
			Tree[i].rchild = -1;//��Ҫ��0�ǺϷ��ڵ���
		}
		height = 0;
		n = 0;
		root = -1;
	};
	
	void input()//����
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
	void renewdepth(const int i, const int newdepth)//�ݹ���½ڵ����
	{
		Tree[i].depth = newdepth;
		if (newdepth == 1)
			root = i;//���һ�����1��ʼ�ݹ�ģ���Ϊ����
		height = (height > newdepth ? height : newdepth);//��������
		int l = Tree[i].lchild;
		if (l >= 0 && l < n)
			renewdepth(l, newdepth + 1);//�ݹ�������������нڵ����
		int r = Tree[i].rchild;
		if (r >= 0 && r < n)
			renewdepth(r, newdepth + 1);//�ݹ�������������нڵ����
	};
};
 
BT t1, t2;
 
 
/* ��t1����root1Ϊ�������� �� ��t2����root2Ϊ�������� �Ƿ�ͬ��*/
int yesorno(BT t1,BT t2,const int root1, const int root2)
{
	if (root1 == -1 && root2 == -1)//�����������ǿ���(������)��ͬ��
		return 1;
	if (root1 == -1 && root2 != -1)//��������һ����һ���ǿգ���ͬ��
		return 0;
	if (root1 != -1 && root2 == -1)//��������һ����һ���ǿգ���ͬ��
		return 0;
	if (t1.Tree[root1].data != t2.Tree[root2].data)//�������ȣ���ͬ��
		return 0;
	else//���˴��������������ǿգ��������
	{
		int root1_l = t1.Tree[root1].lchild;
		int root1_r = t1.Tree[root1].rchild;
		int root2_l = t2.Tree[root2].lchild;
		int root2_r = t2.Tree[root2].rchild;
		//1��������2������ͬ�� �� 1��������2������ͬ����1��2������ͬ��
		if (yesorno(t1, t2, root1_l, root2_l) && yesorno(t1, t2, root1_r, root2_r))
			return 1;
		//1��������2������ͬ�� �� 1��������2��������ͬ����1��2������ͬ��
		if (yesorno(t1, t2, root1_l, root2_r) && yesorno(t1, t2, root1_r, root2_l))
			return 1;
		return 0;
	}
}
 
int main()
{
	t1.input();//���������1
	t2.input();//���������2
	for (int i = 0; i < t1.n; i++)//���¶�����1�ĸ߶�
	{
		if (t1.Tree[i].depth == 0)
			t1.renewdepth(i, 1);
	}
	for (int i = 0; i < t2.n; i++)//���¶�����2�ĸ߶�
	{
		if (t2.Tree[i].depth == 0)
			t2.renewdepth(i, 1);
	}
	cout << (yesorno(t1,t2,t1.root,t2.root) ? "Yes" : "No") << endl;
	cout << t1.height << endl;
	cout << t2.height << endl;
	return 0;
}