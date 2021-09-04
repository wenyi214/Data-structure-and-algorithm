#pragma once
#include<iostream>
using namespace std;

//二叉树应用KV模型
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

	AVLTreeNode *_left;//该节点的左孩子
	AVLTreeNode *_right;//该节点的右孩子
	AVLTreeNode *_parent;//该节点的父亲
	//平衡因子
	int _bf;
	//保存的是键值对，pair结构体
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
		//找到插入位置，现在进行插入
		cur = new Node(kv);
		//要更新父节点
		cur->_parent = parent;
		if (parent->_kv.first < kv.first){
			
			parent->_right = cur;
		}
		else{
			
			parent->_left = cur;
		}

		//更新平衡因子
		while (parent){
			//如果插入左边平衡因子--
			if (parent->_left == cur){
				parent->_bf--;
			}
			//如果插入右边，平衡因子++
			else{
				parent->_bf++;
			}

			//判断平衡因子
			if (parent->_bf == 0){//如果parent位置平衡因子等于0，不再往上更新，高度没变
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1){//高度变了，但是没有不平衡，继续往上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2){//不平衡需要旋转
				if (parent->_bf == 2 && cur->_bf == 1){
					SigelLeft(parent);//左单旋
				}
				else if (parent->_bf == 2 && cur->_bf == -1){
					DoubleRightLeft(parent);//右左双旋
				}
				else if (parent->_bf == -2 && cur->_bf == 1){
					DoubleLeftRight(parent);//左右双旋
				}
				else if (parent->_bf == -2 && cur->_bf == -1){
					SigelRight(parent);//右单旋
				}
				break;//旋转完不需要更新平衡因子了。

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
		//注意要更新父节点
		parent->_right = SubRL;
		if (SubRL){
			SubRL->_parent = parent;
		}

		SubR->_left = parent;
		parent->_parent = SubR;

		//更新新根节点SubR的父节点
		if (Pparent == nullptr){//当前结点为根节点
			//直接置空
			SubR->_parent = nullptr;
			//注意要更新根节点
			_root = SubR;
		}
		else{//当前树为子树
			//连接到上面结点
			if (Pparent->_kv.first < SubR->_kv.first){
				Pparent->_right = SubR;
				
			}
			else{
				Pparent->_left = SubR;
			}

			//更新父节点
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

		if (Pparent == nullptr)//根节点
		{
			
			SubL->_parent = nullptr;
			_root = SubL;
		}
		else//子树
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

		//为了后面更新平衡因子，看插入左边还是右边
		int bf = SubRL->_bf;

		SigelRight(SubR);

		SigelLeft(parent);
		//画图理解,更新平衡因子
		if (bf == 1){//插入方向在右边
			SubR->_bf = 0;
			SubRL->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == -1){//插入方向在左边
			SubRL ->_bf= 0;
			parent->_bf = 0;
			SubR->_bf = 1;
		}
		else if (bf == 0){//SubRL就是插入结点
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


		// 空树也是AVL树
		if (nullptr == pRoot) return true;
		// 计算pRoot节点的平衡因子：即pRoot左右子树的高度差
		int leftHeight = _Height(pRoot->_left);
		int rightHeight = _Height(pRoot->_right);
		int diff = rightHeight - leftHeight;
		// 如果计算出的平衡因子与pRoot的平衡因子不相等，或者
		// pRoot平衡因子的绝对值超过1，则一定不是AVL树
		if (diff != pRoot->_bf || (diff > 1 || diff < -1))
			return false;
		// pRoot的左和右如果都是AVL树，则该树一定是AVL树
		return _IsBalanceTree(pRoot->_left) && _IsBalanceTree(pRoot->_right);
	}

	bool Isbalance(){
		return _IsBalanceTree(_root);
	}

private:
	Node *_root = nullptr;
};