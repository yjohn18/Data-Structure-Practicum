#include <iostream>
#include <iomanip>

using namespace std;

/*********************循环队列定义***********************/
typedef int Status;

#define	TRUE		1
#define	FALSE		0
#define	OK			1
#define	ERROR		0
#define	INFEASIBLE	-1
#define	LOVERFLOW	-2

#define	MAXQSIZE	10000
template<class QElemType>
class SqQueue {
protected:
    QElemType	*base;
    int	front;
    int	rear;
    int	maxsize;
public:
    SqQueue(int n);
    SqQueue();
    virtual	~SqQueue();
    Status	EnQueue(QElemType e);
    Status	DeQueue(QElemType &e);
    void	PrintQueue();
    Status	QueueEmpty();
};

template<class QElemType>
SqQueue<QElemType>::SqQueue(int n)
{
    base = new(nothrow)QElemType[n + 1];
    if (!base)
        exit(LOVERFLOW);
    front = rear = 0;
    maxsize = n + 1;
}

template<class QElemType>
SqQueue<QElemType>::SqQueue()
{
    base = new(nothrow)QElemType[MAXQSIZE];
    if (!base)
        exit(LOVERFLOW);
    front = rear = 0;
    maxsize = MAXQSIZE;
}

template<class QElemType>
SqQueue<QElemType>::~SqQueue()
{
    delete[]base;
}

template<class QElemType>
Status SqQueue<QElemType>::EnQueue(QElemType e)
{
    if ((rear + 1) % maxsize == front)
        return ERROR;
    base[rear] = e;
    rear = (rear + 1) % maxsize;
    return OK;
}

template<class QElemType>
Status SqQueue<QElemType>::DeQueue(QElemType &e)
{
    if (front == rear)
        return ERROR;
    e = base[front];
    front = (front + 1) % maxsize;
    return OK;
}

template<class QElemType>
void SqQueue<QElemType>::PrintQueue()
{
    for (int i = front; i != rear; i = (i + 1) % maxsize)
        cout << base[i] << ' ';
    cout << endl;
}

template<class QElemType>
Status SqQueue<QElemType>::QueueEmpty()
{
    if (front == rear)
        return TRUE;
    else
        return FALSE;
}
/**********************循环队列定义结束************************/
