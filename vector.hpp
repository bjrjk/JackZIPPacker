#ifndef JACKREN_VECTOR
#define JACKREN_VECTOR

#include "include.hpp"
#include "algorithm.hpp"



//向量定义
template<typename T>
class Vector {
private:
	T* _arr; //数组指针地址
	int _size; //数组大小
	int _capacity; //数组容量
	//调整数组容量(_capacity)为size
	void _resize(int size) {
		T* newArr = new T[size];
		for (int i = 0; i < min(_size, size); i++)newArr[i] = _arr[i]; //改为深复制
		//std::memcpy(newArr, _arr, sizeof(T) * min(_size, size));
		delete[] _arr;
		_arr = newArr;
		_capacity = size;
	}
public:
	//析构函数
	~Vector() {
		delete[] _arr;
	}
	//默认构造函数
	Vector() {
		_capacity = 10;
		_arr = new T[_capacity];
		_size = 0;
	}
	//复制构造函数
	Vector(const Vector<T>& v) {
		_capacity = v._size;
		_size = v._size;
		_arr = new T[_size];
		for (int i = 0; i < _size; i++)_arr[i] = v._arr[i]; //改为深复制
		//std::memcpy(_arr, v._arr, sizeof(T) * _size);
	}
	//向量大小
	int size() const {
		return _size;
	}
	//缩小内部数组占用空间(shrink)
	void reduce() {
		_resize(_size);
	}
	//数组增加大小到size
	void reserve(int size) {
		if (size <= _capacity) {
			_size = size;
			return;
		}
		_resize(size);
		_size = size;
	}
	//数组元素清空
	void clear() {
		reserve(0);
	}
	//重载=运算符，实现数组的深复制
	Vector& operator = (const Vector& v) {
		delete[] _arr;
		_capacity = v._size;
		_size = v._size;
		_arr = new T[_size];
		for (int i = 0; i < _size; i++)_arr[i] = v._arr[i]; //改为深复制
		//std::memcpy(_arr, v._arr, sizeof(T) * _size);
		return *this;
	}
	//重载[]运算符，能够使访问更方便
	T& operator [](int index) {
		assert(0 <= index && index < _size);
		return _arr[index];
	}
	//在向量最后附加数据value
	void append(const T& value) {
		if (_size >= _capacity)_resize(2 * _capacity);
		_arr[_size] = value;
		_size++;
	}
	//删除向量中最后一个数据
	bool pop() {
		if (_size == 0)return false;
		_size--;
		return true;
	}
	//移除下标index处的元素
	bool remove(int index) {
		if (index < 0 || index >= _size)return false;
		for (int i = index; i < _size; i++)_arr[i] = _arr[i + 1];
		_size--;
		return true;
	}
	//移除数据为value的元素，如first为1，则只移除第一个，否则移除所有
	bool remove(const T& value, bool first) {
		bool flag = false;
		for (int i = 0; i < _size; i++) {
			if (_arr[i] == value) {
				remove(i);
				if (first)return true;
				flag = true;
				i--;
			}
		}
		return flag;
	}
	//输出向量内容
	void print() const {
		for (int i = 0; i < _size; i++)std::cout << _arr[i] << " ";
		std::cout << "\n";
	}
};


#endif