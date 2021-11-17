#include <iostream>
#include <cstdlib>        //malloc/realloc函数
#include <cstring>
#include <string>
using namespace std;
 
/* P.10 的预定义常量和类型 */
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2    //避免与<math.h>中的定义冲突
 
typedef int Status;
 
/* P.46 结构体定义 */
#define STACK_INIT_SIZE    10000    //初始大小定义为100（可按需修改）
#define STACKINCREMENT    10    //若空间不够，每次增长10（可按需修改）
 
typedef int SElemType;    //可根据需要修改元素的类型
 
class SqStack {
protected:
	SElemType* base;    //存放动态申请空间的首地址
	SElemType* top;     //栈顶指针
	int stacksize;    //当前分配的元素的个数
public:
	/* P.46-47的抽象数据类型定义转换为实际的C++语言 */
	SqStack();    //构造函数，替代InitStack
	~SqStack();    //析构函数，替代DestroyStack
	Status    ClearStack();
	Status    StackEmpty();
	int    StackLength();
	Status    GetTop(SElemType& e);
	Status    Push(SElemType e);
	Status    Pop(SElemType& e);
	Status    StackTraverse(Status(*visit)(SElemType e));
};
 
/* 构造函数（初始化栈） */
SqStack::SqStack()
{
	base = new SElemType[STACK_INIT_SIZE];
	if (base == NULL)
		exit(LOVERFLOW);
	top = base;  //栈顶指针指向栈底，表示栈空
	stacksize = STACK_INIT_SIZE;
}
 
/* 析构函数（删除栈） */
SqStack::~SqStack()
{
	/* 若未执行 InitStack，直接执行本函数，则可能出错，因为指针初始值未定 */
	if (base)
		delete base;  //要考虑空栈删除的情况，因此要判断
	top = NULL;
	stacksize = 0;
}
 
/* 清空栈（已初始化，不释放空间，只清除内容） */
Status SqStack::ClearStack()
{
	/* 如果栈曾经扩展过，恢复初始的大小 */
	if (stacksize > STACK_INIT_SIZE) {
		/* 释放原空间并申请 */
		delete base;
		base = new SElemType[STACK_INIT_SIZE];
		if (base == NULL)
			exit(LOVERFLOW);
		stacksize = STACK_INIT_SIZE;
	}
 
	top = base; //栈顶指针指向栈顶，表示栈空
	return OK;
}
 
/* 判断是否为空栈 */
Status SqStack::StackEmpty()
{
	if (top == base)
		return TRUE;
	else
		return FALSE;
}
 
/* 求栈的长度 */
int SqStack::StackLength()
{
	return top - base;//指针相减，值为相差的元素个数
}
 
/* 取栈顶元素 */
Status SqStack::GetTop(SElemType& e)
{
	if (top == base)
		return ERROR;
 
	e = *(top - 1);    //下标从0开始，top是实际栈顶+1
	return OK;
}
 
/* 元素入栈 */
Status SqStack::Push(SElemType e)
{
	/* 如果栈已满，则扩充空间 */
	if (top - base >= stacksize) {
		SElemType* newbase;
		newbase = new SElemType[stacksize + STACKINCREMENT];
		if (!newbase)
			return LOVERFLOW;
 
		/* 原来的listsize个ElemType空间进行复制 */
		memcpy(newbase, base, stacksize * sizeof(SElemType));
 
		delete base;
		base = newbase;
		top = base + stacksize;  //base可能与原来不同，top也要移动
		stacksize += STACKINCREMENT;
	}
 
	*top++ = e;  //先*top，再top++
	return OK;
}
 
/* 元素出栈 */
Status SqStack::Pop(SElemType& e)
{
	int length;
	if (top == base)
		return ERROR;
	e = *--top;
 
	/* 如果栈缩小，则缩小动态申请空间的大小 */
	length = top - base;
	if (stacksize > STACK_INIT_SIZE && stacksize - length >= STACKINCREMENT) {
		SElemType* newbase;
		newbase = new SElemType[stacksize - STACKINCREMENT];
		if (newbase == NULL)
			return LOVERFLOW;
 
		/* 原来的listsize个ElemType空间进行复制 */
		memcpy(newbase, base, (stacksize - STACKINCREMENT) * sizeof(SElemType));
 
		delete base;
		base = newbase;
		top = base + length; //若S->base变化，则修正S->top的值
		stacksize -= STACKINCREMENT;
	}
 
	return OK;
}
 
/* 遍历栈 */
Status SqStack::StackTraverse(Status(*visit)(SElemType e))
{
	SElemType* t = top-1;
 
	while (t >= base && (*visit)(*t) == TRUE)
		t--;
 
	if (t < top)
		return ERROR;
 
	cout << endl;//最后打印一个换行，只是为了好看，与算法无关
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