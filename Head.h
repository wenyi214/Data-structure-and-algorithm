#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<Windows.h>
#include<assert.h>

typedef int HDdatatype;
typedef struct Head{
	HDdatatype *a;
	int size;
	int capacity;

}HD;

void HeadInit(HD *head, HDdatatype b[], int n);//�ѳ�ʼ��
void HeadDestroy(HD *head);//�ͷŶ�

void HeadPush(HD *head, HDdatatype x);//����Ԫ�ز����ֶѵ�����
HDdatatype HeadPop(HD *head);//�����ѵ���Ԫ��(���ȼ���ߵģ�
HDdatatype HeadTop(HD *head);//�õ��ѵ���Ԫ��

bool HeadIsEmpty(HD *head);//�ж϶��Ƿ�Ϊ��
bool HeadIsFull(HD *head);//�ж϶��Ƿ���

int HeadSize(HD *head);//�õ���Ԫ�س���

void HeadPrint(HD *head);//��ӡ��Ԫ��
