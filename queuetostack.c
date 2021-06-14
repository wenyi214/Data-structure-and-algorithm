//两队列实现栈，将一个队列1作为栈的push，当要pop的时候，
//将队列1的元素push到队列2中，留下最后一个元素，再pop出来
//注意，再pop的时候要将队列2的元素push都队列1里，再经历上面的操作
//取top队列顶元素先将队列2里的元素push到队列1中，拿rear这个元素就好了。


typedef struct Queue{
	int *a;
	int front;
	int rear;
	int capacity;
}Myqueue;

Myqueue *QueueCreate(int cap){//队列初始化
	Myqueue *queue = (Myqueue *)malloc(sizeof(Myqueue));
	queue->a = (int *)malloc(sizeof(int)*cap);
	queue->front = 0;
	queue->rear = 0;
	queue->capacity = cap;
	return queue;
}

void QueuePush(Myqueue *queue, int x){//队列push循环
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->a[(queue->rear)] = x;
}
int QueueTop(Myqueue *queue){//取队列第一个元素
	int x = (queue->front + 1) % queue->capacity;
	return queue->a[x];
}

int QueuePop(Myqueue *queue){//队列pop
	queue->front = (queue->front + 1) % queue->capacity;
	return queue->a[queue->front];
}
int IsEmpty(Myqueue *queue){//判空
	return queue->front == queue->rear;
}

void IntoOut(Myqueue *s1, Myqueue *s2){//将队列1的元素push到队列2中
	int x = (s1->front + 1) % s1->capacity;//留下一个元素
	while (x != s1->rear){
		int y = QueuePop(s1);
		QueuePush(s2, y);
		x = (s1->front + 1) % s1->capacity;
	}
}
void OuttoIn(Myqueue *s1, Myqueue *s2){//将队列2中的元素push到队列1中
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

MyStack* myStackCreate() {//建立两队列
	MyStack *stack = (MyStack *)malloc(sizeof(MyStack));
	stack->inqueue = QueueCreate(10);
	stack->outqueue = QueueCreate(10);
	return stack;

}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {//push到队列1中
	QueuePush(obj->inqueue, x);
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
	if (!IsEmpty(obj->outqueue)){//如果队列2不为空，将他们都push到队列1中
		OuttoIn(obj->inqueue, obj->outqueue);
	}
	if (IsEmpty(obj->outqueue)){//如果队列2为空，将队列1的push到队列2中，留下最后一个元素
		IntoOut(obj->inqueue, obj->outqueue);
	}
	return QueuePop(obj->inqueue);


}

/** Get the top element. */
int myStackTop(MyStack* obj) {//先将队列2中的元素push到队列1中，再拿rear这的元素
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
bool myStackEmpty(MyStack* obj) {//两队列都为空，为空
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

