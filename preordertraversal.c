#include<stdio.h>
struct TreeNode{
	int data;
	struct TreeNode *lchild;
	struct TreeNode *rchild;
};

//�ݹ�
void preorderTraversal(struct TreeNode *root){
	if (root == NULL){//�ݹ���ڣ�������Ϊ��
		return;
	}
	else{
		printf("%d\n", root->data);//���ʸ��ڵ�
		preorderTraversal(root->lchild);//����������
		preorderTraversal(root->rchild);//����������
	}
}

//�ǵݹ�
void preorderTraversal(struct TreeNone *root){
	struct TreeNode *cur = root;
	struct TreeNode *ass[100];//����һ��ջ
	int top = -1;//ջ��ָ��
	while (cur || top != -1){//�������Ϊ�ջ���ջ�ﻹ�нڵ�
		while (cur){//һֱ����������
			printf("%d\n", cur->data);//���ʸ��ڵ�
			ass[++top] = cur;//��ջ
			cur = cur->lchild;
		}
		cur = ass[top--];//��ջ
		cur = cur->rchild;//������һ�����
	}
}
