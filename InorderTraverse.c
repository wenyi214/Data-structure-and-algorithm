struct TreeNode{
	int data;
	struct TreeNode *lchild;
	struct TreeNode *rchild;
};
//�ݹ�
void inorderTraversal(struct TreeNode *root){
	if (root == NULL){//�ݹ���ڣ�������Ϊ��
		return;
	}
	else{
		preorderTraversal(root->lchild);//����������
		printf("%d\n", root->data);//���ʸ��ڵ�
		preorderTraversal(root->rchild);//����������
	}
}
//�ǵݹ�
void inorderTraversal(struct TreeNone *root){
	struct TreeNode *cur = root;
	struct TreeNode *ass[100];//����һ��ջ
	int top = -1;//ջ��ָ��
	while (cur || top != -1){//�������Ϊ�ջ���ջ�ﻹ�нڵ�
		while (cur){//һֱ����������
			ass[++top] = cur;//��ջ
			cur = cur->lchild;
		}
		cur = ass[top--];//��ջ
		printf("%d\n", cur->data);//���ʸ��ڵ�
		cur = cur->rchild;//������һ�����
	}
}
