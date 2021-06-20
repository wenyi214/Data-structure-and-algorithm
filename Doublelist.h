#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<Windows.h>
#pragma warning(disable:4996)

typedef int Datatype;

typedef struct Dlist{
	Datatype data;
	struct Dlist *next;
	struct Dlist *pre;
}Dlist;


Dlist *DlistCreate(Datatype x);//创建结点
Dlist *DlistInit(Datatype x);//初始化头节点

void DlistPushFront(Dlist *list, Datatype x);//头插
void DlistPopFront(Dlist *list);//头删
void DlistPushAfter(Dlist *list, Datatype x);//尾插
void DlistPopAfter(Dlist *list);//尾删

Dlist *DlistFind(Dlist *list, Datatype x);//找某一结点

void DlistInsert(Dlist *pos, Datatype x);//在pos前插
void DlistErease(Dlist *pos);//将pos删除

void DlistPrint(Dlist *list);//打印

int DlistIsEmpty(Dlist *list);//判定空
void DlistDestory(Dlist *list);//释放结点，除头节点

