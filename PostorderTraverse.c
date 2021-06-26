struct TreeNode{
	int data;
	struct TreeNode *lchild;
	struct TreeNode *rchild;
};

void postorderTraversal(struct TreeNode *root){
	if (root == NULL){//递归出口，二叉树为空
		return;
	}
	else{
		preorderTraversal(root->lchild);//访问左子树
		preorderTraversal(root->rchild);//访问右子树
		printf("%d\n", root->data);//访问根节点
	}
}
void postorderTraversal(struct TreeNone *root){
	struct TreeNode *cur = root;
	struct TreeNode *ass[100];//定义一个栈
	int top = -1;//栈顶指针
	struct TreeNode *temp;
	while (cur || top != -1){//如果数不为空或者栈里还有节点
		while (cur){//一直走向左子树
			ass[++top] = cur;//入栈
			cur = cur->lchild;
		}
		cur = ass[top--];//出栈
		if (cur->rchild == NULL || cur->rchild == temp){
			printf("%d\n", cur->data);//访问根节点
			temp = cur;//用一变量保存该节点
			cur = NULL;//置空
		}
		else{
			ass[top++] = cur;//该节点入栈
			cur = cur->rchild;//往右走一个结点
		}
	}
}
