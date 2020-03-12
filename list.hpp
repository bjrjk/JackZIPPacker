#ifndef JACKREN_LIST
#define JACKREN_LIST

#include "include.hpp"
#include "utility.hpp"
#include "vector.hpp"

//单链表定义
template <typename T>
class List {
private:
	Node<T>* _head; //头节点指针
	//从ptr节点开始递归销毁本身及其之后的链表节点
	void _destory(Node<T>* ptr) {
		if (ptr) {
			_destory(ptr->next);
			delete ptr;
		}
	}
	//获取下标为index处的节点指针
	Node<T>* _getAddrAtPos(int index) {
		//Index start from 0, the index may equal -1 to get the position of the last element
		if (_head->next == NULL)return NULL;
		int cnts = -1;
		Node<T>* ptr = _head;
		while (ptr->next) {
			cnts++;
			ptr = ptr->next;
			if (cnts == index)return ptr;
		}
		if (index == -1)return ptr;
		return NULL;
	}
	//在节点ptr后插入一数据域为data的新节点
	Node<T>* _insert(Node<T>* ptr, const T& data) {
		Node<T>* newNode = new Node<T>(data, ptr->next);
		return ptr->next = newNode;
	}
public:
	//构造函数
	List() {
		_head = new Node<T>;
	}
	//复制构造函数
	List(const List& l) {
		_head = new Node<T>;
		Node<T>* oldPtr = l._head;
		Node<T>* newPtr = _head;
		while (oldPtr->next) {
			newPtr->next = new Node<T>(oldPtr->next->data);
			newPtr = newPtr->next;
			oldPtr = oldPtr->next;
		}
	}
	//析构函数
	~List() {
		_destory(_head);
	}
	//清空单链表
	void clear() {
		if (_head->next)_destory(_head->next);
	}
	//单链表判空
	bool empty() {
		return _head->next == NULL;
	}
	//单链表大小
	int size() {
		int cnts = 0;
		for (Node<T>* ptr = _head; ptr->next; ptr = ptr->next, cnts++);
		return cnts;
	}
	//在单链表最后附加一数据域为value的新节点
	void append(const T& value) {
		Node<T>* ptr = _getAddrAtPos(-1);
		if (ptr)_insert(ptr, value);
		else _insert(_head, value);
	}
	//在单链表最后按向量arr中内容顺序依次附加新节点
	void extend(const Vector<T>& arr) {
		for (int i = 0; i < arr.size(); i++) {
			append(arr[i]);
		}
	}
	//在下标为index处插入一数据为value的链表节点
	bool insert(int index, const T& value) {
		// Index greater or equal to 0
		if (index == 0) {
			_insert(_head, value);
			return true;
		}
		Node<T>* ptr = _getAddrAtPos(index - 1);
		if (!ptr)return false;
		_insert(ptr, value);
		return true;
	}
	//获得单链表头节点
	Node<T>* getHead() {
		return _head;
	}
	//输出链表内容
	void print() {
		Node<T>* ptr = _head;
		while (ptr->next) {
			std::cout << ptr->next->data << " ";
			ptr = ptr->next;
		}
		std::cout << "\n";
	}
};


#endif
