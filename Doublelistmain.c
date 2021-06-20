#include"Doublelist.h"


static void Test1(Dlist *list){
	DlistPushFront(list, 4);
	DlistPushFront(list, 3);
	DlistPushFront(list, 2);
	DlistPushFront(list, 1);
	DlistPrint(list);
	DlistPopFront(list);
	DlistPopFront(list);
	DlistPrint(list);
	DlistPushAfter(list, 5);
	DlistPushAfter(list, 6);
	DlistPrint(list);
	DlistPopAfter(list);
	DlistPopAfter(list);
	DlistPrint(list);
	Dlist *pos = DlistFind(list, 4);
	if (pos){
		DlistInsert(pos, 40);
		DlistPrint(list);
	}
	DlistPopAfter(list);
	//DlistPopAfter(list);
	//DlistPopAfter(list);
	int i = DlistIsEmpty(list);
	printf("%d\n", i);
	DlistDestory(list);
	free(list);//释放头节点

}

int main(){
	Dlist *head = DlistInit(0);
	Test1(head);

	system("pause");
	return 0;
}