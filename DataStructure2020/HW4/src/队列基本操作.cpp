#include <iostream>
#include <cstdlib>        //malloc/realloc����
using namespace std;
 
/* P.10 ��Ԥ���峣�������� */
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2    //������<math.h>�еĶ����ͻ
 
typedef int Status;
 
/* P.64 �ṹ�嶨�� */
#define MAXQSIZE    10000    //���д�С����Ϊ100���ɰ����޸ģ���һ��ȷ�����޷����䣩
 
typedef int QElemType;    //�ɸ�����Ҫ�޸�Ԫ�ص�����
 
class SqQueue {
protected:
	QElemType* base;    //��Ŷ�̬����ռ���׵�ַ
	int        front;    //��ͷָ�루ָ���ͷԪ�ص��±꣩
	int        rear;    //��βָ�루ָ���βԪ�ص��±꣩
public:
	/* P.59-60�ĳ����������Ͷ���ת��Ϊʵ�ʵ�C++���� */
	SqQueue();    //���캯�������InitQueue
	~SqQueue();    //�������������DestroyQueue
	Status    ClearQueue();
	Status    QueueEmpty();
	int    QueueLength();
	Status    GetHead(QElemType& e);
	Status    EnQueue(QElemType e);
	Status    DeQueue(QElemType& e);
	Status    QueueTraverse(Status(*visit)(QElemType e));
};
 
 
/* ���캯������ʼ�����У� */
SqQueue::SqQueue()
{
	base = new QElemType[MAXQSIZE];
	if (base == NULL)
		exit(LOVERFLOW);
	front = rear = 0;    //ֻҪfront��rear��ȣ�ָ��0 ~ MAXQSIZE-1������ֵ����
}
 
/* �������������ٶ��У� */
SqQueue::~SqQueue()
{
	if (base)
		delete base;
	front = rear = 0;
}
 
/* ��ն��У��ѳ�ʼ�������ͷſռ䣬ֻ������ݣ� */
Status SqQueue::ClearQueue()
{
	front = rear = 0; //ֻҪfront��rear��ȣ�ָ��0 ~ MAXQSIZE-1������ֵ����
	return OK;
}
 
/* �ж��Ƿ�Ϊ�ն��� */
Status SqQueue::QueueEmpty()
{
	if (front == rear)
		return TRUE;
	else
		return FALSE;
}
 
/* ����еĳ��� */
int SqQueue::QueueLength()
{
	return (rear - front + MAXQSIZE) % MAXQSIZE;
}
 
/* ȡ��ͷԪ�� */
Status SqQueue::GetHead(QElemType& e)
{
	if (front == rear)
		return ERROR;
 
	e = base[front];    //ȡ��ͷ
	return OK;
}
 
/* Ԫ������� */
Status SqQueue::EnQueue(QElemType e)
{
	/* ��������ֱ�ӷ��� */
	if ((rear + 1) % MAXQSIZE == front)
		return ERROR;
 
	base[rear] = e;  //rearָ���β+1�������ǲ���λ��
	rear = (++rear) % MAXQSIZE; //��βָ������ƶ�
	return OK;
}
 
/* Ԫ�س����� */
Status SqQueue::DeQueue(QElemType& e)
{
	/* ���п���ֱ�ӷ��� */
	if (front == rear)
		return ERROR;
 
	e = base[front];
	front = (++front) % MAXQSIZE;    //��ͷָ������ƶ�
	return OK;
}
 
/* �������� */
Status SqQueue::QueueTraverse(Status(*visit)(QElemType e))
{
	int pos = front;
 
	while (pos != rear && (*visit)(base[pos]) == TRUE)
		pos = (++pos) % MAXQSIZE;
 
	if (pos != rear)
		return ERROR;
 
	cout << endl;//����ӡһ�����У�ֻ��Ϊ�˺ÿ������㷨�޹�
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