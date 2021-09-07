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
	bool erase(pair<K,V> kv){
		//������������ɾ���������Ȳ��ͷſռ䣬Ϊ�˺������Ƚ�
		Node *cur = _root;
		Node *parent = nullptr;
		while (cur){
			//ɾ�����С�ڵ�ǰ����ֵ���������
			if (cur->_kv.first > kv.first){
				parent = cur;
				cur = cur->_left;
			}
			//ɾ�������ڵ�ǰ����ֵ�����ұ���
			else if (cur->_kv.first < kv.first){
				parent = cur;
				cur = cur->_right;
			}
			else{
				//�ҵ����������
				if (cur->_left == nullptr&&cur->_right == nullptr){//���Ҷ���
					//Ϊ���ڵ�
					if (parent == nullptr){
						delete cur;
						_root = nullptr;
						return true;
					}
					//ֱ��ɾ��
					if (parent->_left == cur){
						
						parent->_left = nullptr;
						
					}
					else{
						
						parent->_right = nullptr;
					}					
					
				}

				if (cur->_left == nullptr&&cur->_right){//��գ��Ҳ���
					//Ϊ���ڵ�
					if (parent == nullptr){
						_root = cur->_right;
						delete cur;
						return true;
					}
					//���ڵ�ָ���ұ�
					if (parent->_left == cur){
						cur->_right->_parent = parent;
						parent->_left = cur->_right;
					}
					else {
						cur->_right->_parent = parent;
						parent->_right = cur->_right;
					}
				}

				if (cur->_left&&cur->_right == nullptr){//�ҿգ��󲻿�
					//���ڵ�
					if (parent == nullptr){
						_root = cur->_left;
						delete cur;
						return true;
					}
					//
					if (parent->_left == cur){
						cur->_left->_parent = parent;
						parent->_left = cur->_right;
					}
					else {
						cur->_left->_parent = parent;
						parent->_right = cur->_right;
					}
				}
				if (cur->_left&&cur->_right){
					Node *prev = cur;
					parent = cur;
					cur = cur->_right;

					while (cur->_left){
						parent = cur;
						cur = cur->_left;
					}
					K k = cur->_kv.first;
					V v = cur->_kv.second;
					prev->_kv.first = k;
					prev->_kv.second = v;

					if (parent->_left == cur){
						if (cur->_right){
							cur->_right->_parent = parent;
						}
						
						parent->_left = cur->_right;
					}
					else{
						if (cur->_right){
							cur->_right->_parent = parent;
						}
						parent->_right = cur->_right;
					}

				}
				//���ɾ��
				Node *tail = cur;
				
				while (parent){
					//����ƽ������
					if (cur->_kv.first < parent->_kv.first){
						parent->_bf++;
					}
					else{
						parent->_bf--;
					}

					//���ƽ������
					if (parent->_bf == 1 || parent->_bf == -1){//�߶�û��
						break;
					}
					else if (parent->_bf == 0){//�߶Ƚ��ͣ��������
						cur = parent;
						parent = parent->_parent;
					}
					else if (parent->_bf == 2 || parent->_bf == -2){
						//cur���������߶Ƚ��ͣ�����һ�����ʱ�����ˣ����������
						if (parent->_kv.first > cur->_kv.first){
							cur = parent->_right;
						}
						else{
							cur = parent->_left;
						}

						if (parent->_bf == 2 && cur->_bf == 1){//��Ҫ�������ϸ���
							
							SigelLeft(parent);
							cur = parent->_parent;
							parent = cur->_parent;
						}
						else if (parent->_bf == 2 && cur->_bf == 0){
							SigelLeft(parent);
							parent->_bf = 1;
							parent->_parent->_bf = -1;
							break;
						}
						else if (parent->_bf == 2 && cur->_bf == -1){//��Ҫ�������ϸ���
							
							DoubleRightLeft(parent);
							cur = parent->_parent;
							parent = cur->_parent;
							
						}

						else if (parent->_bf == -2 && cur->_bf == -1){//��Ҫ�������ϸ���
							
							SigelRight(parent);
							cur = parent->_parent;
							parent = cur->_parent;
						}
						else if (parent->_bf == -2 && cur->_bf == 0){
							SigelRight(parent);
							parent->_bf = -1;
							parent->_bf = 1;
							break;
						}
						else if (parent->_bf == -2 && cur->_bf == 1){//��Ҫ�������ϸ���
							
							DoubleLeftRight(parent);
							cur = parent->_parent;
							parent = cur->_parent;
						}
						

					}

				}
				delete tail;
				return true;

			}
		}
		//û�ҵ�
		return false;


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

	void _InOrder(Node *root){
		if (root){
			_InOrder(root->_left);
			cout << root->_kv.first;
			_InOrder(root->_right);
		}
	}

	void InOrder(){
		_InOrder(_root);
		cout << endl;
	}

private:
	Node *_root = nullptr;
};