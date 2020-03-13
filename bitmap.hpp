#ifndef JACKREN_BITMAP
#define JACKREN_BITMAP

#include "include.hpp"
#include "utility.hpp"
#include "vector.hpp"

//数据结构：位图（Vector模板对于bool类型的特化）
class BitMap {
private:
	long long _size; //存储的**比特**数
	Vector<unsigned char> _arr; //承载容器Vector
	//第pos比特对应unsigned char数组下标
	inline static long long index(long long pos) {
		return pos >> 3;
	}
	//第pos比特对应unsigned char数组元素的偏移量
	inline static long long shift(long long pos) {
		return pos & 0x7ll;
	}
public:
	//构造函数
	BitMap():_size(0) {}
	//析构函数
	~BitMap() {}
	//预留size比特的空间
	void reserve(long long size) {
		if (_arr.size() < index(size) + 1)_arr.reserve(index(size) * 2 + 1);
		_size = size;
	}
	//返回位图大小
	long long size() {
		return _size;
	}
	//位图清空
	void wipe() {
		for (int i = 0; i < _arr.size(); i++)_arr[i] = 0;
	}
	//获得第pos比特处的值
	bool get(long long pos) {
		return (_arr[index(pos)] >> (7 - shift(pos))) & 1;
	}
	//设置第pos比特处的值为1
	void set(long long pos) {
		_arr[index(pos)] |= 1 << (7 - shift(pos));
	}
	//设置第pos比特处的值为0
	void unset(long long pos) {
		_arr[index(pos)] &= ~(1 << (7 - shift(pos)));
	}
	//在位图末尾附加1比特的值v
	void append(bool v) {
		reserve(_size);
		if (v)set(_size);
		else unset(_size);
		_size++;
	}
	//从filePath以特定格式载入二进制数据到位图中
	bool load(const char* filePath) {
		FILE* f = fopen(filePath, "rb");
		if (!f)return false;
		long long fSize;
		fseek(f, 0, SEEK_END);
		fSize = ftell(f);
		rewind(f);
		fSize -= sizeof(long long);
		fread(&_size, sizeof(long long), 1, f);
		_arr.reserve(fSize);
		for (long long i = 0; i < fSize; i++) {
			unsigned char c;
			fread(&c, 1, 1, f);
			_arr[i] = c;
		}
		fclose(f);
		return true;
	}
	//以特定格式将位图中的二进制数据保存到filePath
	bool pack(const char* filePath) {
		FILE* f = fopen(filePath, "wb");
		if (!f)return false;
		fwrite(&_size, sizeof(long long), 1, f);
		for (long long i = 0; i < index(_size)+1; i++) {
			unsigned char c;
			c = _arr[i];
			fwrite(&c, 1, 1, f);
		}
		fclose(f);
		return true;
	}
};

#endif
