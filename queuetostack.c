//������ʵ��ջ����һ������1��Ϊջ��push����Ҫpop��ʱ��
//������1��Ԫ��push������2�У��������һ��Ԫ�أ���pop����
//ע�⣬��pop��ʱ��Ҫ������2��Ԫ��push������1��پ�������Ĳ���
//ȡtop���ж�Ԫ���Ƚ�����2���Ԫ��push������1�У���rear���Ԫ�ؾͺ��ˡ�


typedef struct Queue{
	int *a;
	int front;
	int rear;
	int capacity;
}Myqueue;

Myqueue *QueueCreate(int cap){//���г�ʼ��
	Myqueue *queue = (Myqueue *)malloc(sizeof(Myqueue));
	queue->a = (int *)malloc(sizeof(int)*cap);
	queue->front = 0;
	queue->rear = 0;
	queue->capacity = cap;
	return queue;
}

void QueuePush(Myqueue *queue, int x){//����pushѭ��
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->a[(queue->rear)] = x;
}
int QueueTop(Myqueue *queue){//ȡ���е�һ��Ԫ��
	int x = (queue->front + 1) % queue->capacity;
	return queue->a[x];
}

int QueuePop(Myqueue *queue){//����pop
	queue->front = (queue->front + 1) % queue->capacity;
	return queue->a[queue->front];
}
int IsEmpty(Myqueue *queue){//�п�
	return queue->front == queue->rear;
}

void IntoOut(Myqueue *s1, Myqueue *s2){//������1��Ԫ��push������2��
	int x = (s1->front + 1) % s1->capacity;//����һ��Ԫ��
	while (x != s1->rear){
		int y = QueuePop(s1);
		QueuePush(s2, y);
		x = (s1->front + 1) % s1->capacity;
	}
}
void OuttoIn(Myqueue *s1, Myqueue *s2){//������2�е�Ԫ��push������1��
	while (!IsEmpty(s2)){
		int y = QueuePop(s2);
		QueuePush(s1, y);
	}
}

void QueueFree(Myqueue *queue){
	free(queue->a);
	free(queue);
}

typedef struct {
	Myqueue *inqueue;
	Myqueue *outqueue;

} MyStack;

/** Initialize your data structure here. */

MyStack* myStackCreate() {//����������
	MyStack *stack = (MyStack *)malloc(sizeof(MyStack));
	stack->inqueue = QueueCreate(10);
	stack->outqueue = QueueCreate(10);
	return stack;

}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {//push������1��
	QueuePush(obj->inqueue, x);
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
	if (!IsEmpty(obj->outqueue)){//�������2��Ϊ�գ������Ƕ�push������1��
		OuttoIn(obj->inqueue, obj->outqueue);
	}
	if (IsEmpty(obj->outqueue)){//�������2Ϊ�գ�������1��push������2�У��������һ��Ԫ��
		IntoOut(obj->inqueue, obj->outqueue);
	}
	return QueuePop(obj->inqueue);


}

/** Get the top element. */
int myStackTop(MyStack* obj) {//�Ƚ�����2�е�Ԫ��push������1�У�����rear���Ԫ��
	OuttoIn(obj->inqueue, obj->outqueue);
	return obj->inqueue->a[obj->inqueue->rear];
	// if(!IsEmpty(obj->outqueue)){
	//     OuttoIn(obj->inqueue,obj->outqueue);
	// }
	// if(IsEmpty(obj->outqueue)){
	//     IntoOut(obj->inqueue,obj->outqueue);
	// }
	// return QueueTop(obj->inqueue);
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {//�����ж�Ϊ�գ�Ϊ��
	if (IsEmpty(obj->inqueue) && IsEmpty(obj->outqueue)){
		return true;
	}
	return false;


}

void myStackFree(MyStack* obj) {
	QueueFree(obj->inqueue);
	QueueFree(obj->outqueue);
	free(obj);

}

