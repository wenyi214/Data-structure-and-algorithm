#include<stdio.h>
#include<Windows.h>
#include<stdbool.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define Null 0//空结点
//用队列建立一颗二叉树
typedef struct Tree{//建立树信息
	int data;
	struct Tree *left;
	struct Tree *right;
}tree;
typedef struct Tree* Mytree;
typedef struct Queue{//建立队列信息
	Mytree *a;
	int front;
	int rear;
	int capacity;
}Myqueue;


Mytree TreenodeCreate(int a){//创建树结点
	Mytree Q = (Mytree)malloc(sizeof(tree));
	Q->data = a;
	Q->left = NULL;
	Q->right = NULL;
	return Q;
}

Myqueue *QueuenodeCreate(int cap){//创建队列结点
	Myqueue *queue = (Myqueue *)malloc(sizeof(Myqueue));
	queue->a = (Mytree *)malloc(sizeof(Mytree)*cap);
	queue->capacity = cap;
	queue->front = 0;
	queue->rear = 0;
	return queue;
}

void AddQ(Myqueue *queue, Mytree Q){//将树结点保存到队列中
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->a[queue->rear] = Q;
}
Mytree DeleteQ(Myqueue *queue){//将树节点出队
	queue->front = (queue->front + 1) % queue->capacity;
	return queue->a[queue->front];
}

bool Isempty(Myqueue *queue){//判定队列是否为空
	if (queue->front == queue->rear){
		return true;
	}
	return false;
}


Mytree TreeCreate(){
	int data;
	printf("Please Enter The Data#");
	scanf("%d", &data);
	Mytree Q = NULL;;
	Myqueue *queue = QueuenodeCreate(10);//创建一个空队列
	if (data == Null){//这里通过输入数据判断是否要创建新的树结点
		return Q;
	}
	
	Q = TreenodeCreate(data);//创建一颗树，元素信息为输入的data
	AddQ(queue, Q);//将树结点入队
	Mytree T;
	while (!(Isempty(queue))){//判断队列是否为空，不为空就说明还有树节点是否要生成左子树，右子树
		T = DeleteQ(queue);//拿出树结点
		int x = 0;
		printf("Please Enter The LX");
		scanf("%d", &x);//输入数据
		if (x == Null){
			T->left = NULL;
		}
		else{
			T->left = TreenodeCreate(x);//先生成左子树
		}
		printf("Please Enter The RX");
		scanf("%d", &x);
		if (x == Null){
			T->right = NULL;
		}
		else{
			T->right = TreenodeCreate(x);//后生成右子树
		}
		if (T->left){//为空树不入队
			AddQ(queue, T->left);//将左子树入队
		}
		if (T->right){
			AddQ(queue, T->right);//将右子树入队
		}

	}
	return Q;
}


int main(){

	Mytree S = TreeCreate();

	system("pause");
	return 0;
}