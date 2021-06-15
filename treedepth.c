#include<stdio.h>
#include<Windows.h>
#pragma warning(disable:4996)

struct TreeNode{
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
};
//根节点的高度等于左子树与右子树的较大值+1
//先求出左子树的高度，再求出右子树的高度，比较较大者，返回较大者加1。

int TreeDepth(struct TreeNode *obj){
	if (!obj){
		return 0;
	}
	int depth;
	int ldep ;
	int rdep ;

	ldep = TreeDepth(obj->left);
	rdep = TreeDepth(obj->right);
	depth = ldep > rdep ? ldep : rdep;
	return depth+1;
}


int main(){
	struct TreeNode a;
	struct TreeNode b;
	struct TreeNode c;
	struct TreeNode d;
	a.data = 0;
	a.left = &b;
	a.right = &c;
	b.data = 0;
	b.left = &d;
	b.right = NULL;
	c.data = 0;
	c.right = NULL;
	c.left = NULL;
	d.data = 0;
	d.left = NULL;
	d.right = NULL;
	int h = TreeDepth(&a);
	printf("%d\n", h);


	system("pause");
	return 0;
}