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
	bool erase(pair<K,V> kv){
		//按二叉搜索树删除，但是先不释放空间，为了后面作比较
		Node *cur = _root;
		Node *parent = nullptr;
		while (cur){
			//删除结点小于当前结点键值，往左边找
			if (cur->_kv.first > kv.first){
				parent = cur;
				cur = cur->_left;
			}
			//删除结点大于当前结点键值，往右边找
			else if (cur->_kv.first < kv.first){
				parent = cur;
				cur = cur->_right;
			}
			else{
				//找到，四种情况
				if (cur->_left == nullptr&&cur->_right == nullptr){//左右都空
					//为根节点
					if (parent == nullptr){
						delete cur;
						_root = nullptr;
						return true;
					}
					//直接删除
					if (parent->_left == cur){
						
						parent->_left = nullptr;
						
					}
					else{
						
						parent->_right = nullptr;
					}					
					
				}

				if (cur->_left == nullptr&&cur->_right){//左空，右不空
					//为根节点
					if (parent == nullptr){
						_root = cur->_right;
						delete cur;
						return true;
					}
					//父节点指向右边
					if (parent->_left == cur){
						cur->_right->_parent = parent;
						parent->_left = cur->_right;
					}
					else {
						cur->_right->_parent = parent;
						parent->_right = cur->_right;
					}
				}

				if (cur->_left&&cur->_right == nullptr){//右空，左不空
					//根节点
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
				//最后删除
				Node *tail = cur;
				
				while (parent){
					//更新平衡因子
					if (cur->_kv.first < parent->_kv.first){
						parent->_bf++;
					}
					else{
						parent->_bf--;
					}

					//检测平衡因子
					if (parent->_bf == 1 || parent->_bf == -1){//高度没变
						break;
					}
					else if (parent->_bf == 0){//高度降低，据徐更新
						cur = parent;
						parent = parent->_parent;
					}
					else if (parent->_bf == 2 || parent->_bf == -2){
						//cur所在子树高度降低，另外一边相对时升高了，看升高这边
						if (parent->_kv.first > cur->_kv.first){
							cur = parent->_right;
						}
						else{
							cur = parent->_left;
						}

						if (parent->_bf == 2 && cur->_bf == 1){//需要继续往上更新
							
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
						else if (parent->_bf == 2 && cur->_bf == -1){//需要继续往上更新
							
							DoubleRightLeft(parent);
							cur = parent->_parent;
							parent = cur->_parent;
							
						}

						else if (parent->_bf == -2 && cur->_bf == -1){//需要继续往上更新
							
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
						else if (parent->_bf == -2 && cur->_bf == 1){//需要继续往上更新
							
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
		//没找到
		return false;


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