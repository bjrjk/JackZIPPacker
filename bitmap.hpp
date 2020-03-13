#ifndef JACKREN_BITMAP
#define JACKREN_BITMAP

#include "include.hpp"
#include "utility.hpp"
#include "vector.hpp"

//���ݽṹ��λͼ��Vectorģ�����bool���͵��ػ���
class BitMap {
private:
	long long _size; //�洢��**����**��
	Vector<unsigned char> _arr; //��������Vector
	//��pos���ض�Ӧunsigned char�����±�
	inline static long long index(long long pos) {
		return pos >> 3;
	}
	//��pos���ض�Ӧunsigned char����Ԫ�ص�ƫ����
	inline static long long shift(long long pos) {
		return pos & 0x7ll;
	}
public:
	//���캯��
	BitMap():_size(0) {}
	//��������
	~BitMap() {}
	//Ԥ��size���صĿռ�
	void reserve(long long size) {
		if (_arr.size() < index(size) + 1)_arr.reserve(index(size) * 2 + 1);
		_size = size;
	}
	//����λͼ��С
	long long size() {
		return _size;
	}
	//λͼ���
	void wipe() {
		for (int i = 0; i < _arr.size(); i++)_arr[i] = 0;
	}
	//��õ�pos���ش���ֵ
	bool get(long long pos) {
		return (_arr[index(pos)] >> (7 - shift(pos))) & 1;
	}
	//���õ�pos���ش���ֵΪ1
	void set(long long pos) {
		_arr[index(pos)] |= 1 << (7 - shift(pos));
	}
	//���õ�pos���ش���ֵΪ0
	void unset(long long pos) {
		_arr[index(pos)] &= ~(1 << (7 - shift(pos)));
	}
	//��λͼĩβ����1���ص�ֵv
	void append(bool v) {
		reserve(_size);
		if (v)set(_size);
		else unset(_size);
		_size++;
	}
	//��filePath���ض���ʽ������������ݵ�λͼ��
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
	//���ض���ʽ��λͼ�еĶ��������ݱ��浽filePath
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
