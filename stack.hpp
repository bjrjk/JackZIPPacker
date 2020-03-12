#ifndef JACKREN_STACK
#define JACKREN_STACK

#include "include.hpp"
#include "vector.hpp"


//栈定义
template<typename T>
class Stack {
private:
	Vector<T> arr; //利用向量作为内部容器承载栈
public:
	//默认构造函数
	Stack(){}
	//复制构造函数
	Stack(const Stack& S) {
		arr = S.arr;
	}
	//重载=运算符，对栈进行浅复制
	Stack& operator = (const Stack& S) {
		arr = S.arr;
		return *this;
	}
	//栈判空
	bool empty() {
		return arr.size() == 0;
	}
	//向栈中压入元素
	void push(const T& value) {
		arr.append(value);
	}
	//元素退栈
	bool pop() {
		return arr.pop();
	}
	//获取栈顶
	T& top() {
		assert(!empty());
		return arr[arr.size() - 1];
	}
};

#endif