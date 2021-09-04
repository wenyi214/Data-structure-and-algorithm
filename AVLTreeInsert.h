#pragma once
#include<iostream>
using namespace std;

//������Ӧ��KVģ��
template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode(const pair<K, V> kv)
	:_left(nullptr)
	, _right(nullptr)
	, _parent(nullptr)
	,_bf(0)
	, _kv(kv)
	{}

	AVLTreeNode *_left;//�ýڵ������
	AVLTreeNode *_right;//�ýڵ���Һ���
	AVLTreeNode *_parent;//�ýڵ�ĸ���
	//ƽ������
	int _bf;
	//������Ǽ�ֵ�ԣ�pair�ṹ��
	pair<K, V> _kv;
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K,V> Node;
public:
	bool insert(const pair<K, V> kv)
	{
		if (_root == nullptr){
			_root = new Node(kv);
			return true;
		}
		Node *cur = _root;
		Node *parent = nullptr;
		while (cur)
		{
			if (kv.first > cur->_kv.first){
				parent = cur;
				cur = cur->_right;
			}
			else if (kv.first < cur->_kv.first){
				parent = cur;
				cur = cur->_left;
			}
			else{
				return false;
			}
		}
		//�ҵ�����λ�ã����ڽ��в���
		cur = new Node(kv);
		//Ҫ���¸��ڵ�
		cur->_parent = parent;
		if (parent->_kv.first < kv.first){
			
			parent->_right = cur;
		}
		else{
			
			parent->_left = cur;
		}

		//����ƽ������
		while (parent){
			//����������ƽ������--
			if (parent->_left == cur){
				parent->_bf--;
			}
			//��������ұߣ�ƽ������++
			else{
				parent->_bf++;
			}

			//�ж�ƽ������
			if (parent->_bf == 0){//���parentλ��ƽ�����ӵ���0���������ϸ��£��߶�û��
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1){//�߶ȱ��ˣ�����û�в�ƽ�⣬�������ϸ���
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2){//��ƽ����Ҫ��ת
				if (parent->_bf == 2 && cur->_bf == 1){
					SigelLeft(parent);//����
				}
				else if (parent->_bf == 2 && cur->_bf == -1){
					DoubleRightLeft(parent);//����˫��
				}
				else if (parent->_bf == -2 && cur->_bf == 1){
					DoubleLeftRight(parent);//����˫��
				}
				else if (parent->_bf == -2 && cur->_bf == -1){
					SigelRight(parent);//�ҵ���
				}
				break;//��ת�겻��Ҫ����ƽ�������ˡ�

			}
			else{
				
			}
		}
		return true;


	}
	void SigelLeft(Node *parent){
		Node *SubR = parent->_right;
		Node *SubRL = SubR->_left;

		Node *Pparent = parent->_parent;
		//ע��Ҫ���¸��ڵ�
		parent->_right = SubRL;
		if (SubRL){
			SubRL->_parent = parent;
		}

		SubR->_left = parent;
		parent->_parent = SubR;

		//�����¸��ڵ�SubR�ĸ��ڵ�
		if (Pparent == nullptr){//��ǰ���Ϊ���ڵ�
			//ֱ���ÿ�
			SubR->_parent = nullptr;
			//ע��Ҫ���¸��ڵ�
			_root = SubR;
		}
		else{//��ǰ��Ϊ����
			//���ӵ�������
			if (Pparent->_kv.first < SubR->_kv.first){
				Pparent->_right = SubR;
				
			}
			else{
				Pparent->_left = SubR;
			}

			//���¸��ڵ�
			SubR->_parent = Pparent;
		}

		SubR->_bf = 0;
		parent->_bf = 0;
	}

	void SigelRight(Node *parent){
		Node *SubL = parent->_left;
		Node *SubLR = SubL->_right;

		Node *Pparent = parent->_parent;

		parent->_left = SubLR;
		if (SubLR){
			SubLR->_parent = parent;
		}

		SubL->_right = parent;
		parent->_parent = SubL;

		if (Pparent == nullptr)//���ڵ�
		{
			
			SubL->_parent = nullptr;
			_root = SubL;
		}
		else//����
		{
			if (Pparent->_kv.first > SubL->_kv.first){
				Pparent->_left = SubL;
			}
			else{
				Pparent->_right = SubL;
			}
			SubL->_parent = Pparent;
		}

		SubL->_bf = 0;
		parent->_bf = 0;
	}

	void DoubleRightLeft(Node *parent){
		Node *SubR = parent->_right;
		Node *SubRL = SubR->_left;

		//Ϊ�˺������ƽ�����ӣ���������߻����ұ�
		int bf = SubRL->_bf;

		SigelRight(SubR);

		SigelLeft(parent);
		//��ͼ���,����ƽ������
		if (bf == 1){//���뷽�����ұ�
			SubR->_bf = 0;
			SubRL->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == -1){//���뷽�������
			SubRL ->_bf= 0;
			parent->_bf = 0;
			SubR->_bf = 1;
		}
		else if (bf == 0){//SubRL���ǲ�����
			SubR->_bf = 0;
			SubRL->_bf = 0;
			parent->_bf = 0;
		}
	}

	void DoubleLeftRight(Node *parent){
		Node *SubL = parent->_left;
		Node *SubLR = SubL->_right;

		int bf = SubLR->_bf;

		SigelLeft(SubL);

		SigelRight(parent);

		if (bf == 1){
			SubL->_bf = -1;
			parent->_bf = 0;
			SubLR->_bf = 0;
		}
		else if (bf == -1){
			parent->_bf = 1;
			SubL->_bf = 0;
			SubLR->_bf = 0;
		}
		else if (bf == 0){
			parent->_bf = 0;
			SubL->_bf = 0;
			SubLR->_bf = 0;
		}
	}

	int _Height(Node *root){
		if (root == nullptr){
			return 0;
		}
		int left = _Height(root->_left);
		int right = _Height(root->_right);

		return left > right ? left + 1 : right + 1;
	}

	bool _JudgeBalance(Node *root){
		if (root == nullptr){
			return true;
		}


		int lefthight = _Height(root->_left);
		int righthight = _Height(root->_right);
		if (righthight - lefthight >= 2 || righthight - lefthight <= -2){
			return false;
		}
		if (righthight - lefthight >= -1 && righthight - lefthight <= 1){
			return true;
		}
		return  _JudgeBalance(root->_left) && _JudgeBalance(root->_right);

	}
	bool JudgeBalance(){
		return _JudgeBalance(_root);
	}



	//int _Height(PNode pRoot);
	bool _IsBalanceTree(Node *pRoot)
	{


		// ����Ҳ��AVL��
		if (nullptr == pRoot) return true;
		// ����pRoot�ڵ��ƽ�����ӣ���pRoot���������ĸ߶Ȳ�
		int leftHeight = _Height(pRoot->_left);
		int rightHeight = _Height(pRoot->_right);
		int diff = rightHeight - leftHeight;
		// ����������ƽ��������pRoot��ƽ�����Ӳ���ȣ�����
		// pRootƽ�����ӵľ���ֵ����1����һ������AVL��
		if (diff != pRoot->_bf || (diff > 1 || diff < -1))
			return false;
		// pRoot��������������AVL���������һ����AVL��
		return _IsBalanceTree(pRoot->_left) && _IsBalanceTree(pRoot->_right);
	}

	bool Isbalance(){
		return _IsBalanceTree(_root);
	}

private:
	Node *_root = nullptr;
};