#include"Head.h"

static void Swap(int *px, int *py){
	int temp = *px;
	*px = *py;
	*py = temp;
}
//�������ϵ������õ������
static void AdjustDown(HDdatatype a[], int size, int parent){
	int child = parent * 2 + 1;//�ȼ�����ߵ����ȸ�����
	while (child < size){//û�к��ӽ���˳�
		if (child + 1 < size&&a[child] < a[child + 1]){//����ұߵ�����child++�͵õ��ұ������±�
			child++;
		}
		if (a[child] > a[parent]){//������ӽ��ȸ��ڵ��;ͽ���
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else{//ֱ��������˳�
			break;
		}
	}
}
static void AdjustUp(HDdatatype a[], int child){//���ϵ���
	while (child > 0){//���ӽڵ����0��û�и��ڵ��˳�
		int parent = (child - 1) / 2;//�õ����ڵ�
		if (a[child]>a[parent]){//���ӽڵ�ȸ��ڵ�󽻻�
			Swap(&a[child], &a[parent]);
			child = parent;
		}
		else{//ֱ�������˳�
			break;
		}
	}
}

//������b[]�������ɶѣ�
void HeadInit(HD *head, HDdatatype b[],int n){
	head->a = (HDdatatype *)malloc(sizeof(HDdatatype)*n);
	if (head->a == NULL){
		printf("malloc fail!\n");
		exit(-1);
	}
	for (int i = 0; i < n; i++){
		head->a[i] = b[i];
	}
	head->size = n;
	head->capacity = n;

	for (int i=(head->size-1-1)/2;i>=0;i--)
	{
		AdjustDown(head->a, head->size, i);
	}
}

void HeadDestroy(HD *head){//�ͷ�
	free(head->a);
	head->a = NULL;
	head->capacity = 0;
	head->size = 0;
}
//�����һ��λ�ò��룬�����ϵ����ɶ�
void HeadPush(HD *head, HDdatatype x){
	assert(head);
	if (HeadIsFull(head)){
		HDdatatype *temp = (HDdatatype *)realloc(head->a, sizeof(HDdatatype)*head->capacity * 2);
		if (temp == NULL){
			printf("realloc fail\n");
			HeadDestroy(head);
			exit(-1);
		}
		head->a = temp;
		head->capacity *= 2;
	}
	head->a[head->size] = x;
	head->size++;
	AdjustUp(head->a, head->size - 1);

}

//������N��Ԫ�أ�����һ��Ԫ��(0)�����һ��Ԫ(N-1)�ؽ������ٽ�ǰ��N-1��Ԫ�����µ����ɶ�
HDdatatype HeadPop(HD *head){
	assert(head);
	int max = head->a[0];
	Swap(&head->a[0], &head->a[head->size - 1]);
	head->size--;
	AdjustDown(head->a, head->size - 1, 0);
	return max;
}

HDdatatype HeadTop(HD *head){
	assert(head);
	return head->a[0];
}

bool HeadIsEmpty(HD *head){
	if (head->size == 0){
		return true;
	}
	return false;
}

bool HeadIsFull(HD *head){
	if (head->size == head->capacity){
		return true;
	}
	return false;
}

int HeadSize(HD *head){
	assert(head);
	return head->size;
}

void HeadPrint(HD *head){
	for (int i = 0; i < head->size; i++){
		printf("%d ", head->a[i]);
	}
	printf("\n");
}