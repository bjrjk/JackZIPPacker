#ifndef JACKREN_STACK
#define JACKREN_STACK

#include "include.hpp"
#include "vector.hpp"


//ջ����
template<typename T>
class Stack {
private:
	Vector<T> arr; //����������Ϊ�ڲ���������ջ
public:
	//Ĭ�Ϲ��캯��
	Stack(){}
	//���ƹ��캯��
	Stack(const Stack& S) {
		arr = S.arr;
	}
	//����=���������ջ����ǳ����
	Stack& operator = (const Stack& S) {
		arr = S.arr;
		return *this;
	}
	//ջ�п�
	bool empty() {
		return arr.size() == 0;
	}
	//��ջ��ѹ��Ԫ��
	void push(const T& value) {
		arr.append(value);
	}
	//Ԫ����ջ
	bool pop() {
		return arr.pop();
	}
	//��ȡջ��
	T& top() {
		assert(!empty());
		return arr[arr.size() - 1];
	}
};

#endif