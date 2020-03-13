#ifndef JACKREN_HUFFMAN_TREE
#define JACKREN_HUFFMAN_TREE

#include "include.hpp"
#include "utility.hpp"
#include "vector.hpp"
#include "priority_queue.hpp"

//Huffman Tree（哈夫曼树）
class HuffmanTree {
	typedef unsigned char T;
	typedef KeyValuePair<int, T> KVP;
	typedef BinaryTreeNode<T> nodeT;
	typedef KeyValuePair<int, nodeT*> pqType;
	
private:
	Vector<KVP> _weightData;  //Huffman Tree输入的权重数据
	Vector<Vector<T> > _resultData;		//Huffman Tree生成的压缩编码存储区
	nodeT * _root;		//Huffman树树根
	//Huffman树析构
	void destroyHuffmanTree(nodeT* node) {
		if (!node)return;
		destroyHuffmanTree(node->l);
		destroyHuffmanTree(node->r);
		delete node;
	}
	//Huffman建树
	void createTree() {
		PriorityQueue<pqType> pq;
		for (int i = 0; i < _weightData.size(); i++) {
			nodeT* leafNode = new nodeT(_weightData[i].value);
			pqType pqNode(_weightData[i].key, leafNode);
			pq.push(pqNode);
		}
		while (pq.size() > 1) {
			pqType nodePtr1 = pq.top();	pq.pop();
			pqType nodePtr2 = pq.top();	pq.pop();
			nodeT* newNode = new nodeT(nodePtr1.value, nodePtr2.value);
			pqType pqNode(nodePtr1.key + nodePtr2.key, newNode);
			pq.push(pqNode);
		}
		_root = pq.top().value;
	}
	//Huffman树遍历
	void traversalTree(nodeT* node,Vector<unsigned char>& storage) {
		if (!node)return; //isNULL
		if (!node->l && !node->r) {  //isLeaf
			_resultData[node->data] = storage;
			return;
		}
		storage.append(0);
		traversalTree(node->l, storage);
		storage.pop();
		storage.append(1);
		traversalTree(node->r, storage);
		storage.pop();
	}
	
public:
	//构造函数
	HuffmanTree(){
		_root = NULL;
	}
	//析构函数
	~HuffmanTree() {
		destroyHuffmanTree(_root);
	}
	//清理操作
	void clear() {
		_weightData.clear();
		_resultData.clear();
		destroyHuffmanTree(_root);
		_root = NULL;
	}
	//向Huffman树中插入权值为weight的data
	void insert(int weight, const T& data) {
		_weightData.append(KVP(weight, data));
	}
	//Huffman树建树、遍历、生成数据对应的压缩信息串
	void build() {
		createTree();
		_resultData.clear();
		_resultData.reserve(256);
		Vector<unsigned char> tmpVec;
		traversalTree(_root, tmpVec);
	}
	//Huffman树查询数据为index所对应的压缩信息串
	const Vector<T>& query(unsigned char index) {
		return _resultData[index];
	}
};
#endif