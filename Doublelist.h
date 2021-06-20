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


Dlist *DlistCreate(Datatype x);//�������
Dlist *DlistInit(Datatype x);//��ʼ��ͷ�ڵ�

void DlistPushFront(Dlist *list, Datatype x);//ͷ��
void DlistPopFront(Dlist *list);//ͷɾ
void DlistPushAfter(Dlist *list, Datatype x);//β��
void DlistPopAfter(Dlist *list);//βɾ

Dlist *DlistFind(Dlist *list, Datatype x);//��ĳһ���

void DlistInsert(Dlist *pos, Datatype x);//��posǰ��
void DlistErease(Dlist *pos);//��posɾ��

void DlistPrint(Dlist *list);//��ӡ

int DlistIsEmpty(Dlist *list);//�ж���
void DlistDestory(Dlist *list);//�ͷŽ�㣬��ͷ�ڵ�

