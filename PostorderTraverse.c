struct TreeNode{
	int data;
	struct TreeNode *lchild;
	struct TreeNode *rchild;
};

void postorderTraversal(struct TreeNode *root){
	if (root == NULL){//�ݹ���ڣ�������Ϊ��
		return;
	}
	else{
		preorderTraversal(root->lchild);//����������
		preorderTraversal(root->rchild);//����������
		printf("%d\n", root->data);//���ʸ��ڵ�
	}
}
void postorderTraversal(struct TreeNone *root){
	struct TreeNode *cur = root;
	struct TreeNode *ass[100];//����һ��ջ
	int top = -1;//ջ��ָ��
	struct TreeNode *temp;
	while (cur || top != -1){//�������Ϊ�ջ���ջ�ﻹ�нڵ�
		while (cur){//һֱ����������
			ass[++top] = cur;//��ջ
			cur = cur->lchild;
		}
		cur = ass[top--];//��ջ
		if (cur->rchild == NULL || cur->rchild == temp){
			printf("%d\n", cur->data);//���ʸ��ڵ�
			temp = cur;//��һ��������ýڵ�
			cur = NULL;//�ÿ�
		}
		else{
			ass[top++] = cur;//�ýڵ���ջ
			cur = cur->rchild;//������һ�����
		}
	}
}
