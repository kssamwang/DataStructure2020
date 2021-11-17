#include <iostream>
#include <cstdlib>        //malloc/realloc函数
using namespace std;
 
/* P.10 的预定义常量和类型 */
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2    //避免与<math.h>中的定义冲突
 
typedef int Status;
 
/* P.64 结构体定义 */
#define MAXQSIZE    10000    //队列大小定义为100（可按需修改，但一旦确定则无法扩充）
 
typedef int QElemType;    //可根据需要修改元素的类型
 
class SqQueue {
protected:
	QElemType* base;    //存放动态申请空间的首地址
	int        front;    //队头指针（指向队头元素的下标）
	int        rear;    //队尾指针（指向队尾元素的下标）
public:
	/* P.59-60的抽象数据类型定义转换为实际的C++语言 */
	SqQueue();    //构造函数，替代InitQueue
	~SqQueue();    //析构函数，替代DestroyQueue
	Status    ClearQueue();
	Status    QueueEmpty();
	int    QueueLength();
	Status    GetHead(QElemType& e);
	Status    EnQueue(QElemType e);
	Status    DeQueue(QElemType& e);
	Status    QueueTraverse(Status(*visit)(QElemType e));
};
 
 
/* 构造函数（初始化队列） */
SqQueue::SqQueue()
{
	base = new QElemType[MAXQSIZE];
	if (base == NULL)
		exit(LOVERFLOW);
	front = rear = 0;    //只要front和rear相等，指向0 ~ MAXQSIZE-1的任意值均可
}
 
/* 析构函数（销毁队列） */
SqQueue::~SqQueue()
{
	if (base)
		delete base;
	front = rear = 0;
}
 
/* 清空队列（已初始化，不释放空间，只清除内容） */
Status SqQueue::ClearQueue()
{
	front = rear = 0; //只要front和rear相等，指向0 ~ MAXQSIZE-1的任意值均可
	return OK;
}
 
/* 判断是否为空队列 */
Status SqQueue::QueueEmpty()
{
	if (front == rear)
		return TRUE;
	else
		return FALSE;
}
 
/* 求队列的长度 */
int SqQueue::QueueLength()
{
	return (rear - front + MAXQSIZE) % MAXQSIZE;
}
 
/* 取队头元素 */
Status SqQueue::GetHead(QElemType& e)
{
	if (front == rear)
		return ERROR;
 
	e = base[front];    //取队头
	return OK;
}
 
/* 元素入队列 */
Status SqQueue::EnQueue(QElemType e)
{
	/* 队列满则直接返回 */
	if ((rear + 1) % MAXQSIZE == front)
		return ERROR;
 
	base[rear] = e;  //rear指向队尾+1，正好是插入位置
	rear = (++rear) % MAXQSIZE; //队尾指针向后移动
	return OK;
}
 
/* 元素出队列 */
Status SqQueue::DeQueue(QElemType& e)
{
	/* 队列空则直接返回 */
	if (front == rear)
		return ERROR;
 
	e = base[front];
	front = (++front) % MAXQSIZE;    //队头指针向后移动
	return OK;
}
 
/* 遍历队列 */
Status SqQueue::QueueTraverse(Status(*visit)(QElemType e))
{
	int pos = front;
 
	while (pos != rear && (*visit)(base[pos]) == TRUE)
		pos = (++pos) % MAXQSIZE;
 
	if (pos != rear)
		return ERROR;
 
	cout << endl;//最后打印一个换行，只是为了好看，与算法无关
	return OK;
}
 
Status myvisit(QElemType e)
{
	cout << e << ' ';
	return OK;
}
 
int main()
{
	int n;
	cin >> n;
	string command;
	SqQueue s;
	while (cin >> command)
	{
		if (command == "quit")
		{
			s.QueueTraverse(myvisit);
			break;
		}
		else if (command == "dequeue")
		{
			if (s.QueueEmpty())
				cout << "Queue is Empty" << endl;
			else
			{
				int res;
				s.DeQueue(res);
				cout << res << endl;
			}
		}
		else if (command == "enqueue")
		{
			int c;
			cin >> c;
			if (s.QueueLength() == n)
				cout << "Queue is Full" << endl;
			else
			{
				s.EnQueue(c);
			}
		}
	}
}