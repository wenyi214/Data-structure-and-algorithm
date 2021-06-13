//用两栈实现队列
//一个栈1用来保存数据的，
//一个栈2是当队列要输出数据时，从栈1中拿数据，放到栈2再输出。

typedef struct Stack{//栈
	int *a;
	int top;
	int capacity;
}stack;

stack *StackCreate(int cap){//创建栈，初始化
	stack *s = (stack *)malloc(sizeof(stack));
	s->a = (int *)malloc(sizeof(int)*cap);
	s->capacity = cap;
	s->top = -1;
	return s;
}

void StackPush(stack *s, int x){//入栈
	s->a[++(s->top)] = x;
}

int Stacktop(stack *s){//拿栈顶数据
	return s->a[s->top];
}

int StackPop(stack *s){//出栈
	return s->a[(s->top)--];
}

bool IsEmpty(stack *s){//判断栈是否为空
	if (s->top == -1){
		return true;
	}
	return false;
}
void IntoOut(stack *s1, stack *s2){//将栈s1的数据拿到栈s2里
	while (!IsEmpty(s1)){
		int x = Stacktop(s1);
		StackPush(s2, x);
		StackPop(s1);
	}
}
void StackFree(stack *s){
	free(s);
}


typedef struct {//队列用两栈实现
	stack *instack;
	stack *outstack;

} MyQueue;

// void IntoOut(MyQueue* obj){
//     while(!IsEmpty(obj->instack)){
//         int x=Stacktop(obj->instack);
//         StackPush(obj->outstack,x);
//         StackPop(obj->instack);
//     }

// }
/** Initialize your data structure here. */

MyQueue* myQueueCreate() {//创建队列，实际创建两栈
	MyQueue *queue = (MyQueue *)malloc(sizeof(MyQueue));
	queue->instack = StackCreate(100);
	queue->outstack = StackCreate(100);
	return queue;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {//入对，时间将数据入栈1(instack)
	StackPush(obj->instack, x);

}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {//出队，是从栈2拿数据，如果栈2为空，将栈1的数据入栈2.
	if (IsEmpty(obj->outstack)){
		IntoOut(obj->instack, obj->outstack);//将栈1(instack))的拿到栈2(outstack)
	}
	return StackPop(obj->outstack);

}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {//拿栈顶数据，也要判定栈2是否为空
	if (IsEmpty(obj->outstack)){
		IntoOut(obj->instack, obj->outstack);
	}
	return Stacktop(obj->outstack);

}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {//判断栈1栈2是否为空
	if (IsEmpty(obj->instack) && IsEmpty(obj->outstack)){
		return true;
	}
	return false;
}

void myQueueFree(MyQueue* obj) {
	StackFree(obj->instack);
	StackFree(obj->outstack);
	free(obj);
}

