#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
const char eptmark = '#';
 
 
// 线索二叉树的结点类
struct ThreadNode {
	int ltag, rtag;    //线索标志
	ThreadNode* leftChild, * rightChild; //线索或子女指针
	char data;            //结点数据
	ThreadNode(const char item) {
		data = item;
		leftChild = NULL;
		rightChild = NULL;
		ltag = 0;
		rtag = 0;
	}
};
 
int flagnext = 0;
int flagprior = 0;
int found = 0;
ThreadNode* last = NULL;
ThreadNode* cur = NULL;
ThreadNode* nnext = NULL;
ThreadNode* nlast = NULL;
char ch = 0;
 
// 线索二叉树类
class ThreadTree {
protected:
	ThreadNode* root;
	void createInThread(ThreadNode* current, ThreadNode*& pre);
	ThreadNode* parent(ThreadNode* t);
public:
	ThreadTree() {
		root = NULL;
	}
	~ThreadTree() {
		destroy(root);
	}
	void InitThreadTree();
	void InitThreadTree(ThreadNode** p);
	void createInThread(); //建立中序线索二叉树e
	ThreadNode* /*&*/ getCurrent() {//返回current,最好是副本
		return current;
	}
	ThreadNode* /*&*/ getRoot() {
		return root;
	}
	void destroy(ThreadNode*& subTree);
	//void Print(ThreadNode* /*&*/p, const int depth);//p不可以为引用，否则实参指针root被移动。尽管本例中会移回来
	void InOrderTravese(ThreadNode* /*&*/p);
private:
	ThreadNode* current;
	static ThreadNode*& leftChild(ThreadNode* t) {//返回左子女
		return t->leftChild;
	}
	static ThreadNode*& rightChild(ThreadNode* t) {
		return t->rightChild;                //返回右子女
	}
 
};
//-----------------------------------------------------------------------------------------------------------------
void ThreadTree::destroy(ThreadNode*& subTree) {//清除子二叉树
	if (subTree != NULL) {
		if (subTree->ltag == 0)
			destroy(subTree->leftChild);
		if (subTree->rtag == 0)
			destroy(subTree->rightChild);
		delete subTree;
	}
}
 
 
 
void ThreadTree::InitThreadTree()
{
	char ch;
	cin >> ch;
	if (ch == eptmark)
		root = NULL;
	else
	{
		root = new(nothrow) ThreadNode(ch);
		if (root == NULL)exit(-1);
		InitThreadTree(&(root->leftChild));
		InitThreadTree(&(root->rightChild));
	}
	return;
}
 
void ThreadTree::InitThreadTree(ThreadNode** p)
{
	char ch;
	cin >> ch;
	if (ch == eptmark)
		*p = NULL;
	else
	{
		*p = new(nothrow) ThreadNode(ch);
		if (*p == NULL)exit(-1);
		InitThreadTree(&((*p)->leftChild));
		InitThreadTree(&((*p)->rightChild));
	}
	return;
}
 
 
void ThreadTree::InOrderTravese(ThreadNode* /*&*/p)
{
	if (p) {
 
		if (p->ltag == 0)
			InOrderTravese(ThreadTree::leftChild(p));//递归输出左子树
 
		cur = p;
		cout << p->data;//输出当前结点    
		if (p->data == ch)
		{
			found = 1;
			if (last != NULL)
				flagprior = 1;
			nlast = last;
		}
		if (last && last->data == ch)
		{
			flagnext = 1;
			nnext = cur;
		}
		last = cur;
 
		if (p->rtag == 0)
			InOrderTravese(ThreadTree::rightChild(p));//递归输出左子树
	}
	return;
}
 
void ThreadTree::createInThread()
{
	ThreadNode* pre = NULL;        //前驱结点指针
	if (/*!*/root) {                    //改
		createInThread(root, pre);    //中序遍历线索化二叉树
		pre->rightChild = NULL;        //后处理中序最后一个结点
		pre->rtag = 1;
	}
}
 
//通过先序遍历, 对二叉树进行线索化
void ThreadTree::createInThread(ThreadNode* current, ThreadNode*& pre)
{
	if (!current) {
		return;
	}
	createInThread(current->leftChild, pre); // 左子树线索化
	if (current->leftChild == NULL) {         //建立当前结点的前驱线索
		current->leftChild = pre;
		current->ltag = 1;
	}
	if (pre != NULL && pre->rightChild == NULL) {//建立前驱结点的后继线索
		pre->rightChild = current;
		pre->rtag = 1;
	}
 
	pre = current;//前驱跟上,当前指针向前遍历    
	createInThread(current->rightChild, pre);//递归, 右子树线索化
}
 
int main()
{
	ThreadTree T;
	T.InitThreadTree();
	T.createInThread();
	cin >> ch;
	T.InOrderTravese(T.getRoot()); cout << endl;
	if (found)
	{
		if(flagnext)
			cout << "succ is " << nnext->data << nnext->rtag << endl;
		else
			cout << "succ is NULL" << endl;
 
		if (flagprior)
			cout << "prev is " << nlast->data << nlast->ltag << endl;
		else
			cout << "prev is NULL" << endl;
	}
	else
		cout << "Not found";
	return 0;
}