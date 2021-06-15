#include<stdio.h>
#include<Windows.h>
#pragma warning(disable:4996)

struct TreeNode{
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
};

//往左走往走走，走到左子树和右子树为空的地方，就是叶节点
void LeafNode(struct TreeNode *s){
	if (s){
		/*if (s->left==NULL&&s->right==NULL)
		printf("%d\n", s->data);*/
		LeafNode(s->left);
		//if (s->left == NULL&&s->right == NULL)
		//	printf("%d\n", s->data);
		LeafNode(s->right);
		if (s->left == NULL&&s->right == NULL)
			printf("%d\n", s->data);
	}
}


int main(){
	struct TreeNode a;
	struct TreeNode b;
	struct TreeNode c;
	struct TreeNode d;
	a.data = 0;
	a.left = &b;
	a.right = &c;
	b.data = 2;
	b.left = &d;
	b.right = NULL;
	c.data = 3;
	c.right = NULL;
	c.left = NULL;
	d.data = 1;
	d.left = NULL;
	d.right = NULL;
	LeafNode(&a);


	system("pause");
	return 0;
}