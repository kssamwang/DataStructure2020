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
	void createInThread(); //建立中序线索二叉树
	bool FindTh(const char& value);    //在线索二叉树中找value,成功返true,并置current为此结点;否则返false
	ThreadNode* First(ThreadNode* current);    //寻找中序下第一个结点
	ThreadNode* Last(ThreadNode* current);    //寻找中序下最后一个结点
	ThreadNode* Next(ThreadNode* current);    //寻找结点在中序下的后继结点
	ThreadNode* Prior(ThreadNode* current);    //寻找结点在中序下的前驱结点
	void InOrder(void (*visit)(ThreadNode* t));    //线索化二叉树的中序遍历
	//void PreOrder(void (*visit)(ThreadNode* t));    //线索化二叉树的前序遍历
	//void PostOrder(void (*visit)(ThreadNode* t));    //线索化二叉树的后序遍历    
	bool Find(const char& value);    //在常规二叉树中找value,成功返true,并置current为此结点;否则返false
	ThreadNode* /*&*/ getCurrent() {//返回current,最好是副本
		return current;
	}
	ThreadNode* /*&*/ getRoot() {
		return root;
	}
	void destroy(ThreadNode*& subTree);
	void Print(ThreadNode* /*&*/p, const int depth);//p不可以为引用，否则实参指针root被移动。尽管本例中会移回来
	void PreOrderTravese(ThreadNode* /*&*/p);
private:
	ThreadNode* current;
	bool Find(ThreadNode* p, const char& value);            //在以p为根的常规二叉树中搜索value
	bool setRoot(const char& rt) {                             //设置根值为rt
		root = new ThreadNode(rt);
		if (root) return true;
		else return false;
	}
	static ThreadNode*& leftChild(ThreadNode* t) {//返回左子女
		return t->leftChild;
	}
	static ThreadNode*& rightChild(ThreadNode* t) {
		return t->rightChild;                //返回右子女
	}
	bool MakeLink(const char ex, const char ap, char linkmark);
	
};
//-----------------------------------------------------------------------------------------------------------------
void ThreadTree::destroy(ThreadNode*& subTree) {//清除子二叉树
	if (subTree != NULL) {
		if(subTree->ltag == 0)
			destroy(subTree->leftChild);
		if (subTree->rtag == 0)
			destroy(subTree->rightChild);
		delete subTree;
	}
}
 
bool ThreadTree::Find(ThreadNode* p, const char& value) {//在以p为根的树中搜索value
	if (!p) {
		return false;
	}
	if (p->data == value) {
		current = p;                 //找到，current指向该结点
		return true;
	}
	else {
		return Find(p->leftChild, value) || Find(p->rightChild, value);//左边找到后不会再去右边
	}
}
 
bool ThreadTree::Find(const char& value) {//建立常规二叉树过程中使用
	if (!root) {
		return 0;
	}
	else {
		return Find(root, value);
	}
}
 
bool ThreadTree::MakeLink(const char ex, const char ap, char linkmark) {//将数据ap连接为数据域为ex结点的子女
	if (linkmark != '#') {//结束标志        
		ThreadNode* p = new ThreadNode(ap);//将ap转化为结点
		if (Find(ex))                             //找ex,置为current
			cout << "cu " << current->data << endl;
		if (current) {
			switch (linkmark) {
				case 'l': current->leftChild = p;
					cout << "input success!" << endl; break;//建立左子女关系
				case 'r': current->rightChild = p;
					cout << "input success!" << endl; break;//建立右子女关系
				default: cout << "error! please reinput again!" << endl;
			}
			return false;//返回假，继续
		}
		else {
			cout << "error! please reinput again!" << endl;
			return false;
		}
	}
	else return true;//返回真，结束
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
 
void ThreadTree::Print(ThreadNode* /*&*/p,const int depth)
{//前序遍历打印
	if (p) {
		if (p->rtag == 0)
			Print(ThreadTree::rightChild(p), depth + 1);//递归输出右子树
 
		for (int j = 0; j < 5 * depth; ++j)
			cout << ' ';    //i为制表符计数
		cout << p->data << p->ltag << p->rtag << endl;//输出当前结点     
 
		if (p->ltag == 0)
			Print(ThreadTree::leftChild(p), depth + 1);//递归输出左子树
		   
	}
	return;
}
 
void ThreadTree::PreOrderTravese(ThreadNode* /*&*/p)
{
	if (p) {
		cout << p->data;//输出当前结点    
		if (p->ltag == 0)
			PreOrderTravese(ThreadTree::leftChild(p));//递归输出左子树
		if (p->rtag == 0)
			PreOrderTravese(ThreadTree::rightChild(p));//递归输出右子树
		
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
 
ThreadNode* ThreadTree::First(ThreadNode* current)
{// 返回以current为根，中序遍历的第一个结点
	ThreadNode* p = current;
	while (p->ltag == 0) {
		p = p->leftChild;//最左下结点（不一定是叶结点）
	}
	return p;
}
 
ThreadNode* ThreadTree ::Next(ThreadNode* current)
{// 返回结点current中序遍历的后继结点
	ThreadNode* p = current->rightChild;
	if (current->rtag == 0) {    //rtag == 0, 表示有右子女    
		return First(p);
	}
	else {    //rtag == 1, 直接返回后继线索    
		return p;
	}
}
 
ThreadNode* ThreadTree::Last(ThreadNode* current)
{// 返回以current为根，中序遍历的最后一个结点
	ThreadNode* p = current;
	//最右下结点（不一定是叶结点）
	while (p->rtag == 0) {
		p = p->rightChild;//最右下结点（不一定是叶结点）
	}
	return p;
}
 
ThreadNode* ThreadTree::Prior(ThreadNode* current)
{// 返回中序遍历的前驱结点
	//函数返回在中序线索二叉树中结点current在中序下的前驱结点。
	ThreadNode* p = current->leftChild;
	if (current->ltag == 0) {    //在左子树中找中序最后一个结点    
		return Last(p);
	}
	else { //ltag==1, 直接返回前驱线索    
		return p;
	}
}
 
bool ThreadTree::FindTh(const char& value) {//线索二叉树中使用
	ThreadNode* p;
	for (p = First(root); p != NULL; p = Next(p)) {
		if (p->data == value) {
			current = p;
			return true;
		}
	}
	return false;
}
 
void ThreadTree ::InOrder(void (*visit)(ThreadNode* t))
{//中序遍历
	ThreadNode* p;
	for (p = First(root); p != NULL; p = Next(p)) {
		visit(p);
	}
}
 
ThreadNode* ThreadTree::parent(ThreadNode* t)
{
	ThreadNode* p;
	if (t == root) {
		return NULL;
	}
	for (p = t; p->ltag == 0; p = p->leftChild);//求*t为根子树第一个结点，其前驱是*t的祖先
	if (p->leftChild != NULL) {//左指针是前驱，仅该结点是全树(t为root)中序第一结点才无前驱
		p = p->leftChild;//找到祖先
		if (p->rightChild != t/*&&p->leftChild != t*/)//如果不是父结点
			for (p = p->rightChild; //向右一步
				/*rightChild != t&&*/p->leftChild != t;//测t是否p的子女，并且一定会找到
				p = p->leftChild);//向左走到底
	}
	else {//该结点是全树(t为root)中序第一结点，无前驱，必须换一个方向，去右边找后继
		for (p = t; p->rtag == 0; p = p->rightChild);//求*t为根子树最后一个结点
		p = p->rightChild;//找到祖先
		if (p->leftChild != t/*&&p->rightChild != t*/)
			for (p = p->leftChild;//向左一步
				/*p->leftChild != t&&*/p->rightChild != t;
				p = p->rightChild);//向右走到底,总能找到
	}
	return p;
}
 
int main()
{
	ThreadTree T;
	T.InitThreadTree();
	T.createInThread();
	T.Print(T.getRoot(),0);
	T.PreOrderTravese(T.getRoot());
	return 0;
}