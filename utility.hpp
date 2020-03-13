#ifndef NULL
#define NULL 0
#endif

#ifndef JACKREN_UTILITY
#define JACKREN_UTILITY

//单链表节点定义
template<typename T>
struct Node {
	T data; //数据域
	Node* next; //指针域
	//默认构造函数
	Node() :next(NULL) {}
	//构造函数重载
	Node(const T& data) :data(data), next(NULL) {}
	//构造函数重载
	Node(const T& data, Node<T>* next) :data(data), next(next) {}
};

//二叉树节点定义
template<typename T>
struct BinaryTreeNode {
	T data; //数据域
	BinaryTreeNode* l; //左孩子
	BinaryTreeNode* r; //右孩子
	//默认构造函数
	BinaryTreeNode() :l(NULL),r(NULL) {}
	//构造函数重载
	BinaryTreeNode(const T& data) :data(data), l(NULL), r(NULL) {}
	//构造函数重载
	BinaryTreeNode(BinaryTreeNode<T>* l, BinaryTreeNode<T>* r) :l(l), r(r) {}
	//构造函数重载
	BinaryTreeNode(const T& data, BinaryTreeNode<T>* l, BinaryTreeNode<T>* r) :data(data), l(l), r(r) {}
};

//键值对定义
template<typename KeyType, typename ValueType>
struct KeyValuePair {
	KeyType key; //键
	ValueType value; //值
	//默认构造函数
	KeyValuePair() {}
	//构造函数重载
	KeyValuePair(KeyType Key) :key(Key) {}
	//构造函数重载
	KeyValuePair(KeyType Key, ValueType Value) :key(Key), value(Value) {}
	//运算符<重载
	bool operator < (const KeyValuePair& v2) const {
		return key < v2.key;
	}
};
#endif
