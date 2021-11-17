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
 
 
// �����������Ľ����
struct ThreadNode {
	int ltag, rtag;    //������־
	ThreadNode* leftChild, * rightChild; //��������Ůָ��
	char data;            //�������
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
 
// ������������
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
	void createInThread(); //������������������e
	ThreadNode* /*&*/ getCurrent() {//����current,����Ǹ���
		return current;
	}
	ThreadNode* /*&*/ getRoot() {
		return root;
	}
	void destroy(ThreadNode*& subTree);
	//void Print(ThreadNode* /*&*/p, const int depth);//p������Ϊ���ã�����ʵ��ָ��root���ƶ������ܱ����л��ƻ���
	void InOrderTravese(ThreadNode* /*&*/p);
private:
	ThreadNode* current;
	static ThreadNode*& leftChild(ThreadNode* t) {//��������Ů
		return t->leftChild;
	}
	static ThreadNode*& rightChild(ThreadNode* t) {
		return t->rightChild;                //��������Ů
	}
 
};
//-----------------------------------------------------------------------------------------------------------------
void ThreadTree::destroy(ThreadNode*& subTree) {//����Ӷ�����
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
			InOrderTravese(ThreadTree::leftChild(p));//�ݹ����������
 
		cur = p;
		cout << p->data;//�����ǰ���    
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
			InOrderTravese(ThreadTree::rightChild(p));//�ݹ����������
	}
	return;
}
 
void ThreadTree::createInThread()
{
	ThreadNode* pre = NULL;        //ǰ�����ָ��
	if (/*!*/root) {                    //��
		createInThread(root, pre);    //�������������������
		pre->rightChild = NULL;        //�����������һ�����
		pre->rtag = 1;
	}
}
 
//ͨ���������, �Զ���������������
void ThreadTree::createInThread(ThreadNode* current, ThreadNode*& pre)
{
	if (!current) {
		return;
	}
	createInThread(current->leftChild, pre); // ������������
	if (current->leftChild == NULL) {         //������ǰ����ǰ������
		current->leftChild = pre;
		current->ltag = 1;
	}
	if (pre != NULL && pre->rightChild == NULL) {//����ǰ�����ĺ������
		pre->rightChild = current;
		pre->rtag = 1;
	}
 
	pre = current;//ǰ������,��ǰָ����ǰ����    
	createInThread(current->rightChild, pre);//�ݹ�, ������������
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