#ifndef __SEARCHTREE_H__
#define __SEARCHTREE_H__

#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef int Elementtype;

typedef struct TreeNode{
	Elementtype val;
	struct TreeNode *left;
	struct TreeNode *right;
}Tree;


Tree *FindNode(Tree *obj, Elementtype x);
int MaxData(Tree *obj);
int MinData(Tree *obj);
Tree *InsertNode(Tree **obj,Elementtype x);
Tree *DeletNode(Tree **obj, Elementtype x);



#endif