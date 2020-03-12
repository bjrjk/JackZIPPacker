#ifndef JACKREN_LIST
#define JACKREN_LIST

#include "include.hpp"
#include "utility.hpp"
#include "vector.hpp"

//��������
template <typename T>
class List {
private:
	Node<T>* _head; //ͷ�ڵ�ָ��
	//��ptr�ڵ㿪ʼ�ݹ����ٱ�����֮�������ڵ�
	void _destory(Node<T>* ptr) {
		if (ptr) {
			_destory(ptr->next);
			delete ptr;
		}
	}
	//��ȡ�±�Ϊindex���Ľڵ�ָ��
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
	//�ڽڵ�ptr�����һ������Ϊdata���½ڵ�
	Node<T>* _insert(Node<T>* ptr, const T& data) {
		Node<T>* newNode = new Node<T>(data, ptr->next);
		return ptr->next = newNode;
	}
public:
	//���캯��
	List() {
		_head = new Node<T>;
	}
	//���ƹ��캯��
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
	//��������
	~List() {
		_destory(_head);
	}
	//��յ�����
	void clear() {
		if (_head->next)_destory(_head->next);
	}
	//�������п�
	bool empty() {
		return _head->next == NULL;
	}
	//�������С
	int size() {
		int cnts = 0;
		for (Node<T>* ptr = _head; ptr->next; ptr = ptr->next, cnts++);
		return cnts;
	}
	//�ڵ�������󸽼�һ������Ϊvalue���½ڵ�
	void append(const T& value) {
		Node<T>* ptr = _getAddrAtPos(-1);
		if (ptr)_insert(ptr, value);
		else _insert(_head, value);
	}
	//�ڵ������������arr������˳�����θ����½ڵ�
	void extend(const Vector<T>& arr) {
		for (int i = 0; i < arr.size(); i++) {
			append(arr[i]);
		}
	}
	//���±�Ϊindex������һ����Ϊvalue������ڵ�
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
	//��õ�����ͷ�ڵ�
	Node<T>* getHead() {
		return _head;
	}
	//�����������
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
