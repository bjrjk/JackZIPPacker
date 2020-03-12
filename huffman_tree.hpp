#ifndef JACKREN_HUFFMAN_TREE
#define JACKREN_HUFFMAN_TREE

#include "include.hpp"
#include "utility.hpp"
#include "vector.hpp"
#include "priority_queue.hpp"

class HuffmanTree {
	typedef unsigned char T;
	typedef KeyValuePair<int, T> KVP;
	typedef BinaryTreeNode<T> nodeT;
	typedef KeyValuePair<int, nodeT*> pqType;
	
private:
	Vector<KVP> _weightData;
	Vector<Vector<T> > _resultData;
	nodeT * _root;
	void destroyHuffmanTree(nodeT* node) {
		if (!node)return;
		destroyHuffmanTree(node->l);
		destroyHuffmanTree(node->r);
		delete node;
	}
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
	HuffmanTree(){
		_root = NULL;
	}
	~HuffmanTree() {
		destroyHuffmanTree(_root);
	}
	void clear() {
		_weightData.clear();
		_resultData.clear();
		destroyHuffmanTree(_root);
		_root = NULL;
	}
	void insert(int weight, const T& data) {
		_weightData.append(KVP(weight, data));
	}
	void build() {
		createTree();
		_resultData.clear();
		_resultData.reserve(256);
		Vector<unsigned char> tmpVec;
		traversalTree(_root, tmpVec);
	}
	const Vector<T>& query(unsigned char index) {
		return _resultData[index];
	}
};
#endif