#ifndef NULL
#define NULL 0
#endif

#ifndef JACKREN_UTILITY
#define JACKREN_UTILITY

//������ڵ㶨��
template<typename T>
struct Node {
	T data; //������
	Node* next; //ָ����
	//Ĭ�Ϲ��캯��
	Node() :next(NULL) {}
	//���캯������
	Node(const T& data) :data(data), next(NULL) {}
	//���캯������
	Node(const T& data, Node<T>* next) :data(data), next(next) {}
};

//�������ڵ㶨��
template<typename T>
struct BinaryTreeNode {
	T data; //������
	BinaryTreeNode* l; //����
	BinaryTreeNode* r; //�Һ���
	//Ĭ�Ϲ��캯��
	BinaryTreeNode() :l(NULL),r(NULL) {}
	//���캯������
	BinaryTreeNode(const T& data) :data(data), l(NULL), r(NULL) {}
	//���캯������
	BinaryTreeNode(BinaryTreeNode<T>* l, BinaryTreeNode<T>* r) :l(l), r(r) {}
	//���캯������
	BinaryTreeNode(const T& data, BinaryTreeNode<T>* l, BinaryTreeNode<T>* r) :data(data), l(l), r(r) {}
};

//��ֵ�Զ���
template<typename KeyType, typename ValueType>
struct KeyValuePair {
	KeyType key;
	ValueType value;
	KeyValuePair() {}
	KeyValuePair(KeyType Key) :key(Key) {}
	KeyValuePair(KeyType Key, ValueType Value) :key(Key), value(Value) {}
	bool operator < (const KeyValuePair& v2) const {
		return key < v2.key;
	}
};
#endif
