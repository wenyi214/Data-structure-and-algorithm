#include"Doublelist.h"

Dlist *DlistCreate(Datatype x){
	Dlist *newnode = (Dlist *)malloc(sizeof(Dlist));
	newnode->data = x;
	newnode->next = NULL;
	newnode->pre = NULL;
	return newnode;
}

Dlist *DlistInit(Datatype x){
	Dlist *head = DlistCreate(x);
	head->next = head;
	head->pre = head;
	return head;
}
void DlistPushFront(Dlist *list, Datatype x){
	//assert(list);
	//Dlist *newnode = DlistCreate(x);
	//if (list->pre == list){
	//	list->pre = newnode;
	//	list->next = newnode;
	//	newnode->pre = list;
	//	newnode->next = list;
	//}
	//else{
	//	Dlist *tail = list->next;
	//	list->next = newnode;
	//	newnode->pre = list;
	//	newnode->next = tail;
	//	tail->pre = newnode;
	//}
	DlistInsert(list->next, x);

}
void DlistPopFront(Dlist *list){
	//assert(list);
	//Dlist *tail = list->next;
	//Dlist *next = tail->next;

	//list->next = next;
	//next->pre = list;
	//free(tail);
	DlistErease(list->next);
}
void DlistPushAfter(Dlist *list, Datatype x){
	//assert(list);
	//dlist *newnode = dlistcreate(x);
	//dlist *tail = list->pre;

	//tail->next = newnode;
	//newnode->next = list;
	//newnode->pre = tail;
	//list->pre = newnode;
	DlistInsert(list, x);
}
void DlistPopAfter(Dlist *list){
	//assert(list);
	//assert(list->next != list);
	//Dlist *tail = list->pre;
	//Dlist *pre = tail->pre;

	//pre->next = list;
	//list->pre = pre;
	//free(tail);
	DlistErease(list->pre);
}

Dlist *DlistFind(Dlist *list, Datatype x){
	assert(list);
	Dlist *cur = list->next;
	while (cur != list){
		if (cur->data == x){
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

void DlistInsert(Dlist *pos, Datatype x){//pos前插入,尾插相当于在list的前面插
	assert(pos);
	Dlist *tail = pos->pre;
	Dlist *newnode = DlistCreate(x);

	tail->next = newnode;
	newnode->pre = tail;
	newnode->next = pos;
	pos->pre = newnode;

}
void DlistErease(Dlist *pos){
	assert(pos);
	//assert(pos->next != list);
	Dlist *tail = pos->pre;
	Dlist *next = pos->next;

	tail->next = next;
	next->pre = tail;
	free(pos);
}

void DlistPrint(Dlist *list){
	assert(list);
	Dlist *cur = list->next;
	while (cur != list){
		printf("%d ",cur->data);
		cur = cur->next;
	}
	printf("\n");

}

//1为空 0为不空
int DlistIsEmpty(Dlist *list){
	if (list->next == list){
		return 1;
	}
	return 0;
}


void DlistDestory(Dlist *list){
	assert(list);
	Dlist *cur = list->next;
	while (cur->next != list){
		Dlist *next = cur->next;
		free(cur);
		cur = next;
	}
}