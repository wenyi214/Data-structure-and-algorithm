//����ջʵ�ֶ���
//һ��ջ1�����������ݵģ�
//һ��ջ2�ǵ�����Ҫ�������ʱ����ջ1�������ݣ��ŵ�ջ2�������

typedef struct Stack{//ջ
	int *a;
	int top;
	int capacity;
}stack;

stack *StackCreate(int cap){//����ջ����ʼ��
	stack *s = (stack *)malloc(sizeof(stack));
	s->a = (int *)malloc(sizeof(int)*cap);
	s->capacity = cap;
	s->top = -1;
	return s;
}

void StackPush(stack *s, int x){//��ջ
	s->a[++(s->top)] = x;
}

int Stacktop(stack *s){//��ջ������
	return s->a[s->top];
}

int StackPop(stack *s){//��ջ
	return s->a[(s->top)--];
}

bool IsEmpty(stack *s){//�ж�ջ�Ƿ�Ϊ��
	if (s->top == -1){
		return true;
	}
	return false;
}
void IntoOut(stack *s1, stack *s2){//��ջs1�������õ�ջs2��
	while (!IsEmpty(s1)){
		int x = Stacktop(s1);
		StackPush(s2, x);
		StackPop(s1);
	}
}
void StackFree(stack *s){
	free(s);
}


typedef struct {//��������ջʵ��
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

MyQueue* myQueueCreate() {//�������У�ʵ�ʴ�����ջ
	MyQueue *queue = (MyQueue *)malloc(sizeof(MyQueue));
	queue->instack = StackCreate(100);
	queue->outstack = StackCreate(100);
	return queue;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {//��ԣ�ʱ�佫������ջ1(instack)
	StackPush(obj->instack, x);

}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {//���ӣ��Ǵ�ջ2�����ݣ����ջ2Ϊ�գ���ջ1��������ջ2.
	if (IsEmpty(obj->outstack)){
		IntoOut(obj->instack, obj->outstack);//��ջ1(instack))���õ�ջ2(outstack)
	}
	return StackPop(obj->outstack);

}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {//��ջ�����ݣ�ҲҪ�ж�ջ2�Ƿ�Ϊ��
	if (IsEmpty(obj->outstack)){
		IntoOut(obj->instack, obj->outstack);
	}
	return Stacktop(obj->outstack);

}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {//�ж�ջ1ջ2�Ƿ�Ϊ��
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

