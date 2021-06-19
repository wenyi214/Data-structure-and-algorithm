#include"searchtree.h"

static Tree *TreeNodecreate(Elementtype x){//建立树节点
	Tree *treenode = (Tree *)malloc(sizeof(Tree));
	treenode->left = NULL;
	treenode->right = NULL;
	treenode->val = x;
	return treenode;
}

//找某一树结点值为x的结点
//迭代方法，循环，当树不为空时，根据二叉搜索树的性质
//如果结点值比要找的值x大
//往左找，如果小往右找，退出循环时两种条件，为空和找到了
Tree *FindNode(Tree *obj, Elementtype x){//迭代
	while (obj){
		if (obj->val > x){
			obj = obj->left;
		}
		else if (obj->val < x){
			obj = obj->right;
		}
		else{
			break;
		}
	}

	return obj;//返回空，没找到

}
//递归思路跟迭代差不多，这里注意是return 再调用函数，要将最后的找到的值一直返回。
//Tree *FindNode(Tree *obj, Elementtype x){//递归
//	if (obj == NULL){
//		return obj;
//	}
//	if (obj->val > x){
//		return FindNode(obj->left, x);
//	}
//	else if (obj->val < x){
//		return FindNode(obj->right, x);
//	}
//	else{
//
//	}
//	return obj;
//
//
//}
//根据二叉树的性质，一直往右找，最大的那个结点的右边肯定为空(退出条件)
int MaxData(Tree *obj){//迭代
	if (obj == NULL){
		return 0;//obj等于空，返回0
	}
	while (obj->right){
		obj = obj->right;
	}
	return obj->val;
}

//int MaxData(Tree *obj){//递归
//	if (obj == NULL){
//		return 0;//obj等于空，返回0
//	}
//	if(obj->right){
//		return MaxData(obj->right);
//	}
//	return obj->val;
//}

//根据二叉树的性质，一直往左找，最小的那个结点的左边肯定为空(退出条件)
int MinData(Tree *obj){//迭代
	if (obj == NULL){
		return 0;
	}
	while (obj->left){
		obj = obj->left;
	}
	return obj->val;

}
//int MinData(Tree *obj){//递归
//	if (obj == NULL){
//		return 0;
//	}
//	if (obj->left){
//		return MinData(obj->left);
//	}
//	return obj->val;
//
//}

//插入的结点肯定会作为叶节点插入
//跟查找差不多，只是要找到插入位置(肯定为空结点)，然后建一个结点返回。如果不是空结点说明存在这个结点。
//注意这里不是一直return，是将子节点结点的地址赋给父节点后再返回，相当于一层一层返回。
Tree *InsertNode(Tree **obj, Elementtype x){
	if (*obj == NULL){
		*obj = TreeNodecreate(x);
	}
	else{
		if ((*obj)->val > x){
			(*obj)->left = InsertNode(&((*obj)->left), x);//不是return
		}
		else if ((*obj)->val < x){
			(*obj)->right = InsertNode(&((*obj)->right), x);
		}
		else{
			printf("已存在\n");
		}
	}
	return *obj;

}
//删除首先要找到要删除结点的位置，我一开始用的循环迭代的方法，当时发现如果删除的结点为叶节点时，不知道前面一个结点，不好删除
//于是想到递归，将要删除的这个结点地址返回给父节点，为叶节点时，直接将这个结点置空。
//找到结点后要考虑几种情况，
//1.左右还有子节点 2.左边有子节点，右边没有 3.左边没有子节点，右边有 4.左右都没有子节点(叶节点)
Tree *DeletNode(Tree **obj, Elementtype x){

	if ((*obj)->val > x){
		(*obj)->left = DeletNode(&((*obj)->left), x);
	}
	else if ((*obj)->val < x){
		(*obj)->right = DeletNode(&((*obj)->right), x);
	}
	else{


		if (obj == NULL){
			printf("结点不存在\n");
		}
		else{
			if ((*obj)->left != NULL && (*obj)->right != NULL){
				int x = MaxData((*obj)->left);
				DeletNode(&(*obj), x);
				(*obj)->val = x;
				//DeletNode()
			}
			else if ((*obj)->left != NULL && (*obj)->right == NULL){
				int x = (*obj)->left->val;
				Tree *temp = (*obj)->left;
				(*obj)->left = NULL;
				(*obj)->val = x;
				free(temp);
			}
			else if ((*obj)->left == NULL && (*obj)->right != NULL){
				int x = (*obj)->right->val;
				Tree *temp = (*obj)->right;
				(*obj)->right = NULL;
				(*obj)->val = x;
				free(temp);
			}
			else{
				Tree *temp = (*obj)->right;
				(*obj) = NULL;
				free(temp);
			}
		}

	}
	return (*obj);
}


