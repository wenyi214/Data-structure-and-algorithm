#include"searchtree.h"


int main(){
	Tree *s = NULL;
	InsertNode(&s, 5);
	InsertNode(&s, 1);
	InsertNode(&s, 3);
	InsertNode(&s, 7);
	InsertNode(&s, 6);
	InsertNode(&s, 4);
	InsertNode(&s, 2);
	DeletNode(&s, 6);
	//int max = MaxData(s);
	//printf("%d\n", max);
	//int min = MinData(s);
	//printf("%d\n", min);
	//Tree *t = FindNode(s, 8);
	system("pause");
	return 0;
}