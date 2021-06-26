struct TreeNode{
	int data;
	struct TreeNode *lchild;
	struct TreeNode *rchild;
};
//递归
void inorderTraversal(struct TreeNode *root){
	if (root == NULL){//递归出口，二叉树为空
		return;
	}
	else{
		preorderTraversal(root->lchild);//访问左子树
		printf("%d\n", root->data);//访问根节点
		preorderTraversal(root->rchild);//访问右子树
	}
}
//非递归
void inorderTraversal(struct TreeNone *root){
	struct TreeNode *cur = root;
	struct TreeNode *ass[100];//定义一个栈
	int top = -1;//栈顶指针
	while (cur || top != -1){//如果数不为空或者栈里还有节点
		while (cur){//一直走向左子树
			ass[++top] = cur;//入栈
			cur = cur->lchild;
		}
		cur = ass[top--];//出栈
		printf("%d\n", cur->data);//访问根节点
		cur = cur->rchild;//往右走一个结点
	}
}
