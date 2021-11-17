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
	void createInThread(); //������������������
	bool FindTh(const char& value);    //����������������value,�ɹ���true,����currentΪ�˽��;����false
	ThreadNode* First(ThreadNode* current);    //Ѱ�������µ�һ�����
	ThreadNode* Last(ThreadNode* current);    //Ѱ�����������һ�����
	ThreadNode* Next(ThreadNode* current);    //Ѱ�ҽ���������µĺ�̽��
	ThreadNode* Prior(ThreadNode* current);    //Ѱ�ҽ���������µ�ǰ�����
	void InOrder(void (*visit)(ThreadNode* t));    //���������������������
	//void PreOrder(void (*visit)(ThreadNode* t));    //��������������ǰ�����
	//void PostOrder(void (*visit)(ThreadNode* t));    //�������������ĺ������    
	bool Find(const char& value);    //�ڳ������������value,�ɹ���true,����currentΪ�˽��;����false
	ThreadNode* /*&*/ getCurrent() {//����current,����Ǹ���
		return current;
	}
	ThreadNode* /*&*/ getRoot() {
		return root;
	}
	void destroy(ThreadNode*& subTree);
	void Print(ThreadNode* /*&*/p, const int depth);//p������Ϊ���ã�����ʵ��ָ��root���ƶ������ܱ����л��ƻ���
	void PreOrderTravese(ThreadNode* /*&*/p);
private:
	ThreadNode* current;
	bool Find(ThreadNode* p, const char& value);            //����pΪ���ĳ��������������value
	bool setRoot(const char& rt) {                             //���ø�ֵΪrt
		root = new ThreadNode(rt);
		if (root) return true;
		else return false;
	}
	static ThreadNode*& leftChild(ThreadNode* t) {//��������Ů
		return t->leftChild;
	}
	static ThreadNode*& rightChild(ThreadNode* t) {
		return t->rightChild;                //��������Ů
	}
	bool MakeLink(const char ex, const char ap, char linkmark);
	
};
//-----------------------------------------------------------------------------------------------------------------
void ThreadTree::destroy(ThreadNode*& subTree) {//����Ӷ�����
	if (subTree != NULL) {
		if(subTree->ltag == 0)
			destroy(subTree->leftChild);
		if (subTree->rtag == 0)
			destroy(subTree->rightChild);
		delete subTree;
	}
}
 
bool ThreadTree::Find(ThreadNode* p, const char& value) {//����pΪ������������value
	if (!p) {
		return false;
	}
	if (p->data == value) {
		current = p;                 //�ҵ���currentָ��ý��
		return true;
	}
	else {
		return Find(p->leftChild, value) || Find(p->rightChild, value);//����ҵ��󲻻���ȥ�ұ�
	}
}
 
bool ThreadTree::Find(const char& value) {//�������������������ʹ��
	if (!root) {
		return 0;
	}
	else {
		return Find(root, value);
	}
}
 
bool ThreadTree::MakeLink(const char ex, const char ap, char linkmark) {//������ap����Ϊ������Ϊex������Ů
	if (linkmark != '#') {//������־        
		ThreadNode* p = new ThreadNode(ap);//��apת��Ϊ���
		if (Find(ex))                             //��ex,��Ϊcurrent
			cout << "cu " << current->data << endl;
		if (current) {
			switch (linkmark) {
				case 'l': current->leftChild = p;
					cout << "input success!" << endl; break;//��������Ů��ϵ
				case 'r': current->rightChild = p;
					cout << "input success!" << endl; break;//��������Ů��ϵ
				default: cout << "error! please reinput again!" << endl;
			}
			return false;//���ؼ٣�����
		}
		else {
			cout << "error! please reinput again!" << endl;
			return false;
		}
	}
	else return true;//�����棬����
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
{//ǰ�������ӡ
	if (p) {
		if (p->rtag == 0)
			Print(ThreadTree::rightChild(p), depth + 1);//�ݹ����������
 
		for (int j = 0; j < 5 * depth; ++j)
			cout << ' ';    //iΪ�Ʊ������
		cout << p->data << p->ltag << p->rtag << endl;//�����ǰ���     
 
		if (p->ltag == 0)
			Print(ThreadTree::leftChild(p), depth + 1);//�ݹ����������
		   
	}
	return;
}
 
void ThreadTree::PreOrderTravese(ThreadNode* /*&*/p)
{
	if (p) {
		cout << p->data;//�����ǰ���    
		if (p->ltag == 0)
			PreOrderTravese(ThreadTree::leftChild(p));//�ݹ����������
		if (p->rtag == 0)
			PreOrderTravese(ThreadTree::rightChild(p));//�ݹ����������
		
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
 
ThreadNode* ThreadTree::First(ThreadNode* current)
{// ������currentΪ������������ĵ�һ�����
	ThreadNode* p = current;
	while (p->ltag == 0) {
		p = p->leftChild;//�����½�㣨��һ����Ҷ��㣩
	}
	return p;
}
 
ThreadNode* ThreadTree ::Next(ThreadNode* current)
{// ���ؽ��current��������ĺ�̽��
	ThreadNode* p = current->rightChild;
	if (current->rtag == 0) {    //rtag == 0, ��ʾ������Ů    
		return First(p);
	}
	else {    //rtag == 1, ֱ�ӷ��غ������    
		return p;
	}
}
 
ThreadNode* ThreadTree::Last(ThreadNode* current)
{// ������currentΪ����������������һ�����
	ThreadNode* p = current;
	//�����½�㣨��һ����Ҷ��㣩
	while (p->rtag == 0) {
		p = p->rightChild;//�����½�㣨��һ����Ҷ��㣩
	}
	return p;
}
 
ThreadNode* ThreadTree::Prior(ThreadNode* current)
{// �������������ǰ�����
	//�������������������������н��current�������µ�ǰ����㡣
	ThreadNode* p = current->leftChild;
	if (current->ltag == 0) {    //�������������������һ�����    
		return Last(p);
	}
	else { //ltag==1, ֱ�ӷ���ǰ������    
		return p;
	}
}
 
bool ThreadTree::FindTh(const char& value) {//������������ʹ��
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
{//�������
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
	for (p = t; p->ltag == 0; p = p->leftChild);//��*tΪ��������һ����㣬��ǰ����*t������
	if (p->leftChild != NULL) {//��ָ����ǰ�������ý����ȫ��(tΪroot)�����һ������ǰ��
		p = p->leftChild;//�ҵ�����
		if (p->rightChild != t/*&&p->leftChild != t*/)//������Ǹ����
			for (p = p->rightChild; //����һ��
				/*rightChild != t&&*/p->leftChild != t;//��t�Ƿ�p����Ů������һ�����ҵ�
				p = p->leftChild);//�����ߵ���
	}
	else {//�ý����ȫ��(tΪroot)�����һ��㣬��ǰ�������뻻һ������ȥ�ұ��Һ��
		for (p = t; p->rtag == 0; p = p->rightChild);//��*tΪ���������һ�����
		p = p->rightChild;//�ҵ�����
		if (p->leftChild != t/*&&p->rightChild != t*/)
			for (p = p->leftChild;//����һ��
				/*p->leftChild != t&&*/p->rightChild != t;
				p = p->rightChild);//�����ߵ���,�����ҵ�
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