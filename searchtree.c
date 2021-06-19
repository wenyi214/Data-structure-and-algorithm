#include"searchtree.h"

static Tree *TreeNodecreate(Elementtype x){//�������ڵ�
	Tree *treenode = (Tree *)malloc(sizeof(Tree));
	treenode->left = NULL;
	treenode->right = NULL;
	treenode->val = x;
	return treenode;
}

//��ĳһ�����ֵΪx�Ľ��
//����������ѭ����������Ϊ��ʱ�����ݶ���������������
//������ֵ��Ҫ�ҵ�ֵx��
//�����ң����С�����ң��˳�ѭ��ʱ����������Ϊ�պ��ҵ���
Tree *FindNode(Tree *obj, Elementtype x){//����
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

	return obj;//���ؿգ�û�ҵ�

}
//�ݹ�˼·��������࣬����ע����return �ٵ��ú�����Ҫ�������ҵ���ֵһֱ���ء�
//Tree *FindNode(Tree *obj, Elementtype x){//�ݹ�
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
//���ݶ����������ʣ�һֱ�����ң������Ǹ������ұ߿϶�Ϊ��(�˳�����)
int MaxData(Tree *obj){//����
	if (obj == NULL){
		return 0;//obj���ڿգ�����0
	}
	while (obj->right){
		obj = obj->right;
	}
	return obj->val;
}

//int MaxData(Tree *obj){//�ݹ�
//	if (obj == NULL){
//		return 0;//obj���ڿգ�����0
//	}
//	if(obj->right){
//		return MaxData(obj->right);
//	}
//	return obj->val;
//}

//���ݶ����������ʣ�һֱ�����ң���С���Ǹ�������߿϶�Ϊ��(�˳�����)
int MinData(Tree *obj){//����
	if (obj == NULL){
		return 0;
	}
	while (obj->left){
		obj = obj->left;
	}
	return obj->val;

}
//int MinData(Tree *obj){//�ݹ�
//	if (obj == NULL){
//		return 0;
//	}
//	if (obj->left){
//		return MinData(obj->left);
//	}
//	return obj->val;
//
//}

//����Ľ��϶�����ΪҶ�ڵ����
//�����Ҳ�ֻ࣬��Ҫ�ҵ�����λ��(�϶�Ϊ�ս��)��Ȼ��һ����㷵�ء�������ǿս��˵�����������㡣
//ע�����ﲻ��һֱreturn���ǽ��ӽڵ���ĵ�ַ�������ڵ���ٷ��أ��൱��һ��һ�㷵�ء�
Tree *InsertNode(Tree **obj, Elementtype x){
	if (*obj == NULL){
		*obj = TreeNodecreate(x);
	}
	else{
		if ((*obj)->val > x){
			(*obj)->left = InsertNode(&((*obj)->left), x);//����return
		}
		else if ((*obj)->val < x){
			(*obj)->right = InsertNode(&((*obj)->right), x);
		}
		else{
			printf("�Ѵ���\n");
		}
	}
	return *obj;

}
//ɾ������Ҫ�ҵ�Ҫɾ������λ�ã���һ��ʼ�õ�ѭ�������ķ�������ʱ�������ɾ���Ľ��ΪҶ�ڵ�ʱ����֪��ǰ��һ����㣬����ɾ��
//�����뵽�ݹ飬��Ҫɾ�����������ַ���ظ����ڵ㣬ΪҶ�ڵ�ʱ��ֱ�ӽ��������ÿա�
//�ҵ�����Ҫ���Ǽ��������
//1.���һ����ӽڵ� 2.������ӽڵ㣬�ұ�û�� 3.���û���ӽڵ㣬�ұ��� 4.���Ҷ�û���ӽڵ�(Ҷ�ڵ�)
Tree *DeletNode(Tree **obj, Elementtype x){

	if ((*obj)->val > x){
		(*obj)->left = DeletNode(&((*obj)->left), x);
	}
	else if ((*obj)->val < x){
		(*obj)->right = DeletNode(&((*obj)->right), x);
	}
	else{


		if (obj == NULL){
			printf("��㲻����\n");
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


