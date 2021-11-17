#include <iostream>
#include <cstdlib>        //malloc/realloc����
#include <cstring>
#include <string>
using namespace std;
 
/* P.10 ��Ԥ���峣�������� */
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2    //������<math.h>�еĶ����ͻ
 
typedef int Status;
 
/* P.46 �ṹ�嶨�� */
#define STACK_INIT_SIZE    10000    //��ʼ��С����Ϊ100���ɰ����޸ģ�
#define STACKINCREMENT    10    //���ռ䲻����ÿ������10���ɰ����޸ģ�
 
typedef int SElemType;    //�ɸ�����Ҫ�޸�Ԫ�ص�����
 
class SqStack {
protected:
	SElemType* base;    //��Ŷ�̬����ռ���׵�ַ
	SElemType* top;     //ջ��ָ��
	int stacksize;    //��ǰ�����Ԫ�صĸ���
public:
	/* P.46-47�ĳ����������Ͷ���ת��Ϊʵ�ʵ�C++���� */
	SqStack();    //���캯�������InitStack
	~SqStack();    //�������������DestroyStack
	Status    ClearStack();
	Status    StackEmpty();
	int    StackLength();
	Status    GetTop(SElemType& e);
	Status    Push(SElemType e);
	Status    Pop(SElemType& e);
	Status    StackTraverse(Status(*visit)(SElemType e));
};
 
/* ���캯������ʼ��ջ�� */
SqStack::SqStack()
{
	base = new SElemType[STACK_INIT_SIZE];
	if (base == NULL)
		exit(LOVERFLOW);
	top = base;  //ջ��ָ��ָ��ջ�ף���ʾջ��
	stacksize = STACK_INIT_SIZE;
}
 
/* ����������ɾ��ջ�� */
SqStack::~SqStack()
{
	/* ��δִ�� InitStack��ֱ��ִ�б�����������ܳ�����Ϊָ���ʼֵδ�� */
	if (base)
		delete base;  //Ҫ���ǿ�ջɾ������������Ҫ�ж�
	top = NULL;
	stacksize = 0;
}
 
/* ���ջ���ѳ�ʼ�������ͷſռ䣬ֻ������ݣ� */
Status SqStack::ClearStack()
{
	/* ���ջ������չ�����ָ���ʼ�Ĵ�С */
	if (stacksize > STACK_INIT_SIZE) {
		/* �ͷ�ԭ�ռ䲢���� */
		delete base;
		base = new SElemType[STACK_INIT_SIZE];
		if (base == NULL)
			exit(LOVERFLOW);
		stacksize = STACK_INIT_SIZE;
	}
 
	top = base; //ջ��ָ��ָ��ջ������ʾջ��
	return OK;
}
 
/* �ж��Ƿ�Ϊ��ջ */
Status SqStack::StackEmpty()
{
	if (top == base)
		return TRUE;
	else
		return FALSE;
}
 
/* ��ջ�ĳ��� */
int SqStack::StackLength()
{
	return top - base;//ָ�������ֵΪ����Ԫ�ظ���
}
 
/* ȡջ��Ԫ�� */
Status SqStack::GetTop(SElemType& e)
{
	if (top == base)
		return ERROR;
 
	e = *(top - 1);    //�±��0��ʼ��top��ʵ��ջ��+1
	return OK;
}
 
/* Ԫ����ջ */
Status SqStack::Push(SElemType e)
{
	/* ���ջ������������ռ� */
	if (top - base >= stacksize) {
		SElemType* newbase;
		newbase = new SElemType[stacksize + STACKINCREMENT];
		if (!newbase)
			return LOVERFLOW;
 
		/* ԭ����listsize��ElemType�ռ���и��� */
		memcpy(newbase, base, stacksize * sizeof(SElemType));
 
		delete base;
		base = newbase;
		top = base + stacksize;  //base������ԭ����ͬ��topҲҪ�ƶ�
		stacksize += STACKINCREMENT;
	}
 
	*top++ = e;  //��*top����top++
	return OK;
}
 
/* Ԫ�س�ջ */
Status SqStack::Pop(SElemType& e)
{
	int length;
	if (top == base)
		return ERROR;
	e = *--top;
 
	/* ���ջ��С������С��̬����ռ�Ĵ�С */
	length = top - base;
	if (stacksize > STACK_INIT_SIZE && stacksize - length >= STACKINCREMENT) {
		SElemType* newbase;
		newbase = new SElemType[stacksize - STACKINCREMENT];
		if (newbase == NULL)
			return LOVERFLOW;
 
		/* ԭ����listsize��ElemType�ռ���и��� */
		memcpy(newbase, base, (stacksize - STACKINCREMENT) * sizeof(SElemType));
 
		delete base;
		base = newbase;
		top = base + length; //��S->base�仯��������S->top��ֵ
		stacksize -= STACKINCREMENT;
	}
 
	return OK;
}
 
/* ����ջ */
Status SqStack::StackTraverse(Status(*visit)(SElemType e))
{
	SElemType* t = top-1;
 
	while (t >= base && (*visit)(*t) == TRUE)
		t--;
 
	if (t < top)
		return ERROR;
 
	cout << endl;//����ӡһ�����У�ֻ��Ϊ�˺ÿ������㷨�޹�
	return OK;
}
 
Status myvisit(SElemType e)
{
	cout << e << ' ';
	return OK;
}
 
int main()
{
	int n;
	cin >> n;
	string command;
	SqStack s;
	while (cin >> command)
	{
		if (command == "quit")
		{
			s.StackTraverse(myvisit);
			break;
		}
		else if (command == "pop")
		{
			if (s.StackEmpty())
				cout << "Stack is Empty" << endl;
			else
			{
				int res;
				s.Pop(res);
				cout << res << endl;
			}
		}
		else if (command == "push")
		{
			int c;
			cin >> c;
			if (s.StackLength() == n)
				cout << "Stack is Full" << endl;
			else
			{
				s.Push(c);
			}
		}
	}
	return 0;
}