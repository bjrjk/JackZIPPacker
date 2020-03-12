#ifndef JACKREN_VECTOR
#define JACKREN_VECTOR

#include "include.hpp"
#include "algorithm.hpp"



//��������
template<typename T>
class Vector {
private:
	T* _arr; //����ָ���ַ
	int _size; //�����С
	int _capacity; //��������
	//������������(_capacity)Ϊsize
	void _resize(int size) {
		T* newArr = new T[size];
		for (int i = 0; i < min(_size, size); i++)newArr[i] = _arr[i]; //��Ϊ���
		//std::memcpy(newArr, _arr, sizeof(T) * min(_size, size));
		delete[] _arr;
		_arr = newArr;
		_capacity = size;
	}
public:
	//��������
	~Vector() {
		delete[] _arr;
	}
	//Ĭ�Ϲ��캯��
	Vector() {
		_capacity = 10;
		_arr = new T[_capacity];
		_size = 0;
	}
	//���ƹ��캯��
	Vector(const Vector<T>& v) {
		_capacity = v._size;
		_size = v._size;
		_arr = new T[_size];
		for (int i = 0; i < _size; i++)_arr[i] = v._arr[i]; //��Ϊ���
		//std::memcpy(_arr, v._arr, sizeof(T) * _size);
	}
	//������С
	int size() const {
		return _size;
	}
	//��С�ڲ�����ռ�ÿռ�(shrink)
	void reduce() {
		_resize(_size);
	}
	//�������Ӵ�С��size
	void reserve(int size) {
		if (size <= _capacity) {
			_size = size;
			return;
		}
		_resize(size);
		_size = size;
	}
	//����Ԫ�����
	void clear() {
		reserve(0);
	}
	//����=�������ʵ����������
	Vector& operator = (const Vector& v) {
		delete[] _arr;
		_capacity = v._size;
		_size = v._size;
		_arr = new T[_size];
		for (int i = 0; i < _size; i++)_arr[i] = v._arr[i]; //��Ϊ���
		//std::memcpy(_arr, v._arr, sizeof(T) * _size);
		return *this;
	}
	//����[]��������ܹ�ʹ���ʸ�����
	T& operator [](int index) {
		assert(0 <= index && index < _size);
		return _arr[index];
	}
	//��������󸽼�����value
	void append(const T& value) {
		if (_size >= _capacity)_resize(2 * _capacity);
		_arr[_size] = value;
		_size++;
	}
	//ɾ�����������һ������
	bool pop() {
		if (_size == 0)return false;
		_size--;
		return true;
	}
	//�Ƴ��±�index����Ԫ��
	bool remove(int index) {
		if (index < 0 || index >= _size)return false;
		for (int i = index; i < _size; i++)_arr[i] = _arr[i + 1];
		_size--;
		return true;
	}
	//�Ƴ�����Ϊvalue��Ԫ�أ���firstΪ1����ֻ�Ƴ���һ���������Ƴ�����
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
	//�����������
	void print() const {
		for (int i = 0; i < _size; i++)std::cout << _arr[i] << " ";
		std::cout << "\n";
	}
};


#endif