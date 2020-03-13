#ifndef JACKREN_ZIP_UNPACK
#define JACKREN_ZIP_UNPACK

#include "include.hpp"
#include "utility.hpp"
#include "vector.hpp"
#include "bitmap.hpp"
#include "trie_tree.hpp"

//jzpk解压缩类
class ZipUnPacker {
private:
	Trie trie; //利用字典树进行Huffman编码的解压
	char* _zippedFilePath; //压缩文件路径
	//从位图bm中获取dataSize比特的二进制串存入vec中
	inline long long recvData(BitMap& bm, long long& ptr, Vector<unsigned char>& vec, long long dataSize) {
		vec.clear();
		int i;
		for (i = 0; i < dataSize && ptr < bm.size(); i++, ptr++) vec.append(bm.get(ptr));
		return i;
	}
	//从位图bm中获取一字节的二进制串放入unsigned char中并返回
	inline unsigned char recvUCData(BitMap& bm, long long& ptr) {
		int i;
		unsigned char c = 0;
		for (i = 0; i < 8&&ptr<bm.size(); i++,ptr++) {
			c <<= 1;
			c |= bm.get(ptr);
		}
		assert(i == 8);
		return c;
	}
public:
	//构造函数
	ZipUnPacker(const char* zippedFilePath) {
		int len = std::strlen(zippedFilePath);
		_zippedFilePath = new char[len + 5];
		std::strcpy(_zippedFilePath, zippedFilePath);
	}
	//析构函数
	~ZipUnPacker() {
		if (_zippedFilePath)delete[] _zippedFilePath;
	}
	//解压到filePath路径
	bool unpack(const char* filePath) {
		BitMap bm;
		if (!bm.load(_zippedFilePath))return false;
		long long ptr = 0;
		unsigned char c;
		for (int i = 0; i < 256; i++) {
			c = recvUCData(bm, ptr);
			Vector<unsigned char> vec;
			recvData(bm, ptr, vec, c);
			trie.insert(vec, i);
		}
		FILE* f = fopen(filePath, "wb");
		if (!f)return false;
		while (ptr<bm.size()) {
			c = trie.bitmap_query(bm, ptr);
			fwrite(&c, 1, 1, f);
			ptr++;
		}
		fclose(f);
		return true;
	}
};


#endif


