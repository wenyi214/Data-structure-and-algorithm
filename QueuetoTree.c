#include<stdio.h>
#include<Windows.h>
#include<stdbool.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define Null 0//�ս��
//�ö��н���һ�Ŷ�����
typedef struct Tree{//��������Ϣ
	int data;
	struct Tree *left;
	struct Tree *right;
}tree;
typedef struct Tree* Mytree;
typedef struct Queue{//����������Ϣ
	Mytree *a;
	int front;
	int rear;
	int capacity;
}Myqueue;


Mytree TreenodeCreate(int a){//���������
	Mytree Q = (Mytree)malloc(sizeof(tree));
	Q->data = a;
	Q->left = NULL;
	Q->right = NULL;
	return Q;
}

Myqueue *QueuenodeCreate(int cap){//�������н��
	Myqueue *queue = (Myqueue *)malloc(sizeof(Myqueue));
	queue->a = (Mytree *)malloc(sizeof(Mytree)*cap);
	queue->capacity = cap;
	queue->front = 0;
	queue->rear = 0;
	return queue;
}

void AddQ(Myqueue *queue, Mytree Q){//������㱣�浽������
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->a[queue->rear] = Q;
}
Mytree DeleteQ(Myqueue *queue){//�����ڵ����
	queue->front = (queue->front + 1) % queue->capacity;
	return queue->a[queue->front];
}

bool Isempty(Myqueue *queue){//�ж������Ƿ�Ϊ��
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
	Myqueue *queue = QueuenodeCreate(10);//����һ���ն���
	if (data == Null){//����ͨ�����������ж��Ƿ�Ҫ�����µ������
		return Q;
	}
	
	Q = TreenodeCreate(data);//����һ������Ԫ����ϢΪ�����data
	AddQ(queue, Q);//����������
	Mytree T;
	while (!(Isempty(queue))){//�ж϶����Ƿ�Ϊ�գ���Ϊ�վ�˵���������ڵ��Ƿ�Ҫ������������������
		T = DeleteQ(queue);//�ó������
		int x = 0;
		printf("Please Enter The LX");
		scanf("%d", &x);//��������
		if (x == Null){
			T->left = NULL;
		}
		else{
			T->left = TreenodeCreate(x);//������������
		}
		printf("Please Enter The RX");
		scanf("%d", &x);
		if (x == Null){
			T->right = NULL;
		}
		else{
			T->right = TreenodeCreate(x);//������������
		}
		if (T->left){//Ϊ���������
			AddQ(queue, T->left);//�����������
		}
		if (T->right){
			AddQ(queue, T->right);//�����������
		}

	}
	return Q;
}


int main(){

	Mytree S = TreeCreate();

	system("pause");
	return 0;
}